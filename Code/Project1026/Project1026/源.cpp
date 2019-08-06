#include "iostream"
#include "cstring"
#include "cmath"
#include "algorithm"

using namespace std;

//常数
constexpr auto maxNum = 10000;
constexpr auto intMax = 20;

//交换
template <class T>
void mySwap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

//冒泡排序
//默认a至b升序
template <class T>
void bubbleSort(T* destination, T* source, int num, bool (*f)(const T& a, const T& b)) {
	//复制
	if (destination != source)
		for (int i = 0; i < num; i++)
			destination[i] = source[i];

	for (int i = num - 2; i >= 0; i--)
		for (int j = 0; j <= i; j++)
			if (!f(destination[j], destination[j + 1]))
				mySwap(destination[j], destination[j + 1]);
}

//无符号大整数类
/*
class unsignedBigInt {
public:
	char ch[maxNum * 2];
	int startNum = maxNum;

	//初始化
	unsignedBigInt(const char *input) {
		memset(ch, 0, maxNum*2);
		for (int i = 0; i < strlen(input); i++)
			ch[i+maxNum] = input[i];
	}
	unsignedBigInt(void) {
		memset(ch, 0, maxNum*2);
	}

	//复制构造函数
	unsignedBigInt(const unsignedBigInt& b) {
		for (int i = 0; i < maxNum * 2; i++)
			ch[i] = b.ch[i];
		startNum = b.startNum;
	}

	//输入输出
	friend ostream &operator<<(ostream &output,const unsignedBigInt &bi);
	friend istream &operator>>(istream &input,unsignedBigInt &bi);

	//赋值
	unsignedBigInt operator=(unsignedBigInt b) {
		for (int i = 0; i < maxNum * 2; i++)
			ch[i] = b.ch[i];
		startNum = b.startNum;
		return *this;
	}

	//比较符
	//小于
	bool operator<(unsignedBigInt b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) < 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) < strlen(b.ch + b.startNum) ? true : false;
	}

	//大于
	bool operator>(unsignedBigInt b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) > 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum)>strlen(b.ch + b.startNum) ? true : false;
	}

	//小于等于
	bool operator<=(unsignedBigInt b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) <= 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) <strlen(b.ch + b.startNum) ? true : false;
	}

	//大于等于
	bool operator>=(unsignedBigInt b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) >= 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) > strlen(b.ch + b.startNum) ? true : false;
	}

	//等于等于
	bool operator==(unsignedBigInt b) {
		return strcmp(ch + startNum, b.ch + b.startNum) == 0 ? true : false;
	}

	//运算符
	//加号
	unsignedBigInt operator+(unsignedBigInt b) {
		unsignedBigInt temp;
		int jw = 0;

		for (int i = 0;ch[startNum+strlen(ch+startNum)-i-1]!=0||b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] != 0||jw!=0; i++) {
			//判断加数
			int j1 = ch[startNum + strlen(ch + startNum) - i - 1] == 0 ? 0 : ch[startNum + strlen(ch + startNum) - i - 1] - '0';
			int j2= b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] == 0 ? 0 : b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] - '0';

			//运算
			temp.ch[--temp.startNum] = (j1 + j2 + jw) % 10+'0';
			jw = (j1 + j2 + jw) / 10;
		}

		//返回
		return temp;
	}

	//++c
	unsignedBigInt operator++() {
		*this = *this + unsignedBigInt("1");
		return *this;
	}

	//c++
	unsignedBigInt operator++(int i) {
		unsignedBigInt temp = *this;
		*this = temp +unsignedBigInt("1");
		return temp;
	}

	//减号
	unsignedBigInt operator-(unsignedBigInt b) {
		unsignedBigInt temp;
		int jw = 0;

		for (int i = 0; ch[startNum + strlen(ch + startNum) - i - 1] != 0 || b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] != 0; i++) {
			//判断被减数与减数
			int j1 = ch[startNum + strlen(ch + startNum) - i - 1] == 0 ? 0 : ch[startNum + strlen(ch + startNum) - i - 1] - '0';
			int j2 = b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] == 0 ? 0 : b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] - '0';

			//运算
			if (j1 - jw - j2 < 0) {
				temp.ch[--temp.startNum] = 10 + j1 - jw - j2 + '0';
				jw = 1;
			}
			else {
				temp.ch[--temp.startNum] =  j1 - jw - j2 + '0';
				jw = 0;
			}
		}

		//修正
		for (;temp.ch[temp.startNum] == '0';)
			temp.ch[temp.startNum++] = 0;

		//返回
		return temp;
	}

	//--c
	unsignedBigInt operator--() {
		*this = *this - unsignedBigInt("1");
		return *this;
	}

	//c--
	unsignedBigInt operator--(int i) {
		unsignedBigInt temp = *this;
		*this = temp - unsignedBigInt("1");
		return temp;
		}

	//乘号
	unsignedBigInt operator*(unsignedBigInt b) {
		unsignedBigInt temp("0");
		for (int i = 0; i < strlen(b.ch + b.startNum); i++) {
			int curPos = b.startNum + strlen(b.ch + b.startNum) - 1 - i;
			unsignedBigInt addNum;
			if (b.ch[curPos] != '0') {
				//Accelerate
				int jw = 0;
				for (int j = startNum + strlen(ch+startNum) - 1; j >= startNum || jw != 0; j--) {
					int c1 = ch[j] == 0 ? 0 : ch[j] - '0';
					int c2 = b.ch[curPos] == 0 ? 0 : b.ch[curPos] - '0';

					if (c1*c2 + jw < 10) {
						addNum.ch[--addNum.startNum] = c1 * c2 + jw + '0';
						jw = 0;
					}
					else {
						addNum.ch[--addNum.startNum] = (c1*c2 + jw) % 10 + '0';
						jw = (c1*c2 + jw) / 10;
					}
				}
				//Calculate
				for (int j = 0; j < i; j++)
					addNum.ch[addNum.startNum + strlen(addNum.ch + addNum.startNum)] = '0';

				temp = temp + addNum;
			}
		}
		return temp;
	}

	//除号
	unsignedBigInt operator/(unsignedBigInt b) {
		//排除异常
		if (b == unsignedBigInt("0")) {
			throw "NaN";
		}

		//临时被除数
		unsignedBigInt temp;
		//最终结果
		unsignedBigInt result;

		for (int i = startNum; i < startNum + strlen(ch + startNum); i++) {
			//下移一位
			temp.ch[temp.startNum + strlen(temp.ch + temp.startNum)] = ch[i];
			//开始计算
			unsignedBigInt tempResult=b;
			int wr = 0;
			for (; tempResult <= temp;wr++) {
				tempResult = tempResult + b;
			}
			result.ch[result.startNum + strlen(result.ch + result.startNum)] = wr + '0';
			//计算差值
			tempResult = tempResult - b;
			if (tempResult == unsignedBigInt("0")) {
				temp = unsignedBigInt();
			}
			else {
				temp = temp - tempResult;
			}
		}

		//去0
		for (; strlen(result.ch + result.startNum) > 1 && result.ch[result.startNum] == '0';)
			result.ch[result.startNum++] = 0;

		return result;
	}

	//%
	unsignedBigInt operator%(unsignedBigInt b) {
		return *this-*this/b*b;
	}

	//+=
	void operator+=(unsignedBigInt b) {
		*this = *this + b;
	}

	//-=
	void operator-=(unsignedBigInt b) {
		*this = *this - b;
	}

	//*=
	void operator*=(unsignedBigInt b) {
		*this = *this * b;
	}

	// /=
	void operator/=(unsignedBigInt b) {
		*this = *this / b;
	}

	//%=
	void operator%=(unsignedBigInt b) {
		*this = *this% b;
	}
};
*/

//新无符号大整数类

class unsignedBigInt {
private:
	bool del = false;
public:
	char* ch;
	int startNum = 0;
	int len = 0;

	//初始化
	unsignedBigInt(const char* input) {
		if (del)
			delete[] ch;

		len = (strlen(input) + 1) * 2;
		startNum = strlen(input);
		ch = new char[len];
		memset(ch, 0, len);
		for (int i = 0; i < strlen(input); i++)
			ch[i + startNum] = input[i];

		del = true;
	}
	unsignedBigInt(int num) {
		if (del)
			delete[] ch;

		//临时数组
		int n = 0, temp[intMax];
		if (num == 0) {
			n = 1;
			temp[0] = 0;
		}
		else
			for (; num > 0; num /= 10)
				temp[n++] = num % 10;


		len = (n + 1) * 2;
		startNum = n;
		ch = new char[len];
		memset(ch, 0, len);

		for (int i = 0; i < n; i++)
			ch[startNum + i] = temp[n - i - 1] + '0';

		del = true;
	}
	unsignedBigInt(void) {
		if (del)
			delete[] ch;

		len = 1;
		startNum = 0;
		ch = new char[len];
		memset(ch, 0, len);

		del = true;
	}
	unsignedBigInt(int num, int sizen) {
		if (del)
			delete[] ch;

		len = (sizen + 1) * 2;
		startNum = sizen;
		ch = new char[len];
		memset(ch, 0, len);

		if (num >= 0) {
			int n = 0, temp[intMax];
			if (num == 0) {
				n = 1;
				temp[0] = 0;
			}
			else
				for (; num > 0; num /= 10)
					temp[n++] = num % 10;

			for (int i = 0; i < n; i++)
				ch[startNum + i] = temp[n - i - 1] + '0';
		}

		del = true;
	}

	//析构
	~unsignedBigInt() {
		if (del)
			delete[] ch;
	}

	//计算真实长度
	int realLength(const unsignedBigInt& b) {
		return strlen(b.ch + b.startNum);
	}

	//复制构造函数
	unsignedBigInt(const unsignedBigInt& b) {
		if (del)
			delete[] ch;

		len = b.len;
		startNum = b.startNum;
		ch = new char[len];
		for (int i = 0; i < len; i++)
			ch[i] = b.ch[i];

		del = true;
	}

	//输入输出
	friend ostream& operator<<(ostream& output, const unsignedBigInt& bi);
	friend istream& operator>>(istream& input, unsignedBigInt& bi);

	//赋值
	unsignedBigInt& operator=(const unsignedBigInt& b) {
		//检查自身赋值
		if (this == &b)
			return *this;

		if (del)
			delete[] ch;

		len = b.len;
		startNum = b.startNum;
		ch = new char[len];
		for (int i = 0; i < len; i++)
			ch[i] = b.ch[i];

		del = true;
		return *this;
	}
	unsignedBigInt& operator=(const char* b) {
		if (del)
			delete[] ch;

		len = (strlen(b) + 1) * 2;
		startNum = strlen(b);
		memset(ch, 0, len);

		for (int i = 0; i < strlen(b); i++)
			ch[i + startNum] = b[i];

		del = true;
		return *this;
	}
	unsignedBigInt& operator=(int num) {
		if (del)
			delete[] ch;

		//临时数组
		int n = 0, temp[intMax];
		if (num == 0) {
			n = 1;
			temp[0] = 0;
		}
		else
			for (; num > 0; num /= 10)
				temp[n++] = num % 10;


		len = (n + 1) * 2;
		startNum = n;
		ch = new char[len];
		memset(ch, 0, len);

		for (int i = 0; i < n; i++)
			ch[startNum + i] = temp[n - i - 1] + '0';

		del = true;
		return *this;
	}

	//比较符
	//小于
	bool operator<(const unsignedBigInt& b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) < 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) < strlen(b.ch + b.startNum) ? true : false;
	}

	//大于
	bool operator>(const unsignedBigInt& b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) > 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) > strlen(b.ch + b.startNum) ? true : false;
	}

	//小于等于
	bool operator<=(const unsignedBigInt& b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) <= 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) < strlen(b.ch + b.startNum) ? true : false;
	}

	//大于等于
	bool operator>=(const unsignedBigInt& b) {
		return (strcmp(ch + startNum, b.ch + b.startNum) >= 0 && strlen(ch + startNum) == strlen(b.ch + b.startNum)) || strlen(ch + startNum) > strlen(b.ch + b.startNum) ? true : false;
	}

	//等于等于
	bool operator==(const unsignedBigInt& b) {
		return strcmp(ch + startNum, b.ch + b.startNum) == 0 ? true : false;
	}

	//运算符
	//加号
	unsignedBigInt operator+(const unsignedBigInt& b) {
		unsignedBigInt temp(-1, max(realLength(*this), realLength(b)) + 2);
		int jw = 0;
		int test = realLength(*this);

		for (int i = 0; realLength(*this) > i || realLength(b) > i || jw != 0; i++) {
			//判断加数
			int j1 = realLength(*this) <= i ? 0 : ch[startNum + strlen(ch + startNum) - i - 1] - '0';
			int j2 = realLength(b) <= i ? 0 : b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] - '0';

			//运算
			temp.ch[--temp.startNum] = (j1 + j2 + jw) % 10 + '0';
			jw = (j1 + j2 + jw) / 10;
		}

		//返回
		return temp;
	}

	//++c
	unsignedBigInt operator++() {
		*this = *this + unsignedBigInt("1");
		return *this;
	}

	//c++
	unsignedBigInt operator++(int i) {
		unsignedBigInt temp = *this;
		*this = temp + unsignedBigInt("1");
		return temp;
	}

	//减号
	unsignedBigInt operator-(const unsignedBigInt& b) {
		if (*this == b)
			return unsignedBigInt(0);

		unsignedBigInt temp(-1, max(realLength(*this), realLength(b)) + 2);
		int jw = 0;

		for (int i = 0; realLength(*this) > i || realLength(b) > i; i++) {
			//判断被减数与减数
			int j1 = realLength(*this) <= i ? 0 : ch[startNum + strlen(ch + startNum) - i - 1] - '0';
			int j2 = realLength(b) <= i ? 0 : b.ch[b.startNum + strlen(b.ch + b.startNum) - i - 1] - '0';

			//运算
			if (j1 - jw - j2 < 0) {
				temp.ch[--temp.startNum] = 10 + j1 - jw - j2 + '0';
				jw = 1;
			}
			else {
				temp.ch[--temp.startNum] = j1 - jw - j2 + '0';
				jw = 0;
			}
		}

		//修正
		for (; temp.ch[temp.startNum] == '0';)
			temp.ch[temp.startNum++] = 0;

		//返回
		return temp;
	}

	//--c
	unsignedBigInt operator--() {
		*this = *this - unsignedBigInt("1");
		return *this;
	}

	//c--
	unsignedBigInt operator--(int i) {
		unsignedBigInt temp = *this;
		*this = temp - unsignedBigInt("1");
		return temp;
	}

	//乘号
	unsignedBigInt operator*(const unsignedBigInt& b) {
		unsignedBigInt temp(0, realLength(*this) + realLength(b) + 2);
		for (int i = 0; i < strlen(b.ch + b.startNum); i++) {
			int curPos = b.startNum + strlen(b.ch + b.startNum) - 1 - i;
			unsignedBigInt addNum(-1, realLength(*this) + realLength(b) + 2);
			if (b.ch[curPos] != '0') {
				//Accelerate
				int jw = 0;
				for (int j = startNum + strlen(ch + startNum) - 1; j >= startNum || jw != 0; j--) {
					int c1 = ch[j] == 0 ? 0 : ch[j] - '0';
					int c2 = b.ch[curPos] == 0 ? 0 : b.ch[curPos] - '0';

					if (c1 * c2 + jw < 10) {
						addNum.ch[--addNum.startNum] = c1 * c2 + jw + '0';
						jw = 0;
					}
					else {
						addNum.ch[--addNum.startNum] = (c1 * c2 + jw) % 10 + '0';
						jw = (c1 * c2 + jw) / 10;
					}
				}
				//Calculate
				for (int j = 0; j < i; j++)
					addNum.ch[addNum.startNum + strlen(addNum.ch + addNum.startNum)] = '0';

				temp = temp + addNum;
			}
		}
		return temp;
	}

	//除号
	unsignedBigInt operator/(const unsignedBigInt& b) {
		//临时被除数
		unsignedBigInt temp(-1, max(realLength(*this), realLength(b)) + 2);
		//最终结果
		unsignedBigInt result(-1, max(realLength(*this), realLength(b)) + 2);

		for (int i = startNum; i < startNum + strlen(ch + startNum); i++) {
			//下移一位
			temp.ch[temp.startNum + strlen(temp.ch + temp.startNum)] = ch[i];
			//开始计算
			unsignedBigInt tempResult = b;
			int wr = 0;
			for (; tempResult <= temp; wr++) {
				tempResult = tempResult + b;
			}
			result.ch[result.startNum + strlen(result.ch + result.startNum)] = wr + '0';
			//计算差值
			tempResult = tempResult - b;
			if (tempResult == temp) {
				temp = unsignedBigInt(-1, max(realLength(*this), realLength(b)) + 2);
			}
			else {
				temp = temp - tempResult;
			}
		}

		//去0
		for (; strlen(result.ch + result.startNum) > 1 && result.ch[result.startNum] == '0';)
			result.ch[result.startNum++] = 0;

		return result;
	}

	//%
	unsignedBigInt operator%(const unsignedBigInt& b) {
		return *this - *this / b * b;
	}

	//+=
	void operator+=(const unsignedBigInt& b) {
		*this = *this + b;
	}

	//-=
	void operator-=(const unsignedBigInt& b) {
		*this = *this - b;
	}

	//*=
	void operator*=(const unsignedBigInt& b) {
		*this = *this * b;
	}

	// /=
	void operator/=(const unsignedBigInt& b) {
		*this = *this / b;
	}

	//%=
	void operator%=(const unsignedBigInt& b) {
		*this = *this % b;
	}
};


//有符号大整数类
class bigInt {
public:
	bool op = true;
	unsignedBigInt ubi;

	//构造函数
	bigInt() {
		ubi = unsignedBigInt();
	}
	bigInt(const char* b) {
		if (b[0] == '-') {
			ubi = unsignedBigInt(b + 1);
			op = false;
		}
		else {
			ubi = unsignedBigInt(b);
			op = true;
		}
	}
	bigInt(int b) {
		if (b < 0) {
			ubi = unsignedBigInt(-b);
			op = false;
		}
		else {
			ubi = unsignedBigInt(b);
			op = true;
		}
	}
	bigInt(int num, int sizen) {
		if (num < 0) {
			ubi = unsignedBigInt(-num, sizen);
			op = false;
		}
		else {
			ubi = unsignedBigInt(num, sizen);
			op = true;
		}
	}

	//复制函数
	bigInt(const bigInt& b) {
		op = b.op;
		ubi = b.ubi;
	}

	//赋值函数
	bigInt& operator=(const bigInt& b) {
		op = b.op;
		ubi = b.ubi;

		return *this;
	}
	bigInt& operator=(const char* b) {
		if (b[0] == '-') {
			ubi = unsignedBigInt(b + 1);
			op = false;
		}
		else {
			ubi = unsignedBigInt(b);
			op = true;
		}

		return *this;
	}
	bigInt& operator=(int b) {
		if (b < 0) {
			ubi = unsignedBigInt(-b);
			op = false;
		}
		else {
			ubi = unsignedBigInt(b);
			op = true;
		}

		return *this;
	}

	//比较部分
	//大于
	bool operator>(const bigInt& b) {
		if (op != b.op)
			return op > b.op ? true : false;
		else
			return op ? ubi > b.ubi:ubi < b.ubi;
	}
	//大于等于
	bool operator>=(const bigInt& b) {
		if (op != b.op)
			return op > b.op ? true : false;
		else
			return op ? ubi >= b.ubi : ubi <= b.ubi;
	}
	//小于
	bool operator<(const bigInt& b) {
		if (op != b.op)
			return op < b.op ? true : false;
		else
			return op ? ubi < b.ubi : ubi > b.ubi;
	}
	//小于等于
	bool operator<=(const bigInt& b) {
		if (op != b.op)
			return op < b.op ? true : false;
		else
			return op ? ubi <= b.ubi : ubi >= b.ubi;
	}
	//等于等于
	bool operator==(const bigInt& b) {
		return op == b.op || ubi == unsignedBigInt(0) ? ubi == b.ubi : false;
	}
	//不等于
	bool operator!=(const bigInt& b) {
		return !(*this == b);
	}

	//计算部分
	//加法
	bigInt operator+(const bigInt& b) {
		bigInt result;

		if (op == b.op) {
			result.ubi = ubi + b.ubi;
			result.op = op;
		}
		else if (op > b.op) {
			if (ubi >= b.ubi) {
				result.ubi = ubi - b.ubi;
				result.op = true;
			}
			else {
				unsignedBigInt temp = b.ubi;
				result.ubi = temp - ubi;
				result.op = false;
			}
		}
		else {
			if (ubi > b.ubi) {
				result.ubi = ubi - b.ubi;
				result.op = false;
			}
			else {
				unsignedBigInt temp = b.ubi;
				result.ubi = temp - ubi;
				result.op = true;
			}
		}

		return result;
	}
	//减法
	bigInt operator-(const bigInt& b) {
		bigInt temp = b;
		temp.op = !temp.op;
		return *this + temp;
	}
	//负号
	bigInt operator-() {
		return bigInt(0) - *this;
	}
	//乘法
	bigInt operator*(const bigInt& b) {
		bigInt result;

		if (op == b.op) {
			result.ubi = ubi * b.ubi;
			result.op = true;
		}
		else {
			result.ubi = ubi * b.ubi;
			result.op = false;
		}

		return result;
	}
	//除法
	bigInt operator/(const bigInt& b) {
		bigInt result;

		if (op == b.op) {
			result.ubi = ubi / b.ubi;
			result.op = true;
		}
		else {
			result.ubi = ubi / b.ubi;
			result.op = false;
		}

		return result;
	}
	//%
	bigInt operator%(const bigInt& b) {
		return *this - *this / b * b;
	}

	//++c
	bigInt operator++() {
		*this = *this + bigInt(1);
	}
	//c++
	bigInt operator++(int b) {
		*this = *this + bigInt(b);
		return *this - bigInt(b);
	}
	//--c
	bigInt operator--() {
		*this = *this - bigInt(1);
	}
	//c--
	bigInt operator--(int b) {
		*this = *this - bigInt(b);
		return *this + bigInt(b);
	}

	//+=
	void operator+=(const bigInt& b) {
		*this = *this + b;
	}
	//-=
	void operator-=(const bigInt& b) {
		*this = *this - b;
	}
	//*=
	void operator*=(const bigInt& b) {
		*this = *this * b;
	}
	// /=
	void operator/=(const bigInt& b) {
		*this = *this / b;
	}
	//%=
	void operator%=(const bigInt& b) {
		*this = *this % b;
	}
};

//输入输出流重载
//无符号大整数
ostream& operator<<(ostream& output, const unsignedBigInt& bi) {
	output << bi.ch + bi.startNum;
	return output;
}
istream& operator>>(istream& input, unsignedBigInt& bi) {
	char ch[maxNum];
	input >> ch;
	bi = unsignedBigInt(ch);
	return input;
}

//有符号大整数
ostream& operator<<(ostream& output, const bigInt& bi) {
	output << (!bi.op ? "-" : "") << bi.ubi;
	return output;
}
istream& operator>>(istream& input, bigInt& bi) {
	input >> bi.ubi;
	if (bi.ubi.ch[bi.ubi.startNum] == '-') {
		bi.op = false;
		bi.ubi.ch[bi.ubi.startNum++] = 0;
	}
	return input;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	bigInt a, b;
	cin >> a >> b;
	a /= b;
	cout << a;
	return 0;
}