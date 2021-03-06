#ifndef _DIY_Vector_HG_
#define _DIY_Vector_HG_



#include "cPerson.h"
#include "iPersonMotron.h"
#include <time.h>

class  DIY_Map : public iPersonMotron
{
public:
	DIY_Map(unsigned int size = 5000);
	~DIY_Map();

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
	bool FindPeople(std::vector<sPerson> &vecPeople, float minHealth, float maxHealth,
		int maxPeopleToReturn = INT_MAX);
	//Health and Radius
	bool FindPeople(std::vector<sPerson> &vecPeople,
		sPoint location, float radius, float minHealth, float maxHealth,
		int maxPeopleToReturn = INT_MAX);
	//Sort
	bool SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType);



	bool GetPerformanceFromLastCall(sPerfData &callStats);
	eContainerType getContainerType(void);

	unsigned int GetSize(void);
	void clear();

	void InsertAt(unsigned int index, sPerson person);

private:

	struct sHashEntry {
		sHashEntry(unsigned int key, sPerson value)
		{
			this->key = key;
			this->value = value;
		}
		unsigned int key;
		sPerson value;
	};

	sHashEntry **m_table;
	unsigned int m_CurSize;
	sPerfData m_perfData;

	void startCall();
	void updateMemoryUsage();
	void endCall();
	clock_t start_time;


};

#endif


