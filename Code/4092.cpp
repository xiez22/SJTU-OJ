#include "iostream"
using namespace std;

class	 Matrix {
public:
	int row = 0, col = 0;
	bool status = true;
	double **data;

	double operator() (int i, int j) {
		status = true;
		return data[i+1][j+1];
	}

	Matrix(void) {
		status = true;
	}

	Matrix(const Matrix &table) {
		status = true;
		row = table.row;
		col = table.col;

		data = new double*[row + 1];
		for (int i = 1; i <= row; i++) {
			data[i] = new double[col + 1];
			for (int j = 1; j <= col; j++)
				data[i][j] = table.data[i][j];
		}
	}

	Matrix &operator=(const Matrix &table) {
		status = true;
		row = table.row;
		col = table.col;

		data = new double*[row + 1];
		for (int i = 1; i <= row; i++) {
			data[i] = new double[col + 1];
			for (int j = 1; j <= col; j++)
				data[i][j] = table.data[i][j];
		}

		return *this;
	}

	Matrix &operator+=(const Matrix &table) {
		status = true;
		if (table.row != row || table.col != col) {
			status = false;
			return *this;
		}
		for (int i = 1; i <= row; i++)
			for (int j = 1; j <= col; j++)
				data[i][j] += table.data[i][j];
	}

	Matrix &operator*=(const Matrix &table) {
		status = true;
		if (col != table.row) {
			status = false;
			return *this;
		}
		//存储原来的数据
		Matrix temp;
		temp = *this;

		//申请新的空间
		data = new double*[row+1];
		for (int i = 1; i <= row; i++) {
			data[i] = new double[table.col + 1];
			for (int j = 1; j <= table.col; j++) {
				data[i][j] = 0;
				//向量乘法
				for (int n = 1; n <= col; n++) {
					data[i][j] += temp.data[i][n] * table.data[n][j];
				}
			}
		}

	//修改
			col = table.col;
		return *this;
	}
};

istream &operator>>(istream &input, Matrix &table) {
	table.status = true;
	input >> table.row >> table.col;
	table.data = new double*[table.row+1];
	for (int i = 1; i <= table.row; i++) {
		table.data[i] = new double[table.col+1];
		for (int j = 1; j <= table.col; j++)
			input >> table.data[i][j];
	}
	return input;
}
ostream &operator<<(ostream &output, const Matrix &table) {
	for (int i = 1; i <= table.row; i++) {
		for (int j = 1; j <= table.col; j++) {
			output << table.data[i][j]<<(j<table.col?" ":"");
		}
		if(i<table.row)
			cout << endl;
	}
	return output;
}

int main() {
	Matrix table1, table2;
	cin >> table1 >> table2;

	cout << table1(table1.row / 2, table1.col / 2) << endl<<endl;
	table1 *= table2;
	if (!table1.status) {
		cout << "ERROR!" << endl << endl;
	}
	else
		cout << table1 << endl << endl;

	table1 += table2;
	if (!table1.status) {
		cout << "ERROR!" << endl << endl;
	}
	else
		cout << table1 << endl << endl;

	table1 = table2;
	if (!table1.status) {
		cout << "ERROR!";
	}
	else
		cout << table1;

	return 0;
}