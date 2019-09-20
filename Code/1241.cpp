#include "iostream"
#include "cstdio"
using namespace std;

int main() {
	int N;
	scanf("%d", &N);

	double TotalGPA = 0.0;

	for (int i = 0; i < N; ++i) {
		int temp;
		scanf("%d",&temp);

		if (temp >= 95) {
			TotalGPA += 4.3;
		}
		else if (temp >= 90) {
			TotalGPA += 4.0;
		}
		else if (temp >= 85) {
			TotalGPA += 3.7;
		}
		else if (temp >= 80) {
			TotalGPA += 3.3;
		}
		else if (temp >= 75) {
			TotalGPA += 3.0;
		}
		else if (temp >= 70) {
			TotalGPA += 2.7;
		}
		else if (temp >= 67) {
			TotalGPA += 2.3;
		}
		else if (temp >= 65) {
			TotalGPA += 2.0;
		}
		else if (temp >= 62) {
			TotalGPA += 1.7;
		}
		else if (temp >= 60) {
			TotalGPA += 1.0;
		}
	}

	printf("%.2f", TotalGPA / N);

	return 0;
}