//=============================================================================
// File Name : option.h
//=============================================================================



// Frequency setting

#define	FCLK		399650000	// 399.650MHz (400MHz)
#define	HCLK		(FCLK/4)		// 99.9125MHz (100MHz)
#define	PCLK		(FCLK/8)		// 49.95625MHz (50MHz)

// Memory management

//64MB
// 0x30000000 ~ 0x30ffffff : Download Area (16MB) Cacheable
// 0x31000000 ~ 0x33feffff : Non-Cacheable Area
// 0x33ff0000 ~ 0x33ff47ff : Heap & RW Area
// 0x33ff4800 ~ 0x33ff7fff : FIQ ~ User Stack Area
// 0x33ff8000 ~ 0x33fffeff : Not Useed Area --> MMU Table·Î »ç¿ëµÊ 
// 0x33ffff00 ~ 0x33ffffff : Exception & ISR Vector Table

//#define	_RAM_STARTADDRESS 		0x30000000
#define	_ISR_STARTADDRESS 		0x33ffff00     
//#define	_MMUTT_STARTADDRESS		0x33ff8000
//#define	_STACK_BASEADDRESS		0x33ff8000
//#define	_NONCACHE_STARTADDRESS	0x31000000
//#define  HEAPEND		    	0x33ff0000 
//#define    FRAME_BUFFER         0x31000000
#define    FRAME_BUFFER         0x33800000
    
