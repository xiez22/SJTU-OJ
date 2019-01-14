#include "iostream"

using namespace std;

constexpr auto maxnum = 10000;

//Ã°ÅÝÅÅÐòº¯Êý
template <class T>
void maopao(T *input, T *output,int num) {
	//¸´ÖÆ
	for (int i = 0; i < num; i++) {
		output[i] = input[i];
	}

	for (int i = num; i >= 2; i--) {
		for (int j = 0; j < i-1; j++) {
			if (output[j] > output[j + 1]) {
				//»»Î»ÖÃ
				T temp = output[j];
				output[j] = output[j + 1];
				output[j + 1] = temp;
			}
		}
	}
}

int main() {
	int num, input[maxnum], output[maxnum];
	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> input[i];
	}
	maopao(input, output,num);
	for (int i = 0; i < num; i++) {
		cout<< output[i]<<" ";
	}

	return 0;
}