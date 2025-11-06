#include "Structures.h"

#pragma once
namespace Tmpl8 {

	class Tetromino
	{
	public:
		Tetromino() = default;
		Tetromino(const Shape& shape);

		bool update(float dt, Grid& grid, bool* collided);

		//getters
		Vector2i getPos();
		Shape getShape();
		
		//setters
		void setPos(Vector2i newPos);
		void setShape(Shape& shape);
		
	private:
		//function that check if the Tetromino collide with the grid
		bool collideWithStaticGrid(Grid& gridStatic);
		//function used to move the Tetromino based on user inputs
		bool move(Grid& gridStatic);

		Vector2i pos;    //position
		Vector2i npos;	 //next position
		Shape shape;	 //matrix shape
		Shape nextShape; //next matrix shape (if rotated)

		char lastKey;    //to prevent user from holding key issues

		float timer;		//time needed to move down
		float defaultTimer; //default time needed
		float fastTimer;	//fast time needed
		float elapsedTime;

		int color;
	};

}
