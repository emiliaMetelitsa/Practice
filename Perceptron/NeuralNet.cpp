#include "NeuralNet.h"
#include <random>

NeuralNet::NeuralNet(int L, int* n) {
	this->layers = L;
	this->neuronsInLayers.resize(L);
	for (int i = 0; i < L; i++) {
		this->neuronsInLayers[i] = n[i];
	}
	neurons.resize(Max(L, n));
	weights.resize(Max(L, n));
	for (int i = 0; i < Max(L, n); i++) {
		neurons[i].resize(3);
		for (int j = 0; j < 3; j++) {
			neurons[i][j].resize(L);
		}
	}
	for (int i = 0; i < Max(L, n); i++) {
		weights[i].resize(Max(L, n));
		for (int j = 0; j < Max(L, n); j++) {
			weights[i][j].resize(L - 1);
		}
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(-1.0, 1.0);

	for (int i = 0; i < Max(L, n); i++) {
		for (int j = 0; j < Max(L, n); j++) {
			for (int l = 0; l < L - 1; l++) {
				weights[i][j][l] = dist(gen) * 0.1;
			}
		}
	}
}

double NeuralNet::Sigmoid(double x){
	return 1.0 / (1.0 + std::exp(-x));
}

double NeuralNet::DiffSigmoid(double x){
	return 1.0 / (1.0 + std::exp(-x)) * (1.0 - (1.0 / (1.0 + std::exp(-x))));
}

double NeuralNet::ForwardProp(int size, std::vector<double>& data) {

	for (int n = 0; n < size; n++) {
		neurons[n][0][0] = data[n]/100.0;
		neurons[n][1][0] = Sigmoid(neurons[n][0][0]);
	}

	for (int l = 1; l < layers - 1; l++) {
		for (int n = 0; n < neuronsInLayers[l]; n++) {
			double sum = 0;
			for (int prevN = 0; prevN < neuronsInLayers[l - 1]; prevN++) {
				sum += neurons[prevN][1][l - 1] * weights[prevN][n][l - 1];
			}
			neurons[n][0][l] = sum;
			neurons[n][1][l] = Sigmoid(sum);
		}

	}

	double last_sum = 0;
	for (int prevN = 0; prevN < neuronsInLayers[layers - 2]; prevN++) {
		last_sum += neurons[prevN][1][layers - 2] * weights[prevN][0][layers - 2];
	}
	neurons[0][0][layers - 1] = last_sum;
	neurons[0][1][layers - 1] = last_sum;

	return neurons[0][1][layers - 1];

}

void NeuralNet::BackProp(int epochs, double nu, std::vector<std::vector<double>>& data, std::vector<double>& ans){
	for (int e = 0; e < epochs; e++) {
		double res = ForwardProp(2, data[e]);

		neurons[0][2][layers - 1] = res - ans[e];
		for (int l = layers - 2; l > 0; l--) {
			for (int n = 0; n < neuronsInLayers[l]; n++) {
				neurons[n][2][l] = 0;
				for (int nextN = 0; nextN < neuronsInLayers[l + 1]; nextN++) {
					neurons[n][2][l] += neurons[n][1][l]*(1 - neurons[n][1][l]) * neurons[nextN][2][l + 1] * weights[n][nextN][l];
					weights[n][nextN][l] -= nu * neurons[nextN][2][l + 1] * neurons[n][1][l];
				}

			}
		}
	}
}

int NeuralNet::Max(int size, int* arr) {
	int m = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > m) {
			m = arr[i];
		}
	}
	return m;
}