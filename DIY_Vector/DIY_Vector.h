#ifndef _DIY_Vector_HG_
#define _DIY_Vector_HG_



#include "cPerson.h"
#include "iPersonMotron.h"
#include <time.h>

class  DIY_Vector : public iPersonMotron
{
public:
	DIY_Vector();
	 ~DIY_Vector();

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



	bool GetPerformanceFromLastCall(sPerfData &callStats);
	eContainerType getContainerType(void);

	void SetCapacity(unsigned int newCapacity);
	unsigned int GetSize(void);		
	unsigned int GetCapacity(void);	
	void clear();

	void PushBack(sPerson person);

private:

	sPerson* m_Data;			
	unsigned int m_CurSize;		
	unsigned int m_next;
	void Qsort(int left, int right, eSortType type);

	sPerfData m_perfData;
	void startCall();
	void updateMemoryUsage();
	void endCall();
	clock_t start_time;
};

#endif


