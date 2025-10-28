#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <windows.h>

#define COLUMNS 10
#define ROWS 20
#define SSIZE 4

namespace Tmpl8
{
	void printGrid(Grid& grid);
	void copyShapeToGrid(Vector2i pos, Shape& shape, Grid* grid);
	Shape rotateShape(Shape& shape);
	void clearGrid(Grid* grid);

	Grid grid = { 0 };
	Grid gridStatic = { 0 };
//	Grid gridStatic = { {
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,0,0,0,0,0,0 },
//	{ 0,0,0,0,1,0,0,0,0,0 },
//	{ 1,1,1,1,1,1,1,1,1,1 }
//} };
	std::array<Shape, 5> standardShapes;

	bool gridToUpdate = false;
	bool tCollided = false;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------



	void Game::Init()
	{
		printGrid(grid);
		standardShapes[0] = { {
								{1,1,0,0},
								{1,1,0,0},
								{0,0,0,0},
								{0,0,0,0}
							} };
		standardShapes[1] = { {
								{1,0,0,0},
								{1,1,0,0},
								{0,1,0,0},
								{0,0,0,0}
							} };
		standardShapes[2] = { {
								{1,0,0,0},
								{1,0,0,0},
								{1,0,0,0},
								{1,0,0,0}
							} };
		standardShapes[3] = { {
								{1,0,0,0},
								{1,0,0,0},
								{1,0,0,0},
								{1,1,0,0}
							} };
		standardShapes[4] = { {
								{1,0,0,0},
								{1,1,0,0},
								{1,0,0,0},
								{0,0,0,0}
							} };

		//Shape newShape = standardShapes[4];
		//copyShapeToGrid(0, 0, newShape, &grid);
		//printGrid(grid);

		//clearGrid(&grid);

		//newShape = rotateShape(newShape);
		//copyShapeToGrid(0, 0, newShape, &grid);

		//printGrid(grid);

		tetromino = Tetromino(standardShapes[4]);

		//printf("%d %d\n", tetromino.getPos().x, tetromino.getPos().y);
		//copyShapeToGrid(tetromino.getPos(), tetromino.getShape(), &grid);

		//printGrid(grid);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------


	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		if (gridToUpdate) {
			clearGrid(&grid);
			copyShapeToGrid(tetromino.getPos(), tetromino.getShape(), &grid);
			gridToUpdate = false;
			printGrid(grid);
		}

		bool tUpdated = tetromino.update(deltaTime, gridStatic, &tCollided);
		
		if (tCollided) {
			tCollided = false;
			gridStatic = grid;
			tetromino.setPos({ rand() % COLUMNS,0});
			tetromino.setShape(standardShapes[rand() % 5]);
		}

		if(tUpdated)
			gridToUpdate = true;
		else 
			tetromino.setPos({ rand() % COLUMNS,tetromino.getPos().y});

	}

	void Game::Shutdown()
	{
	}

	Shape rotateShape(Shape& shape) {
		Shape rotatedShape = { 0 };
		for (int i = 0; i < SSIZE ; i++)
			for (int j = 0; j < SSIZE; j++)
				rotatedShape[i][j] = shape[SSIZE - j - 1][i];
		return rotatedShape;
	}

	void copyShapeToGrid(Vector2i pos, Shape& shape, Grid* grid) {
		for (int i = pos.y, iShape = 0; i < pos.y + SSIZE; i++, iShape++) {
			for (int j = pos.x, jShape = 0; j < pos.x + SSIZE; j++, jShape++) {
				if (i < 0 || i >= ROWS || j < 0 || j >= COLUMNS)
					continue;
				if (shape[iShape][jShape] != 0) {
					(*grid)[i][j] = shape[iShape][jShape];
				}
			}
		}
	}

	void clearGrid(Grid* grid) {
		(*grid) = gridStatic;
	}

	void printGrid(Grid& grid) {
		//system("cls");
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLUMNS; j++)
				printf("%d", grid[i][j]);
			printf("\n");
		}
		printf("\n");
	}
};