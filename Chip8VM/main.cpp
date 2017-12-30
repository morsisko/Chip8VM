#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Chip8.h"

int main()
{
	Chip8 vm;
	static const int RATIO = 15;
	sf::RenderWindow window(sf::VideoMode(Chip8::SCREEN_WIDTH * RATIO, Chip8::SCREEN_HEIHGT * RATIO), "Chip8VM!");
	int elapsedTime = 0;
	window.setFramerateLimit(60);
	std::ifstream file;
	file.open("PONG", std::ios::binary);
	if (!file.is_open())
		return -1;

	vm.LoadROM(file);

	sf::VertexArray vertices;
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(Chip8::SCREEN_HEIHGT * Chip8::SCREEN_WIDTH * 4);

	for (int i = 0; i < Chip8::SCREEN_WIDTH; ++i)
		for (int j = 0; j < Chip8::SCREEN_HEIHGT; ++j)
		{
			sf::Vertex* quad = &vertices[(i + j * Chip8::SCREEN_WIDTH) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * RATIO, j * RATIO);
			quad[1].position = sf::Vector2f((i + 1) * RATIO, j * RATIO);
			quad[2].position = sf::Vector2f((i + 1) * RATIO, (j + 1) * RATIO);
			quad[3].position = sf::Vector2f(i * RATIO, (j + 1) * RATIO);
		}

	for (int i = 0; i < vertices.getVertexCount(); ++i)
		vertices[i].color = sf::Color::Black;
	
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
		}
		window.draw(vertices);
		window.display();
		vm.AffectTimers();
	}
	

	return 0;
}