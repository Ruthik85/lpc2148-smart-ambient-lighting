#include "types.h"
void writeLCD(unsigned char data);
void CmdLCD(unsigned char cmd);
void CharLCD(unsigned char ascii);
void InitLCD(void);
void CtrLCD(char* str);
void U32LCD(u32 n);
void S32LCD(s32 n);
void F32LCD(f32 f,u32 nDP);
void HexLCD(u32 n);
void BinLCD(u32 n,u32 nBD);
void BuildCGRAM(u8 *p,u32 nBytes);
void StrLCD(s8 *p);








