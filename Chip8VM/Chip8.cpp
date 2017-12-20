#include "Chip8.h"

//Resource used: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

Chip8::Chip8() :
	V({}),
	stack({}),
	memory({}),
	delay_timer(0),
	sound_timer(0),
	sp(0),
	pc(0x200)
{
}

ushort Chip8::GetNNN(ushort opcode)
{
	return opcode & 0x0FFF;
}

uchar Chip8::GetN(ushort opcode)
{
	return opcode & 0x000F;
}

uchar Chip8::GetX(ushort opcode)
{
	return (opcode & 0x0F00) >> 8;
}

uchar Chip8::GetY(ushort opcode)
{
	return (opcode & 0x00F0) >> 4;
}

uchar Chip8::GetKK(ushort opcode)
{
	return opcode & 0x00FF;
}

Chip8::~Chip8()
{
}
