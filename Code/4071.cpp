#include "iostream"
#include "cstdio"
#include "cstring"
#include "cmath"
using namespace std;

constexpr long long mod = (long long)(1e9 + 7);

class matrix {
public:
	long long a11 = 0, a12 = 0;
	long long a21 = 0, a22 = 0;

	matrix() = default;
	matrix(long long a11, long long a12, long long a21, long long a22) :a11(a11% mod), a12(a12% mod)
		, a21(a21% mod), a22(a22% mod) {}

	matrix(matrix&& other){
		swap(*this, other);
	}
	
	void operator=(matrix&& other) {
		swap(*this, other);
	}

	matrix&& operator*(const matrix& b) const{
		matrix temp;
		temp.a11 = (a11 * b.a11 + a12 * b.a21) % mod;
		temp.a12 = (a11 * b.a12 + a12 * b.a22) % mod;
		temp.a21 = (a21 * b.a11 + a22 * b.a21) % mod;
		temp.a22 = (a21 * b.a12 + a22 * b.a22) % mod;
		return std::move(temp);
	}
};

matrix&& fast_pow(const matrix& a, long long b) {
	matrix ans(1, 0, 0, 1), base(a.a11, a.a12, a.a21, a.a22);
	for (; b; b >>= 1) {
		if (b & 1LL)
			ans = ans * base;
		base = base * base;
	}
	return std::move(ans);
}

int main() {
	long long n;
	scanf("%lld", &n);

	matrix temp(1, 1, 0, 0);
	matrix to(1, 1, 1, 0);
	matrix ans;
	ans = temp * fast_pow(to, n - 1);
	printf("%lld", ans.a11);

	return 0;
}