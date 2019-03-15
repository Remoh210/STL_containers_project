#ifdef _WIN32
#include <math.h>
#elif __APPLE__
#include <cmath>
#endif
#include <iPersonMotron.h>
#include "DIY_Vector.h"


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


DIY_Vector::DIY_Vector()
	:m_CurSize(10),
	m_next(0) 
{
	this->m_Data = new sPerson[this->m_CurSize];
}

DIY_Vector::~DIY_Vector()
{
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

bool DIY_Vector::GetAt(unsigned int index, sPerson &thePerson) {
	thePerson = this->m_Data[index];
	return true;
}


void DIY_Vector::SetCapacity(unsigned int newCapacity){
	this->m_CurSize = newCapacity;
}
unsigned int DIY_Vector::GetCapacity(void) {
	return m_CurSize;
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


