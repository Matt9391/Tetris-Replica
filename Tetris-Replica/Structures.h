#include <array>

#define COLUMNS 10
#define ROWS 20
#define SSIZE 4

namespace Tmpl8 {

	using Grid = std::array<std::array<int, COLUMNS>, ROWS>;
	using Shape = std::array<std::array<int, SSIZE>, SSIZE>;

	struct Vector2i {
		int x, y;
	};
};