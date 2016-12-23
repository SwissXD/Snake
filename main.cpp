//main.cpp
//--------------------------
// GameProjekt: Snake
// Tkel
// Data: 13.12.2016
//--------------------------

#include "Snake.hpp"

int main()
{
    Snake mySnake(50,50);

    unsigned i = 0;
    for(std::size_t x = 0; x < 50; ++x)
    {
        for(std::size_t y = 0; y < 50; ++y)
        {
            if(mySnake.Positionen[i] == Point(x,y) && i < mySnake.Positionen.size()-1)
            {
                if(i == 0)
                {
                    Pixel[x][y] = Block::SnakeHead;
                }
                else
                {
                    Pixel[x][y] = Block::SnakeBody;
                }
                ++i;
            }
        }
    }

    Point food = GetRandomEmptyBlock();
    Pixel[food.x][food.y] = Block::Food;
}
