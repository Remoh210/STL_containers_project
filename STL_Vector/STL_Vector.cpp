#include <math.h>
#include <fstream>
#include "iPersonMotron.h"
#include "STL_Vector.h"
#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <psapi.h>

#include <map>


//   ________  _________  ___               ___      ___ _______   ________ _________  ________  ________     
//  |\   ____\|\___   ___\\  \             |\  \    /  /|\  ___ \ |\   ____\\___   ___\\   __  \|\   __  \    
//  \ \  \___|\|___ \  \_\ \  \            \ \  \  /  / | \   __/|\ \  \___\|___ \  \_\ \  \|\  \ \  \|\  \   
//   \ \_____  \   \ \  \ \ \  \            \ \  \/  / / \ \  \_|/_\ \  \       \ \  \ \ \  \\\  \ \   _  _\  
//    \|____|\  \   \ \  \ \ \  \____        \ \    / /   \ \  \_|\ \ \  \____   \ \  \ \ \  \\\  \ \  \\  \| 
//      ____\_\  \   \ \__\ \ \_______\       \ \__/ /     \ \_______\ \_______\  \ \__\ \ \_______\ \__\\ _\ 
//     |\_________\   \|__|  \|_______|        \|__|/       \|_______|\|_______|   \|__|  \|_______|\|__|\|__|
//     \|_________|       

float distance(sPoint point, sPoint point2)
{
	return std::sqrt(pow((point.x - point2.x), 2) + pow((point.y - point2.y), 2) + pow((point.z - point2.z), 2));
}

bool sortByFirstASC(sPerson& a, sPerson& b) { 
	if (a.first == b.first) {
		return a.last < b.last;
	}
	else {
		return a.first < b.first;
	}
}

bool sortByFirstDESC(sPerson& a, sPerson& b) {
	if (a.first == b.first) {
		return a.last > b.last;
	}
	else {
		return a.first > b.first;
	}
}

bool sortByLastASC(sPerson& a, sPerson& b) {
	if (a.last == b.last) {
		return a.first < b.first;
	}
	else {
		return a.last < b.last;
	}
}

bool sortByLastDESC(sPerson& a, sPerson& b) {
	if (a.last == b.last) {
		return a.first > b.first;
	}
	else {
		return a.last > b.last;
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


//Random float generator
float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


STL_Vector::STL_Vector()
{
}

STL_Vector::~STL_Vector()
{

}


bool STL_Vector::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName, std::string firstNameMaleFileName, std::string lastNameFileName)
{
	this->startCall();
	std::vector <std::string> vec_FemaleNames;
	std::vector <std::string> vec_MaleNames;
	std::vector <std::string> vec_Surnames;
	mVec_Person.clear();
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
			this->mVec_Person.push_back(curPerson);
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
			this->mVec_Person.push_back(curPerson);

		}

	}
	this->endCall();
	return true;
}



bool STL_Vector::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	this->startCall();
	int count = 0;
	//Search by first
	if (personToMatch.first != "" && personToMatch.last == "")
	{

		for (int i = 0; i < this->mVec_Person.size(); i++)
		{
			if (this->mVec_Person[i].first == personToMatch.first)
			{
				vecPeople.push_back(this->mVec_Person[i]);
				count++;
				if (count == maxNumberOfPeople)
				{
					this->endCall();
					return true;
				}
			}
		}
	}

	//Search by last
	if (personToMatch.last != "" && personToMatch.first == "")
	{

		for (int i = 0; i < this->mVec_Person.size(); i++)
		{
			if (this->mVec_Person[i].last == personToMatch.last)
			{
				vecPeople.push_back(this->mVec_Person[i]);
				count++;
				if (count == maxNumberOfPeople)
				{
					this->endCall();
					return true;
				}
			}
		}
	}

	//Search by first and last
	if (personToMatch.last != "" && personToMatch.first != "")
	{
		for (int i = 0; i < this->mVec_Person.size(); i++)
		{
			if (this->mVec_Person[i].first == personToMatch.first && this->mVec_Person[i].last == personToMatch.last)
			{
				vecPeople.push_back(this->mVec_Person[i]);
				count++;
				if (count == maxNumberOfPeople)
				{
					this->endCall();
					return true;
				}
			}
		}
	}


	//Return all < maxNumberOfPeople
	if (personToMatch.last == "" && personToMatch.first == "")
	{

		for (int i = 0; i < this->mVec_Person.size(); i++)
		{
			vecPeople.push_back(this->mVec_Person[i]);
			count++;
			if (count == maxNumberOfPeople)
			{
				this->endCall();
				return true;
			}

		}

	}

	this->endCall();
	//If 0 people found
	if (count == 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool STL_Vector::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	this->startCall();
	for (int i = 0; i < vecPeopleToMatch.size(); i++)
	{
		FindPeopleByName(vecPeople, vecPeopleToMatch[i], maxNumberOfPeople);
	}
	this->endCall();
	if (vecPeople.size() == 0) { return false; }
	else { return true; }
	
}

bool STL_Vector::GetAt(unsigned int index, sPerson & thePerson)
{
	this->startCall();
	if (index < this->mVec_Person.size())
	{
		thePerson = this->mVec_Person[index];
		this->endCall();
		return true;
	}
	this->endCall();
	return false;
}




bool STL_Vector::GetPerformanceFromLastCall(sPerfData & callStats)
{
	callStats = this->m_perfData;
	return true;
}

eContainerType STL_Vector::getContainerType(void)
{
    return STD_VECTOR;
}

unsigned int STL_Vector::GetSize(void)
{
	this->startCall();
	return this->mVec_Person.size();
	this->endCall();
}

void STL_Vector::PushBack(sPerson person)
{
	this->startCall();
	this->mVec_Person.push_back(person);
	this->endCall();
}

void STL_Vector::startCall()
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

void STL_Vector::updateMemoryUsage()
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

void STL_Vector::endCall()
{
	updateMemoryUsage();
	clock_t end = clock();
	clock_t delta = end - start_time;
	double a = (double)delta / (CLOCKS_PER_SEC / 100);
	this->m_perfData.elapsedCallTime_ms = static_cast<float>(a);
}

bool STL_Vector::FindPersonByID(sPerson &person, unsigned long long uniqueID)
{
	this->startCall();
	for (int i = 0; i < this->mVec_Person.size(); i++)
	{
		
		if(this->mVec_Person[i].uniqueID == uniqueID)
		{
			person = this->mVec_Person[i];
			this->endCall();
			return true;
		}
	}
	this->endCall();
	return false;
}

bool STL_Vector::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	this->startCall();
	int count = 0;
	for (int i = 0; i < this->mVec_Person.size(); i++)
	{
		if (distance(this->mVec_Person[i].location, location) <= radius)
		{
			vecPeople.push_back(this->mVec_Person[i]);
			count++;
			if (count == maxPeopleToReturn)
			{
				this->endCall();
				return true;
			}
		}
	}
    //If 0 people found
	this->endCall();
    if(count == 0)
    {
	return false;
    }
    else
    {
        return true;
    }
}

bool STL_Vector::FindPeople(std::vector<sPerson> &vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	this->startCall();
    int count = 0;
    for (int i = 0; i < this->mVec_Person.size(); i++)
    {
        if (this->mVec_Person[i].health >= minHealth && this->mVec_Person[i].health <= maxHealth)
        {
            vecPeople.push_back(this->mVec_Person[i]);
            count++;
            if (count == maxPeopleToReturn)
            {
				this->endCall();
                return true;
            }
        }
    }
    //If 0 people found
	this->endCall();
    if(count == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool STL_Vector::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	this->startCall();
	int count = 0;
	for (int i = 0; i < this->mVec_Person.size(); i++)
	{
		if (this->mVec_Person[i].health >= minHealth && this->mVec_Person[i].health <= maxHealth)
		{
			if (distance(this->mVec_Person[i].location, location) <= radius)
			{
				vecPeople.push_back(this->mVec_Person[i]);
				count++;
				if (count == maxPeopleToReturn)
				{
					this->endCall();
					return true;
				}
			}
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

bool STL_Vector::SortPeople(std::vector<sPerson>& vecPeople, eSortType sortType)
{
	this->startCall();
	switch (sortType)
	{
	case iPersonMotron::ASC_FIRST_THEN_LAST:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByFirstASC);
		//std::sort(mVec_Person.begin(), mVec_Person.end(), sortByLastASC);
		
		break;
	case iPersonMotron::DESC_FIRST_THEN_LAST:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByFirstDESC);
		
		break;
	case iPersonMotron::ASC_LAST_THEN_FIRST:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByLastASC);
		
		break;
	case iPersonMotron::DESC_LAST_THEN_FIRST:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByLastDESC);
		
		break;
	case iPersonMotron::ASC_BY_ID:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByIdASC);
		
		break;
	case iPersonMotron::DESC_BY_ID:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByIdDESC);
		
		break;
	case iPersonMotron::ASC_BY_HEALTH:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByHpASC);
		
		break;
	case iPersonMotron::DESC_BY_HEALTH:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByHpDESC);
		
		break;
	default:
		return false;
		break;
	}



	vecPeople = mVec_Person;
	this->endCall();
	return true;
}
