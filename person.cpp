#include "person.h"
/**************************************************
* NON-DEFAULT CONSTRUCTOR
*************************************************/
Person::Person(string first, string last, string birth, string record)
{
	this->first = first;
	this->last = last;
	this->birth = birth;
	this->record = record;
}

/**************************************************
* OVERLOADED < OPERATOR
* compares two persons first by last name, then by first
* and finally by birth year.
*************************************************/
bool Person::operator<(Person rhs)
{
	string tLast = last;
	string trhsLast = rhs.last;
	tLast[0] = toupper(tLast[0]); // upercase temp variable for compare
	trhsLast[0] = toupper(trhsLast[0]);
	if (tLast < trhsLast)
		return true;
	else if (tLast > trhsLast)
		return false;
	else if (tLast == trhsLast)
	{
		if (first < rhs.first)
			return true;
		else if (first > rhs.first)
			return false;
		if (first == rhs.first)
		{
			string tBirth = birth; // temp variable to hold last four characters of birth
			string trhsBirth = rhs.birth;
			while (tBirth.length() > 4)
				tBirth.erase(0, 1);
			while (trhsBirth.length() > 4)
				trhsBirth.erase(0, 1);
			if (tBirth < trhsBirth)
				return true;
			else if (tBirth > trhsBirth)
				return false;
		}
	}
}

/**************************************************
* OVERLOADED << OPERATOR
* Outputs a person in a readable format
*************************************************/
ostream& operator <<(ostream & out, const Person person)
{
	out << person.first;
	if (person.first != "" && person.last != "")
		out << " " << person.last;
	else if (person.last != "")
		out << person.last;
	if (person.birth != "")
		out << ", b. " << person.birth;
	out << endl;
	return out;
}
