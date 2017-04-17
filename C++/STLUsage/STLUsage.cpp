// STLUsage.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <conio.h>

#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <hash_map>

using namespace std;

void StringTest(list<string*>& strList)
{

    cout<<"------ StringTest ------"<<endl;

    //////////////////////////////////////////////////////////////////////////

    string strSTL;
    strSTL = "abcde";
    strList.push_back(&strSTL);


    //////////////////////////////////////////////////////////////////////////
    cout<<endl<<"Press any key to contine...";
    _getch();
}

void VectorTest()
{
	cout<<"------ VectorTest ------"<<endl;

	//////////////////////////////////////////////////////////////////////////
	vector<int> v1(5);


	for(int i = 0; i<v1.size(); i++)
	{
		v1[i] = i;
	}



	cout<<"V1=";

	// Reverse order
	vector<int>::iterator iterator;
	for(iterator=v1.begin(); iterator!=v1.end(); iterator++)
	{
		cout<<" "<<*iterator;
	}
	cout<<endl;

	cout<<v1.capacity()<<"   "<<v1.size();
	//
	cout<<endl<<"Press any key to contine...";
	_getch();
}


void ListTest()
{
	cout<<endl<<endl<<"------ ListTest ------"<<endl;
	//
	list<int> l1(10);


	list<int>::iterator it;
	int i=0;
	for (it=l1.begin(); it!=l1.end(); it++,i++)
	{
		*it = i;
	}

	for (it=l1.begin(); it!=l1.end(); it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;


	//
	cout<<endl<<"Press any key to contine...";
	_getch();
}

//
void MapTest()
{
	cout<<endl<<endl<<"------ MapTest ------"<<endl;

	// 
	typedef pair<int,char*> Int_Pair;
	

	map < int, char*,greater<int> > m1;

	m1.insert(Int_Pair(1,"香港"));
	m1.insert(Int_Pair(2,"台湾"));
	m1.insert(Int_Pair(3,"中国"));

	map<int,char*,greater<int> >::iterator it;
	for (it=m1.begin(); it!=m1.end(); it++)
	{
		cout<<" <"<<it->first<<","<<it->second<<">";
	}



	// 
	cout<<endl<<"Press any key to contine...";
	_getch();
}

void SetTest()
{
	cout<<endl<<endl<<"------ SET Test ------"<<endl;
	//



	// 
	cout<<endl<<"Press any key to contine...";
	_getch();
}

//////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
    char aaa = 0x0d;
	//VectorTest();

	//ListTest();

	//MapTest();

	//SetTest();
    list<string*> strList;
    StringTest(strList);


    

	//
	return 0;
}

