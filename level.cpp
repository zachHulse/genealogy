/****************************************
* Module:
*   Week 13, Genealogy
* Author:
*   Zachary Hulse
* Summary:
*   This file includes a custom BNode 
*   that will be used to build a linkedlist
*   and tree of genealogical records
*****************************************/
#pragma once

#include <string>
#include <iostream>

using namespace std;


void BNode::level()
const int MAX = 100;
BNode *queue[MAX];
BNode *temp;
int front = 0;
int back = 0;

queue[back++] = this;

while (front != back)
{
	temp = queue[front];
	front = (front + 1) % MAX;
	if (temp != NULL)
	{
		// visit
		cout.width(4);
		cout << temp->first << " ";
		// end Visit        
		queue[back] = temp->father;// left
		back = (back + 1) % MAX;
		queue[back] = temp->mother;// right
		back = (back + 1) % MAX;

	}
}
}



