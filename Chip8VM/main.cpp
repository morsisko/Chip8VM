#include <iostream>
#include <fstream>
#include "Chip8.h"
#include "Screen.h"

int main()
{
	static const int RATIO = 15;
	std::ifstream file;
	file.open("PONG.user", std::ios::binary);
	if (!file.is_open())
		return -1;

	Chip8 vm;
	vm.LoadROM(file);

	Screen screen(vm, RATIO);
	screen.MainLoop();

	return 0;
}