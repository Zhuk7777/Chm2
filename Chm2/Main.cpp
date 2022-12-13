#include"System.h"

int main()
{
	setlocale(0, "rus");
	System x(4, 5);
	x.randomFillMatr(30, 15);
	x.printMatrix();

	return 0;
}