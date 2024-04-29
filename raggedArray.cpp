#include <iostream>
using namespace std;

class Ragged
{
	int** matrix;
	int rows;
	int cols;
public:
	Ragged(int r = 0, int c = 0)
	{
		rows = r;
		cols = c;
		matrix = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			matrix[i] = new int[cols];
		}
	}
	~Ragged()
	{
		if (matrix != 0)
		{
			for (int i = 0; i < rows; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
		}
	}
	void Input()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << "Enter element:\t";
				cin >> matrix[i][j];
			}
		}
	}
	void Print()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
	void RaggedArray()
	{
		int** m = new int* [rows];
		int* arr = new int[rows];
		for (int i = 0; i < rows; i++)
		{
			int c = 0;
			for (int j = 0; j < cols; j++)		//counts non zero elements per row
			{
				if (matrix[i][j] != 0)
				{
					c++;
				}
			}
			arr[i] = c;
			m[i] = new int[c];
		}
		for (int i = 0; i < rows; i++)		//stores the non zero elements in new matrix
		{
			int k = 0;
			for (int j = 0; j < cols; j++)
			{
				if (matrix[i][j] != 0)
				{
					m[i][k] = matrix[i][j];
					k++;
				}
			}
		}	
		for (int i = 0; i < rows; i++)		//prints the elements (cannot use normal print function as the number of cols is not constant)
		{
			for (int j = 0; j < arr[i]; j++)
			{
				cout << m[i][j] << "\t";
			}
			cout << endl;
		}
	}
};



void main()
{
	int r, c;
	cout << "Enter Rows:\t";
	cin >> r;
	cout << "Enter Columns:\t";
	cin >> c;
	cout << endl;
	Ragged obj(r, c);
	obj.Input();
	obj.Print();
	cout << endl;
	obj.RaggedArray();
	cout << endl << endl;

}

