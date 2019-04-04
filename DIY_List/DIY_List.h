#ifndef _DIY_List
#define _DIY_List

#include <cPerson.h>
#include <iPersonMotron.h>
#include <time.h>

class NodeComparer
{
public:
	virtual bool operator()(sPerson *a, sPerson *b) = 0;
};

class DIY_List : public iPersonMotron
{
public:
	DIY_List() : firstNode(nullptr), lastNode(nullptr), size(0) {};
	~DIY_List() { clear(); }

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

	eContainerType getContainerType(void) {
		return CUSTOM_DIY_LIST;
	}

	unsigned int GetSize(void) { return this->size; }
	void clear();

	void PushBack(sPerson& person);
	void PushFront(sPerson& person);
	void SetAt(int idx, sPerson& p);

private:
	unsigned int size;
	struct Node
	{
		sPerson* value;
		Node* nextNode;
		Node* previousNode;
		Node() 
		{
			nextNode = NULL;
			previousNode = NULL;
		}
		Node(sPerson* val, Node* next, Node* prev) : value(val), nextNode(next), previousNode(prev) 
		{
			nextNode = NULL;
			previousNode = NULL;
		}
		Node(sPerson* val) :value(val) 
		{
			nextNode = NULL;
			previousNode = NULL;
		}
	};

	Node* firstNode;
	Node* lastNode;
	void _qsort(Node* left, Node* right, NodeComparer& cmp, Node** newHead, Node** newTail);

	sPerfData m_perfData;
	void startCall();
	void updateMemoryUsage();
	void endCall();
	clock_t start_time;
};

#endif
