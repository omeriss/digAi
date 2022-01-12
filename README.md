# digAi
This project uses a neural network to recognize handwritten digits in c++. I used the simple grafics library sfml for the visuals.
The neural network was written by me from scratch.
The digits can be written on a 28x28 board.
# The Neural Network
The convolutional neural net consists of 3 type of layers: Input, Hidden and output.
The input layer for this nn is made out of 28x28 neurons, one for each pixel in the digit board.
The output is 10 neuron, one for each digit the nn can recognize.
The neural network learnes using data from the MNIST DATABASE (http://yann.lecun.com/exdb/mnist/).
In order for the nn to learn from the data I use Backpropagation algorithm.
more Info about neural network for digit recognition and Backpropagation that I used In order to make this project:
https://www.3blue1brown.com/topics/neural-networks
# Short video from the project



https://user-images.githubusercontent.com/94307825/149230989-03dbd394-e914-43a3-9ff3-29855f4b2627.mp4

