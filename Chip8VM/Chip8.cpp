#include "Chip8.h"

//Resource used: http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

Chip8::Chip8() :
	V({}),
	stack({}),
	memory({}),
	delay_timer(0),
	sound_timer(0),
	sp(0),
	I(0),
	pc(0x200)
{
	InitializeFunctions();
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

void Chip8::Do1NNN(ushort opcode)
{
	pc = GetNNN(opcode);
}

void Chip8::Do2NNN(ushort opcode)
{
}

void Chip8::Do3XKK(ushort opcode)
{
	if (V[GetX(opcode)] == GetKK(opcode))
		pc += 2;
}

void Chip8::Do4XKK(ushort opcode)
{
	if (V[GetX(opcode)] != GetKK(opcode))
		pc += 2;
}

void Chip8::Do5XY0(ushort opcode)
{
	if (V[GetX(opcode)] == V[GetY(opcode)])
		pc += 2;
}

void Chip8::Do6XKK(ushort opcode)
{
	V[GetX(opcode)] = GetKK(opcode);
}

void Chip8::Do7XKK(ushort opcode)
{
	V[GetX(opcode)] += GetKK(opcode);
}

void Chip8::Do8XY0(ushort opcode)
{
	V[GetX(opcode)] = V[GetY(opcode)];
}

void Chip8::Do8XY1(ushort opcode)
{
	V[GetX(opcode)] |= V[GetY(opcode)];
}

void Chip8::Do8XY2(ushort opcode)
{
	V[GetX(opcode)] &= V[GetY(opcode)];
}

void Chip8::Do8XY3(ushort opcode)
{
	V[GetX(opcode)] ^= V[GetY(opcode)];
}

void Chip8::Do8XY4(ushort opcode)
{
	ushort sum = V[GetX(opcode)] + V[GetY(opcode)];
	V[GetX(opcode)] = static_cast<uchar>(sum);
	V[0xF] = (sum > 255);
}

void Chip8::Do8XY5(ushort opcode)
{
	V[0xF] = (V[GetX(opcode)] > V[GetY(opcode)]);
	V[GetX(opcode)] -= V[GetY(opcode)];
}

void Chip8::Do8XY6(ushort opcode)
{
	V[0xF] = V[GetX(opcode)] & 0x1;
	V[GetX(opcode)] >>= 1;
}

void Chip8::Do8XY7(ushort opcode)
{
	V[0xF] = (V[GetY(opcode)] > V[GetX(opcode)]);
	V[GetX(opcode)] = V[GetY(opcode)] - V[GetX(opcode)];
}

void Chip8::Do8XYE(ushort opcode)
{
	V[0xF] = V[GetX(opcode)] & 0x1;
	V[GetX(opcode)] <<= 1;
}

void Chip8::Do9XY0(ushort opcode)
{
	if (V[GetX(opcode)] == V[GetY(opcode)])
		pc += 2;
}

void Chip8::DoANNN(ushort opcode)
{
	I = GetNNN(opcode);
}

void Chip8::DoBNNN(ushort opcode)
{
	pc = V[0] + GetNNN(opcode);
}

void Chip8::DoCXKK(ushort opcode)
{
	uchar random = 4;
	V[GetX(opcode)] = random & GetKK(opcode);
}

void Chip8::DoDXYN(ushort opcode)
{
}

void Chip8::DoEX9E(ushort opcode)
{
}

void Chip8::DoEXA1(ushort opcode)
{
}

void Chip8::DoFX07(ushort opcode)
{
	V[GetX(opcode)] = delay_timer;
}

void Chip8::DoFX0A(ushort opcode)
{
	std::cin >> V[GetX(opcode)]; //make key mapping later
}

void Chip8::DoFX15(ushort opcode)
{
	delay_timer = V[GetX(opcode)];
}

void Chip8::DoFX18(ushort opcode)
{
	sound_timer = V[GetX(opcode)];
}

void Chip8::DoFX1E(ushort opcode)
{
	I += V[GetX(opcode)];
}

void Chip8::DoFX29(ushort opcode)
{
}

void Chip8::DoFX33(ushort opcode)
{
}

void Chip8::DoFX55(ushort opcode)
{
}

void Chip8::InitializeFunctions()
{
	functions = { {&Chip8::Do1NNN, 0xF000, 0x1000},
	{ &Chip8::Do2NNN, 0xF000, 0x2000 },
	{ &Chip8::Do3XKK, 0xF000, 0x3000 }, 
	{ &Chip8::Do4XKK, 0xF000, 0x4000 }, 
	{ &Chip8::Do5XY0, 0xF00F, 0x5000 }, 
	{ &Chip8::Do6XKK, 0xF000, 0x6000 }, 
	{ &Chip8::Do7XKK, 0xF000, 0x7000 }, 
	{ &Chip8::Do8XY1, 0xF00F, 0x8001 }, 
	{ &Chip8::Do8XY2, 0xF00F, 0x8002 },
	{ &Chip8::Do8XY3, 0xF00F, 0x8003 },
	{ &Chip8::Do8XY4, 0xF00F, 0x8004 },
	{ &Chip8::Do8XY5, 0xF00F, 0x8005 }, 
	{ &Chip8::Do8XY6, 0xF00F, 0x8006 }, 
	{ &Chip8::Do8XY7, 0xF00F, 0x8007 }, 
	{ &Chip8::Do8XYE, 0xF00F, 0x800E }, 
	{ &Chip8::Do9XY0, 0xF00F, 0x9000 }, 
	{ &Chip8::DoANNN, 0xF000, 0xA000 },
	{ &Chip8::DoBNNN, 0xF000, 0xB000 }, 
	{ &Chip8::DoCXKK, 0xF000, 0xC000 }, 
	{ &Chip8::DoDXYN, 0xF000, 0xD000 },
	{ &Chip8::DoEX9E, 0xF0FF, 0xE09E },
	{ &Chip8::DoEXA1, 0xF0FF, 0xE0A1 },
	{ &Chip8::DoFX07, 0xF0FF, 0xF007 },
	{ &Chip8::DoFX0A, 0xF0FF, 0xF00A },
	{ &Chip8::DoFX15, 0xF0FF, 0xF015 }, 
	{ &Chip8::DoFX18, 0xF0FF, 0xF018 },
	{ &Chip8::DoFX1E, 0xF0FF, 0xF01E },
	{ &Chip8::DoFX29, 0xF0FF, 0xF029 },
	{ &Chip8::DoFX33, 0xF0FF, 0xF033 },
	{ &Chip8::DoFX55, 0xF0FF, 0xF055 }, };
}

Chip8::~Chip8()
{
}
