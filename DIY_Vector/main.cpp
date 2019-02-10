#include "DIY_Vector.h"
#include <iostream>
using namespace std;
int main()
{
	sPerson nepersen;
	nepersen.age = 12;
	nepersen.first = "Michel";
	sPerson nepersen2;
	nepersen2.age = 122;
	nepersen2.first = "Michel2";
	DIY_Vector newvec;
	newvec.PushBack(nepersen);
	newvec.PushBack(nepersen2);
	sPerson findperson;
	newvec.GetAt(1, findperson);
	cout << findperson.first << std::endl;
	cout << "size :" << newvec.GetSize() << std::endl;
	cout << "capacity :" << newvec.GetCapacity() << std::endl;
	system ("pause");

}