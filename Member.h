#ifndef MEMBER_H
#define MEMBER_H
#include "Books.h"

//**********************************************************
// THIS STRUCTURE CONTAINS THE USERNAME AND PASSWORD
//**********************************************************

typedef struct{
	char username[50];
	char password[150];
}Credentials;

//**********************************************************
// THIS CLASS CONTAINS FUNCTIONS RELATED TO MEMBERS
//**********************************************************
class Member{
protected:
	Credentials credentials;
	Books books;
public:
	Member(void);
	virtual int menu();
	void loadCredentials(Credentials *crd);
	void addbooks(void);
	void deletebooks(void);
	void editbooks(void);
	void searchbooks(void);
	void issuebooks(void);
	void bookslist(void);
	//virtual ~Member();
};
#endif