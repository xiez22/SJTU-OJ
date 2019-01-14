#include <iostream>



using namespace std;



int main()

{
	int n, i, j, k, tpm, num = 0;

	cout << "please input n:";

	cin >> n;

	int A[100][100] = { 0 }, r[100] = { 0 }, r1[100];

	cout << "please input 0-1 A :";



	for (i = 0; i < n; i++)

	{
		for (j = 0; j < n; j++)

			cin >> A[i][j];
	}



	for (i = 0; i < n; i++)

	{
		num += A[0][i];
	}



	r[0] = num;

	for (j = 1; j < n; j++)

	{

		for (k = num; k < n; k++)

			if (A[j][k] == 0 && k < n - 1)

				r[j] = k;

		if (k == n - 1 && A[j][k] == 1)

			r[j] = n;

		else r[j] = n - 1;

	}





	for (i = 0; i < n; i++)

	{
		r1[i] = r[i];
	}



	for (i = 0; i < n; i++)

	{

		j = i;

		for (k = i + 1; k < n; k++)

		{

			if (r[k] < r[j])

			{
				tpm = r[k];

				r[k] = r[j];

				r[j] = tpm;
			}

		}

	}

	for (i = 0; i < n; i++)



		if (r1[i] == r[n - 1])

			cout << i + 1 << endl;

	return 0;

}
