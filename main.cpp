#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "BT.h"

typedef BST<int> BSTint;
typedef BSTint* BSTPtr;

using namespace std;

string removechars(string, string);
int elementsperinst(string);
string getinst(string);
bool endsWith(string, string);
bool checkdays(string);
bool checkhours(string);
string gettitle(string);
bool checktitle(string);
void aftertitle(string&);
string getdate(string, int);
bool isNumber(const string& );

string sympols = ".,:;\'&[]{}()";

int main(int argn, char** argv){
	BSTPtr root = new BSTint;
	if (argn != 2)
		cout << "incorrect number of arguments" << endl;
	else{
		//to open the file
		ifstream cfile(argv[1]);
		//to read the text file into string

		if (cfile.good() && cfile.is_open()){
			string line;
			string line_1;
			string inst;
			string sec;
			string ds;
			string hs;
			string title;
			string modtitle;
			int words = 0;
			int d = 0; int h = 0;
			//code to convert string line by line
			while (getline(cfile, line)){
				ds.clear();
				hs.clear();
				title.clear(); //resetting variables before every line
				line_1 = removechars(line, sympols);
				inst = getinst(line_1);
				words = elementsperinst(line_1);
				if (inst == "ADD"){
					if (words < 4)
						cout << "Invaild arguments" << endl;
					else{
						title = gettitle(line_1);
						aftertitle(line_1);
						ds = getdate(line_1,1);
						hs = getdate(line_1, 2);
						if (!checktitle(title)){
							cout << "Invalid title" << endl;
						}else if(!checkdays(ds)){
							cout << "Invalid day" << endl;
						}else if(!checkhours(hs)){
							cout << "Invalid hour" << endl;
						}else{
							int d = stoi(ds);
							int h = stoi(hs);
							//title is in variable called title above
							//check for conflict function in .h
							//add if not conflict function in .h
							BSTPtr Temp;
								root->Add(title, d, h);
						}
					}
				}else if (inst == "Find"){
					if (words != 3)
						cout << "Invalid arguments" << endl;
					else{
						ds = getdate(line_1, 2);
						hs = getdate(line_1, 3);
						if (!checkdays(ds))
						{
							cout << "Invalid day" << endl;
						}
						else if (!checkhours(hs))
						{
							cout << "Invalid hour" << endl;
						}
						else
						{
							int d = stoi(ds);
							int h = stoi(hs);
							root->Find(d,h);
						}
					}
				}
				else if (inst == "DEL")
				{
					if (words != 3)
						cout << "Invalid arguments" << endl;
					else
					{
						ds = getdate(line_1, 2);
						hs = getdate(line_1, 3);
						if (!checkdays(ds))
						{
							cout << "Invalid day" << endl;
						}
						else if (!checkhours(hs))
						{
							cout << "Invalid hour" << endl;
						}
						else
						{
							int d = stoi(ds);
							int h = stoi(hs);
							//delete function in .h
							BSTPtr Temp;
							Temp = root->Retrieve(d, h);
							if(Temp->isEmpty() == true)
								Temp->EmptyPrint(d, h);
							else
								root = root->Delete(d, h, root);
						}
					}
				}
				else if (inst == "MOD")
				{
					if (words < 4)
						cout << "Invalid arguments" << endl;
					else
					{
						modtitle = gettitle(line_1);
						aftertitle(line_1);
						ds = getdate(line_1, 1);
						hs = getdate(line_1, 2);
						if (!checktitle(modtitle))
						{
							cout << "Invalid title" << endl;
						}
						else if (!checkdays(ds))
						{
							cout << "Invalid day" << endl;
						}
						else if (!checkhours(hs))
						{
							cout << "Invalid hour" << endl;
						}
						else
						{
							int d = stoi(ds);
							int h = stoi(hs);
							//new title is in variable called modtitle above
							//modify function  in .h
							root->MOD(modtitle, d, h);
						}
					}
				}
				else if (inst == "Print"){
					if (words != 1)
						cout << "Invalid arguments" << endl;
					else{
						if(root->isEmpty())
							cout<<"Empty Planner"<<endl;
						else
							root->Print();
					}
				}
				else
					cout << "Invalid command" << endl;
			}
		}
		else
			cout << "File not found";
	}
	delete root;
	return 0;
}


//used functions

string removechars(string s, string x)
{
	for (unsigned int i = 0;i <= (s.length() - 1);i++)
	{
		for (unsigned int k = 0;k <= (x.length() - 1);k++)
		{
			if (s[i] == x[k])
				s.erase(s.begin() + i);
		}
	}
	return s;
}

string getinst(string s)
{
	string word;
	istringstream iss(s);
		iss >> word;
	return word;
}

int elementsperinst(string s)
{
	string dq = "\"";
	bool flag;
	int f = -1;
	istringstream iss(s);
	do {
		flag = false;
		string word;
		iss >> word;
		if ((word.rfind(dq, 0) == 0) || (word == dq))
		{
			flag = true;
			//if(endsWith(word,dq)){flag =false; break;}
			while (iss)
			{
				if (endsWith(word, dq) || word == dq)
				{
					flag = false; break;
				}
				iss >> word;
			}
		}
		if (!flag)
			f++;

	} while (iss);
	return f;
}

bool endsWith(string s, string suffix)
{
	if (s.length() < suffix.length())
		return false;
	return s.substr(s.length() - suffix.length()) == suffix;
}

bool checkdays(string s)
{
	if(isNumber(s))
	{
	int num = stoi(s);
	if (num >= 1 && num <= 365)
		return true;
	else
			return false;
	}
	else
		return false;
}

bool checkhours(string s)
{

	if(isNumber(s))
		{
		int num = stoi(s);
		if (num >= 0 && num <= 23)
			return true;
		else
				return false;
		}
		else
			return false;
}

string gettitle(string s)
{

	string t;
	t.clear();
	int flag=0;
	int start = 0;
	int end = 0;
	for (unsigned int x = 0;x<s.length();x++)
	{
		if (s[x] == '"')
		{
			start = x;
			flag=1;
			break;
		}
	}
	for (unsigned int x = start;x<s.length();x++)
	{
		if (s[x] == '"')
		{
			end = x;
			flag=2;
		}
	}
	if (flag<2)
		return "Error";
	else
	{
		for (int x = start;x <= end;x++)
		{
			t = t + s[x];
		}
		return t;
	}
}

bool checktitle(string s)
{
	int start = 0;
	int flag = 0;
	int end = 0;
	for (unsigned int x = 0;x<s.length();x++)
	{
		if (s[x] == '"')
		{
			start = x;
			flag = 1;
			break;
		}
	}
	for (unsigned int x = start;x<s.length();x++)
	{
		if (s[x] == '"')
		{
			end = x;
			flag = 2;
		}
	}
	if (flag == 2)
		return true;
	else
		return false;

}

void aftertitle(string &s){
	int start = 0;
	int end = 0;
	for (unsigned int x = 0;x<s.length();x++){
		if (s[x] == '"'){
			start = x;
			break;
		}
	}
	for (unsigned int x = start;x<s.length();x++){
		if (s[x] == '"'){
			end = x;
		}
	}
	s.erase(0, (end + 1));
}

string getdate(string s,int i){
	string word;
	istringstream iss(s);
	for (int j = 0;j<i;j++)
		iss >> word;
	return word;
}


bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}
