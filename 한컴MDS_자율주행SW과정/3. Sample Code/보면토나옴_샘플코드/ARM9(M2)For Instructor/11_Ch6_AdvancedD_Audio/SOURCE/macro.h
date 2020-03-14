//=============================================================================
// File Name : macro.h
//=============================================================================

// Bit opreation macros

#define	Macro_Set_Bit(dest, position)		((dest) |= (0x1 << (position)))
#define	Macro_Clear_Bit(dest, position)		((dest) &= ~(0x1 << (position)))
#define	Macro_Invert_Bit(dest, position)		((dest) ^= (0x1 << (position)))

#define	Macro_Erase_Area(dest, bits, position)		((dest) &= ~((bits) << (position)))
#define	Macro_Write_Area(dest, data, position)		((dest) |= ((data) << (position)))

// Interrupt masking and pending registers control

#define	Macro_Clear_Interrupt_Pending(type)		 { rSRCPND = (type); rINTPND = (type); }

#define	Macro_Clear_Sub_Source_Pending(type)	  rSUBSRCPND = (type)

