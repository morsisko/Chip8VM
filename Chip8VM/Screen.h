#pragma once
#include "Chip8.h"
#include <SFML/Graphics.hpp>

class Screen
{
private:
	Chip8& vm;
	sf::RenderWindow window;
	sf::VertexArray vertices;
	int ratio;

	void InitVertices();
	void FillVertices();
public:
	Screen(Chip8& vm, int ratio);
	void MainLoop();
	~Screen();
};

