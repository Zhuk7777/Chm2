#pragma once

#include<iostream>
#include<ctime>
#include<math.h>


class System {

	double** matrix;
	double* f;
	int sizeMatr;
	int wideTape;

	void GaussMethod(int** PQ)
	{
		int i, j;
		double R;

		for (int k = 0; k < sizeMatr; k++)
		{
			R = 1 / absMax(i, j, PQ);
			PQ[0][k] = i;
			PQ[1][k] = j;

			for (int c = 0; c < sizeMatr; c++)
				matrix[i][c] *= R;
			f[i] *= R;

			for (int r = 0; r < sizeMatr; r++)
			{
				R = matrix[r][j];

				if (minor(r, sizeMatr, PQ) != false)
				{
					for (int c = 0; c < sizeMatr; c++)
						matrix[r][c] -= R * matrix[i][c];
					f[r] -= R * f[i];
					
				}
			}

			
		}

	}

	double absMax(int& _i, int& _j, int** PQ)
	{
		double max = -1;
		for (int i = 0; i < sizeMatr; i++)
			for (int j = 0; j < sizeMatr; j++)
			{
				if (abs(matrix[i][j]) > max && minor(i, j, PQ) != false)
				{
					max = matrix[i][j];
					_i = i;
					_j = j;
				}
			}
		return max;
	}

	bool minor(int i, int j, int** PQ)
	{
		bool row = true, column = true;
		for (int k = 0; k < sizeMatr; k++)
		{
			if (PQ[0][k] == i)
				row = false;

			if (PQ[1][k] == j)
				column = false;
		}

		return row * column;
	}

	int** initializingPQ()
	{
		int** PQ = new int* [2];
		for (int i = 0; i < 2; i++)
			PQ[i] = new int[sizeMatr];

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < sizeMatr; j++)
				PQ[i][j] = -1;

		return PQ;
	}

public:

	System()
	{
		matrix = nullptr;
		f = nullptr;
		sizeMatr = 0;
		wideTape = 0;
	}
	System(int _sizeMatr, int _wideTape)
	{
		sizeMatr = _sizeMatr;
		wideTape = _wideTape;

		matrix = new double* [sizeMatr];
		for (int i = 0; i < sizeMatr; i++)
			matrix[i] = new double[sizeMatr];

		f = new double[sizeMatr];
	}
	System(double** _matrix, double* _f, int _sizeMatr, int _wideTape)
	{
		matrix = _matrix;
		f = _f;
		sizeMatr = _sizeMatr;
		wideTape = _wideTape;
	}

	~System()
	{
		for (int i = 0; i < sizeMatr; i++)
			delete[]matrix[i];
		delete[]matrix;

		delete[]f;
	}

	void fillMatrix()
	{
		for (int i = 0; i < sizeMatr; i++)
			for (int j = 0; j < sizeMatr; j++)
				std::cin >> matrix[i][j];
	}
	void fillZeros()
	{
		for (int i = 0; i < sizeMatr; i++)
			for (int j = 0; j < sizeMatr; j++)
				matrix[i][j] = 0;
	}
	void randomFillMatr(double max, double min)
	{
		int countOfVectors = 2 * wideTape - 1;
		double* vector = new double[sizeMatr];
		fillZeros();

		for (int i = 0; i < sizeMatr; i++)
		{
			for (int j = 0; j < sizeMatr; j++)
			{
				vector[j] = (rand() % (int)max + min) / (rand() % (int)max + min);
				if (vector[j] < min)
					vector[j] = vector[j] + abs(rand() % (int)max / 3 + min);
			}

			int j = i + wideTape - countOfVectors;
			if (j < 0)
				j = 0;

			int endOfRow = i + wideTape;
			if (endOfRow > sizeMatr)
				endOfRow = sizeMatr;

			while (j != endOfRow)
			{
				matrix[i][j] = vector[j];
				j++;
			}
		}

	}

	void fillF()
	{
		for (int i = 0; i < sizeMatr; i++)
			std::cin >> f[i];
	}
	void randomFillF(double max, double min)
	{
		for (int j = 0; j < sizeMatr; j++) {
			f[j] = (rand() % (int)max + min) / (rand() % (int)max + min);
			if (f[j] < min)
				f[j] = f[j] + abs(rand() % (int)max / 3 + min);
		}
	}

	void calculateF(double* x) {
		for (int i = 0; i < sizeMatr; i++) {
			double sum = 0;
			for (int j = 0; j < sizeMatr; j++) {
				sum += matrix[i][j] * x[j];
			}
			f[i] = sum;
		}
	}

	void printMatrix()
	{
		for (int i = 0; i < sizeMatr; i++)
		{
			std::cout << "\n";
			for (int j = 0; j < sizeMatr; j++)
				std::cout << matrix[i][j] << " ";
		}

		std::cout << "\n";
	}
	void printF()
	{
		for (int i = 0; i < sizeMatr; i++)
			std::cout << f[i] << " ";
	}

	double* systemSolution()
	{
		int** PQ = initializingPQ();
		GaussMethod(PQ);

		double* x = new double[sizeMatr];
		for (int i = 0; i < sizeMatr; i++)
			x[i] = 0;
		double sum;

		for (int i = sizeMatr - 1; i >= 0; i--)
		{
			sum = 0;
			for (int j = 0; j < sizeMatr; j++)
			{
				if (j != PQ[1][i])
					sum += matrix[PQ[0][i]][j] * x[j];
			}
			x[PQ[1][i]] = f[PQ[0][i]] - sum;
		}


		return x;
	}


};
