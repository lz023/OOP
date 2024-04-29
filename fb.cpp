#include <iostream>
#include<fstream>
using namespace std;
class Object;
class Pages;
class Users;
class Date;
class Activity;
class Post;
class Comment;
class Memory;
class Connect;

class Helper
{
public:
	static int StringLenght(const char* str)
	{
		int c = 0;
		for (int i=0; str[i] != '\0'; i++)
		{
			c++;
		}
		return c;

	}
	static void StringCopy(char*& dest,const char*& src) {
		int i = 0;
		for (i; src[i] != '\0'; i++)
		{
			dest[i] = src[i];
		}
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(const char* str)
	{
		int len = StringLenght(str);
		char* arr = new char[len+1];
		StringCopy(arr, str);
		return arr;
	}
};
class Date
{
private:

	int day;
	int month;
	int year;
	static Date currentdate;

public:
	Date()
	{
		day = 0;
		month = 0;
		year = 0;
	}
	void GetDateFromFile(ifstream& file)
	{
		file >> day;
		file >> month;
		file >> year;
	}
	static void SetCurrentDate(int d, int m, int y)		//initializing this date
	{
		currentdate.day = d;
		currentdate.month = m;
		currentdate.year = y;
	}
	static void PrintCurrentDate()
	{
		currentdate.PrintDate();
	}
	static Date GetCurrentDate() 
	{
		return currentdate;
	}
	int GetDay()
	{
		return day;
	}
	int GetYear()
	{
		return year;
	}
	bool compare_date()
	{
		return (day == currentdate.day || day == currentdate.day - 1);
	}
	void PrintDate()
	{
		cout << "(" << day << "/" << month << "/" << year << ")";
	}
	int difference()
	{
		int a = currentdate.year - year;
		return a;
	}
};
Date Date::currentdate;		//static initialization
class Object		//parent class
{
private:
	char* ID;
public:
	Object()
	{
		ID = 0;
	}
	virtual ~Object()
	{
		if (ID)
		{
			delete[] ID;
		}
	}
	void setID(char* id)
	{
		ID = id;
	}
	char* getID()
	{
		return ID;
	}
	virtual void PrintName()
	{
	}
	virtual void UpdatePostList(Post* ptr)
	{
	}
	virtual void Print()
	{
	}

};
class Comment
{
private:
	char* comment_id;
	Object* comment_by;
	char* comment_description;
public:
	Comment()
	{
		comment_id = 0;
		comment_by = 0;
		comment_description = 0;
	}
	~Comment()
	{
		if (comment_id && comment_description)
		{
			delete[] comment_id;
			delete[] comment_description;
		}
	}
	void setCommentID(char* temp)		//manually called
	{
		comment_id = temp;
	}
	void setCommentBy(Object* temp)		//returns address of user that posted comment 
	{
		comment_by = temp;
	}
	void setCommentDescription(char* temp)
	{
		comment_description = temp;
	}
	void PrintComment()
	{
		cout << "               ";
		comment_by->PrintName();
		cout << " wrote \" " << comment_description << " \"\n";
	}
};
class Activity
{
private:
	int type;
	char* value;
public:
	Activity()
	{
		type = 0;
		value = 0;
	}
	~Activity()
	{
		delete[] value;
	}
	void GetActivityFromFile(ifstream& fin)
	{
		fin >> type;
		char buffer[80];
		fin.getline(buffer, 80);
		value = Helper::GetStringFromBuffer(buffer);
	}
	void PrintActivity()
	{
		if (type == 1)
		{
			cout << " is feeling ";
		}
		else if (type == 2)
		{
			cout << " is thinking about ";
		}
		else if (type == 3)
		{
			cout << " is making ";
		}
		else
		{
			cout << " is celebrating ";
		}
		cout << value;
	}
};
class Post
{
private:
	int post_type;
	char* post_id;
	char* description;
	Date shared_date;
	Activity activity;
	Object* shared_by;
	Object** liked_by;
	Comment** commentlist;
public:
	Post()
	{
		post_type = 0;
		post_id = 0;
		description = 0;
		shared_by = 0;
		liked_by = 0;
		commentlist = 0;
	}
	~Post()
	{
		if (post_id && description)
		{
			delete[] post_id;
			delete[] description;
		}
		if (liked_by)
		{
			delete[] liked_by;
		}
		if (commentlist)
		{
			delete[] commentlist;
		}
	}
	void ReadPostFromFile(ifstream& fin)
	{
		fin >> post_type;
		char buffer[80];
		fin >> buffer;
		post_id = Helper::GetStringFromBuffer(buffer);
		shared_date.GetDateFromFile(fin); 
		fin.ignore();
		fin.getline(buffer, 80);
		description = Helper::GetStringFromBuffer(buffer);
		if (post_type == 2)
		{
			activity.GetActivityFromFile(fin);
		}
	}
	void setSharedBy(Object* temp)
	{
		shared_by = temp;
	}
	void setLikedBy(Object* temp)
	{
		if (liked_by == 0)
		{
			liked_by = new Object * [10];
			for (int i = 0; i < 10; i++)
			{
				liked_by[i] = 0;
			}
		}
		int i = 0;
		while (liked_by[i] != 0)
		{
			i++;
		}
		liked_by[i] = temp;
	}
	bool CompareSharedDate()
	{
		return(shared_date.compare_date());
	}
	void PrintPost()
	{
		shared_by->PrintName();
		if (post_type == 2)
		{
			activity.PrintActivity();
			cout << endl;
		}
		else
		{
			cout << " shared ";
		}
		cout<< "\"" << description << "\"";
		shared_date.PrintDate();
		cout << endl;
		if (commentlist)
		{
			int i = 0;
			while (commentlist[i] != 0 && i < 3)
			{
				commentlist[i]->PrintComment();
				i++;
			}
		}
	}
	char* getID()
	{
		return post_id;
	}
	void UpdateCommentedList(Comment* temp)
	{
		if (commentlist == 0)
		{
			commentlist = new Comment * [10];
			for (int i = 0; i < 10; i++)
			{
				commentlist[i] = nullptr;
			}
		}
		
		int i = 0;
		while (commentlist[i] != 0)
		{
			i++;
		}
		commentlist[i] = temp;
	}
	void LikedBy()
	{
		if (liked_by)
		{
			int i = 0;
			while (liked_by[i]!=0)
			{
				liked_by[i]->Print();
				cout << endl;
				i++;
			}
		}
	}
	Object* getSharedBy()
	{
		return shared_by;
	}
	Date getDate()
	{
		return shared_date;
	}
	bool isMemory()
	{
		if (shared_date.difference() >= 1)
		{
			return true;
		}
		return false;
	}

};
class Pages:public Object	//polymorphism	chils class
{
private:
	char* page_title;
	Post** postlist;

public:
	Pages()		//constructor
	{
		page_title = 0;
		postlist = 0;
	}
	~Pages()	//destructor
	{
		if (page_title)
		{
			delete[] page_title;
		}
		if (postlist)
		{
			delete[] postlist;
		}
	}
	void ReadPageFromFile(ifstream& fin)		//stores file data to members 
	{
		char array[80];
		fin >> array;
		setID(Helper::GetStringFromBuffer(array));
		fin.getline(array, 80);
		page_title = Helper::GetStringFromBuffer(array);
	}
	void Print()
	{
		cout << getID() << " --- " << page_title;
	}
	void PrintName()
	{
		cout << page_title;
	}
	void UpdatePostList(Post* temp)
	{
		if (postlist == 0)
		{
			postlist = new Post * [10];
			for (int i = 0; i < 10; i++)
			{
				postlist[i] = nullptr;
			}
		}
		int i = 0;
		while (postlist[i] != 0)
		{
			i++;
		}
		postlist[i] = temp;
	}
	void PrintAllPosts()
	{
		if (postlist)
		{
			int i = 0;
			while (postlist[i] != 0)
			{
				if (postlist[i]->CompareSharedDate())
				{
					postlist[i]->PrintPost();
					cout << endl ;
				}
				i++;
			}
		}
	}
	void PrintPosts()
	{
		if (postlist)
		{
			int i = 0;
			while (postlist[i] != 0)
			{
				postlist[i]->PrintPost();
				cout << endl << endl;
				i++;
			}
		}
	}
};
class Memory
{
private:
	Date shared_date;
	char* description;
	Post* originalpost;
	bool exist;
public:
	Memory()
	{
		description = 0;
		originalpost = 0;
		exist = 0;
	}
	~Memory()
	{
		if (description)
		{
			delete[] description;
		}
	}
	void setPost(Post* ptr)
	{
		originalpost = ptr;
	}
	void share(const char* str)
	{
		shared_date = Date::GetCurrentDate();
		description = Helper::GetStringFromBuffer(str);
		exist = 1;
	}
	void PrintSharedMemory()
	{
		if (exist)
		{
			Object* ptr = originalpost->getSharedBy();
			cout << "~~~ ";
			ptr->PrintName();
			cout << " shared a memory~~~~";
			shared_date.PrintDate();
			cout << "\n\"" << description << "\"\n(";
			Date d = originalpost->getDate();
			cout << d.difference() << " Years Ago)\n";
			originalpost->PrintPost();
		}
	}
	void PrintMemory()
	{
		cout << "On this Day\n";
		Date d = originalpost->getDate();
		cout << d.difference() << " Years Ago\n";
		originalpost->PrintPost();

	}
	Post* GerOriginalPost()
	{
		return originalpost;
	}
};
class Users: public Object
{
private:
	char* first_name;
	char* last_name;
	Pages** liked_pages;	//Assosiation
	Users** friends;		//Assosiation
	Post** postlist;
	Memory** memorylist;

public:
	Users()		//constructor
	{
		first_name = 0;
		last_name = 0;
		liked_pages = 0;
		friends = 0;
		postlist = 0;
		memorylist = 0;
	}
	~Users()		//destructor
	{
		if (first_name && last_name)
		{
			delete[] first_name;
			delete[] last_name;
		}
		if (liked_pages)
		{
			delete[] liked_pages;
		}
		if (friends)
		{
			delete[] friends;
		}
		if (postlist)
		{
			delete[] postlist;
		}
		if (memorylist)
		{
			int i = 0;
			while (memorylist[i] != 0)
			{
				delete[] memorylist[i];
				i++;
			}
			delete[] memorylist;
		}
	}
	void ReadUserFromFile(ifstream& fin)		//stores file data in member
	{
		char arr[80];
		fin >> arr;
		setID(Helper::GetStringFromBuffer(arr));
		fin >> arr;
		first_name = Helper::GetStringFromBuffer(arr);
		fin >> arr;
		last_name = Helper::GetStringFromBuffer(arr);
	}
	void LikePage(Pages* like)
	{
		if (liked_pages == 0)
		{
			liked_pages = new Pages * [10];
			for (int i = 0; i < 10; i++)
			{
				liked_pages[i] = 0;
			}
		}
		int i = 0;
		while (liked_pages[i] != 0)
		{
			i++;
		}
		liked_pages[i] = like;

	}
	void MakeFriend(Users* user)
	{
		if (friends==0)
		{
			friends = new Users * [10];
			for (int i = 0; i < 10; i++)
			{
				friends[i] = 0;
			}
			
		}
		int i = 0;
		while (friends[i] != 0)
		{
			i++;
		}
		friends[i] = user;

	}
	void Print()
	{
		cout << getID() << " --- " << first_name << " " << last_name << endl;
	}
	void PrintList()
	{
		int i = 0;
		if (liked_pages)
		{
			Print();
			
			while (liked_pages[i] != 0)
			{
				liked_pages[i]->Print();
				cout << endl;
				i++;
			}
		}	
		if (friends)
		{
			i = 0;
			while (friends[i] != 0)
			{
				friends[i]->Print();
				i++;
			}
		}
	}
	void PrintLikedPages()
	{
		if (liked_pages)
		{
			int i = 0;
			while (liked_pages[i] != 0)
			{
				liked_pages[i]->Print();
				cout << endl;
				i++;
			}
		}
	}
	void PrintFriends()
	{
		if (friends)
		{
			int i = 0;
			while (friends[i] != 0)
			{
				friends[i]->Print();
				i++;
			}
		}
	}
	void PrintName()
	{
		cout << first_name << " " << last_name;
	}
	void UpdatePostList(Post* temp)
	{
		if (postlist == 0)
		{
			postlist = new Post * [10];
			for (int i = 0; i < 10; i++)
			{
				postlist[i] = nullptr;
			}
		}
		
		int i = 0;
		while (postlist[i] != 0)
		{
			i++;
		}
		postlist[i] = temp;
	}
	void PrintAllPosts()
	{
	  	if (postlist)
		{
			int i = 0;
			while (postlist[i] != 0)
			{
				if (postlist[i]->CompareSharedDate())
				{
					postlist[i]->PrintPost();
					cout << endl;
				}
				i++;
			}
		}
	}
	void friendspost()
	{
		if (friends)
		{
			int i = 0;
			while (friends[i] != 0)
			{
				friends[i]->PrintSharedMemories();
				friends[i]->PrintAllPosts();
				i++;
			}
		}
	}
	void likepage()
	{
		if (liked_pages)
		{
			int i = 0;
			while (liked_pages[i] != 0)
			{
				liked_pages[i]->PrintAllPosts();
				i++;
			}
		}
	}
	void ViewHome()
	{
		PrintName();
		cout << "--- Home Page\n\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		friendspost();
		likepage();
	}
	void PrintPosts()
	{
		if (postlist)
		{
			int i = 0;
			while (postlist[i] != 0)
			{
				postlist[i]->PrintPost();
				cout << endl << endl ;
				i++;
			}
		}
	}
	void ViewTimeline()
	{
		PrintName();
		cout << "---Timeline\n\n";
		PrintSharedMemories();
		PrintPosts();
	}
	void PrintSharedMemories()
	{
		if (memorylist)
		{
			int i = 0;
			while (memorylist[i] != 0)
			{
				memorylist[i]->PrintSharedMemory();
				i++;
			}
		}
	}
	void LikePost(Post* ptr)
	{
		if (ptr)
		{
			ptr->setLikedBy(this);
		}
	}
	Comment* PostComment(Post* ptr, const char* str)
	{
		Comment* newcomment= new Comment[1];
		newcomment->setCommentID(Helper::GetStringFromBuffer("c"));
		newcomment->setCommentDescription(Helper::GetStringFromBuffer(str));
		newcomment->setCommentBy(this);
		ptr->UpdateCommentedList(newcomment);
		return newcomment;
	}
	void UpdateMemoryList(Post* ptr)
	{
		if (memorylist == 0)
		{
			memorylist = new Memory * [10];
			for (int i = 0; i < 10; i++)
			{
				memorylist[i] = 0;
			}
		}
		int i = 0;
		while (memorylist[i] != 0)
		{
			i++;
		}
		memorylist[i] = new Memory[1];
		memorylist[i]->setPost(ptr);
	}
	void CallMemory()
	{
		if (postlist)
		{
			int i = 0;
			while (postlist[i] != 0)
			{
				if (postlist[i]->isMemory())
				{
					UpdateMemoryList(postlist[i]);
				}
				i++;
			}
		}
	}
	void SeeMemories()
	{
		if (memorylist)
		{
			cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n";
			int i = 0;
			while (memorylist[i] != 0)
			{
				memorylist[i]->PrintMemory();
				i++;
			}
		}
	}
	void ShareMemory(Post* ptr, const char* str)
	{
		if (memorylist)
		{
			int i = 0;
			while (memorylist[i] != 0)
			{
				if (memorylist[i]->GerOriginalPost()==ptr)
				{
					memorylist[i]->share(str);
				}
				i++;
			}
		}

	}
};

class Connect
{
private:
	Pages** PageList;
	Users** UserList;
	Post** PostList;
	Comment** CommentList;
	int total_pages;
	int total_users;
	int total_posts;
	int total_comments;

public:
	Connect()
	{
		PageList = 0;
		UserList = 0;
		PostList = 0;
		CommentList = 0;
		total_pages = 0;
		total_users = 0;
		total_posts = 0;
		total_comments = 0;
	}
	~Connect()
	{
		if (PageList)
		{
			for (int i = 0; i < total_pages; i++)
			{
				delete[] PageList[i];
			}
			delete[] PageList;
		}
		if (UserList)
		{
			for (int i = 0; i < total_users; i++)
			{
				delete[] UserList[i];
			}
			delete[] UserList;
		}
		if (PostList)
		{
			for (int i = 0; i < total_posts; i++)
			{
				delete[] PostList[i];
			}
			delete[] PostList;
		}
		if (CommentList)
		{
			for (int i = 0; i < total_comments; i++)
			{
				delete[] CommentList[i];
			}
			delete[] CommentList;
		}
	}

	Pages* SearchPageByID(const char* ID)
	{
		for (int i = 0; i < total_pages; i++)
		{
			if (!strcmp(ID, PageList[i]->Object::getID()))
			{
				return PageList[i];
			}
		}
		return 0;
	}
	void ReadAllPages()
	{ 
		ifstream fin;
		fin.open("pages.txt");
		fin >> total_pages;
		PageList = new Pages* [total_pages];
		for (int i = 0; i < total_pages; i++)
		{
			PageList[i] = new Pages[1];
			PageList[i]->ReadPageFromFile(fin);
		}
		fin.close();
	}
	void PrintAllPages()
	{
		for (int i = 0; i < total_pages; i++)
		{
			PageList[i]->Print();
			cout << endl;
		}
	}

	Users* SearchUsersByID(const char* ID)
	{
		for (int i = 0; i < total_users; i++)
		{
			char* temp = UserList[i]->Object::getID();
			if (!strcmp(ID, temp))
			{
				return UserList[i];
			}
		}
		return 0;
	}
	void ReadAllUsers()
	{
		ifstream fin;
		fin.open("users.txt");
		fin >> total_users;
		UserList = new Users*[total_users]; 
		char*** temp = new char** [total_users];
		for (int i = 0; i < total_users; i++)
		{
			UserList[i] = new Users[1];
			UserList[i]->ReadUserFromFile(fin);
			temp[i] = new char* [10];
			char arr[10];
			fin >> arr;
			int j = 0;
			while (arr[0] != '-')
			{
				temp[i][j] = Helper::GetStringFromBuffer(arr);
				j++;
				fin >> arr;
			}
			temp[i][j] = 0;
			fin >> arr;
			while (arr[0] != '-')
			{
				Pages* page = SearchPageByID(arr);
				UserList[i]->LikePage(page);
				fin >> arr;
			}
		}

		for (int i = 0; i < total_users; i++)
		{
			int j = 0;
			for (j = 0; temp[i][j] != 0; j++)
			{
				Users* user = SearchUsersByID(temp[i][j]);
				UserList[i]->MakeFriend(user);
			}
		}


		for (int i = 0; i < total_users; i++)
		{
			for (int j = 0; j < 10 && temp[i][j]!=0; j++)
			{
				delete[] temp[i][j];
			}
			delete[] temp[i];
		}
		delete[] temp;
		fin.close();
	}		
	Post* SearchPostByID(const char* ID)
	{
		for (int i = 0; i < total_posts; i++)
		{
			char* temp = PostList[i]->getID();
			if (!strcmp(ID, temp))
			{
				return PostList[i];
			}
		}
		return 0;
	}
	void PrintAllPosts()
	{
		for (int i = 0; i < total_posts; i++)
		{
			PostList[i]->PrintPost();
			cout << endl;
		}
	}
	void ReadAllPosts()
	{
		ifstream fin;
		fin.open("posts.txt");
		fin >> total_posts;
		char buffer[80];
		Object* temp;
		PostList = new Post*[total_posts];
		for (int i = 0; i < total_posts; i++)
		{
			PostList[i] = new Post[1];
			PostList[i]->ReadPostFromFile(fin);
			fin >> buffer;
			if (buffer[0] == 'p')
			{
				temp = SearchPageByID(buffer);
			}
			else
			{
				temp = SearchUsersByID(buffer);
			}
			PostList[i]->setSharedBy(temp);
			temp->UpdatePostList(PostList[i]);
			fin >> buffer;
			while (buffer[0] != '-')
			{
				if (buffer[0] == 'p')
				{
					temp = SearchPageByID(buffer);
				}
				else
				{
					temp = SearchUsersByID(buffer);
				}

				PostList[i]->setLikedBy(temp);
				fin >> buffer;
			}
		}
		fin.close();
		for (int i = 0; i < total_users; i++)
		{
			UserList[i]->CallMemory();
		}
	}
	void ReadAllComments()
	{
		ifstream fin;
		fin.open("comments.txt");
		fin >> total_comments;
		CommentList = new Comment * [total_comments];
		char buffer[80];
		Post* temp;
		for (int i = 0; i < total_comments; i++)
		{
			CommentList[i] = new Comment[1];
			fin >> buffer;
			CommentList[i]->setCommentID(Helper::GetStringFromBuffer(buffer));
			fin >> buffer;
			temp= SearchPostByID(buffer);
			temp->UpdateCommentedList(CommentList[i]);
			fin >> buffer;
			Object* temp2=0;
			if (buffer[0] == 'p')
			{
				temp2 = SearchPageByID(buffer);
			}
			else
			{
				temp2 = SearchUsersByID(buffer);
			}
			CommentList[i]->setCommentBy(temp2);
			fin.getline(buffer, 80);
			CommentList[i]->setCommentDescription(Helper::GetStringFromBuffer(buffer));
		}
		fin.close();
	} 
	void PrintComment()
	{
		for (int i = 0; i < total_comments; i++)
		{
			CommentList[i]->PrintComment();
			cout<< endl;
		}
	}
	void ViewLikedList(const char* ptr)
	{
		Post* temp=SearchPostByID(ptr);
		if (temp)
		{
			temp->LikedBy();
		}
		else
		{
			cout << "No result found.";
		}
	}
	void ViewPost(const char* str)
	{
		Post* ptr;
		ptr = SearchPostByID(str);
		ptr->PrintPost();
	}
	void Load()
	{
		ReadAllPages();
		ReadAllUsers();
		ReadAllPosts();
		ReadAllComments();
	}
	void ViewPage(const char* ptr)
	{
		Pages* p= SearchPageByID(ptr);
		p->PrintName();
		cout << endl;
		p->PrintPosts();
	}
	static void Run()
	{
		Connect obj;
		Date::SetCurrentDate(15, 7, 2017);
		cout << endl;
		obj.Load();

		//----------------------PHASE I-----------------------//
		Users* currUser = obj.SearchUsersByID("u7");
		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "Command:\tSet current System Date 15 11 2017\nSystem Date :\t 15 / 11 / 2017\n\n";
		cout << "Command:\tSet current user \"u7\"\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->Print();
		cout << " successfully set as Current User\n\n";

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tView Friend List\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->Print();
		cout << "Friend List\n";
		currUser->PrintFriends();

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tView Liked Pages\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->Print();
		cout << "Liked Pages\n";
		currUser->PrintLikedPages();

		//----------------------PHASE II-----------------------//
		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tView Home\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->Print();
		currUser->ViewHome();

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tView Timeline\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->Print();
		currUser->ViewTimeline();
	
		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tView Liked Post (post5)\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		obj.ViewLikedList("post5");
		Post* currPost = obj.SearchPostByID("post5");
		currUser->LikePost(currPost);

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tLikePost(post5)\nCommand:\tViewLikedList(post5)\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		obj.ViewLikedList("post5");

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tPostComment(post4, Good Luck for your Result)\nCommand:\tViewPost(post4)\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currPost = obj.SearchPostByID("post4");
		Comment* ptr = currUser->PostComment(currPost, "Good Luck for your Result");
		obj.ViewPost("post4");

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tPostComment(post8, Thanks for the wishes)\nCommand:\tViewPost(post8)\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currPost = obj.SearchPostByID("post8");
		Comment* ptr1 = currUser->PostComment(currPost, "Thanks for the wishes");
		obj.ViewPost("post8");

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tSeeYourMemories()\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->SeeMemories();

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tShareMemory(post10, 哲ever thought I will be specialist in this field...能nCommand:\tView TimeLine\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currPost = obj.SearchPostByID("post10");
		currUser->ShareMemory(currPost, "Never thought I will be specialist in this field...");

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tView Timeline\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->Print();
		currUser->ViewTimeline();
		
		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tViewPage(p1)\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		obj.ViewPage("p1");

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tSet current user \"u11\"";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser = obj.SearchUsersByID("u11");
		currUser->Print();
		cout << " successfully set as Current User\n\n";

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tView Timeline\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->Print();
		currUser->ViewTimeline();

		cout << "\n---------------------------------------------------------------------------------------------\n";
		cout << "\nCommand:\tView Home\n";
		cout << "\n---------------------------------------------------------------------------------------------\n";
		currUser->Print();
		currUser->ViewHome();
		
		delete[] ptr;
		delete[] ptr1;
	}
};


void main()
{	
	Connect::Run();
}
