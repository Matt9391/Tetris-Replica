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
	void clearGrid(Grid* grid);
	bool deleteFullLines(Grid* gridStatic);

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

		tetromino = Tetromino(standardShapes[2]);

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
			tetromino.setPos({ 3,0 });
			tetromino.setShape(standardShapes[rand() % 5]);
		}

		bool linesDeleted = deleteFullLines(&gridStatic);

		if(tUpdated || linesDeleted)
			gridToUpdate = true;

	}

	void Game::Shutdown()
	{
	}

	bool deleteFullLines(Grid* gridStatic) {
		bool linesDeleted = false;
		for (int i = 0; i < ROWS; i++) {
			bool full = true;
			for (int j = 0; j < COLUMNS; j++) {
				if ((*gridStatic)[i][j] == 0) {
					full = false;
					break;
				}
			}
			if (full) {
				linesDeleted = true;
				for (int ii = i; ii > 0; ii--) {
					for (int j = 0; j < COLUMNS; j++) {
						(*gridStatic)[ii][j] = (*gridStatic)[ii - 1][j];
					}
					(*gridStatic)[0] = { 0 };
				}
			}
		}
		return linesDeleted;
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