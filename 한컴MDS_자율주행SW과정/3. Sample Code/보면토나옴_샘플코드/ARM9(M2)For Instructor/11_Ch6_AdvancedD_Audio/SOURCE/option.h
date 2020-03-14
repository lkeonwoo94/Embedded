//=============================================================================
// File Name : option.h
//=============================================================================

#define _SDRAM_STARTADDRESS			0x30000000
#define _ISR_STARTADDRESS			0x33ffff00
#define _ISR_ENDADDRESS				(_ISR_STARTADDRESS+0x9c)
// C ���� �޸� ������ �ݵ�� ISR_Start �ּ� ���� �̾�� �Ѵ�
#define _CMEMORY_STARTADDRESS	(_SDRAM_STARTADDRESS)

// Frequency setting

#define	FCLK		399650000	// 399.650MHz (400MHz)
#define	HCLK		(FCLK/4)		// 99.9125MHz (100MHz)
#define	PCLK		(FCLK/8)		// 49.95625MHz (50MHz)
