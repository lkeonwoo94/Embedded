/*
 * =====================================================================
 * NAME         : libc.h
 *
 * Descriptions : Definition of S3C2440 Library prototype
 *
 * IDE          : CodeWarrior 2.0 or Later
 *
 * Modification
 *	   2006.9.12 by JunGyu Park
 * =====================================================================
 */

void MemFill(unsigned long ptr, unsigned long pattern, int size);
void MemDump(unsigned long ptr, int size);