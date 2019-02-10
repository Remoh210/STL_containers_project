#include <iPersonMotron.h>
#include "DIY_Vector.h"

DIY_Vector::DIY_Vector()
{

	this->m_CurSize = 10;

	this->m_Data = new sPerson[this->m_CurSize];

	this->m_next = 0;

	return;
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
		for (unsigned int index = 0; index < this->m_next; index++)
		{
			pNewArray[index] = this->m_Data[index];
		}

		delete[] this->m_Data;
		this->m_Data = pNewArray;
	}

	return;

}


bool DIY_Vector::GetAt(unsigned int index, sPerson &thePerson)
{
	thePerson = this->m_Data[index];
	return true;
}