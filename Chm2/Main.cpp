#include"System.h"

double* generateVector(int size, double max, double min);

int main()
{
	setlocale(0, "rus");
	srand(time(NULL));

	std::cout << "Введите размерность матрицы\n";
	int n;
	std::cin >> n;

	std::cout << "Введите ширину ленты\n";
	int WT;
	std::cin >> WT;

	System s(n, WT);
	s.randomFillMatr(30, 15);

	double* x = new double[4];
	x = generateVector(n, 10, 3);
	s.calculateF(x);

	std::cout << "Точное решение\n";
	for (int i = 0; i < n; i++)
		std::cout << x[i] << " ";
	std::cout << "\n";

	std::cout << "Полученное решение\n";
	double* result = s.systemSolution();
	for (int i = 0; i < n; i++)
		std::cout << result[i] << " ";


	return 0;
}

double* generateVector(int size, double max, double min) {
	double* x = new double[size];
	for (int j = 0; j < size; j++) {
		x[j] = (rand() % (int)max + min) / (rand() % (int)max + min);
		if (x[j] < min)
			x[j] = x[j] + abs(rand() % (int)max / 3 + min);
	}
	return x;
}