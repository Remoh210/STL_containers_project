#include "cVector.h"

#include "cPerson.h"
#include <iostream>

int main_vector()
{
	cVector myVec;
	sPoint Point;
	Point.x = 0.0f;
	Point.y = 0.0f;
	Point.z = 0.0f;

	sPerson michael;
	michael.first = "Michael";
	michael.last = "Feeney";
	michael.uniqueID = 0;	
	michael.age = 20;
	michael.health = 100.0f;
	michael.location = Point;

	sPerson robin;
	Point.x += 10.0f;
	robin.first = "Robin";
	robin.last = "Bobbin";
	robin.uniqueID = 1;		
	robin.age = 26;
	robin.health = 80.0f;
	robin.location = Point;

	sPerson fraser;
	Point.z += 10.0f;
	fraser.first = "Fraser";
	fraser.last = "Fareast";
	fraser.uniqueID = 2;
	fraser.age = 19;
	fraser.health = 30.0f;
	fraser.location = Point;

	sPerson jacob;
	Point.z += 10.0f;
	jacob.first = "Jacob";
	jacob.last = "Sir";
	jacob.uniqueID = 3;
	jacob.age = 75;
	jacob.health = 64.0f;
	jacob.location = Point;

	myVec.InsertPersonAtEnd( michael );
	myVec.InsertPersonAtEnd( robin );
	myVec.InsertPersonAtEnd( fraser );
	myVec.InsertPersonAtEnd( jacob );

	for ( unsigned int index = 0; index != myVec.GetSize(); index++ )
	{
		sPerson thePerson;
		myVec.GetPersonAtIndex( index, thePerson );

		std::cout << index << " "
			<< thePerson.first << " " 
			<< thePerson.last << std::endl;
	}

	std::cout << "//////    FindPersonByID     //////";
	sPerson findByIdPerson;
	myVec.FindPersonByID(1, findByIdPerson);

	return 0;
}
