//Snake.hpp
//--------------------------
// GameProjekt: Snake
// Tkel
// Data: 13.12.2016
//--------------------------

#include <iostream>
#include <vector>

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

Block Pixles[50][50];

class Snake
{
    private:
        std::vector<Point> Positionen;

    public:
        Snake(unsigned PixelsX, unsigned PixelsY)
        {
            if(PixelsX > 10 && PixelsY >3)
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
};
