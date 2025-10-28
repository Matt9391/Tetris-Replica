#include "Structures.h"

#pragma once
namespace Tmpl8 {

	class Tetromino
	{
	public:
		Tetromino() = default;
		Tetromino(Shape& shape);

		bool update(float dt, Grid& grid, bool* collided);

		Vector2i getPos();
		Shape getShape();
		
		void setPos(Vector2i newPos);
		void setShape(Shape& shape);
		
	private:
		bool collideWithStaticGrid(Grid& gridStatic);

		Vector2i pos;
		Vector2i npos;
		Shape shape;

		float timer;
		float elapsedTime;
	};

}
