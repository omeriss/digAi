#include "NeuralNetwork.h"
#include <math.h>

double inline GetRand() {
	return (rand() % 2001 - 1000.0) / 1000.0;
}

double inline func(double x) {
	//return max(x, 0.0);
	return 1 / (1 + exp(-x));
}

double inline funcD(double x) {
	//if (x <= 0) return 0;
	//return 1;
	return x * (1 - x);
}

NeuralNetwork::NeuralNetwork() {

	layers[0].resize(NumOfNodesInInput);
	layers[NumOfHiddenLayers + 1].resize(NumOfNodesInOutput);
	bias[NumOfHiddenLayers].resize(NumOfNodesInOutput);

	for (int i = 1; i <= NumOfHiddenLayers; i++) {
		layers[i].resize(NumOfNodesInHidden);
		bias[i - 1].resize(NumOfNodesInHidden);
	}

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = bias[i].size();
		for (int j = 0; j < vlen; j++) {
			bias[i][j] = GetRand();
		}
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			inputW[i][j] = GetRand();
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				hiddenWs[k][i][j] = GetRand();
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			outputW[i][j] = GetRand();
		}
	}
}

NeuralNetwork::NeuralNetwork(string fileName) {

	std::ifstream file(fileName, std::ofstream::binary);
	if (!file) {
		cout << "cant open file\n";
		return;
	}

	layers[0].resize(NumOfNodesInInput);
	layers[NumOfHiddenLayers + 1].resize(NumOfNodesInOutput);
	bias[NumOfHiddenLayers].resize(NumOfNodesInOutput);

	for (int i = 1; i <= NumOfHiddenLayers; i++) {
		layers[i].resize(NumOfNodesInHidden);
		bias[i - 1].resize(NumOfNodesInHidden);
	}

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = bias[i].size();
		for (int j = 0; j < vlen; j++) {
			file.read((char*)&bias[i][j], sizeof(double));
		}
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			file.read((char*)&inputW[i][j], sizeof(double));
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				file.read((char*)&hiddenWs[k][i][j], sizeof(double));
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			file.read((char*)&outputW[i][j], sizeof(double));
		}
	}
}

int NeuralNetwork::Calc(double* input) {
	for (int i = 0; i < NumOfNodesInInput; i++) {
		layers[0][i] = input[i];
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		layers[1][i] = bias[0][i];
		for (int j = 0; j < NumOfNodesInInput; j++) {
			layers[1][i] += layers[0][j] * inputW[i][j];
		}
		layers[1][i] = func(layers[1][i]);
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			layers[k + 2][i] = bias[k + 1][i];
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				layers[k + 2][i] += layers[k + 1][j] * hiddenWs[k][i][j];
			}
			layers[k + 2][i] = func(layers[k + 2][i]);
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		layers[NumOfHiddenLayers + 1][i] = bias[NumOfHiddenLayers][i];
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			layers[NumOfHiddenLayers + 1][i] += layers[NumOfHiddenLayers][j] * outputW[i][j];
		}
		layers[NumOfHiddenLayers + 1][i] = func(layers[NumOfHiddenLayers + 1][i]);
	}

	int mm = 0;

	//std::cout << layers[NumOfHiddenLayers + 1][0] << " ";
	for (int i = 1; i < NumOfNodesInOutput; i++) {
		if (layers[NumOfHiddenLayers + 1][mm] < layers[NumOfHiddenLayers + 1][i])
			mm = i;
		//std::cout << layers[NumOfHiddenLayers + 1][i] << " ";
	}
	//cout << endl;

	return mm;
}

void NeuralNetwork::SaveToFile(string fileName) {
	std::ofstream file(fileName, std::ofstream::binary);
	if (!file) {
		cout << "cant open file\n";
		return;
	}

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = bias[i].size();
		for (int j = 0; j < vlen; j++) {
			file.write((const char*)&(bias[i][j]), sizeof(double));
		}
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			file.write((const char*)&(inputW[i][j]), sizeof(double));
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				file.write((const char*)&(hiddenWs[k][i][j]), sizeof(double));
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			file.write((const char*)&(outputW[i][j]), sizeof(double));
		}
	}
}

void NeuralNetwork::BackProp(vector<double*> input, vector<int> lable, double jumpSize) {
	double inputWC[NumOfNodesInHidden][NumOfNodesInInput];
	double outputWC[NumOfNodesInOutput][NumOfNodesInHidden];
	HiddenW hiddenWsC[NumOfHiddenLayers - 1];
	vector<double> biasC[NumOfHiddenLayers + 1];

	vector<double> layersC[NumOfHiddenLayers + 2];

	layersC[0].resize(NumOfNodesInInput);
	layersC[NumOfHiddenLayers + 1].resize(NumOfNodesInOutput);
	biasC[NumOfHiddenLayers].resize(NumOfNodesInOutput);

	for (int i = 1; i <= NumOfHiddenLayers; i++) {
		layersC[i].resize(NumOfNodesInHidden);
		biasC[i - 1].resize(NumOfNodesInHidden);
	}

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = biasC[i].size();
		for (int j = 0; j < vlen; j++) {
			biasC[i][j] = 0;
		}
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			inputWC[i][j] = 0;
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				hiddenWsC[k][i][j] = 0;
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			outputWC[i][j] =0;
		}
	}

	int inputLen = input.size();
	for (int t = 0; t < inputLen; t++) {
		cout << lable[t]<<"l" << endl;
		cout << Calc(input[t])<<"c" << endl;;

		for (int p = 0; p < NumOfHiddenLayers + 2; p++) {
			int ll = layersC[p].size();
			while (ll--) {
				layersC[p][ll] = 0;
			}
		}

		for (int j = 0; j < NumOfNodesInOutput; j++) {
			for (int k = 0; k < NumOfNodesInHidden; k++) {
				layersC[NumOfHiddenLayers + 1][j] = funcD(layers[NumOfHiddenLayers + 1][j]) * (layers[NumOfHiddenLayers + 1][j] - (lable[t] == j ));
				layersC[NumOfHiddenLayers][k] += outputW[j][k] * layersC[NumOfHiddenLayers + 1][j] * funcD(layers[NumOfHiddenLayers ][k]);//check
				outputWC[j][k] += layers[NumOfHiddenLayers][k] * layersC[NumOfHiddenLayers + 1][j];
			}
			biasC[NumOfHiddenLayers][j] += layersC[NumOfHiddenLayers + 1][j];
		}


		for (int ly = NumOfHiddenLayers - 2; ly >= 0; ly--) {
			int l = ly + 2;
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				for (int k = 0; k < NumOfNodesInHidden; k++) {
					layersC[l - 1][k] += hiddenWs[ly][j][k] * funcD(layers[l-1][k]) * layersC[l][j];
					hiddenWsC[ly][j][k] += layers[l - 1][k] * layersC[l][j];
				}
				biasC[l-1][j] +=  layersC[l][j];
			}
		}

		for (int j = 0; j < NumOfNodesInHidden; j++) {
			for (int k = 0; k < NumOfNodesInInput; k++) {
				 inputWC[j][k] += layers[0][k]  *  layersC[1][j];
			}
			 biasC[0][j] += layersC[1][j];
		}
	}

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = biasC[i].size();
		for (int j = 0; j < vlen; j++) {
			bias[i][j] = bias[i][j] - (jumpSize / (double)inputLen) * biasC[i][j] ;
		}
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			inputW[i][j] = inputW[i][j] - (jumpSize / (double)inputLen) * inputWC[i][j];
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				hiddenWs[k][i][j] = hiddenWs[k][i][j] - (jumpSize / (double)inputLen) * hiddenWsC[k][i][j];
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			outputW[i][j] = outputW[i][j] - (jumpSize / (double)inputLen) * outputWC[i][j];
		}
	}
}

// swap the pos of the objects in the vectors randomly
void randomize(vector<double*>& input, vector<int>& lable) {
	int ilen = input.size();
	for (int i = 0; i < ilen; i++) {
		int k = rand() % ilen;
		swap(input[i], input[k]);
		swap(lable[i], lable[k]);
	}
}

// get input and lables and 
void NeuralNetwork::Learn(vector<double*>& input, vector<int>& lable, double jumpSize) {
	int ilen = input.size();
	vector<double*> trainV;
	vector<int> lableV;
	for (int t = 0; t < 3; t++) {
		randomize(input, lable);
		for (int i = 0; i < ilen / SetSize; i++) {
			for (int j = 0; j < SetSize; j++) {
				trainV.push_back(input[i * SetSize + j]);
				lableV.push_back(lable[i * SetSize + j]);
			}
			BackProp(trainV, lableV, jumpSize);
			trainV.clear();
			lableV.clear();
		}
	}

}

void NeuralNetwork::Test(vector<double*>& input, vector<int>& lable) {
	randomize(input, lable);
	int ilen = input.size();
	vector<double*> trainV;
	vector<int> lableV;
	int cor = 0;
	for (int i = 0; i < ilen; i++) {
		if (Calc(input[i]) == lable[i]) {
			cor++;
			cout << i << " " << "v" << endl;
		}
		else {
			cout << i << " " << "x" << endl;
		}
	}
	cout << (double)cor / ilen<<endl;
}



 