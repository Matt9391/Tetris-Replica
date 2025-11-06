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
	//------------------------------------------------------
	//-------------------GAME CONTROLS----------------------
	// A - D -> Move sideways
	// Hold Q -> Move down faster
	// R -> Rotate the tetromino
	//------------------------------------------------------

	//method that print the grind in the console
	void printGrid(Grid& grid);
	//method that copy any given shape to the grid
	void copyShapeToGrid(Vector2i pos, Shape& shape, Grid* grid);
	//method that clears the grid
	void clearGrid(Grid* grid);
	//function that delete a line if it's full
	bool deleteFullLines(Grid* gridStatic);
	//method that print the grid on the screen
	void drawGrid(Surface* screen, Grid& grid, Grid& tetrominoGrid);

	Grid grid = { 0 };
	Grid gridStatic = { 0 };

	Sprite tilesFrames(new Surface("assets/tetris-Sheet.tga"), 9);

	std::array<Shape, 5> standardShapes;

	bool gridToUpdate = true;
	bool tCollided = false; //has the tetromino collided
	int score = 0;

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


		tetromino = Tetromino(standardShapes[getRandomInt(0, 4)]);

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
			tetromino = Tetromino(standardShapes[getRandomInt(0, 4)]);
			grid = { 0 };
		}

		bool linesDeleted = deleteFullLines(&gridStatic);
		if (linesDeleted)
			score++;

		if(tUpdated || linesDeleted)
			gridToUpdate = true;

		screen->Clear(0);
		drawGrid(screen,gridStatic, grid);
		char textScore[32]; // buffer sicuro
		snprintf(textScore, sizeof(textScore), "%d", score);
		screen->Print(textScore, 32 * COLUMNS / 2, 32, 0xffffff);

	}

	void Game::Shutdown()
	{
	}

	void drawGrid(Surface* screen, Grid& staticGrid, Grid& tetrominoGrid) {
		int tileSize = 32;

		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLUMNS; j++) {
				int value = tetrominoGrid[i][j];
				tilesFrames.SetFrame(value);
				tilesFrames.Draw(screen, tileSize * j, tileSize * i);
			}
		}

	}

	bool deleteFullLines(Grid* gridStatic) {
		bool linesDeleted = false;
		for (int i = 0; i < ROWS; i++) {
			bool full = true;
			//checks if all the line is filled with values != from 0
			for (int j = 0; j < COLUMNS; j++) {
				if ((*gridStatic)[i][j] == 0) {
					full = false;
					break;
				}
			}
			//if it's full then it copies each line above 1 row below
			//and set the first to 0
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