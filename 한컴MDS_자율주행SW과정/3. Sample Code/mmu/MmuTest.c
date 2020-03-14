
#include "2410addr.h"

//===================================================================
void Main(void)
{
	int i, j;
	MMU_Init();
	
	
	// LED Port Initialization
	Port_Init();

	// Dispaly from 0 to 15
	while(1){
	for (i=0; i<16; i++) {
		Led_Display(i);
		for (j=0; j<300000; j++);
	}
	}
	

}
//===================================================================

