#include "Chip8.h"



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


Chip8::~Chip8()
{
}
