#pragma once
#include <cmath>
#include <iostream>
#include <vector>
class NeuralNet {
public:
	NeuralNet(int L, int *);
	double ForwardProp(int size, std::vector<double>& data);
	void BackProp(int epochs, double nu, std::vector<std::vector<double>>& data, std::vector<double>& ans);
private:
	double Sigmoid(double x);
	double DiffSigmoid(double x);
	double ReLU(double x);
	double DiffReLU(double x);
	std::vector<std::vector<std::vector<double>>> neurons;
	std::vector<std::vector<std::vector<double>>> weights;
	int layers;
	std::vector<int> neuronsInLayers;
	int Max(int size, int* arr);
};