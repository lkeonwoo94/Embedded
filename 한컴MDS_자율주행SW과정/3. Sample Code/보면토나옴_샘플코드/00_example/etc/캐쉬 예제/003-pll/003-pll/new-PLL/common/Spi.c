/*============================================================
	File Name: SPI.c
	Description: S3C2440A SPI controller Function Test
   	Version: 0.1 

   	History:
      0.1: 2003. 07. 06, Programming Start.
      0.2: 2004. 05. 14, added keyboard test codes 
      	         		  
=============================================================*/

#include <string.h>
#include "2440addr.h"
#include "2440lib.h"
#include "spi.h"
#include "def.h"

#define spi_count 0x80
#define SPI_BUFFER _NONCACHE_STARTADDRESS

void __irq Spi_Int(void);
void __irq Dma1Tx_Int(void);
void __irq Dma1Rx_Int(void);

void Test_Spi1_MS_poll(void); // added by junon

volatile char *spiTxStr,*spiRxStr;
volatile int endSpiTx;
volatile int tx_dma1Done;
volatile int rx_dma1Done;
unsigned int spi_rGPECON,spi_rGPEDAT,spi_rGPEUP;
unsigned int spi_rGPGCON,spi_rGPGDAT,spi_rGPGUP;
unsigned int spi_rGPDCON,spi_rGPDDAT,spi_rGPDUP;

/////////////////////// 2004.05.14 added by junon
#define ONEBIT    0x1

int	putcToKBCTL(U8 c);
void getsFromKBCTL(U8 *m, int cnt);
void Test_Spikbd_IO(void);
void Test_Spikbd_keyscan(void);

unsigned int spikbd_rGPBCON,spikbd_rGPBDAT,spikbd_rGPBUP;
unsigned int spikbd_rGPDCON,spikbd_rGPDDAT,spikbd_rGPDUP;
unsigned int spikbd_rGPFCON,spikbd_rGPFDAT,spikbd_rGPFUP;
unsigned int spikbd_rGPGCON,spikbd_rGPGDAT,spikbd_rGPGUP;
///////////////////////


/****************************************************************
 *	             MBA24402400 SPI configuration
 *  GPG2=nSS0, GPE11=SPIMISO0, GPE12=SPIMOSI0, GPE13=SPICLK0 
 *  GPG3=nSS1, GPG5 =SPIMISO1, GPG6 =SPIMOSI1, GPG7 =SPICLK1
 *  SPI1 is tested by OS(WINCE). So, Only SPI0 is tested by this code
 ****************************************************************/

void * func_spi_test[][2]=
{	
//	"0123456789012345" max 15자 로한정하여 comment하세요.
//SPI
	(void *)Test_Spi_MS_int, 		"SPI0 RxTx Int  ",
	(void *)Test_Spi_MS_poll, 		"SPI0 RxTx POLL ",
	(void *)Test_Spi_M_Int, 		"SPI0 M Rx INT  ",
	(void *)Test_Spi_S_Int, 		"SPI0 S Tx INT  ",
	(void *)Test_Spi_M_Tx_DMA1, 	"SPI0 M Tx DMA1 ",
	(void *)Test_Spi_S_Rx_DMA1, 	"SPI0 S Rx DMA1 ",
	(void *)Test_Spi_M_Rx_DMA1, 	"SPI0 M Rx DMA1 ",
	(void *)Test_Spi_S_Tx_DMA1, 	"SPI0 S Tx DMA1 ",
//	(void *)Test_Spi1_MS_poll, 		"SPI1 RxTx POLL ",	
//	(void *)Test_Spikbd_IO,			"SPI1 keybd IO  ",
//		(void *)Test_Spikbd_keyscan,	"SPI1 keybd scan",
	0,0
};

void Spi_Test(void)
{
	int i, sel;
	
	while(1)
	{
		i=0;
		Uart_Printf("+------------------[ SPI test ]-------------------+\n");
		while(1)
		{   //display menu
			Uart_Printf("| %2d:%s\n",i+1,func_spi_test[i][1]);
			i++;
			if((int)(func_spi_test[i][0])==0)	break;
		}
		Uart_Printf("| %2d:Previous menu\n", i+1);
		Uart_Printf("+-------------------------------------------------+\n");
		Uart_Printf(" Select the number to test : ");
		sel = Uart_GetIntNum();
		sel--;
		Uart_Printf("+-------------------------------------------------+\n\n\n");
		if(sel == i){
			return;
		}if(sel>=0 && (sel<((sizeof(func_spi_test)-1)/8)) ){
			( (void (*)(void)) (func_spi_test[sel][0]) )();
		}else{
			Uart_Printf("Wrong number seleted.. Try again!!\n\n\n");
		}
	}
}

void SPI_Port_Init(int MASorSLV)
{
	// SPI channel 0 setting
    spi_rGPECON=rGPECON;
    spi_rGPEDAT=rGPEDAT;
    spi_rGPEUP=rGPEUP;
    rGPECON=((rGPECON&0xf03fffff)|0xa800000); // using SPI 0
	rGPEUP = (rGPEUP & ~(7<<11)) | (1<<13);
    spi_rGPGCON=rGPGCON;
    spi_rGPGDAT=rGPGDAT;
    spi_rGPGUP=rGPGUP;
    if(MASorSLV==1)
    {
        rGPGCON=((rGPGCON&0xffffffcf)|0x10); // Master(GPIO_Output)
        rGPGDAT|=0x4; // Activate nSS 
    }
    else
    	rGPGCON=((rGPGCON&0xffffffcf)|0x30); // Slave(nSS)
    rGPGUP|=0x4;
/*
	// SPI channel 1-1 setting --> Key board
	rGPGCON=(rGPGCON&0xffff033f)|(3<<6)|(3<<10)|(3<<12)|(1<<14); // MISO1, MOSI1, CLK1, Master
	rGPGDAT|=0x8;
	rGPGUP=(rGPGUP&~(7<<5))|(1<<7);
*/
	// SPI channel 1-2 setting --> VD16~18
	spi_rGPDCON=rGPDCON;
	spi_rGPDDAT=rGPDDAT;
	spi_rGPDUP=rGPDUP;
	rGPDCON=(rGPDCON&0xcfc0ffff)|(3<<16)|(3<<18)|(3<<20)|(1<<28); // MISO1, MOSI1, CLK1, Master
	rGPDDAT|=1<<14;
	rGPDUP=(rGPDUP&~(7<<8))|(1<<10);
}

void SPI_Port_Return(void)
{
    rGPECON=spi_rGPECON;
    rGPEDAT=spi_rGPEDAT;
    rGPEUP=spi_rGPEUP;

    rGPGCON=spi_rGPGCON;
    rGPGDAT=spi_rGPGDAT;
    rGPGUP=spi_rGPGUP;

    rGPDCON=spi_rGPDCON;
    rGPDDAT=spi_rGPDDAT;
    rGPDUP=spi_rGPDUP;
}


void Test_Spi1_MS_poll(void)
{
    int i;
    char *txStr,*rxStr;
    SPI_Port_Init(1); 
    Uart_Printf("[SPI Polling Tx/Rx Test]\n");
    Uart_Printf("Connect SPIMOSI1 into SPIMISO1.\n");
    endSpiTx=0;
    spiTxStr="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 - SPI1";
    spiRxStr=(char *) SPI_BUFFER;
    txStr=(char *)spiTxStr;
    rxStr=(char *)spiRxStr;

    rSPPRE1=0x0;	//if PCLK=50Mhz,SPICLK=25Mhz
    rSPCON1=(0<<5)|(1<<4)|(1<<3)|(1<<2)|(0<<1)|(0<<0);//Polling,en-SCK,master,low,A,normal
    rSPPIN1=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release
    
    while(endSpiTx==0)
    {
		if(rSPSTA1&0x1)   //Check Tx ready state    
		{
	    	if(*spiTxStr!='\0')
				rSPTDAT1=*spiTxStr++;
	    	else
				endSpiTx=1;
	    	while(!(rSPSTA1&0x1));   //Check Rx ready state 
			*spiRxStr++=rSPRDAT1;
		}
    }

    rSPCON1&=~(1<<4);//dis-SCK
    *(spiRxStr-1)='\0';//remove last dummy data & attach End of String(Null)
    
    Uart_Printf("Tx Strings:%s\n",txStr);
    Uart_Printf("Rx Strings:%s :",rxStr);
    
    if(strcmp(rxStr,txStr)==0)
        Uart_Printf("O.K.\n");
    else 
        Uart_Printf("ERROR!!!\n");
    SPI_Port_Return();
}


void Test_Spi_MS_int(void)
{
    char *txStr,*rxStr;
    SPI_Port_Init(1); 
    Uart_Printf("[SPI0 Interrupt Tx/Rx Test]\n");
    Uart_Printf("Connect SPIMOSI0 into SPIMISO0, and then press any key\n\n");
	Uart_Getch();

    pISR_SPI0=(unsigned)Spi_Int;
    endSpiTx=0;
    spiTxStr="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    spiRxStr=(char *) SPI_BUFFER;
    txStr=(char *)spiTxStr;
    rxStr=(char *)spiRxStr;
    rSPPRE0=0x0;	//if PCLK=50Mhz,SPICLK=25Mhz
    rSPCON0=(1<<5)|(1<<4)|(1<<3)|(1<<2)|(0<<1)|0;//int,en-SCK,master,low,A,normal
    rSPPIN0=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release
    rINTMSK=~(BIT_SPI0);

    while(endSpiTx==0);

	rSPCON0&=~((1<<5)|(1<<4));//poll, dis-SCK
	Uart_Printf("Current Rx address = 0x%x\n",spiRxStr);
    *spiRxStr='\0';//attach End of String(Null)
	
    Uart_Printf("Tx Strings:%s\n",txStr);
    Uart_Printf("Rx Strings:%s :",rxStr+1);//remove first dummy data
    if(strcmp(rxStr+1,txStr)==0)
        Uart_Printf("O.K.\n\n\n");
    else 
        Uart_Printf("ERROR!!!\n\n\n");
    SPI_Port_Return();
}


void __irq Spi_Int(void)
{
    unsigned int status;
		
	rINTMSK|=BIT_SPI0;
    ClearPending(BIT_SPI0); 
    status=rSPSTA0;
    if(rSPSTA0&0x6) 
    	Uart_Printf("Data Collision or Multi Master Error(0x%x)!!!\n", status);
    while(!(rSPSTA0&0x1));   //Check ready state
    *spiRxStr++=rSPRDAT0;    //First Rx data is garbage data
//	Uart_Printf("Current Rx address = 0x%x\n",spiRxStr);
    
    if(*spiTxStr!='\0') 
    {
    	rSPTDAT0=*spiTxStr++;
		rINTMSK&=~BIT_SPI0;
    }
    else
    {
	    endSpiTx=1;
    }
}

void Test_Spi_MS_poll(void)
{
    int i;
    char *txStr,*rxStr;
    SPI_Port_Init(1); 
    Uart_Printf("[SPI Polling Tx/Rx Test]\n");
    Uart_Printf("Connect SPIMOSI0 into SPIMISO0, and then press any key\n\n");
	Uart_Getch();
	
    endSpiTx=0;
    spiTxStr="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    spiRxStr=(char *) SPI_BUFFER;
    txStr=(char *)spiTxStr;
    rxStr=(char *)spiRxStr;

    rSPPRE0=0x0;	//if PCLK=50Mhz,SPICLK=25Mhz
    rSPCON0=(0<<5)|(1<<4)|(1<<3)|(1<<2)|(0<<1)|(0<<0);//Polling,en-SCK,master,low,A,normal
    rSPPIN0=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release
    
    while(endSpiTx==0)
    {
		if(rSPSTA0&0x1)   //Check Tx ready state    
		{
	    	if(*spiTxStr!='\0')
				rSPTDAT0=*spiTxStr++;
	    	else
				endSpiTx=1;
	    	while(!(rSPSTA0&0x1));   //Check Rx ready state 
			*spiRxStr++=rSPRDAT0;
		}
    }

    rSPCON0&=~(1<<4);//dis-SCK
    *(spiRxStr-1)='\0';//remove last dummy data & attach End of String(Null)
    
    Uart_Printf("Tx Strings:%s\n",txStr);
    Uart_Printf("Rx Strings:%s :",rxStr);
    
    if(strcmp(rxStr,txStr)==0)
        Uart_Printf("O.K.\n\n\n");
    else 
        Uart_Printf("ERROR!!!\n\n\n");
    SPI_Port_Return();
}


void Test_Spi_M_Tx_DMA1(void)
{

    int i,first,second;
    unsigned char *tx_ptr;
    SPI_Port_Init(1); // Master(GPIO) 
    Uart_Printf("[SPI DMA1 Master Tx test]\n");
    Uart_Printf("This test should be configured two boards\nStart Rx first.\n");

    tx_ptr=(unsigned char *) SPI_BUFFER;
    for(i=0; i<spi_count; i++)
		*(tx_ptr+i)=i; 

    tx_dma1Done=0;

    pISR_DMA1 = (unsigned)Dma1Tx_Int;
    rINTMSK=~(BIT_DMA1);

    //Step1. SPI init
    rSPPRE0=0x0;	//if PCLK=50Mhz,SPICLK=25Mhz
    rSPCON0=(2<<5)|(1<<4)|(1<<3)|(1<<2)|(0<<1)|(0<<0);//DMA1,en-SCK,master,low,A,normal
//    rSPCON0=(2<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0);//DMA1,en-SCK,master,low,B,normal    
    rSPPIN0=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release

    //Step2. DMA1 init 
    rDISRC1=(unsigned)tx_ptr;	//Address of Memory
    rDISRCC1=(0<<1)|(0);		//AHB(Memory), inc
    rDIDST1=(unsigned)0x59000010;//Address of SPTDAT Register
    rDIDSTC1=(1<<1)|(1);		//APB(SPI), fix
    rDCON1=(1<<31)|(0<<30)|(1<<29)|(0<<28)|(0<<27)|(3<<24)|(1<<23)|(1<<22)|(0<<20)|(spi_count);
    //handshake, sync PCLK, TC int, single tx, single service, SPI, H/W request, 
    //off-reload, byte, 128Bytes

    rGPGDAT&=0xfffffffb; // Activate nSS 
    rDMASKTRIG1=(0<<2)|(1<<1)|(0);    //run, DMA1 channel on, no-sw trigger 

    while(tx_dma1Done==0);

    while(!(rSPSTA0&0x1)); // Tx is done

    rGPGDAT|=0x4; // Deactivate nSS 
//    rSPCON0=(0<<5)|(0<<4)|(1<<3)|(1<<2)|(0<<1)|(0<<0);//poll,dis-SCK,master,low,A,normal
    rSPCON0=(0<<5)|(0<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0);//poll,dis-SCK,master,low,B,normal
    Uart_Printf("\nDMA1 transfer end\n");
	Uart_Printf("\ntransfered data : \n");
    for(i=0; i<spi_count; i++)
		Uart_Printf("0x%02x,",*tx_ptr++);
	Uart_Printf("\b\n\n\n");
    SPI_Port_Return();
}

void __irq Dma1Tx_Int(void)
{
    tx_dma1Done=1;
    rINTMSK|=BIT_DMA1;
    ClearPending(BIT_DMA1);
}


void Test_Spi_S_Rx_DMA1(void)
{
    int i;
    unsigned char *rx_ptr;
    SPI_Port_Init(0); // Slave(nSS) 
    Uart_Printf("[SPI DMA1 Slave Rx Test]\n");
    Uart_Printf("This test should be configured two boards\nStart Rx first.\n");
    rx_ptr=(unsigned char *) SPI_BUFFER;
    for(i=0;i<0x500;i++)
		*(rx_ptr+i)=0x0; // Zero Initialize
    rx_dma1Done=0;

    pISR_DMA1 = (unsigned)Dma1Rx_Int;
    rINTMSK=~(BIT_DMA1);

    //Step1. SPI init
    rSPPRE0=0x0;	//if PCLK=50Mhz,SPICLK=25Mhz
    rSPCON0=(2<<5)|(0<<4)|(0<<3)|(1<<2)|(0<<1)|(1<<0);//DMA1,dis-SCK,slave,low,A,TAGD
//    rSPCON0=(2<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1)|(1<<0);//DMA1,dis-SCK,slave,low,B,TAGD
    //When you use [Slave Rx with DMA] function you should have to set TAGD bit
    rSPPIN0=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release

    //Step2. DMA1 init 
    rDISRC1=(unsigned)0x59000014;//Address of SPRDAT Register
    rDISRCC1=(1<<1)|(1);		//APB(SPI), fix
    rDIDST1=(unsigned)rx_ptr;	//Address of Memory
    rDIDSTC1=(0<<1)|(0);		//AHB(Memory), inc
    rDCON1=(1<<31)|(0<<30)|(1<<29)|(0<<28)|(0<<27)|(3<<24)|(1<<23)|(1<<22)|(0<<20)|(spi_count);
    //handshake, sync PCLK, TC int, single tx, single service, SPI, H/W request, 
    //off-reload, byte, 128Bytes

    rDMASKTRIG1=(0<<2)|(1<<1)|(0);    //run, DMA1 channel on, no-sw trigger 

    while(rx_dma1Done==0);

    rSPCON0=(0<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0);//poll,dis-SCK,slave,low,B,normal
    while(!rSPSTA0&0x1);
    *(rx_ptr+spi_count)=rSPRDAT0;
    rx_ptr=(unsigned char *) SPI_BUFFER;
    Uart_Printf("\nDMA1 receive end\n");
    Uart_Printf("\nreceived data : \n");
    for(i=1;i<(spi_count+1);i++)
		Uart_Printf("0x%02x,",*(rx_ptr+i));
	Uart_Printf("\b\n\n\n");
    SPI_Port_Return();
}

void __irq Dma1Rx_Int(void)
{
    rx_dma1Done=1;
    rINTMSK|=BIT_DMA1;
    ClearPending(BIT_DMA1);
}


void Test_Spi_M_Rx_DMA1(void)
{
    int i;
    unsigned char *rx_ptr;
    SPI_Port_Init(1); // Master(GPIO)
    Uart_Printf("[SPI DMA1 Master Rx Test]\n");
    Uart_Printf("This test should be configured two boards\nStart Tx first.\n");

    rx_ptr=(unsigned char *)SPI_BUFFER;
    for(i=0;i<0x500;i++)
		*(rx_ptr+i)=0x0; // Zero Initialize
    rx_dma1Done=0;

    pISR_DMA1 = (unsigned)Dma1Rx_Int;
    rINTMSK=~(BIT_DMA1);
    //Step1. SPI init

    rSPPRE0=0x1;	//if PCLK=50Mhz,SPICLK=25Mhz
//    rSPCON0=(2<<5)|(1<<4)|(1<<3)|(1<<2)|(0<<1)|(1<<0);//DMA1,en-SCK,master,low,A,TAGD    
    rSPCON0=(2<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0);//DMA1,en-SCK,master,low,B,TAGD
    rGPGDAT&=0xfffffffb; // Activate nSS 
    //When you use [Master Rx with DMA] function you should have to set TAGD bit
    rSPPIN0=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release

 
    //Step2. DMA1 init 
    rDISRC1=(unsigned)0x59000014;//Address of SPRDAT Register
    rDISRCC1=(1<<1)|(1);		//APB(SPI), fix
    rDIDST1=(unsigned)rx_ptr;	//Address of Memory
    rDIDSTC1=(0<<1)|(0);		//AHB(Memory), inc
    rDCON1=(1<<31)|(0<<30)|(1<<29)|(0<<28)|(0<<27)|(3<<24)|(1<<23)|(1<<22)|(0<<20)|(spi_count);
    //handshake, sync PCLK, TC int, single tx, single service, SPI, H/W request, 
    //off-reload, byte, 128Bytes
    rDMASKTRIG1=(0<<2)|(1<<1)|(0);    //run, DMA1 channel on, no-sw trigger 

    while(rx_dma1Done==0);

    rSPCON0=(0<<5)|(1<<4)|(1<<3)|(1<<2)|(0<<1)|(0<<0);//poll,dis-SCK,master,low,A,normal
//    rSPCON0=(0<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0);//poll,dis-SCK,master,low,B,normal

    while(!rSPSTA0&0x1);

    *(rx_ptr+spi_count)=rSPRDAT0;
    rx_ptr=(unsigned char *)SPI_BUFFER;
    rGPGDAT|=0x4; // Deactivate nSS 
    Uart_Printf("\nDMA1 receive end\n");
    Uart_Printf("\nreceived data : \n");
    for(i=1;i<(spi_count+1);i++)
		Uart_Printf("0x%02x,",*(rx_ptr+i));//to remove first dummy data
	Uart_Printf("\b\n\n\n");
    SPI_Port_Return();
}

void Test_Spi_S_Tx_DMA1(void)
{
    int i;
    unsigned char *tx_ptr;
    SPI_Port_Init(0); // Slave (nSS)
    Uart_Printf("[SPI DMA1 Slave Tx test]\n");
    Uart_Printf("This test should be configured two boards\nStart Tx first.\n");
    tx_ptr=(U8 *) SPI_BUFFER;
    for(i=0; i<spi_count; i++)
		*(tx_ptr+i)=i;
    tx_dma1Done=0;
    pISR_DMA1 = (unsigned)Dma1Tx_Int;
    rINTMSK=~(BIT_DMA1);

    //Step1. SPI init
    rSPPRE0=0x0;	//if PCLK=50Mhz,SPICLK=25Mhz
//    rSPCON0=(2<<5)|(0<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0);//DMA1,dis-SCK,slave,low,A,normal
    rSPCON0=(2<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0);//DMA1,dis-SCK,slave,low,B,normal
    rSPPIN0=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release

    //Step2. DMA1 init 
    rDISRC1=(unsigned)tx_ptr;	//Address of Memory
    rDISRCC1=(0<<1)|(0);		//AHB(Memory), inc
    rDIDST1=(unsigned)0x59000010;//Address of SPTDAT Register
    rDIDSTC1=(1<<1)|(1);		//APB(SPI), fix
    rDCON1=(1<<31)|(0<<30)|(1<<29)|(0<<28)|(0<<27)|(3<<24)|(1<<23)|(1<<22)|(0<<20)|(spi_count);
    //handshake, sync PCLK, TC int, single tx, single service, SPI, H/W request, 
    //off-reload, byte, 128Bytes

    rDMASKTRIG1=(0<<2)|(1<<1)|(0);    //run, DMA1 channel on, no-sw trigger 


    while(tx_dma1Done==0);

    while(!(rSPSTA0&0x1)); // Tx is done
    rSPCON0=(0<<5)|(0<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0);//poll,dis-SCK,slave,low,A,normal
//    rSPCON0=(0<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0);//poll,dis-SCK,slave,low,B,normal
    Uart_Printf("\nDMA1 transfer end\n");
    Uart_Printf("\ntransfered data : \n");
    for(i=0; i<spi_count; i++)
		Uart_Printf("0x%02x,",*tx_ptr++);
	Uart_Printf("\b\n\n\n");
    SPI_Port_Return();
}


void Test_Spi_M_Int(void)
{
    char *rxStr,*txStr;
    SPI_Port_Init(1); // Master
    Uart_Printf("[SPI Interrupt Master Rx test]\n");
    Uart_Printf("This test should be configured two boards\nStart Slave first.\n");
    pISR_SPI0=(unsigned)Spi_Int;
    endSpiTx=0;
    spiTxStr="1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    spiRxStr=(char *) SPI_BUFFER;
    txStr=(char *)spiTxStr;
    rxStr=(char *)spiRxStr;
    rSPPRE0=0x1;	//if PCLK=50Mhz,SPICLK=12.5Mhz
    rSPCON0=(1<<5)|(1<<4)|(1<<3)|(1<<2)|(0<<1)|(0<<0);//int,en-SCK,master,low,A,normal
//    rSPCON0=(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0);//int,en-SCK,master,low,B,normal
    rSPPIN0=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release
    rGPGDAT&=0xfffffffb; // Activate nSS 
    rINTMSK=~(BIT_SPI0);

    while(endSpiTx==0);

    rGPGDAT|=0x4; // Deactivate nSS 
    rSPCON0=(0<<5)|(0<<4)|(1<<3)|(1<<2)|(0<<1)|(0<<0);//Poll,dis-SCK,master,low,A,normal
//    rSPCON0=(0<<5)|(0<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0);//Poll,dis-SCK,master,low,B,normal
    Uart_Printf("Current address :0x%x\n",spiRxStr);
    *spiRxStr='\0';//attach End of String(Null)
    Uart_Printf("Tx Strings:%s\n",txStr);
    Uart_Printf("Rx Strings:%s :",rxStr+1);//remove first dummy data
    if(strcmp((rxStr+1),txStr)==0)
        Uart_Printf("O.K.\n\n\n");
    else 
        Uart_Printf("ERROR!!!\n\n\n");
    SPI_Port_Return();
}



void Test_Spi_S_Int(void)
{
    char *rxStr,*txStr;
    SPI_Port_Init(0); // Slave (nSS)
    Uart_Printf("[SPI Interrupt Slave Tx test]\n");
    Uart_Printf("This test should be configured two boards\nStart Slave first.\n");
    pISR_SPI0=(unsigned)Spi_Int;
    endSpiTx=0;
    spiTxStr="1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    spiRxStr=(char *) SPI_BUFFER;
    txStr=(char *)spiTxStr;
    rxStr=(char *)spiRxStr;
    rSPPRE0=0x0;	//if PCLK=50Mhz,SPICLK=25Mhz
    rSPCON0=(1<<5)|(0<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0);//int,dis-SCK,slave,low,A,normal
//    rSPCON0=(1<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0);//int,dis-SCK,slave,low,B,normal
    rSPPIN0=(0<<2)|(1<<1)|(0<<0);//dis-ENMUL,SBO,release
    rINTMSK=~(BIT_SPI0);

    while(endSpiTx==0);

    rSPCON0=(0<<5)|(0<<4)|(0<<3)|(1<<2)|(0<<1)|(0<<0);//Poll,dis-SCK,master,low,A,normal
//    rSPCON0=(0<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1)|(0<<0);//Poll,dis-SCK,master,low,B,normal
	Uart_Printf("Current address :0x%x\n",spiRxStr);
    *spiRxStr='\0';//attach End of String(Null)
    Uart_Printf("Tx Strings:%s\n",txStr);
    Uart_Printf("Rx Strings:%s :",rxStr+1);//remove first dummy data
    if(strcmp((rxStr+1),txStr)==0)
        Uart_Printf("O.K.\n\n\n");
    else 
        Uart_Printf("ERROR!!!\n\n\n");
    SPI_Port_Return();
}


///////////////////////// 2004.05.14 added by junon 

static void __irq Eint1(void)
{
    U8           ui8ScanCode;

	getsFromKBCTL(&ui8ScanCode, 1);
	
	ClearPending(BIT_EINT1);

	Uart_Printf("keybd interrupt asserted -> scancode = 0x%x\n", ui8ScanCode);

}

void SPIKBD_Port_Init()
{
	spikbd_rGPBCON = rGPBCON;
	spikbd_rGPBDAT = rGPBDAT;
	spikbd_rGPBUP  = rGPBUP;
	
	spikbd_rGPDCON = rGPDCON;
	spikbd_rGPDDAT = rGPDDAT;
	spikbd_rGPDUP  = rGPDUP;

	spikbd_rGPFCON = rGPFCON;
	spikbd_rGPFDAT = rGPFDAT;
	spikbd_rGPFUP  = rGPFUP;

	spikbd_rGPGCON = rGPGCON;
	spikbd_rGPGDAT = rGPGDAT;
	spikbd_rGPGUP  = rGPGUP;

	// Setup IO port for SPI interface & Keyboard
	
	// Setup EINT1 (KBDINT)
    rGPFCON &= ~(0x3 << 2); 	// Clear GPF1 
    rGPFCON |= (0x2 << 2);  	// Set GPF1 to EINT1 for Keyboard interrupt

    rEXTINT0 &= ~(0x7 << 4);    // Clear EINT1
    rEXTINT0 |= (0x2 << 4);     // fallig edge triggered for EINT1

	// setup SPI interface
	// GPG5 : SPIMISO (KBDSPIMISO)
	// GPG6 : SPIMOSI (KBDSPIMOSI)
	// GPG7 : SPICLK  (KBDSPICLK)
    rGPGCON &= ~((0x3 << 10) | (0x3 << 12) | (0x3 << 14));   // Clear GPG5,6,7
    rGPGCON |= ((0x3 << 10) | (0x3 << 12) | (0x3 << 14));    
     
	// setup _SS signal(nSS_KBD)
    rGPBCON &= ~(0x3 << 12);         // Clear GPB6
    rGPBCON |= (ONEBIT << 12);        // Set Port GPB6 to output for nSS signal

	// setup _PWR_OK signal (KEYBOARD)
    rGPBCON &= ~(0x3 << 0);         // Clear GPB0 
    rGPBCON |= (ONEBIT << 0);       // Set Port GPB0 to output for _PWR_OK signal

    rGPDDAT &=~(ONEBIT << 0);        // set _PWR_OK to 0
}

void SPIKBD_Port_Return(void)
{
	rGPBCON = spikbd_rGPBCON;
	rGPBDAT = spikbd_rGPBDAT;
	rGPBUP  = spikbd_rGPBUP;
	
	rGPDCON = spikbd_rGPDCON;
	rGPDDAT = spikbd_rGPDDAT;
	rGPDUP  = spikbd_rGPDUP;
                 
	rGPFCON = spikbd_rGPFCON;
	rGPFDAT = spikbd_rGPFDAT;
	rGPFUP  = spikbd_rGPFUP;
                 
	rGPGCON = spikbd_rGPGCON;
	rGPGDAT = spikbd_rGPGDAT;
	rGPGUP  = spikbd_rGPGUP;
}

int	putcToKBCTL(U8 c)
{
	U32	i;

  	rGPBDAT &= ~(ONEBIT << 6);       //Set _SS signal to low (Slave Select)

	while((rSPSTA1 & ONEBIT)==0);	// wait while busy

	rSPTDAT1 = c;	                // write left justified data

	while((rSPSTA1 & ONEBIT)==0);	// wait while busy
   	
   	rGPBDAT |= (ONEBIT << 6);        //Set _SS signal to high (Slave Select)

	i = rSPRDAT1;

	return(i);
}

void getsFromKBCTL(U8 *m, int cnt)
{
	int	i, j;
	volatile tmp = 1;

	for(j = 0; j < 3; j++)
		tmp += tmp;
	for(j = 0; j < 250 * 30; j++)
		tmp += tmp;

	for(i = 0; i < cnt; i++) 
	{
		m[i] = putcToKBCTL(0xFF);

		for(j = 0; j < 400; j++)
			tmp+= tmp;
	}
}

void putsToKBCTL(U8 *m,  int cnt)
{
	int	i, j, x;
	volatile tmp = 1;
	
	for(j = 0; j < 3; j++)
		x = j;
	for(j = 0; j < 3; j++)
		tmp += tmp;
	for(j = 0; j < 250 * 30; j++)
		tmp += tmp;

	for(i = 0; i < cnt; i++) {

		j = putcToKBCTL(m[i]);

		for(j = 0; j < 400; j++)
			tmp+= tmp;
		for(j = 0; j < 400; j++)
			x = j;
    }
}

char lrc(U8 *buffer, int count)
{
    char lrc;
    int n;

    lrc = buffer[0] ^ buffer[1];

    for (n = 2; n < count; n++)
    {
        lrc ^= buffer[n];
    }

    if (lrc & 0x80)
        lrc ^= 0xC0;

    return lrc;
}

int USAR_WriteRegister(int reg, int data)
{
    U8 cmd_buffer[4];

    cmd_buffer[0] = 0x1b; //USAR_PH_WR;
    cmd_buffer[1] = (unsigned char)reg;
    cmd_buffer[2] = (unsigned char)data;

    cmd_buffer[3] = lrc((U8 *)cmd_buffer,3);
    putsToKBCTL((U8 *)cmd_buffer,4);

    return TRUE;
}

void Kbd_PowerOn(void)
{
	U8 msg[5];
	int t;
	char dummy = (char)0xff;	

	SPIKBD_Port_Init();

	// Setup SPI registers
    // Interrupt mode, prescaler enable, master mode, active high clock, format B, normal mode
    rSPCON1 = (ONEBIT<<5)|(ONEBIT<<4)|(ONEBIT<<3)|(0x0<<2)|(ONEBIT<<1);
    
	// Developer MUST change the value of prescaler properly whenever value of PCLK is changed.
    rSPPRE1 = 255;// 99.121K = 203M/4/2/(255+1) PCLK=50.75Mhz FCLK=203Mhz SPICLK=99.121Khz
         
    for(t=0;t<20000; t++); // delay
	    msg[0] = (char)0x1b; msg[1] = (char)0xa0; msg[2] = (char)0x7b; msg[3] = (char)0; // Initialize USAR
    	for(t=0; t < 10; t++) {
    	dummy = putcToKBCTL(0xff);
    }
    
    for(t=0; t<10; t++) { // wait for a while
        putsToKBCTL(msg,3);
        for(t=0;t<20000; t++);
    }
    t = 100;
    while(t--) {
        if((rGPFDAT & 0x2)==0) { // Read _ATN (KBDINT) GPF1
            break;
        }
    }	//check _ATN
    if(t != 0) {
        getsFromKBCTL(msg,3);
    }    
    t=100000;
    while(t--); // delay
	msg[0] = (char)0x1b; msg[1] = (char)0xa1; msg[2] = (char)0x7a; msg[3] = (char)0; //Initialization complete
	putsToKBCTL(msg,3);

	Uart_Printf("KeybdPowerOn\n");
}

void Test_Spikbd_keyscan(void)
{
    Uart_Printf("[SPIKBD Test keyscan] start.\n");

	Kbd_PowerOn();

	rEXTINT0 = (rEXTINT0 & ~(7<<4)) | (2<<4); // falling edge

	pISR_EINT1=(U32)Eint1;

    rSRCPND = BIT_EINT1;
    rINTPND = BIT_EINT1;

    rINTMSK=~(BIT_EINT1);

	Uart_Getch();

	rINTMSK = BIT_ALLMSK;

    Uart_Printf("[SPIKBD Test keyscan] end.\n");

    SPIKBD_Port_Return();
}

void SPIKBD_Port_Init_IO()
{
	spikbd_rGPBCON = rGPBCON;
	spikbd_rGPBDAT = rGPBDAT;
	spikbd_rGPBUP  = rGPBUP;
	
	spikbd_rGPDCON = rGPDCON;
	spikbd_rGPDDAT = rGPDDAT;
	spikbd_rGPDUP  = rGPDUP;

	spikbd_rGPFCON = rGPFCON;
	spikbd_rGPFDAT = rGPFDAT;
	spikbd_rGPFUP  = rGPFUP;

	spikbd_rGPGCON = rGPGCON;
	spikbd_rGPGDAT = rGPGDAT;
	spikbd_rGPGUP  = rGPGUP;

	// Setup IO port for SPI interface & Keyboard
	
	// Setup KBDINT as output
    rGPFCON &= ~(0x3 << 2); 	// Clear GPF1 
    rGPFCON |= (0x1 << 2);  	// Set GPF1 to EINT1 for Keyboard interrupt

	// setup SPI interface
	// GPG5 : SPIMISO (KBDSPIMISO)
	// GPG6 : SPIMOSI (KBDSPIMOSI)
	// GPG7 : SPICLK  (KBDSPICLK)
    rGPGCON &= ~((0x3 << 10) | (0x3 << 12) | (0x3 << 14));   // Clear GPG5,6,7
    rGPGCON |= ((0x1 << 10) | (0x1 << 12) | (0x1 << 14));    
     
	// setup _SS signal(nSS_KBD)
    rGPBCON &= ~(0x3 << 12);         // Clear GPB6
    rGPBCON |= (ONEBIT << 12);        // Set Port GPB6 to output for nSS signal

	// setup _PWR_OK signal (KEYBOARD)
    rGPBCON &= ~(0x3 << 0);         // Clear GPB0 
    rGPBCON |= (ONEBIT << 0);       // Set Port GPB0 to output for _PWR_OK signal
}


void Test_Spikbd_IO(void)
{
	int i = 0;
	
    Uart_Printf("[SPIKBD IO-Test] start\n");

	SPIKBD_Port_Init_IO();

	do 
	{
		Uart_Printf("test loop going - %d\n", i);
		i++;

		if (i%2) 
		{
			rGPFDAT &= ~(1<<1); // GPF1 KBDINT
			rGPBDAT &= ~(1<<6); // GPB6
			rGPBDAT &= ~(1<<0); // GPB0
			rGPGDAT &= ~(7<<5); // GPG5,6,7 (SPIMISO,SPIMOSI,SPICLK)
		}
		else 
		{
			rGPFDAT |= (1<<1); // GPF1 KBDINT
			rGPBDAT |= (1<<6); // GPB6
			rGPBDAT |= (1<<0); // GPB0
			rGPGDAT |= (7<<5); // GPG5,6,7 (SPIMISO,SPIMOSI,SPICLK)
		}
		
	} while(Uart_GetKey() == 0);


    Uart_Printf("[SPIKBD IO-Test] end\n");
    
    SPIKBD_Port_Return();

}
//////////////////////////////////
//2005. 11. 22 Yhyeo SPI LCD insert
void cs_high(void)
{
	rGPGDAT |= (1<<3);
}

void cs_low(void)
{
	rGPGDAT &= ~(1<<3);
}

void n_reset(void)
{
	rGPGDAT &= ~(1<<1);
	Delay(500);				// 100 us
	rGPGDAT |= (1<<1);
}

void Spi_Port_Init(int port)
{
	// SPI channel 1 setting
	if(port) {
		rGPGUP = ~(0xFFFF);
		spi_rGPGCON=rGPGCON;
		spi_rGPGDAT=rGPGDAT;
		spi_rGPGUP=rGPGUP;

		rGPGCON = ((rGPGCON & ~(0xFF<<8)) | (0xFF<<8));	// Master(GPIO_Output)
		rGPGDAT |= (3<<2);							// RESET, CE -> High
		rGPGCON = ((rGPGCON & ~(0xF<<4)) | (0x7<<4));	// RESET, CE -> Output Mode
		rGPGCON &= ~(0x3<<8);
		Uart_Printf("GPG = %x,\t%x,\t%x\n", rGPGCON, rGPGDAT, rGPGUP);
	} else {
		rGPDCON = ((rGPDCON & ~0xF) | (0x5));
		rGPDDAT = 0x3;
		spi_rGPDCON=rGPDCON;
		spi_rGPDDAT=rGPDDAT;
		spi_rGPDUP=rGPDUP;

		rGPDCON = ((rGPDCON & ~(0x003F000F)) | (0x3F0005));	// Master(GPIO_Output)
		rGPDDAT |= (3<<0);							// RESET, CE -> High
		Uart_Printf("GPD = %x,\t%x,\t%x\n", rGPDCON, rGPDDAT, rGPDUP);
		Uart_Printf("GPG = %x,\t%x,\t%x\n", rGPGCON, rGPGDAT, rGPGUP);
	}
}

void Spi_Release(int port)
{
	if(port) {
		rGPGCON=spi_rGPGCON;
		rGPGDAT=spi_rGPGDAT;
		rGPGUP=spi_rGPGUP;
	} else {
		rGPDCON=spi_rGPDCON;
		rGPDDAT=spi_rGPDDAT;
		rGPDUP=spi_rGPDUP;
		Uart_Printf("GPD = %x,\t%x,\t%x\n", rGPDCON, rGPDDAT, rGPDUP);
	}
}

void spi_tx(unsigned char index, unsigned short data)
{
	int i=0, j; char tmp[6];

	// INDEX
	tmp[0]=0x74;
	tmp[1]=(unsigned char)index;
	tmp[2]=0x0;
	tmp[3]=0x76;
	tmp[4]=(unsigned char)((data&0xff00)>>8);
	tmp[5]=(unsigned char)((data&0x00ff)>>0);
	
	//SEND INDEX
	cs_low();
	for(i=0; i<6; i++) {
		if(i!=2)
		rSPTDAT1=tmp[i];
		while(!(rSPSTA1&0x1)) ;
		if(i==2) {
			cs_high();
			rSPCON1 &= ~(1<<4);	//dis-SCK
			cs_low();
			rSPCON1 |= (1<<4);	//dis-SCK
		}
	}

	cs_high();
}

void Tcon_Init(unsigned short data)
{
	n_reset();
	Delay(400);

	spi_tx(0x09, 0x0000);
	Delay(5000);
	spi_tx(0x09, 0x4000);
	spi_tx(0x0a, 0x2000);
	Delay(20);
	spi_tx(0x09, 0x4055);
	Delay(25000);
	spi_tx(0x01, 0x409D);		// Sync Mode
	spi_tx(0x02, 0x0204);
	spi_tx(0x03, 0x0100);
	spi_tx(0x04, 0x3000);
	spi_tx(0x05, 0x4003);
	spi_tx(0x06, data);
	spi_tx(0x07, 0x0018);
	spi_tx(0x08, 0x0C00);
	spi_tx(0x10, 0x0103);
	spi_tx(0x11, 0x0301);
	spi_tx(0x12, 0x1F0F);
	spi_tx(0x13, 0x1F0F);
	spi_tx(0x14, 0x0707);
	spi_tx(0x15, 0x0307);
	spi_tx(0x16, 0x0707);
	spi_tx(0x17, 0x0000);
	spi_tx(0x18, 0x0004);
	spi_tx(0x19, 0x0000);
	Delay(25000);
	spi_tx(0x09, 0x4A55);
	spi_tx(0x05, 0x5003);
}

void Spi_Lcd_Init(void)
{
	int i,j,k;
	char *txStr,*rxStr;
	char tmp[6];

	Spi_Port_Init(1);		// using SPI1
	Uart_Printf("[SPI Polling TFT LCD TCON Initialize]\n");

	endSpiTx=0;

	spiTxStr= tmp+0;
	txStr=(char *)spiTxStr;

	rSPPRE1=0x1;	//if PCLK=67.5Mhz,SPICLK=16.875Mhz
	rSPCON1=(00<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0);//Polling,en-SCK,master,low,A,normal
	rSPPIN1=(0<<2)|(1<<1)|(1<<0);//dis-ENMUL,SBO,release

	Tcon_Init(0x8);
	Delay(300);

	rSPCON1 &= ~(1<<4);	//dis-SCK

	Spi_Release(1);
	Delay(300000);
}
