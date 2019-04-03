#ifdef _WIN32
#include <math.h>
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
	m_CurSize = size;
	this->m_table = new sHashEntry*[this->m_CurSize];

	for (int index = 0; index != this->m_CurSize; index++)
	{
		this->m_table[index] = NULL;
	}
	return;
}

DIY_Map::~DIY_Map()
{
	for (int i = 0; i < m_CurSize; i++)

		if (m_table[i] != NULL)

			delete m_table[i];

	delete[] m_table;
}

bool DIY_Map::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName, std::string firstNameMaleFileName, std::string lastNameFileName)
{
	std::vector <std::string> vec_FemaleNames;
	std::vector <std::string> vec_MaleNames;
	std::vector <std::string> vec_Surnames;
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

	return true;
}

bool DIY_Map::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	int count = 0;
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
				return true;
			}

		}

	}


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
	for (int i = 0; i < vecPeopleToMatch.size(); i++)
	{
		FindPeopleByName(vecPeople, vecPeopleToMatch[i], maxNumberOfPeople);
	}
	if (vecPeople.size() == 0) { return false; }
	else { return true; }
}

eContainerType DIY_Map::getContainerType(void)
{
	return CUSTOM_DIY_MAP;
}

unsigned int DIY_Map::GetSize(void)
{
	return this->m_CurSize;
}

void DIY_Map::clear()
{
	for (int index = 0; index != this->m_CurSize; index++)
	{
		this->m_table[index] = NULL;
	}
	return;
}

bool DIY_Map::GetAt(unsigned int index, sPerson & thePerson)
{
	int hash = (index % m_CurSize);

	while (m_table[hash] != NULL && m_table[hash]->key != index)

		hash = (hash + 1) % m_CurSize;

	if (m_table[hash] == NULL)
	{
		return false;
	}
		
	else
	{
		thePerson = m_table[hash]->value;
	}
		
}

bool DIY_Map::FindPersonByID(sPerson & person, unsigned long long uniqueID)
{
	for (int i = 0; i < this->GetSize(); i++)
	{
		sPerson CurPerson;
		this->GetAt(i, CurPerson);
		if (CurPerson.uniqueID == uniqueID)
		{
			person = CurPerson;
			return true;
		}
	}

	return false;
}

bool DIY_Map::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
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
				return true;
			}
		}
	}
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
				return true;
			}
		}
	}
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
					return true;
				}
			}
		}
	}
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
