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
	    auto it = Parts.begin();
        switch(Direction)
        {
        case Cardinals::Top:
            1//it = Parts.insert(it,(Parts[0].x,Parts[0].y+1));
            2//Parts.insert(Parts.begin(),(Parts[0].x,Parts[0].y+1));
            3//Parts.emplace(Parts.begin(),(Parts[0].x,Parts[0].y+1));
            break;
        case Cardinals::Right:
            it = Parts.insert(it,(Parts[0].x+1,Parts[0].y));
            break;
        case Cardinals::Bottom:
            it = Parts.insert(it,(Parts[0].x,Parts[0].y-1));
            break;
        case Cardinals::Left:
            it = Parts.insert(it,(Parts[0].x-1,Parts[0].y));
            break;
        default:
            assert(false);
        }
        Parts.erase(Parts.end());
	}
};

class Game
{
	enum
	{
		mWidth = 50,
		mHeight = 50,
	};

	Snake mSnake;

	std::minstd_rand mEngine{ std::random_device{}() };
	std::uniform_int_distribution<std::size_t> mXDist{ 0, mWidth - 1 };
	std::uniform_int_distribution<std::size_t> mYDist{ 0, mHeight - 1 };
	Point mFood;

protected:
	void GenerateFood()
	{
		for (;;)
		{
			mFood.x = mXDist(mEngine);
			mFood.y = mYDist(mEngine);
			if (std::find(std::begin(mSnake.Parts), std::end(mSnake.Parts), mFood) == std::end(mSnake.Parts))
				break;
		}
	}

    bool Collision()
	{
	    Point newPos(mSnake.Parts[0].x,mSnake.Parts[0].y)
	    switch(mSnake.Direction)
	    {
        case Cardinals::Top:
            ++newPos.y;
            break;
        case Cardinals::Right:
            ++newPos.x;
            break;
        case Cardinals::Bottom:
            --newPos.y;
            break;
        case Cardinals::Left:
            --newPos.x;
            break;
        default:
            assert(false);
	    }

	    if(mSnake.Parts.end() != std::find(mSnake.Parts.begin(),mSnake.Parts.begin(),newPos))
            return true;//collision

        return false;//no collision
	}

	bool SnakeEat()
	{
	    if(this->Snake.Parts[0] == this->mFood)
            return true;
        else
            return false;
	}

public:
	Game()
	{
		for (std::size_t i = 0; i < 5; ++i)
			mSnake.Parts.emplace_back(mWidth / 2 - i, mHeight / 2);
		mSnake.Direction = Cardinals::Right;

		GenerateFood();
	}

};
