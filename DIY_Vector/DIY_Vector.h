#ifndef _DIY_Vector_HG_
#define _DIY_Vector_HG_

#include "cPerson.h"

class  DIY_Vector
{
public:
	DIY_Vector();
	~DIY_Vector();

	void PushBack(sPerson person);
	void InsertAt(unsigned int index, sPerson person);
	bool GetAt(unsigned int index, sPerson &thePerson);		
	void SetCapacity(unsigned int newCapacity);		
	unsigned int GetSize(void);		
	unsigned int GetCapacity(void);	
	void clear();

private:

	sPerson* m_Data;			
	unsigned int m_CurSize;		
	unsigned int m_next;		
};

#endif

