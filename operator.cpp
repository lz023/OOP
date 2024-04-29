#include<iostream>
using namespace std;

class MyString
{
	friend ostream& operator<<(ostream&, const MyString&);
	friend istream& operator>>(istream&, MyString&);

private:
	char* str;
	int length;
	int stringLength(char* a)
	{
		int count = 0;
		for (int i = 0; a[i] != '\0'; i++)
		{
			count++;
		}
		return count;
	}

	void stringcpy(char* array, char* arr)
	{
		int i = 0;
		for (i; array[i] != '\0'; i++)
		{
			arr[i] = array[i];
		}
		arr[i] = '\0';
	}

	char* StringConcatenate(char* string1, char* string2)
	{
		int len = stringLength(string1);
		int len1 = stringLength(string2);
		int tlen = len + len1;

		char* arr = new char[tlen + 1];
		int j = 0;
		for (int i = 0; i < len; i++)
		{
			arr[j] = string1[i];
			j++;
		}
		for (int i = 0; i < len1; i++)
		{
			arr[j] = string2[i];
			j++;
		}
		arr[j] = '\0';
		return arr;
	}


public:
	MyString operator+(const MyString);
	MyString& operator=(const MyString&);
	bool operator<(MyString);
	MyString()
	{
		str = new char('\0');
		length = 0;
	}
	~MyString()
	{
		delete[] str;
	}

	MyString(const MyString& a)
	{
		str = new char[a.length + 1];
		stringcpy(a.str, str);
		length = a.length;
	}

	bool operator!()
	{
		return(length == 0);
	}

	char& operator[](int i)
	{
		if (i < length)
		{
			return str[i];
		}
		cout << "out of bound";
	}

	MyString operator() (int index, int len)
	{
		MyString res;
		res.length = len;
		delete res.str;
		res.str = new char[len + 1];
		int j = 0;
		for (int i = index; str[i] != '\0' && j < len; i++)
		{
			res.str[j] = str[i];
			j++;
		}
		res.str[j] = '\0';
		return res;

	}
};


MyString& MyString:: operator=(const MyString& a)
{
	if (this != &a)
	{
		delete str;
		str = new char[a.length + 1];
		stringcpy(a.str, str);
		length = a.length;
	}
	return *this;
}
MyString MyString::operator+(const MyString a)
{
	MyString res;
	res.str = StringConcatenate(str, a.str);
	res.length = stringLength(res.str);
	return res;
}

bool MyString:: operator< (MyString a)
{
	int c = 0;
	char ch, ch1;
	for (int i = 0; str[i] != '\0' && a.str[i] != '\0' && c == 0; i++)
	{
		if (str[i] >= 'A' && a[i] <= 'Z')
		{
			ch = str[i] + 32;
		}
		else
		{
			ch = str[i];
		}
		if (a.str[i] >= 'A' && a.str[i] <= 'Z')
		{
			ch1 = a.str[i] + 32;
		}
		else
		{
			ch1 = a.str[i];
		}
		if (ch > ch1)
		{
			c = 1;
		}
	}
	return c;
}

ostream& operator<<(ostream& cout, const MyString& a)
{
	cout << a.str;
	return cout;
}

istream& operator>>(istream& input, MyString& a)
{
	char arr[80];
	input >> arr;
	int size = a.stringLength(arr) + 1;
	a.length = size - 1;
	delete a.str;
	a.str = new char[size];
	a.stringcpy(arr, a.str);
	return input;

}

void main()
{
	MyString str1, str2, str3, str4;

	if (!str1)
	{
		cout << "String 1 is Empty.\n";
		cout << "Str 1 = " << str1 << endl << endl << endl;
	}

	cout << "Enter String 1:\t";
	cin >> str1;


	cout << "Enter String 2:\t";
	cin >> str2;


	cout << "\n\n\nUser Entered:\n";
	cout << "String 1 = " << str1 << endl;
	cout << "String 2 = " << str2 << endl << endl << endl;

	cout << "Before str1 = str1; str1 = " << str1 << endl;
	str1 = str1;
	cout << "After str1 = str1, str1 = " << str1 << endl << endl << endl;


	cout << "Before str4 = str3 = str1+str2\n";
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;

	str4 = str3 = str1 + str2;


	cout << "\n\n\nAfter str4 = str3 = str1+str2\n";
	cout << "str1 = " << str1 << endl;
	cout << "str2 = " << str2 << endl;
	cout << "str3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;

	cout << "\n\n\nEnter String 3:\t";
	cin >> str3;

	cout << "\n\n\nEnter String 4:\t";
	cin >> str4;


	cout << "\n\n\nstr3 = " << str3 << endl;
	cout << "str4 = " << str4 << endl;

	if (str3 < str4)
		cout << "String 3 is Less than String 4.\n";
	else
		cout << "String 3 is NOT Less than String 4.\n";

	MyString str5 = str1 + str2;
	cout << "\n\n\nStr5:\t" << str5 << endl;
	cout << "Str5[7]:\t" << str5[7] << endl;
	str5[7] = '$';

	cout << "\n\nStr5:\t" << str5 << endl;



}
