#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "NeuralNetwork.h"


class DrawingBoard
{
public:
	DrawingBoard();
	// draw the board on the screen
	void DrawBoard(sf::RenderWindow* wind);
	// set the scale of the wind
	void SetCell(int x, int y);
	// insert the train data
	void InsertInput(const char* dataName,const char* lableName, int mode);
	// get the num drawn on the screen using the neural net
	int GetNum();
	// clear the board
	void ClearBoard();

private:
	float Matrix[SideLen][SideLen];
	sf::RectangleShape pixel;
	NeuralNetwork* network;
	int lastx;
	int lasty;
};

