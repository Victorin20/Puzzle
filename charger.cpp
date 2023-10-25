#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// 4x5

    const int squareSize(100);
    const int space(10);
    const int squaresHorizontal(6);
    const int squaresVertical(6);
    const int width(squaresHorizontal * squareSize + (squaresHorizontal-1) * space);
    const int heigth(squaresVertical * squareSize + (squaresVertical-1) * space);
    const int squaresH = width / squareSize;
    const int squaresV = heigth / squareSize;

int checkIfClicked(Sprite squares[], Vector2i pos)
{
    for (int k(0); k < squaresH * squaresV; k++)
    {
        if (pos.x >= k % squaresH * squareSize + k % squaresH * space && pos.x <= k % squaresH * squareSize + k % squaresH * space + squareSize && pos.y >= k / squaresH * squareSize + k / squaresH * space && pos.y <= k / squaresH * squareSize + k / squaresH * space + squareSize)
        {
            return k;
        }
                  
    }
    return 0;
}


int main()
{

    sf::RenderWindow window(sf::VideoMode(width, heigth), "Square");

    Texture texture, emptyTexture;
    texture.loadFromFile("images/parrot.jpg");
    emptyTexture.loadFromFile("images/empty.jpg");

    Sprite* squares = new Sprite[squaresH * squaresV];

    int table[squaresH * squaresV];

    for (int k(0); k < squaresH * squaresV; k++)
    {
        if (k < squaresH * squaresV - 1)table[k] = 1;
        else table[k] = 0;
    }

    for (int k(0); k < squaresH*squaresV; k++)
    {       
            squares[k].setTexture(texture);
            if (k != squaresH * squaresV - 1)squares[k].setTextureRect(IntRect(k % squaresH * squareSize, k / squaresH * squareSize, squareSize, squareSize));
            if(k % squaresH == 0)squares[k].setPosition(k % squaresH * squareSize, k / squaresH * squareSize);
            if(k % squaresH != 0)squares[k].setPosition(k % squaresH * squareSize + k % squaresH * space, k / squaresH * squareSize);
            if(k / squaresH > 0)squares[k].setPosition(k % squaresH * squareSize + k % squaresH * space, k / squaresH * squareSize +k / squaresH * space);
            if (k == squaresH * squaresV - 1)
            {
                squares[k].setTexture(emptyTexture);
                squares[k].setTextureRect(IntRect(0, 0, squareSize, squareSize));
                squares[k].setPosition(k % squaresH * squareSize + k % squaresH * space, k / squaresH * squareSize + k / squaresH * space);
            }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Vector2i pos = Mouse::getPosition(window);

        int c = checkIfClicked(squares, pos);
        int x = c % squaresH;
        int y = c / squaresH;
        if (event.type == Event::MouseButtonPressed)
        {

            if (table[c - 1] == 0)
            {
                table[c - 1] = 1;
                table[c] = 0;    

                Sprite tmp = squares[c - 1];
                squares[c].setPosition((x - 1)* squareSize + (c-1) % squaresH  * space, y * squareSize + c / squaresH * space); 
                squares[c - 1].setPosition(x * squareSize + (c-1) % squaresH * space, y * squareSize + c / squaresH * space);
                squares[c - 1] = squares[c];
                squares[c] = tmp;
               
            }
            if (table[c + 1] == 0)
            {
                table[c + 1] = 1;
                table[c] = 0;
                Sprite tmp = squares[c + 1];
               
                squares[c].setPosition((x + 1) * squareSize + (c+1) % squaresH * space, y * squareSize + c / squaresH * space);
                squares[c+1].setPosition(x * squareSize + (c+1) % squaresH * space, y * squareSize + c / squaresH * space);
                squares[c + 1] = squares[c];
                squares[c] = tmp;
            }

            if (table[c + squaresH] == 0)
            {
                table[c + squaresH] = 1;
                table[c] = 0;
                Sprite tmp = squares[c + squaresH];

                squares[c].setPosition(x * squareSize + c % (squaresH ) *space, (y+1) * squareSize + ((c / squaresH)+1) * space);
                squares[c + squaresH].setPosition(x * squareSize + c % (squaresH ) *space, (y-1) * squareSize + ((c / squaresH)+1) * space);
                squares[c + squaresH] = squares[c];
                squares[c] = tmp;
            }

            if (table[c - squaresH] == 0)
            {
                table[c - squaresH] = 1;
                table[c] = 0;
                Sprite tmp = squares[c - squaresH];

                squares[c].setPosition(x * squareSize + c % (squaresH) *space, (y - 1) * squareSize + ((c  / squaresH)-1) * space);
                squares[c - squaresH].setPosition(x * squareSize + c % (squaresH) *space, (y + 1) * squareSize + ((c / squaresH)-1) * space);
                squares[c - squaresH] = squares[c];
                squares[c] = tmp;
            }

        }
       

        window.clear();
       
        for (int k(0); k < squaresH * squaresV; k++)
        {
           window.draw(squares[k]);
        }

        window.display();
    }

    delete[] squares;

    return 0;
}