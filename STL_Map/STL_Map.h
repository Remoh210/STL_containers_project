#pragma once



#include "cPerson.h"
#include "iPersonMotron.h"
#include <vector>
#include <map>


class  STL_Map : public iPersonMotron
{
public:
	STL_Map();
    ~STL_Map();

	//Will also generate random data for each peeson
	bool LoadDataFilesIntoContainer(std::string firstNameFemaleFileName,
		std::string firstNameMaleFileName,
		std::string lastNameFileName);

	//Name
	bool FindPeopleByName(std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople = INT_MAX);
	bool FindPeopleByName(std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople = INT_MAX);
	//Index
	bool GetAt(unsigned int index, sPerson &thePerson);
	//ID
	bool FindPersonByID(sPerson &person, unsigned long long uniqueID);
	//Radius
	bool FindPeople(std::vector<sPerson> &vecPeople, sPoint location, float radius,
		int maxPeopleToReturn = INT_MAX);
    //Health
    bool FindPeople( std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
                    int maxPeopleToReturn = INT_MAX );
	//Health and Radius
	bool FindPeople(std::vector<sPerson> &vecPeople,
		sPoint location, float radius, float minHealth, float maxHealth,
		int maxPeopleToReturn = INT_MAX);
	//Sort
	bool SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType);



	bool GetPerformanceFromLastCall(sPerfData &callStats) { return false; }
	eContainerType getContainerType(void);

	unsigned int GetSize(void);
	void PushBack(sPerson person);

private:
	std::map<unsigned int, sPerson> mMap_Person;
    //std::vector<sPerson> mVec_Person;
	//Generate n random data for all people
	//Called inside LoadDataFilesIntoContainer();
	void GenerateData(std::string first, int number = 10);
};



