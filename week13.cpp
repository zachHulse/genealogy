/****************************************
* Module:
*   Week 13, Genealogy
* Author:
*   Zachary Hulse
* Summary:
*   This file includes main and the funtions
*   to read in the GEDCOM file, display each
*   record alphabetically, and then display
*   all the progenitors of Gregory Lawerence
*****************************************/
#include <iostream>
#include "list.h"
#include "person.h"
#include <cstring>
#include <fstream>
#include <cassert>

using namespace std;

/**************************************************
* ATTACH PARENTS
* Looks through a linked list that is also a tree
* and attaches parents to children
*************************************************/
void attachParents(List<Person>& list, string child, string father, string mother)
{
	Node<Person>* kid = NULL;
	Node<Person>* dad = NULL;
	Node<Person>* mom = NULL;
	for (ListIterator<Person> it = list.begin(); it != list.end(); it++)
	{
		if ((*it).getRecord() == child)
			kid = it.p;
		if ((*it).getRecord() == father)
			dad = it.p;
		if ((*it).getRecord() == mother)
			mom = it.p;
	}
	kid->father = dad;
	kid->mother = mom;
}

/**************************************************
* Read GEDCOM
* Reads a gedcom file into a sorted linked list
*************************************************/
List<Person> readGEDCOM(char * filename)
{
	ifstream fin(filename);
	if (fin.fail())
		cout << "Error opening file:" << filename << endl;
	string word = "";
	string first = "";
	string last = "";
	string birth = "";
	string record = "";
	string husband = "";
	string wife = "";
	string child = "";
	List<Person> list;
	while (fin >> word)
	{
		if (word == "0")
		{
			fin >> word;
			if (word[0] == '@' && word[1] == 'I') // found a new record
			{
				if (record != "") // if there was a record before read it into the list
				{
					Person person(first, last, birth, record);
					//cerr << person << endl;
					sortInsertion(list, person);
					first = last = birth = record = "";
				}
				record = word;
			}
			if (word[0] == '@' && word[1] == 'F') // found a family
			{
				if (record != "") // if there was a record before read it into the list
				{
					Person person(first, last, birth, record);
					//cerr << person << endl;
					sortInsertion(list, person);
					first = last = birth = record = "";
				}
				if (child != "") // if their was a family before attach parents to children
				{
					attachParents(list, child, husband, wife);
					child = husband = wife = "";
				}
			}
		}
		if (word == "GIVN") // found a first name
		{
			getline(fin, word);
			word.erase(0, 1);
			first = word;
		}
		if (word == "SURN") // found a last name
		{
			getline(fin, word);
			word.erase(0, 1);
			last = word;
		}
		if (word == "BIRT") // found a birth day
		{
			fin >> word;
			fin >> word;
			if (word == "DATE")
			{
				getline(fin, word);
				word.erase(0, 1);
				birth = word;
			}
		}
		if (word == "HUSB") // found a dad
		{
			fin >> word;
			husband = word;
		}
		if (word == "WIFE") // found a mom
		{
			fin >> word;
			wife = word;
		}
		if (word == "CHIL") // found a child
		{
			fin >> word;
			child = word;
		}
	}
	attachParents(list, child, husband, wife); // after the loop connect the last family
	fin.close();
	return list;
}

/**************************************************
* WRITE ALPHABETICAL LIST
* Writes the data from a passed in list to another file
*************************************************/
void writeAlphabeticalList(List<Person>& list)
{
	ofstream fout("sorted.dat");
	if (fout.fail())
	{
		cout << "Error opeing: sorted.dat\n";
	}
	fout.clear();
	for (ListIterator<Person> it = list.begin(); it != list.end(); it++)
	{
		fout << *it;
	}
	fout.close();
}

/**************************************************
* DISPLAY GENEALOGY TREE
* Finds the first record in the list and
* displays his family with a level order traversal
*************************************************/
void displayGenealogyTree(List<Person>& list)
{
	ListIterator<Person> it;
	for (it = list.begin(); it != list.end(); it++) // find the first record 
	{
		if ((*it).getRecord() == "@I1@")
			break;
	}
	const int MAX = 100;
	Node<Person> *queue[MAX];
	Node<Person> *temp;
	int front = 0;
	int back = 0;
	int gennum = 0;
	int saveback = back;

	queue[back++] = it.p;

	while (front != back)
	{
		temp = queue[front];
		if (front == saveback && temp != NULL) // display the generation info
		{
			saveback = back;
			gennum++;
			if (gennum == 2)
				cout << "Parents:\n";
			else if (gennum == 3)
				cout << "Grandparents:\n";
			else if (gennum == 4)
				cout << "Great Grandparents:\n";
			else if (gennum == 5)
				cout << "2nd Great Grandparents:\n";
			else if (gennum == 6)
				cout << "3rd Great Grandparents:\n";
			else if (gennum > 6)
				cout << gennum - 3 << "th Great Grandparents:\n";
		}
		front = (front + 1) % MAX;
		if (temp != NULL)
		{
			if (temp->data.getRecord() == "@I1@")
			{
				cout << "The Ancestors of Gregory Lawrence Cameron:\n";
			}
			else
			{
				// visit
				cout.width(8);
				cout << " ";
				cout << temp->data;
				// end Visit        
			}
			queue[back] = temp->father;// left
			back = (back + 1) % MAX;
			queue[back] = temp->mother;// right
			back = (back + 1) % MAX;
		}
	}
}

/**************************************************
* MAIN
* Reads in a genalogical file, Writes all individuals
* to a seperatfile in alphabetical order and displays
* the progenitors of Gregory Lawernce Cameron.
*************************************************/
int main(int argc, const char* argv[])
{
	char filename[50];
	if (argc == 1)
	{
		cout << "Enter a filename.\n";
		cin >> filename;
	}
	else if (argc == 2)
	{
		strcpy(filename, argv[1]);
	}

	List<Person> list = readGEDCOM(filename); // read the file in
	writeAlphabeticalList(list); // write the alphabetical list to another file
	displayGenealogyTree(list); // display family generations

	return 0;
}