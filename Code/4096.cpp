#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;

int box[25][25] = { 0 };
int boxx[25] = { 0 }, boxy[25] = { 0 };
int box_num[25] = { 0 };

int main() {
	int N;
	scanf("%d", &N);

	//初始化
	for (int i = 0; i < N; ++i) {
		box[i][0] = i;
		boxx[i] = i;
		boxy[i] = 0;
		box_num[i] = 1;
	}

	while (true) {
		char opt1[20], opt2[20];
		int a, b;
		scanf("%s", opt1);
		if (strcmp(opt1, "quit") == 0)
			break;
		scanf("%d %s %d", &a, opt2, &b);
		if (a == b || boxx[a] == boxx[b])
			continue;
		if (strcmp(opt1, "move") == 0 && strcmp(opt2, "over") == 0) {
			for (int i = boxy[a] + 1; i < box_num[boxx[a]]; ++i) {
				auto temp = box[boxx[a]][i];
				box[temp][0] = temp;
				box[boxx[a]][i] = 0;
				boxx[temp] = temp;
				boxy[temp] = 0;
				box_num[temp] = 1;
			}
			box[boxx[a]][boxy[a]] = 0;
			box_num[boxx[a]] = boxy[a];
			//移动
			box[boxx[b]][box_num[boxx[b]]] = a;
			boxx[a] = boxx[b];
			boxy[a] = box_num[boxx[b]]++;
		}
		else if (strcmp(opt1, "move") == 0 && strcmp(opt2, "onto") == 0) {
			for (int i = boxy[a] + 1; i < box_num[boxx[a]]; ++i) {
				auto temp = box[boxx[a]][i];
				box[temp][0] = temp;
				box[boxx[a]][i] = 0;
				boxx[temp] = temp;
				boxy[temp] = 0;
				box_num[temp] = 1;
			}
			for (int i = boxy[b] + 1; i < box_num[boxx[b]]; ++i) {
				auto temp = box[boxx[b]][i];
				box[temp][0] = temp;
				box[boxx[b]][i] = 0;
				boxx[temp] = temp;
				boxy[temp] = 0;
				box_num[temp] = 1;
			}
			box[boxx[a]][boxy[a]] = 0;
			box_num[boxx[a]] = boxy[a];
			box_num[boxx[b]] = boxy[b] + 1;
			//移动
			box[boxx[b]][box_num[boxx[b]]] = a;
			boxx[a] = boxx[b];
			boxy[a] = box_num[boxx[b]]++;
		}
		else if (strcmp(opt1, "pile") == 0 && strcmp(opt2, "over") == 0) {
			//移动
			auto ori_x = boxx[a], ori_y = boxy[a], ori_num = box_num[boxx[a]];
			for (int i = ori_y; i < ori_num; ++i) {
				auto temp = box[ori_x][i];
				box[boxx[b]][box_num[boxx[b]]++] = temp;
				box[ori_x][i] = 0;
				--box_num[ori_x];
				boxx[temp] = boxx[b];
				boxy[temp] = box_num[boxx[b]] - 1;
			}
		}
		else if (strcmp(opt1, "pile") == 0 && strcmp(opt2, "onto") == 0) {
			for (int i = boxy[b] + 1; i < box_num[boxx[b]]; ++i) {
				auto temp = box[boxx[b]][i];
				box[temp][0] = temp;
				box[boxx[b]][i] = 0;
				boxx[temp] = temp;
				boxy[temp] = 0;
				box_num[temp] = 1;
			}
			box_num[boxx[b]] = boxy[b] + 1;
			//移动
			auto ori_x = boxx[a], ori_y = boxy[a], ori_num = box_num[boxx[a]];
			for (int i = ori_y; i < ori_num; ++i) {
				auto temp = box[ori_x][i];
				box[boxx[b]][box_num[boxx[b]]++] = temp;
				box[ori_x][i] = 0;
				--box_num[ori_x];
				boxx[temp] = boxx[b];
				boxy[temp] = box_num[boxx[b]] - 1;
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		cout << i << ":";
		for (int j = 0; j < box_num[i]; ++j)
			cout << " " << box[i][j];
		cout << endl;
	}

	return 0;
}