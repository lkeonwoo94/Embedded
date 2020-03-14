/*
 * =====================================================================
 * NAME         : libc.c
 *
 * Descriptions : C library for S3C2450
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *     Modified by MDS Tech. NT Div.(2Gr) (2015.10.1)
 * =====================================================================
 */
 

void MemFill(unsigned long ptr, unsigned long pattern, int size);
void MemDump(unsigned long ptr, int size);

void MemFill(unsigned long ptr, unsigned long pattern, int size)
{
	int i;
	unsigned long *data;
	data = (unsigned long *)ptr;

	for (i=0; i<size;i++)
		*data++ = pattern;
}

void MemDump(unsigned long ptr, int size)
{
	int i;
	unsigned long *data;
	data = (unsigned long *)ptr;

	Uart_Printf("\n");
	Uart_Printf("*** Dump Memory from [0x%08x] to [0x%08x] : \n",ptr, (unsigned long *)ptr+size);
	for (i=0; i<size;i++) {
		if ( !(i%4) )
			Uart_Printf("\n  [0x%08x] : ",data);
		Uart_Printf("0x%08x ",*data++);
	}
	Uart_Printf("\n");
}
