#include "Tetromino.h"
#include <Windows.h>
namespace Tmpl8 {

	//function that rotate any shape by 90 degrees clockwise
	Shape rotateShape(Shape& shape) {
		Shape rotatedShape = { 0 };
		for (int i = 0; i < SSIZE; i++)
			for (int j = 0; j < SSIZE; j++)
				rotatedShape[i][j] = shape[SSIZE - j - 1][i];
		return rotatedShape;
	}

	//random number generator
	int getRandomInt(int min, int max)
	{
		static std::random_device rd;  
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<> dis(min, max); // range [min,max]
		return dis(gen);
	}

	Tetromino::Tetromino(const Shape& shape) :
		shape(shape),
		nextShape(shape),
		pos({ 3,0 }),
		timer(500),
		defaultTimer(500),
		fastTimer(80),
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
		//variables used to give a feedback if the piece moved
		bool xMove = false, yMove = false;
		if (GetAsyncKeyState('Q') & 0x8000) { //hold 'Q' to fall faster
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
			//calculate next position
			this->npos = pos;
			this->npos.y++;

			//if next position is valid (return false) the piece moves
			if(!collideWithStaticGrid(grid)){
				this->pos = this->npos;
			}
			else {
				//feedback variable to update the static grid
				(*collided) = true;
			}
		

			elapsedTime = 0;
			yMove = true;
		}
		
		return xMove || yMove;

	}

	bool Tetromino::move(Grid& gridStatic) {
		//read user input
		char input = ' ';
		if (GetAsyncKeyState('A') & 0x8000) input = 'a';
		if (GetAsyncKeyState('D') & 0x8000) input = 'd';
		if (GetAsyncKeyState('R') & 0x8000) input = 'r'; 
		if (lastKey == input) //prevent holding key
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

		//logic to keep the piece in bounds 
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

		//logic that check if the piece collides with the grid/other pieces
		for (int i = this->npos.y, iShape = 0; i < this->npos.y + SSIZE; i++, iShape++) {
			for (int j = this->npos.x, jShape = 0; j < this->npos.x + SSIZE; j++, jShape++) {
				if (this->nextShape[iShape][jShape] == 0) //ignore 0 values
					continue;
				if (i < 0 || j < 0 || j >= COLUMNS) //if it's not 0 then check if it is bound
					continue;
				if(i >= ROWS)
					return true;

				if (gridStatic[i][j] != 0) { //check if it collide with the grid
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