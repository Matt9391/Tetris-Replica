#include "Tetromino.h"
#include <Windows.h>
namespace Tmpl8 {
	Shape rotateShape(Shape& shape) {
		Shape rotatedShape = { 0 };
		for (int i = 0; i < SSIZE; i++)
			for (int j = 0; j < SSIZE; j++)
				rotatedShape[i][j] = shape[SSIZE - j - 1][i];
		return rotatedShape;
	}

	int getRandomInt(int min, int max)
	{
		static std::random_device rd;  // seme casuale
		static std::mt19937 gen(rd()); // generatore Mersenne Twister

		std::uniform_int_distribution<> dis(min, max); // range [min,max]
		return dis(gen);
	}

	Tetromino::Tetromino(const Shape& shape) :
		shape(shape),
		nextShape(shape),
		pos({ 3,0 }),
		timer(2000),
		defaultTimer(2000),
		fastTimer(200),
		elapsedTime(0),
		npos(pos),
		lastKey(' '),
		color(getRandomInt(1, 8))
	{
		//randomize color
		for (int i = 0; i < SSIZE; i++) {
			for (int j = 0; j < SSIZE; j++) {
				if (this->shape[i][j] != 0)
					this->shape[i][j] = this->color;
			}
		}

	}

	bool Tetromino::update(float dt, Grid& grid, bool* collided) {
		bool xMove = false, yMove = false;
		if (GetAsyncKeyState('Q') & 0x8000) {
			this->timer = this->fastTimer;
		}
		else {
			this->timer = this->defaultTimer;
		}

		xMove = this->move(grid);

		elapsedTime += dt;
		if (elapsedTime < timer) {
			yMove = false;
		}
		else {
			this->npos = pos;
			this->npos.y++;

			if(!collideWithStaticGrid(grid)){
				this->pos = this->npos;
				printf("Y: %d\n", this->pos.y);
			}
			else {
				(*collided) = true;
			}
		

			elapsedTime = 0;
			yMove = true;
		}
		
		return xMove || yMove;

	}

	bool Tetromino::move(Grid& gridStatic) {
		char input = ' ';
		if (GetAsyncKeyState('A') & 0x8000) input = 'a';
		if (GetAsyncKeyState('D') & 0x8000) input = 'd';
		if (GetAsyncKeyState('R') & 0x8000) input = 'r'; 
		if (lastKey == input)
			return false;

		lastKey = input;
		bool shapeRotated = false;
		this->nextShape = this->shape;

		if (input == 'a') {
			this->npos = this->pos;
			this->npos.x--;
		}
		else if (input == 'd') {
			this->npos = this->pos;
			this->npos.x++;
		}
		else if (input == 'r') {
			this->nextShape = rotateShape(nextShape);
			shapeRotated = true;
		}

		if (collideWithStaticGrid(gridStatic)) {

			if (shapeRotated) {
				this->nextShape = this->shape;
			}
			return false;
		}

		bool canMove = true;

		for (int i = this->npos.y, iShape = 0; i < this->npos.y + SSIZE; i++, iShape++) {
			for (int j = this->npos.x, jShape = 0; j < this->npos.x + SSIZE; j++, jShape++) {
				if (this->nextShape[iShape][jShape] == 0)
					continue;

				if (j < 0 || j > COLUMNS - 1) {
					canMove = false;
					break;
				}
			}
		}

		if (canMove) {
			this->pos = this->npos;
			if (shapeRotated) {
				this->shape = nextShape;
			}
			return true;
		}

		return false;
	}

	bool Tetromino::collideWithStaticGrid(Grid& gridStatic) {

		for (int i = this->npos.y, iShape = 0; i < this->npos.y + SSIZE; i++, iShape++) {
			for (int j = this->npos.x, jShape = 0; j < this->npos.x + SSIZE; j++, jShape++) {
				if (this->nextShape[iShape][jShape] == 0)
					continue;
				if (i < 0 || j < 0 || j >= COLUMNS)
					continue;
				if(i >= ROWS)
					return true;

				if (gridStatic[i][j] != 0) {
					return true;
				}

			}
		}

		return false;
	}

	Vector2i Tetromino::getPos() {
		return this->pos;
	}

	Shape Tetromino::getShape() {
		return this->shape;
	}

	void Tetromino::setPos(Vector2i newPos) {
		this->pos = newPos;
	}
	void Tetromino::setShape(Shape& newShape) {
		this->shape = newShape;
	}

	
}