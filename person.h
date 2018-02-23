/****************************************
* Module:
*   person.h
* Author:
*   Zachary Hulse
* Summary:
*   This file contains a class to encapsulate
*   a single person in a genalogical record
*****************************************/
#pragma once

#include <string>
#include <iostream>

using namespace std;
class Person
{

private:
	string first;
	string last;
	string birth;
	string record;

public:
	Person() : first(""), last(""), birth(""), record("") {}
	Person(string first, string last, string birth, string record);
	bool operator<(Person rhs);
	friend ostream& operator <<(ostream & out, const Person person);

	string getFirst() { return first; }
	string getLast() { return last; }
	string getBirth() { return birth; }
	string getRecord() { return record; }
};


