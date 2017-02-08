//Snake.hpp
//--------------------------
// GameProjekt: Snake
// Tkel
// Data: 13.12.2016
//--------------------------

#ifndef Snake_hpp_included
#define Snake_hpp_included

#include <algorithm>
#include <cstdlib>
#include <ostream>
#include <array>
#include <cassert>
#include <random>
#include <chrono>

#include <SFML/Graphics.hpp>

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

enum class Cardinals : int
{
	Top,
	Right,
	Bottom,
	Left
};

class Snake : public sf::Drawable
{
public:
	std::vector<Point> Parts;
	Cardinals Direction;

protected:
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override
	{
		static const double Margin = 0.1;

		sf::RectangleShape Shape;
		Shape.setFillColor(sf::Color::Green);
		Shape.setSize({ 1 - 2 * Margin, 1 - 2 * Margin });
		for(auto&& i : Parts)
		{
			Shape.setPosition(i.x + Margin, i.y + Margin);
			Target.draw(Shape, States);
		}
	}

public:
	Point NextPosition() const
	{
		Point Head = Parts.front();
		switch(Direction)
		{
		case Cardinals::Top:
			--Head.y;
			break;
		case Cardinals::Right:
			++Head.x;
			break;
		case Cardinals::Bottom:
			++Head.y;
			break;
		case Cardinals::Left:
			--Head.x;
			break;
		default:
			assert(false);
		}
		return Head;
	}

	void Propagate()
	{
		Parts.insert(Parts.begin(), NextPosition());
	}
	void Shrink()
	{
		Parts.pop_back();
	}

	void Move()
	{
		Propagate();
		Shrink();
	}

	bool ChangeDirection(Cardinals NewDirection)
	{
		if((static_cast<int>(NewDirection) + 2) % 4 == static_cast<int>(Direction))
			return false;

		Direction = NewDirection;
		return true;
	}
};

class Game : public sf::Drawable
{
	enum
	{
		mWidth = 50,
		mHeight = 50,
	};

	Snake mSnake;

	std::minstd_rand mEngine{ std::chrono::steady_clock::now().time_since_epoch().count() };
	std::uniform_int_distribution<std::size_t> mXDist{ 0, mWidth - 1 };
	std::uniform_int_distribution<std::size_t> mYDist{ 0, mHeight - 1 };
	Point mFood;

	bool mRunning = true;

protected:
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override
	{
		Target.draw(mSnake, States);

		sf::RectangleShape Shape;
		Shape.setFillColor(sf::Color::Red);
		Shape.setSize({ 1, 1 });
		Shape.setPosition(mFood.x, mFood.y);
		Target.draw(Shape, States);
	}

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

	bool Collision() const
	{
		return std::find(mSnake.Parts.begin(),mSnake.Parts.end(), mSnake.NextPosition()) != mSnake.Parts.end();
	}

	bool HitFood() const
	{
		return mSnake.NextPosition() == mFood;
	}

public:
	Game()
	{
		for (std::size_t i = 0; i < 5; ++i)
			mSnake.Parts.emplace_back(mWidth / 2 - i, mHeight / 2);
		mSnake.Direction = Cardinals::Right;

		GenerateFood();
	}

	unsigned int Width() const
	{
		return mWidth;
	}
	unsigned int Height() const
	{
		return mHeight;
	}

	void Tick()
	{
		if(Running())
		{
			if(Collision())
			{
				mRunning = false;
				return;
			}
			if(HitFood())
			{
				mSnake.Propagate();
				GenerateFood();
			}
			else
			{
				mSnake.Move();
			}
		}
	}

	void ChangeDirection(Cardinals NewDirection)
	{
		mSnake.ChangeDirection(NewDirection);
	}

	bool Running() const
	{
		return mRunning;
	}
};

#endif // !Snake_hpp_included
