#pragma once
#include <array>

typedef unsigned short ushort;
typedef unsigned char uchar;

class Chip8
{
private:
	std::array<uchar, 16> V;
	std::array<ushort, 16> stack;
	std::array<ushort, 4096> memory;

	uchar delay_timer;
	uchar sound_timer;
	uchar sp;
	ushort pc;
public:
	Chip8();
	~Chip8();
};

