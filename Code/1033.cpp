#include "iostream"
#include "cmath"
#include "cstring"

using namespace std;

const int maxnum = 1000;

const bool fuckSJTU = true;

//识别函数(  (0,^1,*10,/11,+20,-21,)100  )
template <class T>
void transExpression(char *input, T *output,bool *cate) {
	for (int i = 0,j=1; i < strlen(input); i++,j++) {
		//识别操作符
		if (input[i] == '-' && (i == 0 || (input[i - 1] != '+'&&input[i - 1] != '-'&&input[i - 1] != '*'&&input[i - 1] != '/'&&input[i - 1] != '^'&&input[i - 1] != '('))) {
			output[++output[0]] =21;
			cate[j] = true;
		}
		else if (input[i] == '+') {
			output[++output[0]] =20;
			cate[j] = true;
		}
		else if (input[i] == '*') {
			output[++output[0]] =10;
			cate[j] = true;
		}
		else if (input[i] == '/') {
			output[++output[0]] = 11;
			cate[j] = true;
		}
		else if (input[i] == '^') {
			output[++output[0]] =1;
			cate[j] = true;
		}
		else if (input[i] == '(') {
			output[++output[0]] =0;
			cate[j] = true;
		}
		else if (input[i] == ')') {
			output[++output[0]] =100;
			cate[j] = true;
		}
		else {
			//识别数字
			char temp[maxnum] = "";
			for (int t = 0; ; i++, t++) {
				temp[t] = input[i];
				temp[t + 1] = '\0';
				if (!((input[i + 1] >= 48 && input[i + 1] <= 57) || input[i + 1] == '.')) {
					break;
				}
			}
			double getInt;
			sscanf(temp, "%lf", &getInt);
			output[++output[0]] = T(getInt);
			cate[j] = false;
		}
	}

	//为^添加括号
	for (int i = output[0]; i >= 1; i--) {
		if (output[i] == 1 && cate[i]) {
			int kl = 0, kr = 0;
			for (int j = i - 1; j >= 1; j--) {
				if (output[j] == 0 && cate[j])
					kl++;
				else if (output[j] == 100 && cate[j])
					kr++;
				if (kl == kr) {
					//修改
					i++;
					for (int n = output[0]; n >= j; n--) {
						output[n + 1] = output[n];
						cate[n + 1] = cate[n];
					}
					output[0]++;
					output[j] = 0;
					cate[j] = true;
					break;
				}

			}
			kl = 0, kr = 0;
			for (int j = i+1; j<=output[0]; j++) {
				if (output[j] == 0 && cate[j])
					kl++;
				else if (output[j] == 100 && cate[j])
					kr++;
				if (kl == kr) {
					j++;
					//修改
					for (int n = output[0] - 1; n >= j; n--) {
						output[n + 1] = output[n];
						cate[n + 1] = cate[n];
					}
					output[0]++;
					output[j] = 100;
					cate[j] = true;
					break;
				}

			}
		}
	}
}

template <class T>
void houzhuiExpression(T *zhongzhui,bool *zhongzhuiCate, T *houzhui,bool *houzhuiCate) {
	//栈表达式
    int zhanExpression[maxnum];
	zhanExpression[0] = 0;

	//扫描
	for (int i = 1; i <= zhongzhui[0]; i++) {
		//操作数
		if (zhongzhuiCate[i] == false) {
			//塞入
			houzhui[++houzhui[0]] = zhongzhui[i];
			houzhuiCate[houzhui[0]] = false;
		}
		else {
			//符号
			if (zhongzhui[i] ==0) {
				//入栈
				zhanExpression[++zhanExpression[0]] = 0;
			}
			else if (zhongzhui[i] ==100) {
				//出栈
				T zhanTemp[maxnum];
				zhanTemp[0] = 0;
				for (int j = zhanExpression[0]; j > 0; j--) {
					if (zhanExpression[j] == 0) {
						zhanExpression[0]--;
						break;
					}
					zhanTemp[++zhanTemp[0]] = zhanExpression[j];
					zhanExpression[0]--;
				}
				//塞入
				for (int j = 1; j<=zhanTemp[0]; j++) {
					houzhui[++houzhui[0]] = zhanTemp[j];
					houzhuiCate[houzhui[0]] = true;
				}
			}
			else {
				T temp[maxnum];
				temp[0] = 0;
				for (; (zhongzhui[i] - zhanExpression[zhanExpression[0]] > -5)&&zhanExpression[zhanExpression[0]]!=0;) {	
					//弹出
					temp[++temp[0]] = zhanExpression[zhanExpression[0]--];
				}
				//添加
				zhanExpression[++zhanExpression[0]] = zhongzhui[i];
				//塞入
				for (; temp[0] > 0;) {
					houzhui[++houzhui[0]] = temp[temp[0]--];
					houzhuiCate[houzhui[0]] = true;
				}
			}
		}
	}
	//塞入
	for (int i = zhanExpression[0]; i>0; i--) {
		houzhui[++houzhui[0]] = zhanExpression[i];
		houzhuiCate[houzhui[0]] = true;
	}
}

//后缀表达式计算
template <class T>
int calHouzhui(T *houzhui, bool *cateHouzhui,T &ans) {
	//是否存在
	bool isExist[maxnum];
	for (int i = 1; i <= houzhui[0]; i++)
		isExist[i] = true;

	//扫描
	for (int i = 1; i <= houzhui[0]; i++) {
		if (!isExist[i])
			continue;
		//运算符
		if (cateHouzhui[i] == true) {
			//分类
			if (houzhui[i] == 1) {
				//不存在了
				isExist[i] = false;
				//寻找运算数
				T a, b;
				for (;; i--) {
					if (isExist[i]) {
						b = houzhui[i];
						isExist[i] = false;
						break;
					}
				}
				for (;; i--) {
					if (isExist[i]) {
						a = houzhui[i];
						break;
					}
				}
				if(a==0&&b<0)
					return -1;
				houzhui[i] = T(pow(double(a), double(b)));
			}
			else if (houzhui[i] == 10) {
				//不存在了
				isExist[i] = false;
				//寻找运算数
				T a, b;
				for (;; i--) {
					if (isExist[i]) {
						b = houzhui[i];
						isExist[i] = false;
						break;
					}
				}
				for (;; i--) {
					if (isExist[i]) {
						a = houzhui[i];
						break;
					}
				}
				houzhui[i] =a*b;
			}
			else if (houzhui[i] == 11) {
				//不存在了
				isExist[i] = false;
				//寻找运算数
				T a, b;
				for (;; i--) {
					if (isExist[i]) {
						b = houzhui[i];
						isExist[i] = false;
						break;
					}
				}
				for (;; i--) {
					if (isExist[i]) {
						a = houzhui[i];
						break;
					}
				}
				if (b == 0)
					return -1;
				houzhui[i] = a / b;
			}
			else if (houzhui[i] == 20) {
				//不存在了
				isExist[i] = false;
				//寻找运算数
				T a, b;
				for (;; i--) {
					if (isExist[i]) {
						b = houzhui[i];
						isExist[i] = false;
						break;
					}
				}
				for (;; i--) {
					if (isExist[i]) {
						a = houzhui[i];
						break;
					}
				}
				houzhui[i] = a +b;
			}
			else if (houzhui[i] == 21) {
				//不存在了
				isExist[i] = false;
				//寻找运算数
				T a, b;
				for (;; i--) {
					if (isExist[i]) {
						b = houzhui[i];
						isExist[i] = false;
						break;
					}
				}
				for (;; i--) {
					if (isExist[i]) {
						a = houzhui[i];
						break;
					}
				}
				houzhui[i] = a-b;
			}
		}
	}
	//输出结果
	ans = houzhui[1];
	return 0;
}
//计算函数
template <class T>
int calExpression(char *input,T &ans,int mode=0) {
	int kl=0, kr=0;
    //计算括号
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == '(')
			kl++;
		else if (input[i] == ')')
			kr++;
		if (kr > kl)
			return -1;
	}
	if (kl!=kr)
		return -1;

	//识别表达式
	T inputExpression[maxnum];
	inputExpression[0] = 0;
	//后缀表达式
	T formatExpression[maxnum];
	formatExpression[0] = 0;
	//分类(false操作数 true操作符）
	bool cateExpression[maxnum];
	bool cateInput[maxnum];
	

	//识别表达式
	if(mode==0)
		transExpression(input, inputExpression, cateInput);


	//转为后缀表达式
	houzhuiExpression(inputExpression, cateInput, formatExpression, cateExpression);

	//计算后缀表达式
	if (calHouzhui(formatExpression, cateExpression, ans) == 0) {
		return 0;
	}
	else
		return -1;
}

int main() {
	char input[maxnum]="";
	if(!fuckSJTU)
		cin.getline(input,maxnum);
	else {
		//分析是否输入了一个单独的负数
		char temp[maxnum];
 		while (cin >> temp) {
			if (temp[0] == '-'&&temp[1] >= 48 && temp[1] <= 57) {
				char temp1[maxnum];
				sprintf(temp1, "(%s)", temp);
				strcat(input, temp1);
			}
			else
			    strcat(input, temp);
			if (getchar() == '\n')
				break;
		}
	}

	char expr[maxnum];

	//加0
	if (input[0] == '-') {
		input[strlen(input)+1] = '\0';
		for (int i = strlen(input)-1; i >= 0; i--) {
			input[i + 1] = input[i];
		}
		input[0] ='0';
	}
	

	//除去空格
	for (int i = 0, j = 0; i < maxnum; i++) {
		if (input[i] != ' ') {
			expr[j] = input[i];
			j++;
		}
	}

	long long ans;

	if (calExpression<long long>(expr, ans) != 0)
		cout << "Error";
	else
	    cout << ans;

	return 0;
}