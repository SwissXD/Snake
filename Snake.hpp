//Snake.hpp
//--------------------------
// GameProjekt: Snake
// Tkel
// Data: 13.12.2016
//--------------------------

#include <algorithm>
#include <cstdlib>
#include <ostream>
#include <array>
#include <cassert>
#include <random>

struct Point
{
    std::size_t x;
    std::size_t y;
    Point(std::size_t X, std::size_t Y): x(X),y(Y)
    {}
    Point(): Point{ 0, 0 }
    {}
};

inline bool operator== (Point const& Lhs, Point const& Rhs)
{
	return Lhs.x == Rhs.x && Lhs.y == Rhs.y;
}
inline bool operator!= (Point const& Lhs, Point const& Rhs)
{
	return !(Lhs == Rhs);
}

enum class Cardinals
{
	Top,
	Right,
	Bottom,
	Left
};

struct Snake
{
	std::vector<Point> Parts;
	Cardinals Direction;

	bool Propagate()
	{

	}
};

class Game
{
	enum
	{
		mWidth = 50,
		mHeight = 50,
	};

	Snake snake;

	std::minstd_rand mEngine{ std::random_device{}() };
	std::uniform_int_distribution<std::size_t> mXDist{ 0, mWidth - 1 };
	std::uniform_int_distribution<std::size_t> mYDist{ 0, mHeight - 1 };
	Point Food;

protected:
	void GenerateFood()
	{
		for (;;)
		{
			Food.x = mXDist(mEngine);
			Food.y = mYDist(mEngine);
			if (std::find(std::begin(snake.Parts), std::end(snake.Parts), Food) == std::end(snake.Parts))
				break;
		}
	}

public:
	Game()
	{
		for (std::size_t i = 0; i < 5; ++i)
			snake.Parts.emplace_back(mWidth / 2 - i, mHeight / 2);
		snake.Direction = Cardinals::Right;

		GenerateFood();
	}
};
