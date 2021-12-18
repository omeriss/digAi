#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define NumOfHiddenLayers 3
#define NumOfNodesInHidden 20
#define NumOfNodesInInput 784
#define NumOfNodesInOutput 10
#define SetSize 10

typedef double HiddenW[NumOfNodesInHidden][NumOfNodesInHidden];


// input layer: all 28x28 pixels
// output layer: 10 neurons for every dig

class NeuralNetwork
{
public:
	vector<double> layers[NumOfHiddenLayers + 2];
	vector<double> bias[NumOfHiddenLayers + 1];
	double inputW[NumOfNodesInHidden][NumOfNodesInInput];
	double outputW[NumOfNodesInOutput][NumOfNodesInHidden];
	HiddenW hiddenWs[NumOfHiddenLayers - 1];
	NeuralNetwork();
	NeuralNetwork(string fileName);
	// get the output num
	int Calc(double* input);
	void SaveToFile(string fileName);
	// back propegation
	void BackProp(vector<double*> input, vector<int> lable, double jumpSize);
	void Learn(vector<double*>& input, vector<int>& lable, double jumpSize);
	void Test(vector<double*>& input, vector<int>& lable);
};

