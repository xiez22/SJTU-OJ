#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


//定义一个数类，可接收普通整数、大整数、小数等等作为实例
class Number
{
	//请在此添加‘Number’类的实现代码
	/********** Begin **********/
public:
	vector<int> lnum, rnum;
	//判断是否正常
	bool status = true, is_rnum = false, op = true;

	Number(const Number& other) :lnum(other.lnum), rnum(other.rnum),
		status(other.status), is_rnum(other.is_rnum), op(other.op) {}
	Number(const string& str) {
		int cnt = 0;
		int length = str.length();
		for (int i = 0; i < length; ++i) {
			if (str[i] == '-') {
				if (i == 0) {
					op = false;
				}
				else {
					status = false;
					break;
				}
			}
			else if (str[i] == '.') {
				is_rnum = true;
				++cnt;
			}
			else {
				if (!(str[i] >= '0' && str[i] <= '9')) {
					status = false;
					break;
				}
				if (cnt == 0) {
					lnum.emplace_back(str[i] - '0');
				}
				else if (cnt == 1) {
					rnum.emplace_back(str[i] - '0');
				}
				else {
					status = false;
					break;
				}
			}
		}
	}
	Number(bool op, const vector<int> num_list, int ppos) :op(op) {
		if (ppos <= num_list.size())
			lnum.assign(num_list.begin(), num_list.end() - ppos);
		if (ppos) {
			if (ppos > num_list.size()) {
				rnum = vector<int>(ppos - num_list.size(), 0);
				for (auto p : num_list)
					rnum.emplace_back(p);
			}
			else
				rnum.assign(num_list.end() - ppos, num_list.end());
			is_rnum = true;
		}
	}

	bool check() {
		if (is_rnum && lnum.size() + rnum.size() + 1 > 128) {
			status = false;
		}
		else if (!is_rnum && lnum.size() > 128) {
			status = false;
		}

		return status;
	}

	void cut() {
		if (is_rnum > 0) {
			int cut_num = int(!op) + lnum.size() + rnum.size() + 1 - 128;
			if (rnum.size() >= cut_num) {
				rnum.erase(rnum.end() - cut_num, rnum.end());
			}
		}
	}

	void print() {
		if (!op)
			cout << "-";
		for (auto p : lnum)
			cout << p;
	}
	/********** End **********/
};


//定义一个表达式类，支持任意两个Number类实例的加减乘除操作，计算规则满足一般的数学计算法则
class Expression
{
	//请在此添加‘Expression’类的实现代码
	/********** Begin **********/
	//简化运算结果
	void simplify(Number& num) const {
		int length = num.lnum.size(), pos = 0;
		for (; pos < length - 1; ++pos) {
			if (num.lnum[pos] != 0)
				break;
		}
		if (pos != 0)
			num.lnum.assign(num.lnum.begin() + pos, num.lnum.end());

		if (num.is_rnum) {
			for (pos = num.rnum.size() - 1; pos >= 0; --pos) {
				if (num.rnum[pos] == 0)
					num.rnum.pop_back();
				else
					break;
			}
			if (pos < 0)
				num.is_rnum = false;
		}
		if (num.lnum.empty())
			num.lnum.emplace_back(0);
		if (!num.is_rnum && num.lnum.size() == 1 && num.lnum[0] == 0)
			num.op = true;
	}
	void simplify(vector<int>& num) const {
		int length = num.size(), pos = 0;
		for (; pos < length; ++pos) {
			if (num[pos] != 0)
				break;
		}
		if (pos != length) {
			num.assign(num.begin() + pos, num.end());
		}
		else {
			num = vector<int>(1, 0);
		}
	}
	//转为运算模式数
	int change(const Number& a, const Number& b, vector<int>& an, vector<int>& bn) const {
		int ppos = 0;
		for (auto p : a.lnum)
			an.emplace_back(p);
		for (auto p : b.lnum)
			bn.emplace_back(p);
		//扩充为小数
		if (a.is_rnum || b.is_rnum) {
			ppos = max(a.rnum.size(), b.rnum.size());

			for (int i = 0; i < ppos; ++i) {
				an.emplace_back(i < a.rnum.size() ? a.rnum[i] : 0);
				bn.emplace_back(i < b.rnum.size() ? b.rnum[i] : 0);
			}
		}
		return ppos;
	}
	//比较数字大小
	int compare(const vector<int>& an, const vector<int>& bn) const {
		if (an.size() < bn.size()) {
			return -1;
		}
		else if (an.size() > bn.size()) {
			return 1;
		}
		else {
			int length = an.size();
			for (int i = 0; i < length; ++i) {
				if (an[i] < bn[i])
					return -1;
				if (an[i] > bn[i])
					return 1;
			}
			return 0;
		}
	}
public:
	//对正整数的四则运算
	vector<int> add_raw(const vector<int>& an, const vector<int>& bn) const {
		vector<int> ans;
		int jw = 0;
		for (int i = an.size() - 1, j = bn.size() - 1; jw || i >= 0 || j >= 0;) {
			int x, y;
			if (i >= 0) {
				x = an[i];
				--i;
			}
			else
				x = 0;
			if (j >= 0) {
				y = bn[j];
				--j;
			}
			else
				y = 0;
			if (x + y + jw >= 10) {
				ans.emplace_back(x + y + jw - 10);
				jw = 1;
			}
			else {
				ans.emplace_back(x + y + jw);
				jw = 0;
			}
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}

	vector<int> minus_raw(const vector<int>& an, const vector<int>& bn) const {
		vector<int> ans;
		int jw = 0;
		for (int i = an.size() - 1, j = bn.size() - 1; jw || i >= 0 || j >= 0;) {
			int x, y;
			if (i >= 0) {
				x = an[i];
				--i;
			}
			else
				x = 0;
			if (j >= 0) {
				y = bn[j];
				--j;
			}
			else
				y = 0;
			if (x - y - jw < 0) {
				ans.emplace_back(x - y - jw + 10);
				jw = 1;
			}
			else {
				ans.emplace_back(x - y - jw);
				jw = 0;
			}
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}

	vector<int> times_raw(const vector<int>& an, const vector<int>& bn) const {
		int al = an.size(), bl = bn.size();

		vector<int> ans(1, 0);
		for (int i = bl - 1; i >= 0; --i) {
			vector<int> temp;
			int jw = 0;
			for (int j = al - 1; j >= 0; --j) {
				temp.emplace_back((jw + an[j] * bn[i]) % 10);
				jw = (jw + an[j] * bn[i]) / 10;
			}
			if (jw)
				temp.emplace_back(jw);
			reverse(temp.begin(), temp.end());
			for (int k = 0; k < bl - i - 1; ++k)
				temp.emplace_back(0);
			ans = add_raw(ans, temp);
		}

		return ans;
	}

	int devides_raw(const vector<int>& an_raw, const vector<int>& bn, vector<int>& ans) const {
		int ppos = 0;
		vector<int> an(an_raw);
		int al = an.size(), bl = bn.size();

		//补齐
		for (; al < bl; ++al) {
			an.emplace_back(0);
			++ppos;
		}

		//计算9个bl的乘积值
		vector<vector<int>> fast_ans(10);
		fast_ans[0] = vector<int>(1, 0);
		for (int i = 1; i < 10; ++i) {
			fast_ans[i] = add_raw(fast_ans[i - 1], bn);
		}

		vector<int> temp(an.begin(), an.begin() + bl);
		for (int pos = 0;; ++pos) {
			for (int i = 9; i >= 0; --i) {
				if (compare(temp, fast_ans[i]) >= 0) {
					ans.emplace_back(i);
					temp = minus_raw(temp, fast_ans[i]);
					break;
				}
			}
			simplify(temp);
			if (temp.size() == 1 && temp[0] == 0 && pos + bl >= al) {
				break;
			}
			if (ppos >= 2)
				break;
			//移动到下一位
			if (pos + bl + 1 <= al) {
				temp.emplace_back(an[pos + bl]);
			}
			else {
				++ppos;
				temp.emplace_back(0);
			}
			simplify(temp);
		}

		return ppos;
	}

	Number add(const Number& a, const Number& b) {
		vector<int> an, bn;
		int ppos = change(a, b, an, bn);

		if (a.op && b.op) {
			vector<int> ans = add_raw(an, bn);
			Number ans_num(true, ans, ppos);
			simplify(ans_num);
			return ans_num;
		}
		else if (a.op && !b.op) {
			if (compare(an, bn) >= 0) {
				vector<int> ans = minus_raw(an, bn);
				Number ans_num(true, ans, ppos);
				simplify(ans_num);
				return ans_num;
			}
			else {
				vector<int> ans = minus_raw(bn, an);
				Number ans_num(false, ans, ppos);
				simplify(ans_num);
				return ans_num;
			}
		}
		else if (!a.op && b.op) {
			if (compare(an, bn) >= 0) {
				vector<int> ans = minus_raw(an, bn);
				Number ans_num(false, ans, ppos);
				simplify(ans_num);
				return ans_num;
			}
			else {
				vector<int> ans = minus_raw(bn, an);
				Number ans_num(true, ans, ppos);
				simplify(ans_num);
				return ans_num;
			}
		}
		else {
			vector<int> ans = add_raw(an, bn);
			Number ans_num(false, ans, ppos);
			simplify(ans_num);
			return ans_num;
		}
	}

	Number minus(const Number& a, const Number& b) {
		Number nb(b);
		nb.op = !nb.op;

		return add(a, nb);
	}

	Number times(const Number& a, const Number& b) {
		vector<int> an, bn;
		int ppos = 2 * change(a, b, an, bn);

		if (a.op == b.op) {
			vector<int> ans = times_raw(an, bn);
			Number ans_num(true, ans, ppos);
			simplify(ans_num);
			return ans_num;
		}
		else {
			vector<int> ans = times_raw(an, bn);
			Number ans_num(false, ans, ppos);
			simplify(ans_num);
			return ans_num;
		}
	}

	Number devides(const Number& a, const Number& b) {
		vector<int> an, bn, ans;
		change(a, b, an, bn);
		simplify(an);
		simplify(bn);

		int ppos = devides_raw(an, bn, ans);
		if (bn.size() == 1 && bn[0] == 0) {
			Number ans_num(true, ans, ppos);
			ans_num.status = false;
			return ans_num;
		}
		if (a.op == b.op) {
			Number ans_num(true, ans, ppos);
			simplify(ans_num);
			ans_num.cut();
			return ans_num;
		}
		else {
			Number ans_num(false, ans, ppos);
			simplify(ans_num);
			ans_num.cut();
			return ans_num;
		}
	}
	/********** End **********/
};


//定义main函数
int main()
{
	/********** Begin **********/
	Expression expression;

	string a, b;
	cin >> a >> b;

	expression.devides(a, b).print();

	//请打印输出运算结果，输出结果时无需换行


	/********** End **********/
	return 0;
}
