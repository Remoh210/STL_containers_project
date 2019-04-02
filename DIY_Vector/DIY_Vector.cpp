#ifdef _WIN32
#include <math.h>
#elif __APPLE__	
#include <cmath> //if OSX compiler -> use cmath
#endif
#include <fstream>
#include "iPersonMotron.h"
#include "DIY_Vector.h"
#include <iostream>

#include <map>
std::map<std::string, int> test;


//   ________  ___      ___    ___      ___      ___ _______   ________ _________  ________  ________     
//  |\   ___ \|\  \    |\  \  /  /|    |\  \    /  /|\  ___ \ |\   ____\\___   ___\\   __  \|\   __  \    
//  \ \  \_|\ \ \  \   \ \  \/  / /    \ \  \  /  / | \   __/|\ \  \___\|___ \  \_\ \  \|\  \ \  \|\  \   
//   \ \  \ \\ \ \  \   \ \    / /      \ \  \/  / / \ \  \_|/_\ \  \       \ \  \ \ \  \\\  \ \   _  _\  
//    \ \  \_\\ \ \  \   \/  /  /        \ \    / /   \ \  \_|\ \ \  \____   \ \  \ \ \  \\\  \ \  \\  \| 
//     \ \_______\ \__\__/  / /           \ \__/ /     \ \_______\ \_______\  \ \__\ \ \_______\ \__\\ _\ 
//      \|_______|\|__|\___/ /             \|__|/       \|_______|\|_______|   \|__|  \|_______|\|__|\|__|
//                    \|___|/                                                                             
//                                                                                                        
// 

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


DIY_Vector::DIY_Vector()
	:m_CurSize(10),
	m_next(0) 
{
	this->m_Data = new sPerson[this->m_CurSize];
}

DIY_Vector::~DIY_Vector()
{

}


bool DIY_Vector::LoadDataFilesIntoContainer(std::string firstNameFemaleFileName, std::string firstNameMaleFileName, std::string lastNameFileName)
{
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
		int GenerateNumber = rand() % 1 + 10;
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
				this->m_Data[indx].last = treshold;
				this->m_Data[indx].uniqueID = indx;
				indx++;
				if (indx > this->GetSize()) { return true; }
			}
		}
		file3 >> treshold;
		file3 >> treshold;
		file3 >> treshold;
	}
	file.close();


	

	return true;
}




void DIY_Vector::PushBack(sPerson person) 
{

	this->m_Data[this->m_next] = person;
	this->m_next++;

	if (this->m_next >= this->m_CurSize) 
	{
		this->m_CurSize *= 2;
		sPerson* pNewArray = new sPerson[this->m_CurSize];		
		for (unsigned int index = 0; index < this->m_next; index++) {
			pNewArray[index] = this->m_Data[index];
		}

		delete[] this->m_Data;
		this->m_Data = pNewArray;
	}

	return;

}


void DIY_Vector::GenerateData(std::string first, int number)
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
		this->PushBack(curPerson);
	}
	
}


bool DIY_Vector::FindPeopleByName(std::vector<sPerson>& vecPeople, sPerson personToMatch, int maxNumberOfPeople)
{
	int count = 0;
	//Search by first
	if (personToMatch.first != "" && personToMatch.last == "")
	{

		for (int i = 0; i < this->GetSize(); i++)
		{
			if (this->m_Data[i].first == personToMatch.first)
			{
				vecPeople.push_back(this->m_Data[i]);
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
			if (this->m_Data[i].last == personToMatch.last)
			{
				vecPeople.push_back(this->m_Data[i]);
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
			if (this->m_Data[i].first == personToMatch.first && this->m_Data[i].last == personToMatch.last)
			{
				vecPeople.push_back(this->m_Data[i]);
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
			vecPeople.push_back(this->m_Data[i]);
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

bool DIY_Vector::FindPeopleByName(std::vector<sPerson>& vecPeople, std::vector<sPerson>& vecPeopleToMatch, int maxNumberOfPeople)
{
	for (int i = 0; i < vecPeopleToMatch.size(); i++)
	{
		FindPeopleByName(vecPeople, vecPeopleToMatch[i], maxNumberOfPeople);
	}
	if (vecPeople.size() == 0) { return false; }
	else { return true; }
	
}

bool DIY_Vector::GetAt(unsigned int index, sPerson &thePerson) {
	thePerson = this->m_Data[index];
	return true;
}


eContainerType DIY_Vector::getContainerType(void)
{
	return eContainerType();
}

void DIY_Vector::SetCapacity(unsigned int newCapacity){
	this->m_CurSize = newCapacity;
}
unsigned int DIY_Vector::GetCapacity(void) {
	return m_CurSize;
}

void DIY_Vector::clear()
{
	// Delete data
	delete[] this->m_Data;

	//Reset Everithing
	unsigned int m_CurSize = 0;
	this->m_Data = new sPerson[this->m_CurSize];
	this->m_next = 0;
}

unsigned int DIY_Vector::GetSize(void)
{
	return m_next;
}

bool DIY_Vector::FindPersonByID(sPerson &person, unsigned long long uniqueID)
{
	for (int i = 0; i < this->GetSize(); i++)
	{
		
		if(this->m_Data[i].uniqueID == uniqueID)
		{
			person = this->m_Data[i];
			return true;
		}
	}

	return false;
}

bool DIY_Vector::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, int maxPeopleToReturn)
{
	int count = 0;
	for (int i = 0; i < this->GetSize(); i++)
	{
		if (distance(this->m_Data[i].location, location) <= radius)
		{
			vecPeople.push_back(this->m_Data[i]);
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

bool DIY_Vector::FindPeople(std::vector<sPerson> &vecPeople, float minHealth, float maxHealth, int maxPeopleToReturn)
{
    int count = 0;
    for (int i = 0; i < this->GetSize(); i++)
    {
        if (this->m_Data[i].health >= minHealth && this->m_Data[i].health <= maxHealth)
        {
            vecPeople.push_back(this->m_Data[i]);
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

bool DIY_Vector::FindPeople(std::vector<sPerson>& vecPeople, sPoint location, float radius, float minHealth, float maxHealth, int maxPeopleToReturn)
{
	int count = 0;
	for (int i = 0; i < this->GetSize(); i++)
	{
		if (this->m_Data[i].health >= minHealth && this->m_Data[i].health <= maxHealth)
		{
			if (distance(this->m_Data[i].location, location) <= radius)
			{
				vecPeople.push_back(this->m_Data[i]);
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

bool DIY_Vector::SortPeople(std::vector<sPerson>& vecPeople, eSortType sortType)
{
	Qsort(0, GetSize() - 1, sortType);
	for (int i = 0; i < this->GetSize(); i++)
	{
		vecPeople.push_back(this->m_Data[i]);
	}

	return true;
}





static int rec = 0;
void DIY_Vector::Qsort(int left, int right, eSortType type)
{

	int i = left;
	int j = right;
	sPerson tmp;
	sPerson pivot = m_Data[(left + right) / 2];
	rec++;

	switch (type)
	{
	case ASC_FIRST_THEN_LAST:
	{
		while (i <= j) {
			while (m_Data[i].first < pivot.first) {
				i++;
			}
			while (m_Data[j].first > pivot.first) {
				j--;
			}

			if (i <= j) {
				tmp = m_Data[i];
				m_Data[i] = m_Data[j];
				m_Data[j] = tmp;
				i++;
				j--;
			}
		}

		// Recursion
		if (left < j) {
			Qsort(left, j, ASC_FIRST_THEN_LAST);
		}

		if (i < right) {
			Qsort(i, right, ASC_FIRST_THEN_LAST);
		}
		if (rec == 1)
		{
			bool IsSortingFinished = false;

			while (!IsSortingFinished)
			{
				IsSortingFinished = true;

				size_t length = this->GetSize() - 1;
				for (size_t i = 0; i < length; i++)
				{
					if (m_Data[i].last > m_Data[i + 1].last && m_Data[i].first == m_Data[i + 1].first)
					{
						tmp = m_Data[i];
						m_Data[i] = m_Data[i + 1];
						m_Data[i + 1] = tmp;
						IsSortingFinished = false;
					}
				}
			}
		}
	}
	break;
	case DESC_FIRST_THEN_LAST:
	{

		while (i <= j)
		{
			while (m_Data[i].first > pivot.first)
				i++;

			while (m_Data[j].first < pivot.first)
				j--;

			if (i <= j)
			{
				tmp = m_Data[i];
				m_Data[i] = m_Data[j];
				m_Data[j] = tmp;
				i++;
				j--;
			}
		}

		if (left < j) {
			Qsort(left, j, DESC_FIRST_THEN_LAST);
		}

		if (i < right) {
			Qsort(i, right, DESC_FIRST_THEN_LAST);
		}
		if (rec == 1)
		{
			bool IsSortingFinished = false;

			while (!IsSortingFinished)
			{
				// Flag to exit
				IsSortingFinished = true;

				size_t length = this->GetSize() - 1;
				for (size_t i = 0; i < length; i++)
				{
					if (m_Data[i].last < m_Data[i + 1].last && m_Data[i].first == m_Data[i + 1].first)
					{
						tmp = m_Data[i];
						m_Data[i] = m_Data[i + 1];
						m_Data[i + 1] = tmp;
						IsSortingFinished = false;
					}
				}
			}
		}
	}
	break;
	case ASC_LAST_THEN_FIRST:
	{
		while (i <= j)
		{
			while (m_Data[i].last < pivot.last)
				i++;

			while (m_Data[j].last > pivot.last)
				j--;

			if (i <= j)
			{
				tmp = m_Data[i];
				m_Data[i] = m_Data[j];
				m_Data[j] = tmp;
				i++;
				j--;
			}
		}

		if (left < j) {
			Qsort(left, j, ASC_LAST_THEN_FIRST);
		}

		if (i < right) {
			Qsort(i, right, ASC_LAST_THEN_FIRST);
		}

		if (rec == 1)
		{
			bool IsSortingFinished = false;

			while (!IsSortingFinished)
			{
				IsSortingFinished = true;
				size_t length = this->GetSize() - 1;
				for (size_t i = 0; i < length; i++)
				{
					if (m_Data[i].first > m_Data[i + 1].first && m_Data[i].last == m_Data[i + 1].last)
					{
						tmp = m_Data[i];
						m_Data[i] = m_Data[i + 1];
						m_Data[i + 1] = tmp;
						IsSortingFinished = false;
					}
				}
			}
		}
	}
	break;
	case DESC_LAST_THEN_FIRST:
	{
		while (i <= j)
		{
			while (m_Data[i].last > pivot.last)
				i++;

			while (m_Data[j].last < pivot.last)
				j--;

			if (i <= j)
			{
				tmp = m_Data[i];
				m_Data[i] = m_Data[j];
				m_Data[j] = tmp;
				i++;
				j--;
			}
		}

		if (left < j) {
			Qsort(left, j, DESC_LAST_THEN_FIRST);
		}

		if (i < right) {
			Qsort(i, right, DESC_LAST_THEN_FIRST);
		}
		if (rec == 1)
		{
			bool IsSortingFinished = false;

			while (!IsSortingFinished)
			{
				IsSortingFinished = true;

				size_t length = this->GetSize() - 1;
				for (size_t i = 0; i < length; i++)
				{
					if (m_Data[i].first < m_Data[i + 1].first && m_Data[i].last == m_Data[i + 1].last)
					{
						tmp = m_Data[i];
						m_Data[i] = m_Data[i + 1];
						m_Data[i + 1] = tmp;
						IsSortingFinished = false;
					}
				}
			}
		}
	}
	break;
	case ASC_BY_ID:
	{
		while (i <= j)
		{
			while (m_Data[i].uniqueID < pivot.uniqueID)
				i++;

			while (m_Data[j].uniqueID > pivot.uniqueID)
				j--;

			if (i <= j)
			{
				tmp = m_Data[i];
				m_Data[i] = m_Data[j];
				m_Data[j] = tmp;
				i++;
				j--;
			}
		}

		if (left < j) {
			Qsort(left, j, ASC_BY_ID);
		}

		if (i < right) {
			Qsort(i, right, ASC_BY_ID);
		}
	}
	break;
	case DESC_BY_ID:
	{
		while (i <= j)
		{
			while (m_Data[i].uniqueID > pivot.uniqueID)
				i++;

			while (m_Data[j].uniqueID < pivot.uniqueID)
				j--;

			if (i <= j)
			{
				tmp = m_Data[i];
				m_Data[i] = m_Data[j];
				m_Data[j] = tmp;
				i++;
				j--;
			}
		}
		if (left < j) {
			Qsort(left, j, DESC_BY_ID);
		}

		if (i < right) {
			Qsort(i, right, DESC_BY_ID);
		}
	}
	break;
	case ASC_BY_HEALTH:
	{
		while (i <= j)
		{
			while (m_Data[i].health < pivot.health)
				i++;

			while (m_Data[j].health > pivot.health)
				j--;

			if (i <= j)
			{
				tmp = m_Data[i];
				m_Data[i] = m_Data[j];
				m_Data[j] = tmp;
				i++;
				j--;
			}
		}

		if (left < j) {
			Qsort(left, j, ASC_BY_HEALTH);
		}

		if (i < right) {
			Qsort(i, right, ASC_BY_HEALTH);
		}
	}
	break;
	case DESC_BY_HEALTH:
	{
		while (i <= j)
		{
			while (m_Data[i].health > pivot.health)
				i++;

			while (m_Data[j].health < pivot.health)
				j--;

			if (i <= j)
			{
				tmp = m_Data[i];
				m_Data[i] = m_Data[j];
				m_Data[j] = tmp;
				i++;
				j--;
			}
		}

		if (left < j) {
			Qsort(left, j, DESC_BY_HEALTH);
		}

		if (i < right) {
			Qsort(i, right, DESC_BY_HEALTH);
		}
	}
	break;
	default:
		break;
	}

	rec--;
}
