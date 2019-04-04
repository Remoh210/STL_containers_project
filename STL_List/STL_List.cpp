#include <math.h>
#include <fstream>
#include "iPersonMotron.h"
#include <algorithm>
#include <iostream>
#include "STL_List.h"
#include <Windows.h>
#include <psapi.h>


//   ________  _________  ___               ___       ___  ________  _________   
//  |\   ____\|\___   ___\\  \             |\  \     |\  \|\   ____\|\___   ___\ 
//  \ \  \___|\|___ \  \_\ \  \            \ \  \    \ \  \ \  \___|\|___ \  \_| 
//   \ \_____  \   \ \  \ \ \  \            \ \  \    \ \  \ \_____  \   \ \  \  
//    \|____|\  \   \ \  \ \ \  \____        \ \  \____\ \  \|____|\  \   \ \  \ 
//      ____\_\  \   \ \__\ \ \_______\       \ \_______\ \__\____\_\  \   \ \__\
//     |\_________\   \|__|  \|_______|        \|_______|\|__|\_________\   \|__|
//     \|_________|                                          \|_________|        


float distance(sPoint point, sPoint point2)
{
	return std::sqrt(pow((point.x - point2.x), 2) + pow((point.y - point2.y), 2) + pow((point.z - point2.z), 2));
}


//Random float generator
float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}



bool sortByFirstASC(sPerson& a, sPerson& b) {
	if (a.first == b.first) {
		return a.last > b.last;
	}
	else {
		return a.first > b.first;
	}
}


bool sortByFirstDESC(sPerson& a, sPerson& b) {
	if (a.first == b.first) {
		return a.last < b.last;
	}
	else {
		return a.first < b.first;
	}
}

bool sortByLastASC(sPerson& a, sPerson& b) {
	if (a.last == b.last) {
		return a.first > b.first;
	}
	else {
		return a.last > b.last;
	}
}

bool sortByLastDESC(sPerson& a, sPerson& b) {
	if (a.last == b.last) {
		return a.first < b.first;
	}
	else {
		return a.last < b.last;
	}
}


bool sortByIdASC(sPerson& a, sPerson& b) {
	return a.uniqueID < b.uniqueID;
}

bool sortByIdDESC(sPerson& a, sPerson& b) {
	return a.uniqueID > b.uniqueID;
}

bool sortByHpASC(sPerson& a, sPerson& b) {
	return a.health < b.health;
}

bool sortByHpDESC(sPerson& a, sPerson& b) {
	return a.health > b.health;
}

STL_List::STL_List()

{
	this->mList_Person.clear();
}

STL_List::~STL_List()
{

}


bool STL_List::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName, std::string firstNameMaleFileName, std::string lastNameFileName)
{
	this->startCall();
	std::vector <std::string> vec_FemaleNames;
	std::vector <std::string> vec_MaleNames;
	std::vector <std::string> vec_Surnames;
	mList_Person.clear();
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
		if (treshold != "") {
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
		if (treshold != "") {
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
		if (treshold != "") {
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
			int NameRandIndex = rand() % vec_MaleNames.size();
			int SurnameRandIndex = rand() % vec_Surnames.size();
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
			this->mList_Person.push_back(curPerson);
		}
		//Female
		else
		{
			int NameRandIndex = rand() % vec_FemaleNames.size();
			int SurnameRandIndex = rand() % vec_Surnames.size();
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
			this->mList_Person.push_back(curPerson);

		}

	}
	this->endCall();
	return true;
}




bool STL_List::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	this->startCall();
	int count = 0;
	//Search by first
	if (personToMatch.first != "" && personToMatch.last == "")
	{
		std::list<sPerson>::iterator it = mList_Person.begin();
		for (int i = 0; i < this->mList_Person.size(); i++)
		{
			if (it->first == personToMatch.first)
			{
				vecPeople.push_back(*it);
				count++;
				if (count == maxNumberOfPeople)
				{
					this->endCall();
					return true;
				}
			}
			it++;
		}
	}

	//Search by last
	if (personToMatch.last != "" && personToMatch.first == "")
	{
		std::list<sPerson>::iterator it = mList_Person.begin();
		for (int i = 0; i < this->mList_Person.size(); i++)
		{
			if (it->last == personToMatch.last)
			{
				vecPeople.push_back(*it);
				count++;
				if (count == maxNumberOfPeople)
				{
					this->endCall();
					return true;
				}
			}
			it++;
		}
	}

	//Search by first and last
	if (personToMatch.last != "" && personToMatch.first != "")
	{
		std::list<sPerson>::iterator it = mList_Person.begin();
		for (int i = 0; i < this->mList_Person.size(); i++)
		{
			if (it->first == personToMatch.first && it->last == personToMatch.last)
			{
				vecPeople.push_back(*it);
				count++;
				if (count == maxNumberOfPeople)
				{
					this->endCall();
					return true;
				}
			}
			it++;
		}
	}


	//Return all < maxNumberOfPeople
	if (personToMatch.last == "" && personToMatch.first == "")
	{
		std::list<sPerson>::iterator it = mList_Person.begin();
		for (int i = 0; i < this->mList_Person.size(); i++)
		{
			vecPeople.push_back(*it);
			count++;
			if (count == maxNumberOfPeople)
			{
				this->endCall();
				return true;
			}
			it++;
		}

	}


	//If 0 people found
	this->endCall();
	if (count == 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool STL_List::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	int added = 0;
	this->startCall();
	for (int i = 0; i < vecPeopleToMatch.size(); i++)
	{
		int cur = vecPeople.size();
		FindPeopleByName(vecPeople, vecPeopleToMatch[i], maxNumberOfPeople - added);
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





bool STL_List::GetPerformanceFromLastCall(sPerfData & callStats)
{
	callStats = this->m_perfData;
	return true;
}

eContainerType STL_List::getContainerType(void)
{
	return STD_LIST;
}

unsigned int STL_List::GetSize(void)
{
	this->startCall();
	return this->mList_Person.size();
	this->endCall();
}

void STL_List::PushBack(sPerson person)
{
	this->mList_Person.push_back(person);
}

void STL_List::startCall()
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

void STL_List::updateMemoryUsage()
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

void STL_List::endCall()
{
	updateMemoryUsage();
	clock_t end = clock();
	clock_t delta = end - start_time;
	double a = (double)delta / (CLOCKS_PER_SEC / 100);
	this->m_perfData.elapsedCallTime_ms = static_cast<float>(a);
}


bool STL_List::FindPersonByID(sPerson &person, unsigned long long uniqueID)
{
	this->startCall();
	std::list<sPerson>::iterator it = mList_Person.begin();
	for (int i = 0; i < this->mList_Person.size(); i++)
	{
		
		if (it->uniqueID == uniqueID)
		{
			person = *it;
			this->endCall();
			return true;
		}
		it++;
	}
	this->endCall();
	return false;
}

bool STL_List::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	this->startCall();
	int count = 0;
	std::list<sPerson>::iterator it = mList_Person.begin();
	for (int i = 0; i < this->mList_Person.size(); i++)
	{
		if (distance(it->location, location) <= radius)
		{
			vecPeople.push_back(*it);
			count++;
			if (count == maxPeopleToReturn)
			{
				this->endCall();
				return true;
			}
		}
		it++;
	}
	//If 0 people found
	this->endCall();
	if (count == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool STL_List::FindPeople(std::vector<sPerson> &vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	this->startCall();
	int count = 0;
	std::list<sPerson>::iterator it = mList_Person.begin();
	for (int i = 0; i < this->mList_Person.size(); i++)
	{
		if (it->health >= minHealth && it->health <= maxHealth)
		{
			vecPeople.push_back(*it);
			count++;
			if (count == maxPeopleToReturn)
			{
				this->endCall();
				return true;
			}
		}
		it++;
	}
	//If 0 people found
	this->endCall();
	if (count == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool STL_List::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	this->startCall();
	int count = 0;
	std::list<sPerson>::iterator it = mList_Person.begin();
	for (int i = 0; i < this->mList_Person.size(); i++)
	{
		if (it->health >= minHealth && it->health <= maxHealth)
		{
			if (distance(it->location, location) <= radius)
			{
				vecPeople.push_back(*it);
				count++;
				if (count == maxPeopleToReturn)
				{
					this->endCall();
					return true;
				}
			}
		}
		it++;
	}
	//If 0 people found
	this->endCall();
	if (count == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool STL_List::SortPeople(std::vector<sPerson>& vecPeople, eSortType sortType)
{
	this->startCall();
	switch (sortType)
	{
	case iPersonMotron::ASC_FIRST_THEN_LAST:
	{
		mList_Person.sort(sortByFirstASC);

		break;
	}

	case iPersonMotron::DESC_FIRST_THEN_LAST:
	{
		
		mList_Person.sort(sortByFirstDESC);
		break;
	}

	case iPersonMotron::ASC_LAST_THEN_FIRST:
	{
		mList_Person.sort(sortByLastASC);
		break;
	}
	case iPersonMotron::DESC_LAST_THEN_FIRST:
	{

		mList_Person.sort(sortByLastDESC);
		break;
	}

	case iPersonMotron::ASC_BY_ID:
	{
		mList_Person.sort(sortByIdASC);
		break;
	}

	case iPersonMotron::DESC_BY_ID:
	{
		mList_Person.sort(sortByIdDESC);
		break;
	}

	case iPersonMotron::ASC_BY_HEALTH:
	{
		mList_Person.sort(sortByHpASC);
		break;
	}

	case iPersonMotron::DESC_BY_HEALTH:
	{
		mList_Person.sort(sortByHpDESC);
		break;
	}

	default:
		return false;
		break;
	}


	std::list<sPerson>::iterator it;
	for (it = mList_Person.begin(); it != mList_Person.end(); it++)
	{
		vecPeople.push_back(*it);
	}

	this->endCall();
	return true;
}

