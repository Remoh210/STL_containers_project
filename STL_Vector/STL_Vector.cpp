#ifdef _WIN32
#include <math.h>
#elif __APPLE__	
#include <cmath> //if OSX compiler -> use cmath
#endif
#include <fstream>
#include "iPersonMotron.h"
#include "STL_Vector.h"
#include <algorithm>
#include <iostream>

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
			GenerateData(treshold);
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
			GenerateData(treshold);
		}
		file2 >> treshold;
		file2 >> treshold;
		file2 >> treshold;
	}
	file.close();


	//Load last names
	std::ifstream file3(lastNameFileName.c_str());
	//Return false if no file
	if (!file3.is_open())
	{
		return false;
	}

	int indx = 0;
	while (!file3.eof())
	{
		treshold = "";
		file3 >> treshold;
		if (treshold != "") {
			//Give same r last names 
			int r = rand() % 3 + 1;
			for(int i = 0; i < r; i ++){
				//int randIndex = rand() % this->GetSize() + 1;
				this->mVec_Person[indx].last = treshold;
				this->mVec_Person[indx].uniqueID = indx;
				indx++;
				if (indx > this->GetSize() - 1) { return true; }
			}
		}
		file3 >> treshold;
		file3 >> treshold;
		file3 >> treshold;
	}
	file.close();


	

	return true;
}


void STL_Vector::GenerateData(std::string first, int number)
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
		this->mVec_Person.push_back(curPerson);
	}
	
}


bool STL_Vector::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
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

bool STL_Vector::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	for (int i = 0; i < vecPeopleToMatch.size(); i++)
	{
		FindPeopleByName(vecPeople, vecPeopleToMatch[i], maxNumberOfPeople);
	}
	if (vecPeople.size() == 0) { return false; }
	else { return true; }
	
}

bool STL_Vector::GetAt(unsigned int index, sPerson & thePerson)
{
	if (index < this->mVec_Person.size())
	{
		thePerson = this->mVec_Person[index];
		return true;
	}

	return false;
}




eContainerType STL_Vector::getContainerType(void)
{
    return STD_VECTOR;
}

unsigned int STL_Vector::GetSize(void)
{
	return this->mVec_Person.size();
}

void STL_Vector::PushBack(sPerson person)
{
	this->mVec_Person.push_back(person);
}

bool STL_Vector::FindPersonByID(sPerson &person, unsigned long long uniqueID)
{
	for (int i = 0; i < this->mVec_Person.size(); i++)
	{
		
		if(this->mVec_Person[i].uniqueID == uniqueID)
		{
			person = this->mVec_Person[i];
			return true;
		}
	}

	return false;
}

bool STL_Vector::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	int count = 0;
	for (int i = 0; i < this->mVec_Person.size(); i++)
	{
		if (distance(this->mVec_Person[i].location, location) <= radius)
		{
			vecPeople.push_back(this->mVec_Person[i]);
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

bool STL_Vector::FindPeople(std::vector<sPerson> &vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
    int count = 0;
    for (int i = 0; i < this->mVec_Person.size(); i++)
    {
        if (this->mVec_Person[i].health >= minHealth && this->mVec_Person[i].health <= maxHealth)
        {
            vecPeople.push_back(this->mVec_Person[i]);
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

bool STL_Vector::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
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

bool STL_Vector::SortPeople(std::vector<sPerson>& vecPeople, eSortType sortType)
{
	switch (sortType)
	{
	case iPersonMotron::ASC_FIRST_THEN_LAST:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByFirstASC);
		//std::sort(mVec_Person.begin(), mVec_Person.end(), sortByLastASC);
		return true;
		break;
	case iPersonMotron::DESC_FIRST_THEN_LAST:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByFirstDESC);
		return true;
		break;
	case iPersonMotron::ASC_LAST_THEN_FIRST:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByLastASC);
		return true;
		break;
	case iPersonMotron::DESC_LAST_THEN_FIRST:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByLastDESC);
		return true;
		break;
	case iPersonMotron::ASC_BY_ID:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByIdASC);
		return true;
		break;
	case iPersonMotron::DESC_BY_ID:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByIdDESC);
		return true;
		break;
	case iPersonMotron::ASC_BY_HEALTH:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByHpASC);
		return true;
		break;
	case iPersonMotron::DESC_BY_HEALTH:
		std::sort(mVec_Person.begin(), mVec_Person.end(), sortByHpDESC);
		return true;
		break;
	default:
		return false;
		break;
	}
}
