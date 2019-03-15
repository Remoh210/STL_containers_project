#include "DIY_Vector.h"
#include <iostream>
using namespace std;
int main()
{
	DIY_Vector myVec;
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

	myVec.PushBack(michael);
	myVec.PushBack(robin);
	myVec.PushBack(fraser);
	myVec.PushBack(jacob);
	
	sPerson findperson;




	myVec.GetAt(1, findperson);
	cout << findperson.first << std::endl;
	cout << "size :" << myVec.GetSize() << std::endl;
	cout << "capacity :" << myVec.GetCapacity() << std::endl;

	for (unsigned int index = 0; index != myVec.GetSize(); index++)
	{
		sPerson thePerson;
		myVec.GetAt(index, thePerson);

		std::cout << index << " "
			<< thePerson.first << " "
			<< thePerson.last << std::endl;
	}

	std::cout << "//////    FindPersonByID     //////" << std::endl;
	sPerson findByIdPerson;
	myVec.FindPersonByID(findByIdPerson, 2);
	std::cout << "First: " << findByIdPerson.first << std::endl;
	std::cout << "Last: " << findByIdPerson.last << std::endl;
	std::cout << "Age: " << findByIdPerson.age << std::endl;
	std::cout << "Unique ID: " << findByIdPerson.uniqueID << std::endl;
	std::cout << "Health: " << findByIdPerson.health << std::endl;
	std::cout << "Location: (" << findByIdPerson.location.x << "," << findByIdPerson.location.y << "," 
		<< findByIdPerson.location.z << ")" << std::endl;

	std::cout << "//////    FindPeopleByRadius     //////" << std::endl;
	std::vector<sPerson> vec_findByRadius;
	sPoint loc;
	loc.x = 0.1f; loc.y = 1.1f; loc.z = 3.1f;
	myVec.FindPeople(vec_findByRadius, loc, 30.0f);
	for (int i = 0; i < vec_findByRadius.size(); i++)
	{
		std::cout << "First: " << vec_findByRadius[i].first << std::endl;
		std::cout << "Last: " << vec_findByRadius[i].last << std::endl;
		std::cout << "Age: " << vec_findByRadius[i].age << std::endl;
		std::cout << "Unique ID: " << vec_findByRadius[i].uniqueID << std::endl;
		std::cout << "Health: " << vec_findByRadius[i].health << std::endl;
		std::cout << "Location: (" << vec_findByRadius[i].location.x << "," << vec_findByRadius[i].location.y << ","
			<< vec_findByRadius[i].location.z << ")" << std::endl;
		std::cout << std::endl;
	}
	system("pause");

}