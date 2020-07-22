//�Ϻ���ͨ��ѧ Online Judge
//��Ŀ1000
//OJ��ַ��https://acm.sjtu.edu.cn/OnlineJudge/
//����:ligongzzz
//����GitHub: https://github.com/ligongzzz/
//2019 ligongzzz 上海交通大学
#include "iostream"
#include "cstdlib"
#include "cmath"
#include "ctime"
using namespace std;

constexpr int BATCH_SIZE = 90000;
constexpr auto LR = 0.0001;
constexpr auto EPOCH = 100;

//����������
int x[BATCH_SIZE][2] = { 0 };
int y[BATCH_SIZE] = { 0 };

//������
double w[2] = { 0 };
double bias = 0;

int main() {
	//��������
	for (int i = 0; i < BATCH_SIZE; i++) {
		x[i][0] = rand() % 10;
		x[i][1] = rand() % 10;
		y[i] = x[i][0] + x[i][1];
	}
	bias = (double)rand() /RAND_MAX;
	w[0] = rand() % 10;
	w[1] = rand() % 10;
	//��ʼѵ��
	for(int _=0;_<EPOCH;_++)
		for (int i = 0; i < BATCH_SIZE; i++) {
			auto prediction = w[0] * x[i][0] + w[1] * x[i][1]+bias;
			auto label = y[i];
			double loss = pow(prediction-label,2);
			double grad[3] = {
				2*(prediction-label)*x[i][0],
				2*(prediction-label)*x[i][1],
				2*(prediction-label)
			};
			//���򴫲�
			w[0] -= grad[0] * LR;
			w[1] -= grad[1] * LR;
			bias -= grad[2] * LR;
		}
	
	int a, b;
	cin >> a >> b;
	cout << (int)floor(0.5 + w[0] * a + w[1] * b + bias);

	return 0;
}