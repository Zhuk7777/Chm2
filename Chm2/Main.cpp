#include"System.h"

double* generateVector(int size, double max, double min);
double normOfVec(double* vec, int size);
double* differenceVec(double* vec1, double* vec2, int size);

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
	std::cout << "\n\n";

	std::cout << "Полученное решение\n";
	double* result = s.systemSolution();
	for (int i = 0; i < n; i++)
		std::cout << result[i] << " ";
	std::cout << "\n\n";

	std::cout << "Погрешность\n";
	result = differenceVec(x, result, n);
	std::cout << normOfVec(result, n);


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

double normOfVec(double* vec, int size)
{
	double max = abs(vec[0]);
	for (int i = 1; i < size; i++)
		if (abs(vec[i]) > max)
			max = abs(vec[i]);

	return max;
}

double* differenceVec(double* vec1,double* vec2,int size)
{
	double* result = new double[size];
	for (int i = 0; i < size; i++)
		result[i] = vec2[i] - vec1[i];
	return result;
}