#include "game.h"

Game::Game(int board[22][12], unsigned int boardHeight, unsigned int boardWidth, sf::Vector2f blockSize)
{
	this->boardHeight = boardHeight;
	this->boardWidth = boardWidth;

	this->blockSize = blockSize;

	for (int i = 0; i < this->boardHeight; i++) {
		for (int j = 0; j < this->boardWidth; j++) {
			this->board[i][j] = board[i][j];

			if (this->board[i][j] == 1) {
				sf::RectangleShape block = sf::RectangleShape(blockSize);

				float x = blockSize.x * j;
				float y = blockSize.y * i;

				block.setPosition(sf::Vector2f(x, y));
				block.setOutlineThickness(0.5f);
				block.setOutlineColor(sf::Color::Black);

				border.push_back(block);
			}
		}
	}

	speed = 1.0f;
	timer = 1.0f;

	inputBuffer = 0.0f;

	left = false;
	right = false;
	space = false;

	resetTetromino();
}

void Game::update(float dT)
{
	timer += dT * speed;

	// reset board
	for (int i = 1; i < boardHeight - 1; i++) {
		for (int j = 1; j < boardWidth - 1; j++) {
			if (board[i][j] != 1) {
				board[i][j] = 0;
			}
		}
	}

	int y = tetrominoPos.y;
	int x = tetrominoPos.x;

	input(dT, x);
	collsionCheck(x, y);

	if (y < 0) {
		gameOver();
		return;
	}

	bool stopPiece = false;

	for (int i = y; i < y + 4; i++) {
		for (int j = x; j < x + 4; j++) {
			if (i >= 1) {
				if (tetromino.getTetromino()[i - y][j - x] == 2) {
					if (board[i + 1][j] == 1) {
						stopPiece = true;
					}

					board[i][j] = 2;
				}
			}
		}
	}

	//printBoard();

	if ((int)timer >= 1) {
		checkBoard();

		tetrominoPos.y++;

		if (stopPiece) {
			for (int i = y; i < y + 4; i++) {
				for (int j = x; j < x + 4; j++) {
					if (board[i][j] == 2) {
						board[i][j] = 1;
					}
				}
			}

			resetTetromino();
		}

		timer = 0.0f;
	}

	std::list<sf::RectangleShape>::iterator iterator = blocks.begin();

	for (int i = 1; i < boardHeight - 1; i++) {
		for (int j = 1; j < boardWidth - 1; j++) {
			if (board[i][j] != 0) {
				(*iterator).setPosition(sf::Vector2f(j * blockSize.x, i * blockSize.y));
				iterator++;
			}
		}
	}
}

void Game::draw(sf::RenderWindow * window)
{
	for (std::list<sf::RectangleShape>::iterator it = border.begin(); it != border.end(); it++) {
		window->draw(*it);
	}

	for (std::list<sf::RectangleShape>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		window->draw(*it);
	}
}

void Game::input(float dT, int &x) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		speed = 5.0f;
	}
	else {
		speed = 1.0f;
	}

	// move left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !right) {
		left = true;

		if (inputBuffer == 0.0f) {
			x--;
		}

		inputBuffer += dT;

		if (inputBuffer > 0.2f) {
			inputBuffer = 0.0f;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !left) {
		right = true;

		if (inputBuffer == 0.0f) {
			x++;
		}

		inputBuffer += dT;

		if (inputBuffer > 0.2f) {
			inputBuffer = 0.0f;
		}
	}
	else {
		left = false;
		right = false;
		inputBuffer = 0.0f;
	}

	// rotate piece
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!space) {
			tetromino.rotate();
			space = true;
		}
	}
	else {
		space = false;
	}
}

void Game::resetTetromino()
{
	tetromino.setTetromino(&blocks);

	tetrominoPos = sf::Vector2i(boardWidth / 4, 1);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetromino.getTetromino()[i][j] == 2) {
				sf::RectangleShape currentBlock = sf::RectangleShape(blockSize);
				currentBlock.setOutlineThickness(0.5f);
				currentBlock.setOutlineColor(sf::Color::Black);

				blocks.push_back(currentBlock);
			}
		}
	}
}

void Game::collsionCheck(int &x, int &y) {
	for (int j = x; j < x + 4; j++) {
		bool shiftLeft = false;
		bool shiftRight = false;

		for (int i = y; i < y + 4; i++) {
			if (tetromino.getTetromino()[i - y][j - x] == 2) {
				if (j < 1) {	// tetromino block is out of bounds
					shiftRight = true;
				}
				else if (j > 10) {
					shiftLeft = true;
				}
				else {
					if (board[i][j] == 1) {	// target x position is on a block
						if ((int)tetrominoPos.x > x) {	// if moving left
							shiftRight = true;
						}
						else if ((int)tetrominoPos.x < x) {
							shiftLeft = true;
						}
					}
				}
			}
		}

		if (shiftRight) {
			x++;
		}
		else if (shiftLeft) {
			x--;
		}
	}

	tetrominoPos.x = x;

	for (int i = y; i < y + 4; i++) {
		bool shiftUp = false;

		for (int j = x; j < x + 4; j++) {
			if (j > 0 && j < 12) {
				if (tetromino.getTetromino()[i - y][j - x] == 2 && board[i][j] == 1) {
					shiftUp = true;
				}
			}
		}

		if (shiftUp) {
			y--;
		}
	}

	tetrominoPos.y = y;
}

void Game::printBoard() {
	system("CLS");

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 12; j++) {
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}

void Game::checkBoard()
{
	for (int i = 1; i < 21; i++) {
		int count = 0;
		for (int j = 1; j < 11; j++) {
			if (board[i][j] == 1) {
				count++;
			}
		}

		if (count == 10) {
			shiftBoard(i);

			for (int k = 0; k < 10; k++) {
				blocks.pop_back();
			}
		}
	}
}

void Game::shiftBoard(int i)
{
	for (int y = i; y >= 1; y--) {
		for (int x = 1; x < 11; x++) {
			if (y > 1) {
				board[y][x] = board[y - 1][x];
			}
			else {
				board[y][x] = 0;
			}
		}
	}
}

void Game::gameOver()
{
	for (int i = 1; i < boardHeight - 1; i++) {
		for (int j = 1; j < boardWidth - 1; j++) {
			if (board[i][j] != 0) {
				board[i][j] = 0;
			}
		}
	}
	
	int n = blocks.size();

	for (int i = 0; i < n; i++) {
		blocks.pop_back();
	}

	resetTetromino();
}
