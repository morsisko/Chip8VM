#pragma once
#include <array>
#include <iostream>
#include <vector>

class Chip8;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef void (Chip8::*ProcFunc)(ushort);

struct OpcodeFunction
{
	ProcFunc func;
	ushort mask;
	ushort opcode;
};

class Chip8
{
private:
	std::array<uchar, 16> V;
	std::array<ushort, 16> stack;
	std::array<ushort, 4096> memory;
	std::vector<OpcodeFunction> functions;

	uchar delay_timer;
	uchar sound_timer;
	uchar sp;
	ushort pc;
	ushort I;

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
	void Do8XYE(ushort opcode);
	void Do9XY0(ushort opcode);
	void DoANNN(ushort opcode);
	void DoBNNN(ushort opcode);
	void DoCXKK(ushort opcode);
	void DoDXYN(ushort opcode);
	void DoEX9E(ushort opcode);
	void DoEXA1(ushort opcode);
	void DoFX07(ushort opcode);
	void DoFX0A(ushort opcode);
	void DoFX15(ushort opcode);
	void DoFX18(ushort opcode);
	void DoFX1E(ushort opcode);
	void DoFX29(ushort opcode);
	void DoFX33(ushort opcode);
	void DoFX55(ushort opcode);

	void InitializeFunctions();
public:
	Chip8();
	~Chip8();
};

