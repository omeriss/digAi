#include "DrawingBoard.h"

DrawingBoard::DrawingBoard() {
    srand((unsigned)time(NULL));
    pixel = sf::RectangleShape(sf::Vector2f(RecSize, RecSize));
    lastx = 0;
    lasty = 0;
    for (int i = 0; i < SideLen; i++) {
        for (int j = 0; j < SideLen; j++) {
            Matrix[i][j] = 0;
        }
    }
    if (UploadFile == "0")
        network = new NeuralNetwork();
    else
        network = new NeuralNetwork(UploadFile);
}

void DrawingBoard::SetCell(int x, int y) {
    if (x != lastx || y != lasty) {
        int m = x / RecSize;
        int n = y / RecSize;
        for (int i = n - 1; i <= n + 1; i++) {
            for (int j = m - 1; j <= m + 1; j++) {
                printf("%d %d\n", i, j);
                if (i >= 0 && i < SideLen && j >= 0 && j < SideLen) {
                    float xx = j * RecSize + RecSize / 2.0;
                    float yy = i * RecSize + RecSize / 2.0;
                    Matrix[i][j] += 1 - std::min((double)1, (sqrt(pow(x - xx, 2) + pow(y - yy, 2))) / ((3.0/4.0)*(2*sqrt(2*RecSize*RecSize))));
                    if (Matrix[i][j] > 1)
                        Matrix[i][j] = 1;
                }
            }
        }
        if (x > 0 && x <= ScreenSize && y > 0 && y <= ScreenSize)
            Matrix[(int)(y / RecSize)][(int)(x / RecSize)] = 1.0;
        lastx = x;
        lasty = y;
    }
}

void DrawingBoard::DrawBoard(sf::RenderWindow* wind) {
    for (int i = 0; i < SideLen; i++) {
        for (int j = 0; j < SideLen; j++) {
            pixel.setFillColor(sf::Color::Color(Matrix[i][j] * 255, Matrix[i][j] * 255, Matrix[i][j] * 255));
            pixel.setPosition(sf::Vector2f(j * RecSize, i * RecSize));
            wind->draw(pixel);
        }
    }
}

void DrawingBoard::InsertInput(const char* dataName, const char* lableName, int mode) {
    unsigned int filelen = 0;
    FILE* fData = fopen(dataName, "rb");
    fseek(fData, 4, SEEK_SET);
    fread(&filelen, 4, 1, fData);
    filelen = (filelen >> 24) |
        ((filelen << 8) & 0x00FF0000) |
        ((filelen >> 8) & 0x0000FF00) |
        (filelen << 24);
    cout << filelen << endl << endl;
    fseek(fData, 16, SEEK_SET);
    FILE* fLable = fopen(lableName, "rb");
    fseek(fLable, 8, SEEK_SET);

    vector<double*> trainV;
    vector<int> lableV;
    for (int i = 0; i < filelen/TestDataSize; i++) {
        for (int k = 0; k < TestDataSize; k++) {
            double* d = new double[28 * 28];
            for (int j = 0; j < 28 * 28; j++) {
                bool n;
                fread(&n, 1, 1, fData);
                d[j] = (double)n / 255;
            }
            trainV.push_back(d);
            bool n;
            fread(&n, 1, 1, fLable);
            lableV.push_back((int)n);
                
        }
    }
    if (mode) {
        network->Learn(trainV, lableV, LearnSpeed);
        if (SaveFile != "0")
            network->SaveToFile(SaveFile);
    }
    else
        network->Test(trainV, lableV);
}


int DrawingBoard::GetNum() {
    double* d = new double[28 * 28];
    for (int i = 0; i < SideLen; i++) {
        for (int j = 0; j < SideLen; j++) {
            d[i * SideLen + j] = Matrix[i][j];
        }
    }

    return network->Calc(d);
}


void DrawingBoard::ClearBoard() {
    for (int i = 0; i < SideLen; i++) {
        for (int j = 0; j < SideLen; j++) {
            Matrix[i][j] = 0;
        }
    }
}