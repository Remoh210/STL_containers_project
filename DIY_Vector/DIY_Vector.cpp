
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

