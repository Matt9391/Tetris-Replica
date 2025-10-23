#include "Tetromino.h"

namespace Tmpl8 {


	Tetromino::Tetromino(Shape& shape) :
		shape(shape),
		pos({ 3,0 }),
		timer(200),
		elapsedTime(0),
		npos(pos)
	{}

	bool Tetromino::update(float dt, Grid& grid) {
		elapsedTime += dt;
		if (elapsedTime < timer)
			return false;
			
		
		this->npos = pos;
		this->npos.y++;

		if(!collideWithStaticGrid(grid)){
			this->pos = this->npos;
			printf("Y: %d\n", this->pos.y);
		}

		elapsedTime = 0;
		return true;
	

	}

	bool Tetromino::collideWithStaticGrid(Grid& gridStatic) {
		if (this->npos.y >= ROWS)
			return true;

		for (int i = this->npos.y, iShape = 0; i < this->npos.y + SSIZE; i++, iShape++) {
			for (int j = this->npos.x, jShape = 0; j < this->npos.x + SSIZE; j++, jShape++) {
				if (shape[iShape][jShape] == 0)
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

	
}