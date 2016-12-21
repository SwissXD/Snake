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

Block Pixles[50][50];

struct Point
{
    unsigned x;
    unsigned y;
    Punkt(unsigned X, unsigned Y): x(X),y(Y)
    {}
    Punkt(): x(0),y(0)
    {}
};

struct Block
{
    bool SnakeHead;
    bool SnakeBody;
    bool Food;
    bool Empty;
    Feld():SnakeHead(false),SnakeBody(false),Food(false),Empty(true)
    {}
};

class Snake
{
    private:
        std::vector<Point> Positionen;
        std::vector<Point> FoodPos;

    public:
        Snake(unsigned PixelsX, unsigned PixelsY)
        {
            if(PixelsX > 10 && PixelsY > 3)
            {
                for(std::size_t i = 0; i < 6; ++i)
                {
                    Point Temp((PixelsX/2)-(2+i),PixelsY/2);
                    this->Positionen.push_back(Temp);
                }
            }
        }

        void Move(char direction)
        {
            Point OldPos = this->Positionen[0];
            switch(direciton)
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
                    std::cout << "Error: direciton not valid\n"
                    return;
                    break;
            }

            if(this->Collision())
            {
                std::cout << "Error: Coolision"
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

        bool Collision()
        {
            for(std::size_t i = 1; i < this->Positionen.size(); ++i)
            {
                if(this->Position[i] == this->Position[0])
                    return true;
            }
            return false;
        }

        Point GetSnakeHead()
        {
            return this->Positionen[0];
        }

        std::vector<Point> GetSnakePoints()
        {
            return this->Positionen;
        }

        void eat()
        {
            this->FoodPos.push_back(this->Positionen[0]);
        }
};

Point GetRandomEmptyBlock()
{
    std::srand(std::time(0));
    std::vector EmptyPoints;
    for(std::size_t x = 0; x < 50; ++x)
    {
        for(std::size_t y = 0; y < 50; ++y)
        {
            if(Pixles[x][y] == Block::Empty)
            {
                Point temp(x,y);
                EmptyPoints.push_back(Point);
            }
        }
    }
    unsigned random = std::rand%(EmptyPoints.size()-1);
    return EmptyPoints[random];
}
