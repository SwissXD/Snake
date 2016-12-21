//Snake.hpp
//--------------------------
// GameProjekt: Snake
// Tkel
// Data: 13.12.2016
//--------------------------

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>



struct Point
{
    unsigned x;
    unsigned y;
    Point(unsigned X, unsigned Y): x(X),y(Y)
    {}
    Point(): x(0),y(0)
    {}

    bool operator== (Point const& Rhs) const
    {
        return this->x == Rhs.x && this->y == Rhs.y;
    }
};


struct Block
{
    bool SnakeHead;
    bool SnakeBody;
    bool Food;
    bool Empty;
    Block():SnakeHead(false),SnakeBody(false),Food(false),Empty(true)
    {}
};

Block Pixels[50][50];

class Snake
{
    private:
        std::vector<Point> Positionen;
        std::vector<Point> FoodPos;

    public:
        Snake(unsigned, unsigned);
        void Move(char);
        bool Collision();
        Point GetSnakeHead();
        std::vector<Point> GetSnakePoints();
        void eat();
};

Point GetRandomEmptyBlock();
