#pragma once
#include <iostream>
#include <list>
#include <iterator>
#include "SFML\Graphics.hpp"
#include "tetromino.h"

class Game {
public:
	Game(int board[22][12], unsigned int boardHeight, unsigned int boardWidth, sf::Vector2f blockSize);
	void update(float dT);
	void draw(sf::RenderWindow * window);
private:
	Tetromino tetromino;

	std::list<sf::RectangleShape> border;
	std::list<sf::RectangleShape> blocks;

	int board[22][12];

	int boardWidth;
	int boardHeight;

	sf::Vector2f blockSize;
	sf::Vector2i tetrominoPos;

	float speed;
	float timer;

	float inputBuffer;

	bool left;
	bool right;
	bool space;

	void resetTetromino();
	void input(float dT, int &x);
	void collsionCheck(int &x, int &y);
	void printBoard();
	void checkBoard();
	void shiftBoard(int i);
	void gameOver();
};