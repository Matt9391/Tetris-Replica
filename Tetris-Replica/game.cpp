#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <windows.h>
#include <array>

#define COLUMNS 10
#define ROWS 20
#define SSIZE 4

namespace Tmpl8
{
	using Grid = std::array<std::array<int, COLUMNS>, ROWS>;
	using Shape = std::array<std::array<int, SSIZE>, SSIZE>;
	void printGrid(Grid& grid);
	void copyShapeToGrid(int x, int y, Shape& shape, Grid* grid);
	Shape rotateShape(Shape& shape);
	void clearGrid(Grid* grid);

	Grid grid = { 0 };
	std::array<Shape, 5> standardShapes;

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

		Shape newShape = standardShapes[4];
		copyShapeToGrid(0, 0, newShape, &grid);
		printGrid(grid);

		clearGrid(&grid);

		newShape = rotateShape(newShape);
		copyShapeToGrid(0, 0, newShape, &grid);

		printGrid(grid);

	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------


	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
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

	void copyShapeToGrid(int x, int y, Shape& shape, Grid* grid) {
		for (int i = y; i < SSIZE; i++) {
			for (int j = x; j < SSIZE; j++) {
				if (shape[i][j] != 0) {
					(*grid)[i][j] = shape[i][j];
				}
			}
		}
	}

	void clearGrid(Grid* grid) {
		(*grid) = { 0 };
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