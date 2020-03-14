#include "2440addr.h"
#include "option.h"
#include "macro.h"

void Timer0_Init(void);
void Timer0_Delay(unsigned int msec);

// Timer0 : 특정 기준 시간을 측정하는 용도로 사용 

void Timer0_Init(void)
{
	// 현재 Timer out pin은 스위치와 연결 되어 있으므로 별도 설정 않음

	// Timer0 주파수 설정 (현재 PCLK는 49.95625MHz)
	// 1클럭 기준 목표주파수 = PCLK/(분주비)
	// 이때, 분주비의 최대값이 256*16 = 4096이므로 
	// 최소 timer time tick은 4096/49956250초 이하 시간이다
	// 즉, 약 82usec 정도가 된다
	
	// Timer0 : 50usec unit clock으로 생성하고자 하면 = (1/50)MHz = 20KHz)
	// 이 경우 16bit timer이므로 50usec ~ 65536*50(= 3276800usec) 가능 (약 3.2초)
	
	// 목표치 50usec => 20000hz = 49956250 / (N) 이 성립된다
	// 따라서 N = (49956250/20000) = 2497.8125
	// 2497.8125은 Prescler 최대값 256를 초과함
	// 따라서 뒷단에서 MUX로 재차 분주를 하여 사용하여야 함
	// 2497.8125을 MUX가 2,4,8,16 분주가 가능하나 256을 초과하지 않는 값은 16뿐이다
	// 따라서 MUX는 1/16, PRESCLER는 int(2497.8125/16) - 1이므로 155이다
	
	// 최종 결정된 정확한 tick 주파수는 49956250/(156*16) = 20014.5
	// 따라서 tick time은 약 49.964usec이다 
	
	Macro_Erase_Area(rTCFG0, 0xff, 0);
	Macro_Write_Area(rTCFG0, 155, 0);

	Macro_Erase_Area(rTCFG1, 0xf, 0);
	Macro_Write_Area(rTCFG1, 0x3, 0);
	
	// stop, auto reload = NO, 
	Macro_Erase_Area(rTCON, 0x1f, 0);
	
	// DMA mode = no
	Macro_Erase_Area(rTCFG1, 0xf, 20);
}

void Timer0_Delay(unsigned int msec)
{
	// 1msec = 1000usec이므로 단위를 usec로 통일한다
	// 즉 원하는 msec는 msec * 1000 usec 이다
	// 따라서 카운터 설정치는 msec * 1000 / 50 = msec * 20
	// 이때, 원하는 시간이 3.2초(65535) 보다 크면? For Loop 사용
	
	unsigned int temp, i, j;
	
	temp = (msec * 20);
	
	for(i=0; i < (temp / 0xffff); i++)
	{
		rTCNTB0 = 0xffff;
		// Manual update & stop
		Macro_Erase_Area(rTCON, 0x3, 0);
		Macro_Write_Area(rTCON, 0x2, 0);
		// start and don't manual update
		Macro_Erase_Area(rTCON, 0x3, 0);
		Macro_Write_Area(rTCON, 0x1, 0);

		#if 1
		for(j=0; j<0xff;j++);
		#endif
		
		// wait until timer expierd (= 0)
		while(rTCNTO0 != 0);
	}
	
	rTCNTB0 = (temp % 0xffff);
	// Manual update & stop
	Macro_Erase_Area(rTCON, 0x3, 0);
	Macro_Write_Area(rTCON, 0x2, 0);
	// start and don't manual update
	Macro_Erase_Area(rTCON, 0x3, 0);
	Macro_Write_Area(rTCON, 0x1, 0);
	
	#if 1
	for(j=0; j<0xff;j++);
	#endif
	
	// wait until timer expierd (= 0)
	while(rTCNTO0 != 0);
}
