#ifdef _WIN32
#include <math.h>
#elif __APPLE__	
#include <cmath> //if OSX compiler -> use cmath
#endif
#include <fstream>
#include "iPersonMotron.h"
#include "STL_Map.h"
#include <algorithm>
#include <iostream>


//   ________  _________  ___               _____ ______   ________  ________   
//  |\   ____\|\___   ___\\  \             |\   _ \  _   \|\   __  \|\   __  \  
//  \ \  \___|\|___ \  \_\ \  \            \ \  \\\__\ \  \ \  \|\  \ \  \|\  \ 
//   \ \_____  \   \ \  \ \ \  \            \ \  \\|__| \  \ \   __  \ \   ____\
//    \|____|\  \   \ \  \ \ \  \____        \ \  \    \ \  \ \  \ \  \ \  \___|
//      ____\_\  \   \ \__\ \ \_______\       \ \__\    \ \__\ \__\ \__\ \__\   
//     |\_________\   \|__|  \|_______|        \|__|     \|__|\|__|\|__|\|__|   
//     \|_________|       

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


STL_Map::STL_Map()

{
    this->mMap_Person.clear();
}

STL_Map::~STL_Map()
{

}


bool STL_Map::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName, std::string firstNameMaleFileName, std::string lastNameFileName)
{
	std::vector <std::string> vec_FemaleNames;
	std::vector <std::string> vec_MaleNames;
	std::vector <std::string> vec_Surnames;
	mMap_Person.clear();
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
			this->mMap_Person.insert(std::pair<unsigned int, sPerson>(i, curPerson));
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
			this->mMap_Person.insert(std::pair<unsigned int, sPerson>(i, curPerson));

		}	
		
	}

	return true;
}


void STL_Map::GenerateData(std::string first, int number)
{
	int GenerateNumber = rand() % number + 1;
	for(int i = 0; i < GenerateNumber; i++)
	{
		sPerson curPerson;
		curPerson.first = first;
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
		//this->mMap_Person.insert(curPerson);
	}
	
}


bool STL_Map::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	int count = 0;
	//Search by first
	if (personToMatch.first != "" && personToMatch.last == "")
	{

		for (int i = 0; i < this->mMap_Person.size(); i++)
		{
			if (this->mMap_Person[i].first == personToMatch.first)
			{
				vecPeople.push_back(this->mMap_Person[i]);
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

		for (int i = 0; i < this->mMap_Person.size(); i++)
		{
			if (this->mMap_Person[i].last == personToMatch.last)
			{
				vecPeople.push_back(this->mMap_Person[i]);
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
		for (int i = 0; i < this->mMap_Person.size(); i++)
		{
			if (this->mMap_Person[i].first == personToMatch.first && this->mMap_Person[i].last == personToMatch.last)
			{
				vecPeople.push_back(this->mMap_Person[i]);
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

		for (int i = 0; i < this->mMap_Person.size(); i++)
		{
			vecPeople.push_back(this->mMap_Person[i]);
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

bool STL_Map::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	for (int i = 0; i < vecPeopleToMatch.size(); i++)
	{
		FindPeopleByName(vecPeople, vecPeopleToMatch[i], maxNumberOfPeople);
	}
	if (vecPeople.size() == 0) { return false; }
	else { return true; }
	
}

bool STL_Map::GetAt(unsigned int index, sPerson & thePerson)
{
	if (index < this->mMap_Person.size())
	{
		thePerson = this->mMap_Person[index];
		return true;
	}

	return false;
}




eContainerType STL_Map::getContainerType(void)
{
    return STD_MAP;
}

unsigned int STL_Map::GetSize(void)
{
	return this->mMap_Person.size();
}


bool STL_Map::FindPersonByID(sPerson &person, unsigned long long uniqueID)
{
	for (int i = 0; i < this->mMap_Person.size(); i++)
	{
		
		if(this->mMap_Person[i].uniqueID == uniqueID)
		{
			person = this->mMap_Person[i];
			return true;
		}
	}

	return false;
}

bool STL_Map::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	int count = 0;
	for (int i = 0; i < this->mMap_Person.size(); i++)
	{
		if (distance(this->mMap_Person[i].location, location) <= radius)
		{
			vecPeople.push_back(this->mMap_Person[i]);
			count++;
			if (count == maxPeopleToReturn)
			{
				return true;
			}
		}
	}
    //If 0 people found
    if(count == 0)
    {
		return false;
    }
    else
    {
		return true;
    }
}

bool STL_Map::FindPeople(std::vector<sPerson> &vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
    int count = 0;
    for (int i = 0; i < this->mMap_Person.size(); i++)
    {
        if (this->mMap_Person[i].health >= minHealth && this->mMap_Person[i].health <= maxHealth)
        {
            vecPeople.push_back(this->mMap_Person[i]);
            count++;
            if (count == maxPeopleToReturn)
            {
                return true;
            }
        }
    }
    //If 0 people found
    if(count == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool STL_Map::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	int count = 0;
	for (int i = 0; i < this->mMap_Person.size(); i++)
	{
		if (this->mMap_Person[i].health >= minHealth && this->mMap_Person[i].health <= maxHealth)
		{
			if (distance(this->mMap_Person[i].location, location) <= radius)
			{
				vecPeople.push_back(this->mMap_Person[i]);
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

bool STL_Map::SortPeople(std::vector<sPerson>& vecPeople, eSortType sortType)
{
	switch (sortType)
	{
	case iPersonMotron::ASC_FIRST_THEN_LAST:
	{
		std::map<std::string, sPerson> mapCopy;

		for (size_t i = 0; i < mMap_Person.size(); i++)
		{
			std::string ID = mMap_Person[i].first + " " + mMap_Person[i].last 
				+ " " + std::to_string(mMap_Person[i].uniqueID);
			mapCopy[ID] = mMap_Person[i];
		}

		mMap_Person.clear();

		std::map<std::string, sPerson>::iterator it;
		size_t index = 0;
		for (it = mapCopy.begin(); it != mapCopy.end(); it++)
		{
			mMap_Person[index] = it->second;
			index++;
		}

		break;
	}

	case iPersonMotron::DESC_FIRST_THEN_LAST:
	{
		std::map<std::string, sPerson> mapCopy;

		for (size_t i = 0; i < mMap_Person.size(); i++)
		{
			std::string ID = mMap_Person[i].first + " " + mMap_Person[i].last
				+ " " + std::to_string(mMap_Person[i].uniqueID);
			mapCopy[ID] = mMap_Person[i];
		}

		mMap_Person.clear();

		std::map<std::string, sPerson>::iterator it;
		size_t index = mapCopy.size() - 1;
		for (it = mapCopy.begin(); it != mapCopy.end(); it++)
		{
			mMap_Person[index] = it->second;
			index--;
		}

		break;
	}
		
	case iPersonMotron::ASC_LAST_THEN_FIRST:
	{
		std::map<std::string, sPerson> mapCopy;

		for (size_t i = 0; i < mMap_Person.size(); i++)
		{
			std::string ID = mMap_Person[i].last + " " + mMap_Person[i].first
				+ " " + std::to_string(mMap_Person[i].uniqueID);
			mapCopy[ID] = mMap_Person[i];
		}

		mMap_Person.clear();

		std::map<std::string, sPerson>::iterator it;
		size_t index = 0;
		for (it = mapCopy.begin(); it != mapCopy.end(); it++)
		{
			mMap_Person[index] = it->second;
			index++;
		}
		break;
	}
	case iPersonMotron::DESC_LAST_THEN_FIRST:
	{

		std::map<std::string, sPerson> mapCopy;

		for (size_t i = 0; i < mMap_Person.size(); i++)
		{
			std::string ID = mMap_Person[i].last + " " + mMap_Person[i].first
				+ " " + std::to_string(mMap_Person[i].uniqueID);
			mapCopy[ID] = mMap_Person[i];
		}

		mMap_Person.clear();

		std::map<std::string, sPerson>::iterator it;
		size_t index = mapCopy.size() - 1;
		for (it = mapCopy.begin(); it != mapCopy.end(); it++)
		{
			mMap_Person[index] = it->second;
			index--;
		}

		break;
	}
		
	case iPersonMotron::ASC_BY_ID:
	{
		std::map<unsigned int, sPerson> mapCopy;

		for (size_t i = 0; i < mMap_Person.size(); i++)
		{
			mapCopy[mMap_Person[i].uniqueID] = mMap_Person[i];
		}

		mMap_Person.clear();

		std::map<unsigned int, sPerson>::iterator it;
		size_t index = 0;
		for (it = mapCopy.begin(); it != mapCopy.end(); it++)
		{
			mMap_Person[index] = it->second;
			index++;
		}

		break;
	}
		
	case iPersonMotron::DESC_BY_ID:
	{

		std::map<unsigned int, sPerson> mapCopy;

		for (size_t i = 0; i < mMap_Person.size(); i++)
		{
			mapCopy[mMap_Person[i].uniqueID] = mMap_Person[i];
		}

		mMap_Person.clear();

		std::map<unsigned int, sPerson>::iterator it;
		size_t index = mapCopy.size() - 1;
		for (it = mapCopy.begin(); it != mapCopy.end(); it++)
		{
			mMap_Person[index] = it->second;
			index--;
		}

		break;
	}
		
	case iPersonMotron::ASC_BY_HEALTH:
	{

		std::map<float, sPerson> mapCopy;

		for (size_t i = 0; i < mMap_Person.size(); i++)
		{
			mapCopy[mMap_Person[i].health] = mMap_Person[i];
		}

		mMap_Person.clear();

		std::map<float, sPerson>::iterator it;
		size_t index = 0;
		for (it = mapCopy.begin(); it != mapCopy.end(); it++)
		{
			mMap_Person[index] = it->second;
			index++;
		}

		break;
	}
		
	case iPersonMotron::DESC_BY_HEALTH:
	{

		std::map<float, sPerson> mapCopy;

		for (size_t i = 0; i < mMap_Person.size(); i++)
		{
			mapCopy[mMap_Person[i].health] = mMap_Person[i];
		}

		mMap_Person.clear();

		std::map<float, sPerson>::iterator it;
		size_t index = mapCopy.size() - 1;
		for (it = mapCopy.begin(); it != mapCopy.end(); it++)
		{
			mMap_Person[index] = it->second;
			index--;
		}

		break;
	}
		
	default:
		break;
	}

	for (int i = 0; i < mMap_Person.size(); i++)
	{
		vecPeople.push_back(mMap_Person[i]);
	}


	return true;
}
