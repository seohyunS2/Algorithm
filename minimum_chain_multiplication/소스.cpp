#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "MInfo.h"
#include "Tokenizer.h"
#include "trim.h"

//#define MIN(A, B) ((A)>(B)?(B):(A))

using namespace std;

template<typename T>
void print_element(T st) {
	cout << st.get_name() << "\t" << st.get_row() << "\t" << st.get_col() << endl;//print element
}

template<typename T>
void print_element_2(T d) {
	cout << d << "\t";//print element
}

vector<MInfo>read_matrix_info(char *fName)
{
	ifstream fin(fName);
	string buf;
	Tokenizer str;
	string name;
	int row;
	int col;
	vector<MInfo>mats;//���� ����
	while (getline(fin, buf))
	{
		str.set(buf);
		name = trim(str.next());
		string tmp = str.next();
		row = atoi(tmp.c_str());
		tmp = str.next(); col = atoi(tmp.c_str());
		mats.push_back(MInfo(name, row, col));//���� ����
	}
	return mats;
}

vector<int>make_dimensions(vector<MInfo>mats)
{
	vector<int> d(mats.size() + 1);
	d[0] = mats[0].get_row();
	for (int i = 0; i < mats.size(); i++)
		d[i + 1] = mats[i].get_col();
	return d;
}

vector<vector<int>>make_matrix(vector<MInfo>mats) {
	vector<vector<int>> matrix;
	int nrow, ncol;
	nrow = ncol = mats.size();
	for (int i = 0; i < nrow; i++) {
		vector<int>nrow(ncol);
		matrix.push_back(nrow);
	}
	return matrix;
}

int minmulti(int n, vector<int> &d, vector<vector<int> >& M, vector<vector<int> > &P) {

	int s2;
	int z;
	for (int diagonal = 1; diagonal <= n; diagonal++) {
		for (int i = 1; i <= n - diagonal; i++) {
			int j = i + diagonal;
			int s1 = 1000000;//���� �� ��(�ƹ��ų� �־���)
			for (int k = i; k <= j - 1; k++) {
				s2 = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
				if (s1>s2) {
					z = k;//
					s1 = s2;//�� ����
				}
			}

			M[i][j] = s1;
			P[i][j] = z;
		}
	}
	return M[0][n - 1];
}

void order(int i, int j, vector<vector<int> > P, vector<MInfo> mats) {
	if (i == j) {
		cout << mats[i - 1].get_name();
	}
	else {
		int k = P[i][j];
		cout << "(";
		order(i, k, P, mats);
		cout << ",";
		order(k + 1, j, P, mats);
		cout << ")";
	}
}
int main(int argc, char* argv[])
{
	char *fName = "lab5-matrix.txt";//1.��ü ��� 2.�����̸���

	vector<MInfo> mats = read_matrix_info(fName);
	for_each(mats.begin(), mats.end(), print_element<MInfo>);

	vector<int> d = make_dimensions(mats);
	for_each(d.begin(), d.end(), print_element_2<int>);

	vector<vector<int> > M = make_matrix(mats);		// ��� M�� �����ؼ� �ʱ�ȭ�Ѵ�.
	vector<vector<int> > P = make_matrix(mats);		// ��� P�� �����ؼ� �ʱ�ȭ�Ѵ�.

	P[mats.size() - 1][mats.size() - 1];

	cout << endl;

	minmulti(M.size() - 1, d, M, P);
	order(1, M.size() - 1, P, mats);

}
