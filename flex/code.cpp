#include<iostream>
#include<fstream>
using namespace std;

int stringLength(char* a)
{
	int count = 0;
	for (int i = 0; a[i] != '\0'; i++)
	{
		count++;
	}
	return count;
}
class FlexEvaluation
{
	friend void UpdateStatistics(FlexEvaluation*);
	friend FlexEvaluation* ReadDataFromFile(ifstream&);
	friend void PrintAll(FlexEvaluation*, int);
	friend bool IsSubString(char*, char*);
	friend FlexEvaluation* SearchStudentsByKeyWord(FlexEvaluation*, int&, char*);

private:

	char* roll_no;
	char* name;
	static int totalNoQuiz, totalNoAssignments, totalStudents;
	static int* quizstats;
	static int* assignmentstats;
	static int* totalQuiz;
	static int* totalAssignment;
	int* quiz;
	int* assignment;
	int totalmarks;



	void stringcpy(char* array, char* arr)
	{
		int i = 0;
		for (i; array[i] != '\0'; i++)
		{
			arr[i] = array[i];
		}
		arr[i] = '\0';
	}
	void arraycpy(int* array, int* arr, int size)
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = array[i];
		}

	}
public:

	FlexEvaluation()
	{
		quiz = 0;
		assignment = 0;
		roll_no = 0;
		name = 0;
		totalmarks = 0;
	}

	~FlexEvaluation()
	{
		if (quiz && assignment && roll_no && name)
		{
			delete[] quiz;
			delete[] assignment;
			delete[] roll_no;
			delete[] name;
		}
	}

	FlexEvaluation& operator=(const FlexEvaluation& a)
	{
		if (this != &a)
		{
			if (quiz && assignment && roll_no && name)
			{
				delete[] quiz;
				delete[] assignment;
				delete[] roll_no;
				delete[] name;
			}

			roll_no = new char[stringLength(a.roll_no) + 1];
			stringcpy(a.roll_no, roll_no);
			name = new char[stringLength(a.name) + 1];
			stringcpy(a.name, name);
			quiz = new int[totalNoQuiz];
			arraycpy(a.quiz, quiz, totalNoQuiz);
			assignment = new int[totalNoAssignments];
			arraycpy(a.assignment, assignment, totalNoAssignments);
			totalmarks = a.totalmarks;
		}
		return *this;
	}
	void SetRollNumber(char* temp)
	{
		roll_no = new char[stringLength(temp) + 1];
		stringcpy(temp, roll_no);
	}
	void SetName(char* temp)
	{
		name = new char[stringLength(temp) + 1];
		stringcpy(temp, name);
	}
	void SetQuiz(ifstream& file)
	{

		int size = totalNoQuiz;
		quiz = new int[size];
		for (int i = 0; i < size; i++)
		{
			int s = 0;
			file >> s;
			quiz[i] = s;
		}
	}
	void SetAssignment(ifstream& file)
	{
		int size = totalNoAssignments;
		assignment = new int[size];
		for (int i = 0; i < size; i++)
		{
			int a = 0;
			file >> a;
			assignment[i] = a;
		}
	}
	void SetTotalMarks()
	{

		int sum = 0;
		for (int i = 0; i < totalNoQuiz; i++)
		{
			sum += quiz[i];
		}
		for (int i = 0; i < totalNoQuiz; i++)
		{
			sum += assignment[i];
		}

		totalmarks = sum;
	}
	FlexEvaluation(const FlexEvaluation& a)
	{

		roll_no = new char[stringLength(a.roll_no) + 1];
		stringcpy(a.roll_no, roll_no);
		name = new char[stringLength(a.name) + 1];
		stringcpy(a.name, name);
		quiz = new int[totalNoQuiz];
		arraycpy(a.quiz, quiz, totalNoQuiz);
		assignment = new int[totalNoAssignments];
		arraycpy(a.assignment, assignment, totalNoAssignments);
		totalmarks = a.totalmarks;
	}



	void Print()
	{
		cout << roll_no << "\t" << name << "\t";
		for (int i = 0; i < totalNoQuiz; i++)
		{
			cout << quiz[i] << "\t";
		}
		for (int i = 0; i < totalNoAssignments; i++)
		{
			cout << assignment[i] << "\t";
		}
		cout << totalmarks;

	}
	static void PrintStats()
	{
		int s1 = totalNoQuiz * 3;
		int s2 = totalNoAssignments * 3;
		cout << "\tQ1 min\tQ2 min\tQ3 min\tQ4 min\tQ1 max\tQ2 max\tQ3 max\tQ4 max\tQ1 avg\tQ2 avg\tQ3 avg\tQ4 avg\n";
		cout << "Quiz: \t";
		for (int i = 0; i < s1; i++)
		{
			cout << quizstats[i] << "\t";
		}
		cout << endl << endl;
		cout << "\t\tA1 min\tA2 min\tA3 min\tA4 min\tA1 max\tA2 max\tA3 max\tA4 max\tA1 avg\tA2 avg\tA3 avg\tA4 avg\n";
		cout << "Assignment: \t";
		for (int i = 0; i < s2; i++)
		{
			cout << assignmentstats[i] << "\t";
		}
		cout << endl << endl;
		cout << "\t\t" << "Q1\tQ2\tQ3\tQ4\n";
		cout << "Quiz total:\t";
		for (int i = 0; i < totalNoQuiz; i++)
		{
			cout << totalQuiz[i] << "\t";
		}
		cout << endl << endl;
		cout << "\t\t\t" << "A1\tA2\tA3\tA4\n";  
		cout << "Assignment total:\t";
		for (int i = 0; i < totalNoAssignments; i++)
		{
			cout << totalAssignment[i] << "\t";
		}
		cout << "\n-------------------------------------------------------------------------------------------------\n";
		cout << endl;
	}
	static void DeleteStatic()
	{

		if (quizstats && assignmentstats && totalQuiz && totalAssignment)
		{
			delete[] quizstats;
			delete[] assignmentstats;
			delete[] totalQuiz;
			delete[] totalAssignment;
		}
	}
	static int GetTotalStudents()
	{
		return totalStudents;
	}
	int getTotal()
	{
		return totalmarks;
	}

};


int FlexEvaluation::totalStudents = 0;
int FlexEvaluation::totalNoQuiz = 0;
int FlexEvaluation::totalNoAssignments = 0;
int* FlexEvaluation::quizstats = 0;
int* FlexEvaluation::assignmentstats = 0;
int* FlexEvaluation::totalQuiz = 0;
int* FlexEvaluation::totalAssignment = 0;



FlexEvaluation* ReadDataFromFile(ifstream& file)
{
	int temp = 0;
	file >> temp;	//49
	FlexEvaluation::totalStudents = temp;
	file >> temp;	 //4
	FlexEvaluation::totalNoQuiz = temp;
	file >> temp;	//4
	FlexEvaluation::totalNoAssignments = temp;
	int size = FlexEvaluation::totalNoQuiz;
	FlexEvaluation::totalQuiz = new int[size];

	for (int i = 0; i < size; i++)
	{
		file >> temp;
		FlexEvaluation::totalQuiz[i] = temp;
	}

	int size1 = FlexEvaluation::totalNoAssignments;
	FlexEvaluation::totalAssignment = new int[size1];
	for (int i = 0; i < size1; i++)
	{
		file >> temp;
		FlexEvaluation::totalAssignment[i] = temp;
	}

	int total = FlexEvaluation::totalStudents;
	FlexEvaluation* studentlist = new FlexEvaluation[total];
	char temp1[80];
	for (int i = 0; i < total; i++)
	{
		file >> temp1;
		studentlist[i].SetRollNumber(temp1);
		file.ignore();
		file.getline(temp1, 80);
		studentlist[i].SetName(temp1);
		
		studentlist[i].SetQuiz(file);
		studentlist[i].SetAssignment(file);
		studentlist[i].SetTotalMarks();
	}
	return studentlist;	
}
void UpdateStatistics(FlexEvaluation* data)	
{
	int size = FlexEvaluation::totalNoQuiz;
	FlexEvaluation::quizstats = new int[size * 3];
	int total = FlexEvaluation::totalStudents;
	int k = 0;
	for (int i = 0; i < size; i++)	
	{
		int min = 10000;
		for (int j = 0; j < total; j++)	
		{
			if (data[j].quiz[i] < min)
			{
				min = data[j].quiz[i];
			}
		}
		FlexEvaluation::quizstats[k] = min;
		k++;	
	}
	for (int i = 0; i < size; i++)
	{
		int max = 0;
		for (int j = 0; j < total; j++)	
		{
			if (data[j].quiz[i] > max)
			{
				max = data[j].quiz[i];
			}
		}
		FlexEvaluation::quizstats[k] = max;
		k++;
	}
	for (int i = 0; i < size; i++)	
	{
		int avg = 0, sum = 0;
		for (int j = 0; j < total; j++)	
		{
			sum += data[j].quiz[i];
		}
		avg = sum / total;
		FlexEvaluation::quizstats[k] = avg;
		k++;	
	}



	int size1 = FlexEvaluation::totalNoAssignments;
	k = 0;
	FlexEvaluation::assignmentstats = new int[size1 * 3];
	for (int i = 0; i < size1; i++)	
	{
		int min = 10000;
		for (int j = 0; j < total; j++)	
		{
			if (data[j].assignment[i] < min)
			{
				min = data[j].assignment[i];
			}
		}
		FlexEvaluation::assignmentstats[k] = min;
		k++;	
	}
	for (int i = 0; i < size1; i++)	
	{
		int max = 0;
		for (int j = 0; j < total; j++)	
		{
			if (data[j].assignment[i] > max)
			{
				max = data[j].assignment[i];
			}
		}
		FlexEvaluation::assignmentstats[k] = max;
		k++;	
	}
	for (int i = 0; i < size1; i++)
	{
		int avg = 0, sum = 0;
		for (int j = 0; j < total; j++)	
		{
			sum += data[j].assignment[i];
		}
		avg = sum / total;
		FlexEvaluation::assignmentstats[k] = avg;
		k++;	
	}

}


bool IsSubString(char* str, char* substr)
{

	int i, j;
	int l = strlen(substr);
	for (i = 0, j = 0; str[i] != '\0' && substr[j] != '\0'; i++)
	{
		if (str[i] == substr[j])
		{
			j++;
		}
		else
		{
			j = 0;
		}
	}
	if (j == l)
	{
		return true;
	}
	return false;
}


FlexEvaluation* SearchStudentsByKeyWord(FlexEvaluation* list, int& count, char* sub)
{
	int size = FlexEvaluation::GetTotalStudents();
	count = 0;
	for (int i = 0; i < size; i++)
	{
		if (IsSubString(list[i].roll_no, sub) || IsSubString(list[i].name, sub))
		{
			count++;
		}
	}
	if (count > 0)
	{
		FlexEvaluation* temp = new FlexEvaluation[count];
		if (temp)
		{
			int j = 0;
			for (int i = 0; i < size; i++)
			{
				if (IsSubString(list[i].roll_no, sub) || IsSubString(list[i].name, sub))
				{
					temp[j] = list[i];
					j++;
				}
			}
			
		}
		return temp;
	}
	return 0;
}
void SortListByTotal(FlexEvaluation* list)
{
	int size = FlexEvaluation::GetTotalStudents();
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (list[j].getTotal() > list[j + 1].getTotal()) {
				FlexEvaluation temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}


void PrintAll(FlexEvaluation* data, int size)
{
	
	cout << "Roll No\t\tName\t\tQ1\tQ2\tQ3\tQ4\tA1\tA2\tA3\tA4\tTotal\n";
	for (int i = 0; i < size; i++)
	{
		data[i].Print();
		cout << endl;
	}
}
void main()
{
	ifstream file;
	file.open("data.txt");
	FlexEvaluation* studentlist = ReadDataFromFile(file);
	file.close();
	UpdateStatistics(studentlist);
	int size = FlexEvaluation::GetTotalStudents();
	FlexEvaluation::PrintStats();
	PrintAll(studentlist, size);

	cout << "\n----------------------------------------- SEARCH STUDENT BY KEY-WORD ------------------------------------------------\n";
	char arr[10] = { "15L-1234" };
	int count;
	FlexEvaluation* b = SearchStudentsByKeyWord(studentlist, count, arr);
	if (b)
	{
		PrintAll(b, count);
	}
	else
	{
		cout << "Student Not Found\n";
	}
	char arra[10] = { "15L-4023" };
	b = SearchStudentsByKeyWord(studentlist, count, arra);
	if (b)
	{
		PrintAll(b, count);
	}
	else
	{
		cout << "Student Not Found\n";
	}
	cout << "\n------------------------------------------------- SORTED ARRAY ------------------------------------------------------\n";
	SortListByTotal(studentlist);
	PrintAll(studentlist, size);
	FlexEvaluation::DeleteStatic();
	delete[] studentlist;
	delete[] b;
}
