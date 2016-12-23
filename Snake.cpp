//Snake.cpp
//--------------------------
// GameProjekt: Snake
// Tkel
// Data: 13.12.2016
//--------------------------
#include "Snake.hpp"

Snake::Snake(unsigned asdf, unsigned fdas)
{
    if(asdf > 10 && fdas > 3)
    {
        for(std::size_t i = 0; i < 6; ++i)
        {
            Point Temp((asdf/2)-(2+i),fdas/2);
            this->Positionen.push_back(Temp);
        }
    }
}

void Snake::Move(char direction)
{
    Point OldPos = this->Positionen[0];
    switch(direction)
    {
        case 'r':
        case 'R':
            ++this->Positionen[0].x;
            break;
        case 'l':
        case 'L':
            --this->Positionen[0].x;
            break;
        case 'u':
        case 'U':
            ++this->Positionen[0].y;
            break;
        case 'd':
        case 'D':
            --this->Positionen[0].y;
            break;
        default:
            std::cout << "Error: direction not valid\n";
            return;
            break;
    }

    if(this->Collision())
    {
        std::cout << "Error: Coolision\n";
        return;
    }

    //grow
    if(this->FoodPos.size() > 0)
    {
        if(this->FoodPos[0] == this->Positionen[this->Positionen.size()-1])
        {
            this->Positionen.push_back(this->FoodPos[0]);
            this->FoodPos.erase(this->FoodPos.begin());
        }
    }

    for(std::size_t i = 1; i < this->Positionen.size(); ++i)
    {
        Point temp = this->Positionen[i];
        this->Positionen[i] =  OldPos;
        OldPos = temp;
    }
}

bool Snake::Collision()
{
    for(std::size_t i = 1; i < this->Positionen.size(); ++i)
    {
        if(this->Positionen[i] == this->Positionen[0])
            return true;
    }
    return false;
}

Point Snake::GetSnakeHead()
{
    return this->Positionen[0];
}

std::vector<Point> Snake::GetSnakePoints()
{
    return this->Positionen;
}

void Snake::eat()
{
    this->FoodPos.push_back(this->Positionen[0]);
}

Point GetRandomEmptyBlock()
{
    std::srand(std::time(0));
    std::vector<Point> EmptyPoints;
    for(std::size_t x = 0; x < 50; ++x)
    {
        for(std::size_t y = 0; y < 50; ++y)
        {
            if(Pixel[x][y].Empty == true)
            {
                Point temp(x,y);
                EmptyPoints.push_back(temp);
            }
        }
    }
    int random = std::rand()%(EmptyPoints.size()-1);
    return EmptyPoints[random];
}
