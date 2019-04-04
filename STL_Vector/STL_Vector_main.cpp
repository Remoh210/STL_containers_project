#include "STL_Vector.h"
#include <iostream>
using namespace std;
int main()
{
	STL_Vector myVec;
	sPoint Point;
	Point.x = 0.0f;
	Point.y = 0.0f;
	Point.z = 0.0f;

	sPerson michael;
	michael.first = "";
	michael.last = "SMITH";
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

	sPerson fraserWithLastOnly;
	Point.z += 10.0f;
	fraserWithLastOnly.first = "";
	fraserWithLastOnly.last = "Fareast";
	fraserWithLastOnly.uniqueID = 2;
	fraserWithLastOnly.age = 19;
	fraserWithLastOnly.health = 30.0f;
	fraserWithLastOnly.location = Point;

	sPerson jacob;
	Point.z += 10.0f;
	jacob.first = "Jacob";
	jacob.last = "Sir";
	jacob.uniqueID = 3;
	jacob.age = 75;
	jacob.health = 64.0f;
	jacob.location = Point;


	sPerson jacobWithFirstOnly;
	Point.z += 10.0f;
	jacobWithFirstOnly.first = "JACOB";
	jacobWithFirstOnly.last = "";
	jacobWithFirstOnly.uniqueID = 3;
	jacobWithFirstOnly.age = 75;
	jacobWithFirstOnly.health = 64.0f;
	jacobWithFirstOnly.location = Point;

	myVec.PushBack(michael);
	myVec.PushBack(robin);
	myVec.PushBack(fraser);
	myVec.PushBack(jacob);
	myVec.PushBack(fraserWithLastOnly);
	myVec.PushBack(jacobWithFirstOnly);
	
	sPerson findperson;



	if (!myVec.LoadDataFilesIntoContainer("../USCen/dist.female.first.txt",
		"../USCen/dist.male.first.txt", "../USCen/US_LastNames.txt"))
	{
		std::cout << "error NO such file found" << std::endl;
		system("pause");
		return 0;
	}
	sPerfData perfData;
	myVec.GetPerformanceFromLastCall(perfData);
	std::cout << "//////    Perfomance     //////" << std::endl;
	std::cout << " elapsedCallTime_ms  :" << std::fixed << perfData.elapsedCallTime_ms << std::endl;
	std::cout << " memoryUsageBytes_avg: " << std::fixed << perfData.memoryUsageBytes_avg << std::endl;
	std::cout << " memoryUsageBytes_max: " << std::fixed << perfData.memoryUsageBytes_max << std::endl;
	std::cout << " memoryUsageBytes_min: " << std::fixed << perfData.memoryUsageBytes_min << std::endl;



	

	//myVec.GetAt(1, findperson);
	//cout << findperson.first << std::endl;
	cout << "size :" << myVec.GetSize() << std::endl;
	//cout << "capacity :" << myVec.GetCapacity() << std::endl;
	std::vector<sPerson> sortedVec;
	myVec.SortPeople(sortedVec,  iPersonMotron::ASC_BY_HEALTH);

	std::cout << "//////   ASC_BY_HEALTH      //////" << std::endl;

	for (unsigned int index = 0; index != 100 /*myVec.GetSize()*/; index++)
	{
		sPerson thePerson;
		myVec.GetAt(index, thePerson);

		std::cout << index << " "
			<< thePerson.first << " "
			<< thePerson.health << " "
			<< thePerson.last << std::endl;
	}

	std::cout << "//////    Perfomance     //////" << std::endl;
	std::cout << " elapsedCallTime_ms  :" << std::fixed << perfData.elapsedCallTime_ms << std::endl;
	std::cout << " memoryUsageBytes_avg: " << std::fixed << perfData.memoryUsageBytes_avg << std::endl;
	std::cout << " memoryUsageBytes_max: " << std::fixed << perfData.memoryUsageBytes_max << std::endl;
	std::cout << " memoryUsageBytes_min: " << std::fixed << perfData.memoryUsageBytes_min << std::endl;


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
	myVec.FindPeople(vec_findByRadius, loc, 30.0f, 2);
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
    
    std::cout << "//////    FindPeopleByHealth     //////" << std::endl;
    std::vector<sPerson> vec_findByHealth;
    myVec.FindPeople(vec_findByHealth, 40, 75, 10);
    for (int i = 0; i < vec_findByHealth.size(); i++)
    {
        std::cout << "First: " << vec_findByHealth[i].first << std::endl;
        std::cout << "Last: " << vec_findByHealth[i].last << std::endl;
        std::cout << "Age: " << vec_findByHealth[i].age << std::endl;
        std::cout << "Unique ID: " << vec_findByHealth[i].uniqueID << std::endl;
        std::cout << "Health: " << vec_findByHealth[i].health << std::endl;
        std::cout << "Location: (" << vec_findByHealth[i].location.x << "," << vec_findByHealth[i].location.y << ","
        << vec_findByHealth[i].location.z << ")" << std::endl;
        std::cout << std::endl;
    }
	myVec.GetPerformanceFromLastCall(perfData);
	std::cout << "//////    Perfomance     //////" << std::endl;
	std::cout << " elapsedCallTime_ms  :" << std::fixed << perfData.elapsedCallTime_ms << std::endl;
	std::cout << " memoryUsageBytes_avg: " << std::fixed << perfData.memoryUsageBytes_avg << std::endl;
	std::cout << " memoryUsageBytes_max: " << std::fixed << perfData.memoryUsageBytes_max << std::endl;
	std::cout << " memoryUsageBytes_min: " << std::fixed << perfData.memoryUsageBytes_min << std::endl;

	std::cout << "//////    FindPeople by health and radius     //////" << std::endl;
	std::vector<sPerson> vec_findByHealthRad;
	loc.x = 10.0f;
	loc.y = 1.0f;
	loc.z = 15;
	myVec.FindPeople(vec_findByHealthRad, loc, 199, 0.0f, 80.0f);
	for (int i = 0; i < vec_findByHealthRad.size(); i++)
	{
		std::cout << "First: " << vec_findByHealthRad[i].first << std::endl;
		std::cout << "Last: " << vec_findByHealthRad[i].last << std::endl;
		std::cout << "Age: " << vec_findByHealthRad[i].age << std::endl;
		std::cout << "Unique ID: " << vec_findByHealthRad[i].uniqueID << std::endl;
		std::cout << "Health: " << vec_findByHealthRad[i].health << std::endl;
		std::cout << "Location: (" << vec_findByHealthRad[i].location.x << "," << vec_findByHealthRad[i].location.y << ","
			<< vec_findByHealthRad[i].location.z << ")" << std::endl;
		std::cout << std::endl;
	}


	std::cout << "//////    FindPeople by First     //////" << std::endl;
	std::vector<sPerson> vec_findByNameFirst;
	myVec.FindPeopleByName(vec_findByNameFirst, jacobWithFirstOnly);
	for (int i = 0; i < vec_findByNameFirst.size(); i++)
	{
		std::cout << "First: " << vec_findByNameFirst[i].first << std::endl;
		std::cout << "Last: " << vec_findByNameFirst[i].last << std::endl;
		std::cout << "Age: " << vec_findByNameFirst[i].age << std::endl;
		std::cout << "Unique ID: " << vec_findByNameFirst[i].uniqueID << std::endl;
		std::cout << "Health: " << vec_findByNameFirst[i].health << std::endl;
		std::cout << "Location: (" << vec_findByNameFirst[i].location.x << "," << vec_findByNameFirst[i].location.y << ","
			<< vec_findByNameFirst[i].location.z << ")" << std::endl;
		std::cout << std::endl;
	}


	std::cout << "//////    FindPeople by Last     //////" << std::endl;
	std::vector<sPerson> vec_findByNameLast;
	myVec.FindPeopleByName(vec_findByNameLast, michael);
	for (int i = 0; i < vec_findByNameLast.size(); i++)
	{
		std::cout << "First: " << vec_findByNameLast[i].first << std::endl;
		std::cout << "Last: " << vec_findByNameLast[i].last << std::endl;
		std::cout << "Age: " << vec_findByNameLast[i].age << std::endl;
		std::cout << "Unique ID: " << vec_findByNameLast[i].uniqueID << std::endl;
		std::cout << "Health: " << vec_findByNameLast[i].health << std::endl;
		std::cout << "Location: (" << vec_findByNameLast[i].location.x << "," << vec_findByNameLast[i].location.y << ","
			<< vec_findByNameLast[i].location.z << ")" << std::endl;
		std::cout << std::endl;
	}






	
	system("pause");

}
