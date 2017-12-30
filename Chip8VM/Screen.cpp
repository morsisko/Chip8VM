#include "Screen.h"

Screen::Screen(Chip8 & vm, int ratio) :
	vm(vm),
	ratio(ratio),
	window(sf::VideoMode(Chip8::SCREEN_WIDTH * ratio, Chip8::SCREEN_HEIHGT * ratio), "Chip8VM!")
{
	window.setFramerateLimit(60);
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(Chip8::SCREEN_HEIHGT * Chip8::SCREEN_WIDTH * 4);

	InitVertices();
}

void Screen::MainLoop()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (int i = 0; i != 16; ++i)
		{
			vm.ExecuteOpcode();
			if (vm.ShouldRedraw())
			{
				FillVertices();
			}
		}
		window.draw(vertices);
		window.display();
		vm.AffectTimers();
	}
}

void Screen::InitVertices()
{
	for (int i = 0; i < Chip8::SCREEN_WIDTH; ++i)
		for (int j = 0; j < Chip8::SCREEN_HEIHGT; ++j)
		{
			sf::Vertex* quad = &vertices[(i + j * Chip8::SCREEN_WIDTH) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * ratio, j * ratio);
			quad[1].position = sf::Vector2f((i + 1) * ratio, j * ratio);
			quad[2].position = sf::Vector2f((i + 1) * ratio, (j + 1) * ratio);
			quad[3].position = sf::Vector2f(i * ratio, (j + 1) * ratio);
		}

	for (int i = 0; i < vertices.getVertexCount(); ++i)
		vertices[i].color = sf::Color::Black;
}

void Screen::FillVertices()
{
	for (int y = 0; y != Chip8::SCREEN_HEIHGT; ++y)
	{
		for (int x = 0; x != Chip8::SCREEN_WIDTH; ++x)
		{
			sf::Vertex* quad = &vertices[(x + y * Chip8::SCREEN_WIDTH) * 4];

			uchar pixel = vm.GetPixel(x, y);

			for (int j = 0; j != 4; ++j)
			{
				if (pixel == 0)
					quad[j].color = sf::Color::Black;
				else
					quad[j].color = sf::Color::White;
			}
		}
	}
}

Screen::~Screen()
{
}
