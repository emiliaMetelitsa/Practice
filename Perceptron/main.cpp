#include "NeuralNet.h"
#include <vector>
#include <iostream>
#include <cmath>

int main() {
	int l[] = { 2, 16, 1 };
	NeuralNet NN(3, l);

	std::vector<std::vector<double>> data(1000, std::vector<double>(2));
	std::vector<double> ans(1000);
	std::vector<std::vector<double>> test(500, std::vector<double>(2));
	std::vector<double> ans_test(500);

	for (int i = 0; i < ans.size(); i++) {
		data[i][0] = (std::rand() % 1000) / 10.0;
		data[i][1] = (std::rand() % 1000) / 10.0;
		ans[i] = data[i][0] + data[i][1];
	}

	for (int i = 0; i < ans_test.size(); i++) {
		test[i][0] = (std::rand() % 1000) / 10.0;
		test[i][1] = (std::rand() % 1000) / 10.0;
		ans_test[i] = test[i][0] + test[i][1];
	}

	NN.BackProp(100, 0.001, data, ans);

	std::vector<double> NN_test(ans_test.size());
	double RMSE = 0;
	for (int i = 0; i < ans_test.size(); i++) {
		NN_test[i] = NN.ForwardProp(2, test[i]);
		RMSE += std::pow(ans_test[i] - NN_test[i], 2);
	}

	RMSE = std::sqrt(RMSE / ans_test.size());

	for (int i = 0; i < ans_test.size(); i++) {
		std::cout << "Answer:" << ans_test[i] << " NN:" << NN.ForwardProp(2, test[i]) << std::endl;
	}

	std::cout << "RMSE:" << RMSE << std::endl;

	return 0;
}