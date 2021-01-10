#include <iostream>
#include <string>
#include "List.h"

// All work below was written by Benjamin Zech. Do not steal

using namespace std;
using namespace cop4530;

// Function object types, for use with remove_if()
class isOdd {
public:
  bool operator() (const int& value) { return (value%2)!=0; }
};

class LongerThanFive {
public:
  bool operator() (const string& s) { return (s.size() > 5); }
};

int main()
{
	List<int> benny;
	int num = 10;

	for (int i = 0; i < num; ++i)
	{
                benny.push_back(i);
        }

	cout << "size: " << benny.size() << endl;
	cout << benny << endl;

	cout << "reversing list..." << endl;
	benny.reverse();
	
	cout << "size: " << benny.size() << endl;
	cout << benny << endl;

	List<int> fun(5, 4);
	cout << "size: " << fun.size() << endl;
	cout << fun << endl;

	cout << "List = " << benny << endl;
	auto sItr = benny.begin();
	cout << "iterator1 points to " << *sItr << endl;
	sItr++;
	cout << "iterator1++ points to " << *sItr << endl;
	auto eItr = benny.end();
	eItr--;
	cout << "iterator2 points to " << *eItr << endl;
	eItr--;
	cout << "iterator2-- points to " << *eItr << endl;
	
	List<int> bigBoy(sItr, eItr);
	cout << bigBoy << endl;

	cout << "building iList 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 90, 80, 70, 60, 50" << endl;
	List<int> iList {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 90, 80, 70, 60, 50};
	iList.print(cout, '_');
	cout << endl;

	iList = {17, 38, 13, 50, -134};
	iList.print(cout, '.');
	cout << endl;

	List<int> john;
	cout << john << endl;
	john.reverse();
	cout << john << endl;
	john = {5};	
	john.reverse();
	cout << john << endl;
	john = {5, 4};
	john.reverse();
	cout << john << endl;

	List<int> re;
	cout << re << endl;
	re.remove(2);
	cout << re << endl;
	re = {1};	
	cout << re << endl;
	re.remove(1);
	cout << re << endl;

	List<int> L5(5,9);
	cout << L5 << endl;
	L5.remove(9);
	cout << L5 << endl;

	List<int> numbers = {2, 3, 3};
	cout << numbers << endl;
	numbers.remove_if(isOdd());
	cout << numbers << endl;
	
	List<int> fin1 = {5, 4, 3};
	List<int> fin2 = {5, 4, 394};
	cout << fin1 << endl;
	cout << fin2 << endl;
	
	if (fin1 != fin2)
		cout << "Lists are not equal" << endl;
	else
		cout << "Lists are equal" << endl;

}
