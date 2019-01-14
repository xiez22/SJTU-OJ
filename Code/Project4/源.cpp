#include "stdio.h"

float fun(int n) {
	if (0== n % 5)
		return ++n;
	else
		return float(n) / 5;
}
void main() {
	printf("%ld\n", fun(7));
	getchar();
}