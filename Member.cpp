#include "Member.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//**********************************************************
// CONSTRUCTOR
//**********************************************************
Member::Member(void){
	credentials.username[0] = '\0';
	credentials.password[0] = '\0';
}

void Member::loadCredentials(Credentials *crd){
	strcpy(credentials.username, crd->username);
	strcpy(credentials.password, crd->password);
}

//**********************************************************
// MENU FOR MEMBERS (LIMITED OPTIONS)
//**********************************************************
int Member::menu(void){

here1:
	system("cls");
	system("color 9");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t\t----Please choose one of the options below----\n");
	printf("\n\t\t< 1 > Search Books");
	printf("\n\t\t< 2 > Book list");
	printf("\n\t\t< 3 > Exit\n");
	fflush(stdin);
	switch (getch()){
	case '1':
		searchbooks();
		break;
	case '2':
		bookslist();
		break;
	case '3':
		return 0;
	default:
			   printf("\nWrong Entry!!");
			   break;
	}
	goto here1;
}

//**********************************************************
// CALLING BOOOK METHODS
//**********************************************************
void Member::addbooks(void){ books.addbooks(); };
void Member::deletebooks(void){ books.deletebooks(); };
void Member::editbooks(void){ books.editbooks(); };
void Member::searchbooks(void){ books.searchbooks(); };
void Member::issuebooks(void){ books.issuebooks(); };
void Member::bookslist(void){ books.bookslist(); };