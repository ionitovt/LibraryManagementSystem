#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Member.h"

//**********************************************************
// THIS CLASS CONTAINS FUNCTIONS RELATED TO EMPLOYEES
//**********************************************************

class Employee : public Member{
public:
	int menu();
	int createAccount();
	int deleteAccount();
	int signUp();
};

#endif