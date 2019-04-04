#include "iPersonMotron.h"
#include "cPerson.h"
#include "DIY_List.h"
#include <iostream>
#include <Windows.h>
#include <psapi.h>
#include <fstream>
#include <cmath>


//   ________  ___      ___    ___      ___       ___  ________  _________   
//  |\   ___ \|\  \    |\  \  /  /|    |\  \     |\  \|\   ____\|\___   ___\ 
//  \ \  \_|\ \ \  \   \ \  \/  / /    \ \  \    \ \  \ \  \___|\|___ \  \_| 
//   \ \  \ \\ \ \  \   \ \    / /      \ \  \    \ \  \ \_____  \   \ \  \  
//    \ \  \_\\ \ \  \   \/  /  /        \ \  \____\ \  \|____|\  \   \ \  \ 
//     \ \_______\ \__\__/  / /           \ \_______\ \__\____\_\  \   \ \__\
//      \|_______|\|__|\___/ /             \|_______|\|__|\_________\   \|__|
//                    \|___|/                            \|_________|        
// 

//Random float generator
float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

DIY_List::DIY_List()
{
}

bool DIY_List::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName, std::string firstNameMaleFileName, std::string lastNameFileName)
{
	this->startCall();
	std::vector<std::string> vec_FemaleNames;
	std::vector<std::string> vec_MaleNames;
	std::vector<std::string> vec_Surnames;
	this->clear();
	//Load female first names
	std::ifstream file(firstNameFemaleFileName.c_str());
	//Return false if no file
	if (!file.is_open())
	{
		return false;
	}
	std::string treshold;
	while (!file.eof())
	{
		treshold = "";
		file >> treshold;
		if (treshold != "")
		{
			vec_FemaleNames.push_back(treshold);
		}
		file >> treshold;
		file >> treshold;
		file >> treshold;
	}
	file.close();

	//Load male first names
	std::ifstream file2(firstNameMaleFileName.c_str());
	//Return false if no file
	if (!file2.is_open())
	{
		return false;
	}
	while (!file2.eof())
	{
		treshold = "";
		file2 >> treshold;
		if (treshold != "")
		{
			vec_MaleNames.push_back(treshold);
		}
		file2 >> treshold;
		file2 >> treshold;
		file2 >> treshold;
	}
	file2.close();

	//Load surnames
	std::ifstream file3(lastNameFileName.c_str());
	if (!file3.is_open())
	{
		return false;
	}
	while (!file3.eof())
	{
		treshold = "";
		file3 >> treshold;
		if (treshold != "")
		{
			vec_Surnames.push_back(treshold);
		}
		file3 >> treshold;
		file3 >> treshold;
		file3 >> treshold;
	}
	file3.close();

	int numPeopleToGen = 1000;
	for (int i = 0; i < numPeopleToGen; i++)
	{

		int MaleFemale = rand() % 10 + 1;

		//Male
		if (MaleFemale < 5)
		{
			int NameRandIndex = rand() % vec_MaleNames.size() - 1;
			int SurnameRandIndex = rand() % vec_Surnames.size() - 1;
			sPerson curPerson;
			curPerson.first = vec_MaleNames[NameRandIndex];
			curPerson.last = vec_Surnames[SurnameRandIndex];
			//Generate age
			int age = rand() % 100 + 1;
			curPerson.age = age;
			//Generate health
			float health = RandomFloat(10.0f, 100.0f);
			curPerson.health = health;
			float x = RandomFloat(-5000.0f, 5000.0f);
			float y = RandomFloat(-100.0f, 100.0f);
			float z = RandomFloat(-5000.0f, 5000.0f);
			sPoint location;
			location.x = x;
			location.y = y;
			location.z = z;
			curPerson.location = location;
			curPerson.uniqueID = i;
			this->PushBack(curPerson);
		}
		//Female
		else
		{
			int NameRandIndex = rand() % vec_FemaleNames.size() - 1;
			int SurnameRandIndex = rand() % vec_Surnames.size() - 1;
			sPerson curPerson;
			curPerson.first = vec_FemaleNames[NameRandIndex];
			curPerson.last = vec_Surnames[SurnameRandIndex];
			//Generate age
			int age = rand() % 100 + 1;
			curPerson.age = age;
			//Generate health
			float health = RandomFloat(10.0f, 100.0f);
			curPerson.health = health;
			float x = RandomFloat(-5000.0f, 5000.0f);
			float y = RandomFloat(-100.0f, 100.0f);
			float z = RandomFloat(-5000.0f, 5000.0f);
			sPoint location;
			location.x = x;
			location.y = y;
			location.z = z;
			curPerson.location = location;
			curPerson.uniqueID = i;
			this->PushBack(curPerson);
		}
	}
	this->endCall();
	return true;
}

bool DIY_List::FindPeopleByName(std::vector<sPerson> &vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	int added = 0;
	this->startCall();
	for (Node *i = firstNode; i != NULL; i = i->nextNode)
	{
		if (personToMatch.first == i->value->first || personToMatch.last == i->value->last)
		{
			vecPeople.push_back(*i->value);
			added++;
		}
	}
	this->endCall();
	return added > 0;
}
bool DIY_List::FindPeopleByName(std::vector<sPerson> &vecPeople, std::vector<sPerson> &vecPeopleToMatch, int maxNumberOfPeople)
{
	int added = 0;
	this->startCall();
	for (int i = 0; i < vecPeopleToMatch.size(); i++)
	{
		int cur = vecPeople.size();
		FindPeopleByName(vecPeople, vecPeopleToMatch, maxNumberOfPeople - added);
		added += (vecPeople.size() - cur);
		if (added >= maxNumberOfPeople)
		{
			this->endCall();
			return true;
		}
	}
	this->endCall();
	return added > 0;
}
//Index
bool DIY_List::GetAt(unsigned int index, sPerson &thePerson)
{
	this->startCall();
	Node *nth = firstNode;
	for (int i = 0; i < index; i++)
	{
		if (nth == NULL || nth->nextNode == NULL)
		{
			break;
		}
		nth = nth->nextNode;
	}
	if (nth != NULL)
	{
		thePerson = *nth->value;
		this->endCall();
		return true;
	}
	this->endCall();
	return false;
}
//ID
bool DIY_List::FindPersonByID(sPerson &person, unsigned long long uniqueID)
{
	this->startCall();
	Node *nth = firstNode;
	for (int i = 0; i < this->size; i++)
	{
		if (nth == NULL || nth->nextNode == NULL)
		{
			break;
		}
		if (nth->value->uniqueID == uniqueID)
		{
			break;
		}
		nth = nth->nextNode;
	}
	if (nth != NULL)
	{
		person = *nth->value;
		this->endCall();
		return true;
	}
	this->endCall();
	return false;
}

float distance(sPoint point, sPoint point2)
{
	return std::sqrt(pow((point.x - point2.x), 2) + pow((point.y - point2.y), 2) + pow((point.z - point2.z), 2));
}
//Radius
bool DIY_List::FindPeople(std::vector<sPerson> &vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	this->startCall();
	int added_cnt = 0;
	for (Node *n = firstNode; n != NULL; n = n->nextNode)
	{
		if (distance(n->value->location, location) <= radius)
		{
			vecPeople.push_back(*n->value);
			added_cnt++;
			if (added_cnt == maxPeopleToReturn)
			{
				this->endCall();
				return true;
			}
		}
	}
	this->endCall();
	return added_cnt > 0;
}
//Health
bool DIY_List::FindPeople(std::vector<sPerson> &vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	this->startCall();
	int added_cnt = 0;
	for (Node *n = firstNode; n != NULL; n = n->nextNode)
	{
		if (n->value->health < maxHealth && n->value->health > minHealth)
		{
			vecPeople.push_back(*n->value);
			added_cnt++;
			if (added_cnt == maxPeopleToReturn)
			{
				this->endCall();
				return true;
			}
		}
	}
	this->endCall();
	return added_cnt > 0;
}
//Health and Radius
bool DIY_List::FindPeople(std::vector<sPerson> &vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	this->startCall();
	int added_cnt = 0;
	for (Node *n = firstNode; n != NULL; n = n->nextNode)
	{
		if (n->value->health <= maxHealth && n->value->health >= minHealth && distance(n->value->location, location) <= radius)
		{
			vecPeople.push_back(*n->value);
			added_cnt++;
			if (added_cnt == maxPeopleToReturn)
			{
				this->endCall();
				return true;
			}
		}
	}
	this->endCall();
	return added_cnt > 0;
}

//class FirstNameComparer : public NodeComparer
//{
//public:
//	bool operator()(sPerson *a, sPerson *b)
//	{
//		if (a->first == b->first) {
//			return a->last <= b->last;
//		}
//		else {
//			return a->first <= b->first;
//		}
//	};
//};

class FirstNameComparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		return a->first <= b->first;
	};
};



class FirstThenLastASC_omparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		if (b->first > a->first)
		{
			return true;
		}
		else if (b->first == a->first)
		{
			return a->last <= b->last;
		}
		return false;
	};
};

class LastThenFirstASC_omparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		if (b->last > a->last)
		{
			return true;
		}
		else if (b->last == a->last)
		{
			return a->first <= b->first;
		}
		return false;
	};
};


class FirstThenLastDESC_omparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		if (b->first < a->first)
		{
			return true;
		}
		else if (b->first == a->first)
		{
			return a->last >= b->last;
		}
		return false;
	};
};

class LastThenFirstDESC_omparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		if (b->last < a->last)
		{
			return true;
		}
		else if (b->last == a->last)
		{
			return a->first >= b->first;
		}
		return false;
	};
};







class ID_ASC_Comparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		return a->uniqueID <= b->uniqueID;
	};
};

class ID_DESC_Comparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		return a->uniqueID >= b->uniqueID;
	};
};


class HealthASC_Comparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		return a->health <= b->health;
	};
};

class HealthDESC_Comparer : public NodeComparer
{
public:
	bool operator()(sPerson *a, sPerson *b)
	{
		return a->health >= b->health;
	};
};








void DIY_List::startCall()
{
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;

	hProcess = GetCurrentProcess();
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
	if (NULL == hProcess)
	{
		return;
	}

	this->m_perfData.memoryUsageBytes_min = pmc.WorkingSetSize;
	this->m_perfData.memoryUsageBytes_max = pmc.WorkingSetSize;
	this->m_perfData.memoryUsageBytes_avg = pmc.WorkingSetSize;
}

void DIY_List::updateMemoryUsage()
{
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;

	hProcess = GetCurrentProcess();
	GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));

	if (NULL == hProcess)
	{
		return;
	}

	double current = pmc.WorkingSetSize;
	this->m_perfData.memoryUsageBytes_avg = (this->m_perfData.memoryUsageBytes_avg + current) / 2.0;
	if (current > this->m_perfData.memoryUsageBytes_max) {
		this->m_perfData.memoryUsageBytes_max = current;
	}
	else if (current < this->m_perfData.memoryUsageBytes_min) {
		this->m_perfData.memoryUsageBytes_min = current;
	}
}

void DIY_List::endCall()
{
	updateMemoryUsage();
	clock_t end = clock();
	clock_t delta = end - start_time;
	double a = (double)delta / (CLOCKS_PER_SEC / 100);
	this->m_perfData.elapsedCallTime_ms = static_cast<float>(a);
}

bool DIY_List::GetPerformanceFromLastCall(sPerfData & callStats)
{
	callStats = this->m_perfData;
	return true;
}

void DIY_List::_qsort(Node *left, Node *right, NodeComparer &cmp, Node **newHead, Node **newTail)
{
	if (left == right || left == NULL || right == NULL)
		return;
	Node *i = left;

	Node *pivot = right;
	Node *tail = pivot;
	Node *newLeft = NULL;
	bool swapsOccured = false;
	int swaps = 0;
	while (i != pivot && i != NULL)
	{

		if (cmp(i->value, pivot->value))
		{
			if (newLeft == NULL)
			{
				newLeft = i;
			}
			i = i->nextNode;
			continue;
		}
		if (i == NULL || i == pivot)
		{
			break;
		}
		swapsOccured = true;
		swaps++;
		Node *newI = i->nextNode;
		newI->previousNode = i->previousNode;

		if (i->previousNode != NULL) {
			i->previousNode->nextNode = newI;
		}

		i->previousNode = tail;
		i->nextNode = tail->nextNode;
		tail->nextNode = i;
		tail = i;
		i = newI;
	}
	if (newLeft == NULL) {
		newLeft = pivot;
	}
	if (swapsOccured)
	{
		// std::cout << "LEFT RECUR\n";
		_qsort(newLeft, pivot->previousNode, cmp, NULL, NULL);
		// std::cout << "RIGHT RECUR\n";
		_qsort(pivot, tail, cmp, NULL, NULL);
	}

	if (newHead != NULL)
	{
		while (newLeft->previousNode != NULL) {
			newLeft = newLeft->previousNode;
		}
		*newHead = newLeft;

		while (tail->nextNode != NULL) {
			tail = tail->nextNode;
		}
		*newTail = tail;
	}
}



//Sort
bool DIY_List::SortPeople(std::vector<sPerson> &vecPeople, eSortType sortType)
{
	this->startCall();
	NodeComparer *cmp = NULL;

	switch (sortType)
	{
	case iPersonMotron::ASC_FIRST_THEN_LAST:
	{
		cmp = new FirstThenLastASC_omparer();
		break;
	}
	case iPersonMotron::DESC_FIRST_THEN_LAST:
	{
		cmp = new FirstThenLastDESC_omparer();
		break;
	}
		
	case iPersonMotron::ASC_LAST_THEN_FIRST:
	{
		cmp = new LastThenFirstASC_omparer();
		break;
	}

	case iPersonMotron::DESC_LAST_THEN_FIRST:
	{
		cmp = new LastThenFirstDESC_omparer();
		break;
	}
		
	case iPersonMotron::ASC_BY_ID:
	{
		cmp = new ID_ASC_Comparer();
		break;
	}
	case iPersonMotron::DESC_BY_ID:
	{
		cmp = new ID_DESC_Comparer();
		break;
	}
		
	case iPersonMotron::ASC_BY_HEALTH:
	{
		cmp = new HealthASC_Comparer();
		break;
	}
		
	case iPersonMotron::DESC_BY_HEALTH:
	{
		cmp = new HealthDESC_Comparer();
		break;
	}
	default:
		break;
	}

	Node *newFirst;
	Node *newLast;
	_qsort(firstNode, lastNode, *cmp, &newFirst, &newLast);

	firstNode = newFirst;
	lastNode = newLast;
	for (Node *i = firstNode; i != NULL; i = i->nextNode)
	{
		vecPeople.push_back(*i->value);
	}
	delete cmp;

	this->endCall();
	return true;
}

void DIY_List::clear()
{
	Node *i = firstNode;
	while (i != NULL)
	{
		Node *i_cpy = i;
		i = i->nextNode;
		delete i_cpy->value;
		delete i_cpy;
	}
	this->firstNode = NULL;
	this->lastNode = NULL;
	this->size = 0;
}
void DIY_List::PushFront(sPerson &person)
{
	sPerson *sp = new sPerson(person);
	Node *newNode = new Node(sp);
	if (this->lastNode == NULL)
	{
		this->firstNode = newNode;
		this->lastNode = newNode;
	}
	else
	{
		this->firstNode->previousNode = newNode;
		newNode->nextNode = this->firstNode;
		this->firstNode = newNode;
	}
	this->size++;
}
void DIY_List::SetAt(int idx, sPerson &p)
{
	this->startCall();
	if (this->size == 0)
	{
		PushBack(p);
		this->endCall();
		return;
	}
	Node *nth = firstNode;
	for (int i = 0; i < idx; i++)
	{
		if (nth->nextNode == NULL)
		{
			break;
		}
		nth = nth->nextNode;
	}
	Node *newNode = new Node(&p, nth, nth->nextNode);
	Node *nextNode = nth->nextNode;
	if (nextNode != NULL)
	{
		nextNode->previousNode = newNode;
	}
	nth->nextNode = newNode;
	this->endCall();
}

void DIY_List::PushBack(sPerson &person)
{
	this->startCall();
	sPerson *sp = new sPerson(person);
	Node *newNode = new Node(sp);
	if (this->firstNode == NULL)
	{
		this->firstNode = newNode;
		this->lastNode = newNode;
	}
	else
	{
		this->lastNode->nextNode = newNode;
		newNode->previousNode = this->lastNode;
		this->lastNode = newNode;
	}
	this->size++;
	this->endCall();
}