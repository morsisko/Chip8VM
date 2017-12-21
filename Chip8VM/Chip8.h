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

	ushort GetNNN(ushort opcode);
	uchar GetN(ushort opcode);
	uchar GetX(ushort opcode);
	uchar GetY(ushort opcode);
	uchar GetKK(ushort opcode);

	void Do1NNN(ushort opcode);
	void Do2NNN(ushort opcode);
	void Do3XKK(ushort opcode);
	void Do4XKK(ushort opcode);
	void Do5XY0(ushort opcode);
	void Do6XKK(ushort opcode);
	void Do7XKK(ushort opcode);
	void Do8XY0(ushort opcode);
	void Do8XY1(ushort opcode);
	void Do8XY2(ushort opcode);
	void Do8XY3(ushort opcode);
	void Do8XY4(ushort opcode);
	void Do8XY5(ushort opcode);
	void Do8XY6(ushort opcode);
	void Do8XY7(ushort opcode);
public:
	Chip8();
	~Chip8();
};

