#ifndef _DIY_Vector_HG_
#define _DIY_Vector_HG_



#include "cPerson.h"


class  DIY_Vector
{
public:
	DIY_Vector();
	virtual ~DIY_Vector();



	void PushBack(sPerson person);
	void InsertAt(unsigned int index, sPerson person);

	//Name
	bool FindPeopleByName(std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople = INT_MAX);
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
	//bool SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType);



	void SetCapacity(unsigned int newCapacity);
	unsigned int GetSize(void);		
	unsigned int GetCapacity(void);	
	void clear();

private:

	sPerson* m_Data;			
	unsigned int m_CurSize;		
	unsigned int m_next;		
};

#endif


