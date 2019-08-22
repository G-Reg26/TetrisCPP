#include "tetromino.h"

Tetromino::Tetromino()
{
	for (int i = 0; i < 4; i++) {
		tetromino[i] = new int[4];
	}
}

Tetromino::Tetromino(std::list<sf::RectangleShape> * blocks)
{
	Tetromino();
	setTetromino(blocks);
}

void Tetromino::setTetromino(std::list<sf::RectangleShape> * blocks)
{
	// set random piece from pieces
	srand(time(NULL));

	int pieceID = rand() % 7;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tetromino[i][j] = tetrominos[pieceID][i][j];
		}
	}
}

void Tetromino::update()
{
}


void Tetromino::rotate()
{
	int n = sizeof(tetromino) / sizeof(tetromino[0]);

	for (int i = 0; i < n / 2; i++) {
		for (int j = i; j < n - 1 - i; j++) {
			int temp = tetromino[i][j];
			tetromino[i][j] = tetromino[n - j - 1][i];// SET TOP edge to LEFT edge elements 
			tetromino[n - j - 1][i] = tetromino[n - i - 1][n - j - 1];// SET LEFT edge to BOTTOM edge elements
			tetromino[n - i - 1][n - j - 1] = tetromino[j][n - i - 1];// SET BOTTOM edge to RIGHT edge elements
			tetromino[j][n - i - 1] = temp;// SET RIGHT edge to TOP edge elements
		}
	}
}
