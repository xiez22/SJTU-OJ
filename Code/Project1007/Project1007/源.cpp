#include "iostream"
using namespace std;

bool firstwrite = true;
long long f[35][35];
int root[35][35];

long long search(int L, int r)
{
	int  k;
	long long  now;
	if (L > r) return 1;
	if (f[L][r]<0)
		for (k = L; k <= r; k++) {
			now = search(L, k - 1) * search(k + 1, r) + f[k][k];
			if (now > f[L][r]) {
				f[L][r] = now;
				root[L][r] = k;
			}
		}
	return  f[L][r];
}

// Ç°Ðò±éÀú
void  preorder(int L, int r)
{
	if (L > r)  return;
	if (firstwrite)
		firstwrite = false;
	else
		cout << ' ';
	cout << root[L][r];
	preorder(L, root[L][r] - 1);
	preorder(root[L][r] + 1, r);
}

int main()
{
	int n, i;
	cin >> n; 
	for (i = 1; i <= n; i++)
		for (int j = i; j <= n; j++)
			f[i][j] = -1;
	for (i = 1; i <= n; i++) {
		cin >> f[i][i];
		root[i][i] = i;
	}
	cout << search(1, n) << endl;
	preorder(1, n);
	return 0;
}