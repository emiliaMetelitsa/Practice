#include "NeuralNet.h"
#include <vector>
#include <iostream>

int main() {
	int l[] = { 2, 16, 1 };
	NeuralNet NN(3, l);

	std::vector<std::vector<double>> data(100, std::vector<double>(2));
	std::vector<double> ans(100);
	for (int i = 0; i < 100; i++) {
		data[i][0] = (std::rand() % 1000) / 10.0;
		data[i][1] = (std::rand() % 1000) / 10.0;
		ans[i] = data[i][0] + data[i][1];
	}

	NN.BackProp(50, 0.01, data, ans);

	for (int i = 50; i < ans.size(); i++) {
		std::cout << "Answer:" << ans[i] << " NN:" << NN.ForwardProp(2, data[i]) << std::endl;
	}

	return 0;
}
