#ifndef __GLIB_H__
#define __GLIB_H__


void Glib_Init(int type);

void Glib_Line(int x1,int y1,int x2,int y2,int color);
void Glib_Rectangle(int x1,int y1,int x2,int y2,int color);
void Glib_FilledRectangle(int x1,int y1,int x2,int y2,int color);
void Glib_ClearScr(U32 c,int type);

void _PutStn1Bit(U32 x,U32 y,U32 c);
void _PutStn2Bit(U32 x,U32 y,U32 c);
void _PutStn4Bit(U32 x,U32 y,U32 c);
void _PutCstn8Bit(U32 x,U32 y,U32 c);
void _PutCstn12Bit(U32 x,U32 y,U32 c);
void _PutCstn16Bit(U32 x,U32 y,U32 c);
void _PutTft8Bit_240320(U32 x,U32 y,U32 c);
void _PutTft16Bit_240320(U32 x,U32 y,U32 c);
#if 1	/* khjung */
void _PutTft8Bit_320240(U32 x,U32 y,U32 c);
void _PutTft16Bit_320240(U32 x,U32 y,U32 c);
#endif
void _PutTft1Bit_640480(U32 x,U32 y,U32 c);
void _PutTft8Bit_640480(U32 x,U32 y,U32 c);
void _PutTft16Bit_640480(U32 x,U32 y,U32 c);
void _PutTft24Bit_640480(U32 x,U32 y,U32 c);
void _PutTft1Bit_800600(U32 x,U32 y,U32 c);
void _PutTft8Bit_800600(U32 x,U32 y,U32 c);
void _PutTft16Bit_800600(U32 x,U32 y,U32 c);

extern void (*PutPixel)(U32,U32,U32);

#endif //__GLIB_H__
