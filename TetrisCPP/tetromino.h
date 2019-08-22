#pragma once
#include <list>
#include <iterator>
#include "SFML\Graphics.hpp"

class Tetromino {
public:
	Tetromino();
	Tetromino(std::list<sf::RectangleShape> * blocks);
	void setTetromino(std::list<sf::RectangleShape> * blocks);
	void update();
	void rotate();
	int ** getTetromino() { return tetromino; }
private:
	sf::Vector2i piecePosition;

	const int tetrominos[7][4][4] = {
		// I
		{
			{ 0, 0, 2, 0 },
			{ 0, 0, 2, 0 },
			{ 0, 0, 2, 0 },
			{ 0, 0, 2, 0 }
		},

		// O
		{
			{ 0, 0, 0, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 0, 0 }
		},

		// Z
		{
			{ 0, 0, 0, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 2, 2 },
			{ 0, 0, 0, 0 }
		},

		// S
		{
			{ 0, 0, 0, 0 },
			{ 0, 0, 2, 2 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 0, 0 }
		},

		// T
		{
			{ 0, 0, 0, 0 },
			{ 2, 2, 2, 0 },
			{ 0, 2, 0, 0 },
			{ 0, 0, 0, 0 }
		},

		// L
		{
			{ 0, 2, 0, 0 },
			{ 0, 2, 0, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 0, 0 }
		},

		// J
		{
			{ 0, 0, 2, 0 },
			{ 0, 0, 2, 0 },
			{ 0, 2, 2, 0 },
			{ 0, 0, 0, 0 }
		},
	};

	int * tetromino[4];
};