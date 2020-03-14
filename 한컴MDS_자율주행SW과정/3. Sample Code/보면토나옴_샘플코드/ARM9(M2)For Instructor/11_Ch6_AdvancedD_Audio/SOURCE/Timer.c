#include "2440addr.h"
#include "option.h"
#include "macro.h"

void Timer0_Init(void);
void Timer0_Delay(unsigned int msec);

// Timer0 : Ư�� ���� �ð��� �����ϴ� �뵵�� ��� 

void Timer0_Init(void)
{
	// ���� Timer out pin�� ����ġ�� ���� �Ǿ� �����Ƿ� ���� ���� ����

	// Timer0 ���ļ� ���� (���� PCLK�� 49.95625MHz)
	// 1Ŭ�� ���� ��ǥ���ļ� = PCLK/(���ֺ�)
	// �̶�, ���ֺ��� �ִ밪�� 256*16 = 4096�̹Ƿ� 
	// �ּ� timer time tick�� 4096/49956250�� ���� �ð��̴�
	// ��, �� 82usec ������ �ȴ�
	
	// Timer0 : 50usec unit clock���� �����ϰ��� �ϸ� = (1/50)MHz = 20KHz)
	// �� ��� 16bit timer�̹Ƿ� 50usec ~ 65536*50(= 3276800usec) ���� (�� 3.2��)
	
	// ��ǥġ 50usec => 20000hz = 49956250 / (N) �� �����ȴ�
	// ���� N = (49956250/20000) = 2497.8125
	// 2497.8125�� Prescler �ִ밪 256�� �ʰ���
	// ���� �޴ܿ��� MUX�� ���� ���ָ� �Ͽ� ����Ͽ��� ��
	// 2497.8125�� MUX�� 2,4,8,16 ���ְ� �����ϳ� 256�� �ʰ����� �ʴ� ���� 16���̴�
	// ���� MUX�� 1/16, PRESCLER�� int(2497.8125/16) - 1�̹Ƿ� 155�̴�
	
	// ���� ������ ��Ȯ�� tick ���ļ��� 49956250/(156*16) = 20014.5
	// ���� tick time�� �� 49.964usec�̴� 
	
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
	// 1msec = 1000usec�̹Ƿ� ������ usec�� �����Ѵ�
	// �� ���ϴ� msec�� msec * 1000 usec �̴�
	// ���� ī���� ����ġ�� msec * 1000 / 50 = msec * 20
	// �̶�, ���ϴ� �ð��� 3.2��(65535) ���� ũ��? For Loop ���
	
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
