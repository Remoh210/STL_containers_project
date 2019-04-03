#ifdef _WIN32
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <psapi.h>
#elif __APPLE__	
#include <cmath> //if OSX compiler -> use cmath
#endif
#include <fstream>
#include "iPersonMotron.h"
#include "DIY_Map.h"



//   ________  ___      ___    ___      _____ ______   ________  ________   
//  |\   ___ \|\  \    |\  \  /  /|    |\   _ \  _   \|\   __  \|\   __  \  
//  \ \  \_|\ \ \  \   \ \  \/  / /    \ \  \\\__\ \  \ \  \|\  \ \  \|\  \ 
//   \ \  \ \\ \ \  \   \ \    / /      \ \  \\|__| \  \ \   __  \ \   ____\
//    \ \  \_\\ \ \  \   \/  /  /        \ \  \    \ \  \ \  \ \  \ \  \___|
//     \ \_______\ \__\__/  / /           \ \__\    \ \__\ \__\ \__\ \__\   
//      \|_______|\|__|\___/ /             \|__|     \|__|\|__|\|__|\|__|   
//                    \|___|/        


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
DIY_Map::DIY_Map(unsigned int size)
{
	this->startCall();
	m_CurSize = size;
	this->m_table = new sHashEntry*[this->m_CurSize];

	for (int index = 0; index != this->m_CurSize; index++)
	{
		this->m_table[index] = NULL;
	}
	this->endCall();
	return;
}

DIY_Map::~DIY_Map()
{
	
	for (int i = 0; i < m_CurSize; i++)
	{
		if (m_table[i] != NULL)
		{
			delete m_table[i];
		}	
	}

	delete[] m_table;
}

bool DIY_Map::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName, std::string firstNameMaleFileName, std::string lastNameFileName)
{
	this->startCall();
	std::vector <std::string> vec_FemaleNames;
	std::vector <std::string> vec_MaleNames;
	std::vector <std::string> vec_Surnames;
	this->clear();
	//Load female first names
	std::ifstream file(firstNameFemaleFileName.c_str());
	//Return false if no file
	if (!file.is_open())
	{
		this->endCall();
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
		this->endCall();
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
		this->endCall();
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
			this->InsertAt(i, curPerson);
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
			this->InsertAt(i, curPerson);

		}

	}
	this->endCall();
	return true;
}

bool DIY_Map::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	int count = 0;
	this->startCall();
	//Search by first
	if (personToMatch.first != "" && personToMatch.last == "")
	{

		for (int i = 0; i < this->GetSize(); i++)
		{
			sPerson curPerson; 
			this->GetAt(i, curPerson);

			if (curPerson.first == personToMatch.first)
			{
				vecPeople.push_back(curPerson);
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

		for (int i = 0; i < this->GetSize(); i++)
		{
			sPerson curPerson;
			this->GetAt(i, curPerson);
			if (curPerson.last == personToMatch.last)
			{
				vecPeople.push_back(curPerson);
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
		for (int i = 0; i < this->GetSize(); i++)
		{
			sPerson curPerson;
			this->GetAt(i, curPerson);
			if (curPerson.first == personToMatch.first && curPerson.last == personToMatch.last)
			{
				vecPeople.push_back(curPerson);
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

		for (int i = 0; i < this->GetSize(); i++)
		{
			sPerson curPerson;
			this->GetAt(i, curPerson);
			vecPeople.push_back(curPerson);
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

bool DIY_Map::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
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

bool DIY_Map::GetPerformanceFromLastCall(sPerfData & callStats)
{
	callStats = this->m_perfData;
	return true;
}

void DIY_Map::startCall()
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

void DIY_Map::updateMemoryUsage()
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

void DIY_Map::endCall()
{

	updateMemoryUsage();
	clock_t end = clock();
	clock_t delta = end - start_time;
	double a = (double)delta / (CLOCKS_PER_SEC / 100);
	this->m_perfData.elapsedCallTime_ms = static_cast<float>(a);

}

eContainerType DIY_Map::getContainerType(void)
{
	return CUSTOM_DIY_MAP;
}

unsigned int DIY_Map::GetSize(void)
{
	this->startCall();
	return this->m_CurSize;
	this->endCall();
}

void DIY_Map::clear()
{
	this->startCall();
	for (int index = 0; index != this->m_CurSize; index++)
	{
		this->m_table[index] = NULL;
	}
	this->endCall();
	return;
}

bool DIY_Map::GetAt(unsigned int index, sPerson & thePerson)
{
	this->startCall();
	int hash = (index % m_CurSize);

	while (m_table[hash] != NULL && m_table[hash]->key != index)
	{
		hash = (hash + 1) % m_CurSize;
	}

	if (m_table[hash] == NULL)
	{
		this->endCall();
		return false;
	}
		
	else
	{
		thePerson = m_table[hash]->value;
		this->endCall();
		return true;
	}
	
		
}

bool DIY_Map::FindPersonByID(sPerson & person, unsigned long long uniqueID)
{

	this->startCall();
	for (int i = 0; i < this->GetSize(); i++)
	{
		sPerson CurPerson;
		this->GetAt(i, CurPerson);
		if (CurPerson.uniqueID == uniqueID)
		{
			person = CurPerson;
			this->endCall();
			return true;
		}
	}
	this->endCall();
	return false;
}

bool DIY_Map::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	this->startCall();
	int count = 0;
	for (int i = 0; i < this->GetSize(); i++)
	{
		sPerson CurPerson;
		this->GetAt(i, CurPerson);
		if (distance(CurPerson.location, location) <= radius)
		{
			vecPeople.push_back(CurPerson);
			count++;
			if (count == maxPeopleToReturn)
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

bool DIY_Map::FindPeople(std::vector<sPerson>& vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	this->startCall();
	int count = 0;
	for (int i = 0; i < this->GetSize(); i++)
	{
		sPerson CurPerson;
		this->GetAt(i, CurPerson);
		if (CurPerson.health >= minHealth && CurPerson.health <= maxHealth)
		{
			vecPeople.push_back(CurPerson);
			count++;
			if (count == maxPeopleToReturn)
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

bool DIY_Map::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	this->startCall();
	int count = 0;
	for (int i = 0; i < this->GetSize(); i++)
	{
		sPerson CurPerson;
		this->GetAt(i, CurPerson);
		if (CurPerson.health >= minHealth && CurPerson.health <= maxHealth)
		{
			if (distance(CurPerson.location, location) <= radius)
			{
				vecPeople.push_back(CurPerson);
				count++;
				if (count == maxPeopleToReturn)
				{
					this->endCall();
					return true;
				}
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

bool DIY_Map::SortPeople(std::vector<sPerson>& vecPeople, eSortType sortType)
{
	this->startCall();
	switch (sortType)
	{
	case iPersonMotron::ASC_FIRST_THEN_LAST:
	{

		break;
	}
		
	case iPersonMotron::DESC_FIRST_THEN_LAST:
	{

		break;
	}
	case iPersonMotron::ASC_LAST_THEN_FIRST:
	{

		break;
	}
	case iPersonMotron::DESC_LAST_THEN_FIRST:
	{

		break;
	}
	case iPersonMotron::ASC_BY_ID:
	{

		break;
	}
	case iPersonMotron::DESC_BY_ID:
	{

		break;
	}
	case iPersonMotron::ASC_BY_HEALTH:
	{

		break;
	}
	case iPersonMotron::DESC_BY_HEALTH:
	{

		break;
	}
	default:
		break;
	}

	this->endCall();
	return true;

	//TODO push
}

void DIY_Map::InsertAt(unsigned int index, sPerson person)
{
	int hash = (index % m_CurSize);

	while (m_table[hash] != NULL && m_table[hash]->key != index)
	{
		hash = (hash + 1) % m_CurSize;
	}

	//delete if exist
	if (m_table[hash] != NULL)
	{
		delete m_table[hash];
	}

	m_table[hash] = new sHashEntry(index, person);
}


