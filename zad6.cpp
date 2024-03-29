#include "pch.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <typeinfo>
#include <time.h>
#include<ctime>

using namespace std;

class Matrix
{
	int column;
	int row;
	vector<vector<double> > a;


public:

	Matrix(int r, int c)
	{
		column = c;
		row = r;
		a.resize(row, vector<double>(column));
	}

	Matrix(ifstream &x)
	{
		int b;
		int rCounter = 0;
		int cCounter = 0;
		vector<int> number;

		while (x >> b)
		{
			number.push_back(b);
		}
		row = number[0];
		column = number[1];
		a.resize(row, std::vector<double>(column));

		for (int i = 2; i < number.size(); i++)
		{

			a[rCounter][cCounter] = number[i];
			cCounter++;

			if (cCounter == column)
			{
				cCounter = 0;
				rCounter++;
			}
		}
	}


	int elements_s(int r, int c)
	{
		return a[r][c];
	}

	void change_elements(int b, int c, int d)
	{
		a[b][c] = d;
	}

	string row_s(int c)
	{
		string return_to_string = "";

		for (int i = 0; i < column; i++)
		{
			return_to_string += to_string(a[c - 1][i]);
			return_to_string += " ";
		}

		return_to_string += "\n";
		return return_to_string;

	}

	string column_s(int r)
	{
		string stringToReturn = "";

		for (int i = 0; i < row; i++)
		{
			stringToReturn += to_string(a[i][r - 1]);
			stringToReturn += "\n";
		}

		return stringToReturn;
	}

	string matrix_s()
	{
		string stringToReturn = "";

		for (int i = 1; i < row + 1; i++)
		{

			stringToReturn += row_s(i);
		}

		return stringToReturn;

	}

	void elements_add(int n)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				a[i][j] += n;
			}
		}
	}

	void transfer()
	{
		vector<vector<double>> tr;

		tr.resize(column, vector<double>(row));
		a.resize(column, vector<double>(row));
		a = tr;
		int t;
		t = row;
		row = column;
		column = t;

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				tr[j][i] = a[i][j];
			}
		}


	}
	void saveToTxt(string x, string &saved_file)
	{
		time_t now = time(0);
		tm *local_time = localtime(&now);

		string second;
		string minutes;
		string hour;

		if (stoi(to_string(local_time->tm_hour)) < 10)
		{
			hour = "0" + to_string(local_time->tm_hour);
		}
		else
		{
			hour = to_string(local_time->tm_hour);
		}

		if (stoi(to_string(local_time->tm_min)) < 10)
		{
			minutes = "0" + to_string(local_time->tm_min);
		}
		else
		{
			minutes = to_string(local_time->tm_min);
		}

		if (stoi(to_string(local_time->tm_sec)) < 10)
		{
			second = "0" + to_string(local_time->tm_sec);
		}

		else
		{
			second = to_string(local_time->tm_sec);
		}

		ofstream f;
		string fname = "matrix" + hour + minutes + second + x + ".txt";
		f.open(fname);
		{
			f << row << " " << column;
			for (int i = 0; i < row; i++)
			{
				f << "\n";

				for (int j = 0; j < column; j++)
				{
					f << a[i][j] << " ";
				}
			}

		}
		saved_file = fname;
	}
};
int main()
{
	string name_file = "";
	ifstream _file("matrix.txt");

	if (!_file.good())
	{
		cout << "whether the file definitely exists??";
	}

	Matrix m1(_file);
	m1.change_elements(0, 0, 0);
	m1.change_elements(2, 4, 0);
	m1.change_elements(4, 2, 0);
	m1.saveToTxt("change elements", name_file);
	_file.close();
	_file.open(name_file);

	Matrix m2(_file);
	m2.transfer();
	m2.saveToTxt("transposition matrix", name_file);
	_file.close();
	_file.open(name_file);

	Matrix m3(_file);
	m3.elements_add(66);
	m3.saveToTxt("add elements to all", name_file);
	_file.close();

	return 0;
}