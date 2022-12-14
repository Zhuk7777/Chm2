#include"System.h"

double* generateVector(int size, double max, double min);

int main()
{
	setlocale(0, "rus");
	srand(time(NULL));

	double** matrix = new double* [4];
	for (int i = 0; i < 4; i++)
		matrix[i] = new double[4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			std::cin >> matrix[i][j];
	

	double* f = new double[4];
	for (int i = 0; i < 4; i++)
		std::cin >> f[i];

	System s(matrix, f, 4, 2);
	/*System s(4, 2);*/
	/*s.randomFillMatr(30, 15);*/
	//s.printMatrix();

	double x[] = { 3,2,-5,1 };
	/*double* x = new double[4];
	x = generateVector(5, 10, 3);
	s.calculateF(x);*/

	std::cout << "Точное решение\n";
	for (int i = 0; i < 4; i++)
		std::cout << x[i] << " ";
	std::cout << "\n";

	std::cout << "Полученное решение\n";
	double* result = s.systemSolution();
	for (int i = 0; i < 4; i++)
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