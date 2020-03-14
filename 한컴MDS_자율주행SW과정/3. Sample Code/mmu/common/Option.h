//====================================================================
// File Name : option.h
// Function  : S3C2410 
// Program   : Shin, On Pil (SOP)
// Date      : May 15, 2002
// Version   : 0.0
// History
//   0.0 : Programming start (February 20,2002) -> SOP
//====================================================================

#ifndef __OPTION_H__
#define __OPTION_H__


#define FCLK 202800000
#define HCLK (202800000/2)
#define PCLK (202800000/4)
#define UCLK PCLK



// BUSWIDTH : 16,32
#define BUSWIDTH    (32)

//64MB
// 0x30000000 ~ 0x30ffffff : Download Area (16MB) Cacheable
// 0x31000000 ~ 0x33feffff : Non-Cacheable Area
// 0x33ff0000 ~ 0x33ff47ff : Heap & RW Area
// 0x33ff4800 ~ 0x33ff7fff : FIQ ~ User Stack Area
// 0x33ff8000 ~ 0x33fffeff : Not Used Area
// 0x33ffff00 ~ 0x33ffffff : Exception & ISR Vector Table

#define _RAM_STARTADDRESS       0x30000000
#define _NONCACHE_STARTADDRESS	0x31000000
#define _ISR_STARTADDRESS       0x33ffff00     
#define _MMUTT_STARTADDRESS     0x33ff8000
#define _STACK_BASEADDRESS      0x33ff8000
#define HEAPEND                 0x33ff0000

#endif    //__OPTION_H__