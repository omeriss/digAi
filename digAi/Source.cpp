#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <math.h>
#include <algorithm>
#include "DrawingBoard.h"


/*
FILE* f;


void OpenFile() {
    f = fopen("td.idx3-ubyte", "rb");
    fseek(f, 16, SEEK_SET);
}

void readf() {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            Matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            bool n;
            fread(&n, 1, 1, f);
            Matrix[i][j] = (float)n/255;
        }
    }
}
*/


int main()
{
    int lastx = -1, lasty = -1;

    DrawingBoard* board = new DrawingBoard();

    sf::RenderWindow window(sf::VideoMode(ScreenSize, ScreenSize), "dig");
    window.setFramerateLimit(60);

    if(UploadFile == "0")
        board->InsertInput(TrainData, TrainLable, 1);
    board->InsertInput(TestData, TestLable, 0);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int xx = sf::Mouse::getPosition(window).x;
            int yy = sf::Mouse::getPosition(window).y;
            board->SetCell(xx, yy);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            cout<<board->GetNum()<<endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            board->ClearBoard();
        }
        window.clear();
        board->DrawBoard(&window);
        window.display();
    }

    //fclose(f);
    return 0;
}