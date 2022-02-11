#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <conio.h>
#include "Member.h"
#include "Employee.h"

//**********************************************************
// PROTOTIPES
//**********************************************************
void headMessage(void);
void welcome(void);
int login(Credentials *);
int signIn(char *, char *, Credentials **);


//**********************************************************
// LOGIN SYSTEM
//**********************************************************
int login(Credentials *crd) {
	int i;
	char username[50], password[150];
	char tempChar = ' ';
	int signInResult;

	fflush(stdin);
	system("cls");
	system("color 6");
	printf("\n\t\tENTER USERNAME : ");
	for (i = 0; tempChar != 13; i++){
		username[i] = getch();
		tempChar = username[i];
		//Stoping the user from entering more than 50 characters
		if (i >= 50 && tempChar != 13 && tempChar != 8){
			username[i] = '\0';
			i--;
			printf("\b \b");
			fflush(stdin);
		}
		//Stoping the user from entering some characters such as space, esc, tab etc.
		if (tempChar >= 0 && tempChar <= 32 && tempChar != 13){
			username[i] = '\0';
			i--;
			//Deleting a char if backspace entered
			if (tempChar == 8 && i >= 0){
				username[i] = '\0';
				i--;
				printf("\b \b");
			}
			fflush(stdin);
		}
		else printf("%c", username[i]);
	}username[i - 1] = '\0';

	tempChar = 0;
	fflush(stdin);
	system("cls");
	printf("\n\t\tENTER PASSWORD : ");
	for (i = 0; tempChar != 13; i++){
		password[i] = getch();
		tempChar = password[i];
		//Stoping the user from entering more than 150 characters for password
		if (i >= 150 && tempChar != 13 && tempChar != 8){
			password[i] = '\0';
			i--;
			printf("\b \b");
			fflush(stdin);
		}
		//Stoping the user from entering some characters such as space, esc, tab etc.
		if (tempChar >= 0 && tempChar <= 32 && tempChar != 13){
			password[i] = '\0';
			i--;
			//Deleting a char if backspace entered
			if (tempChar == 8 && i >= 0){
				password[i] = '\0';
				i--;
				printf("\b \b");
			}
			fflush(stdin);
		}
		else printf("*");
	}password[i - 1] = '\0';

	//returns 1 when username and password correct
	//returns 0 when username or password incorrect
	//returns -1 when can't open file
	//returns 2 when username and password of emploee
	signInResult = signIn(username, password, &crd);
	if (signInResult == -1) return -1;
	else if (signInResult == 1) return 1;
	else if (signInResult == 2) return 2;
	system("PAUSE");
	return 0;
}

int signIn(char *username, char *password, Credentials **crd) {
	FILE *file;
	char *text;
	int size;
	if ((file = fopen("Credentials.txt", "r")) == NULL){
		printf("\nError! Opening file");
		system("PAUSE");
		return -1;
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);
	text = (char*)malloc(sizeof(char)*(size + 999));
	fread(text, sizeof(char), size, file);
	text[size] = '\0';

	int i, j;
	char usernamefile[50], passwordfile[50];
	//*****************************************************************************************
	//cheking the first set of credentials
	for (i = 0, j = 0; text[i + j] != ' '; j++){
		usernamefile[j] = text[i + j];
	}usernamefile[j] = '\0';
	i += j + 1;
	for (j = 0; text[i + j] != ' '; j++){
		passwordfile[j] = text[i + j];
	}passwordfile[j] = '\0';
	i += j + 1;

	if ((strcmp(username, usernamefile) == 0) && (strcmp(password, passwordfile) == 0)) {
		system("cls");
		printf("\n>>>You entered an emploee username and password!<<<\n");
		//*****************************************************************************************
		//copying the credentials into emploee object
		strcpy((*crd)->username, username);
		strcpy((*crd)->password, password);
		fclose(file);
		free(text);
		return 2;
	}
	//*****************************************************************************************
	for (; i < size;){
		for (j = 0; text[i + j] != ' '; j++){
			usernamefile[j] = text[i + j];
		}usernamefile[j] = '\0';
		i += j + 1;
		for (j = 0; text[i + j] != ' '; j++){
			passwordfile[j] = text[i + j];
		}passwordfile[j] = '\0';
		i += j + 1;

		if ((strcmp(username, usernamefile) == 0) && (strcmp(password, passwordfile) == 0)) {
			system("cls");
			printf("\n>>>User and password correct!<<<\n");
			//*****************************************************************************************
			//copying the credentials into member object
			strcpy((*crd)->username, username);
			strcpy((*crd)->password, password);
			fclose(file);
			free(text);
			return 1;
		}
	}

	system("cls");
	printf("\n>>>Username or password incorrect!<<<\n");

	fclose(file);
	free(text);
	//system("PAUSE");
	return 0;
}


int main()
{
	Member *user;
	Credentials crd;
	int loginResult = 0;
	do{
		welcome();
		loginResult = login(&crd);
	} while (loginResult != 1 && loginResult != 2);
	if (loginResult == 1) user = new Member;
	else user = new Employee;
		//dynamic cast user to being a member
		/*Member *m = dynamic_cast<Member *>(user);
		if (m == NULL){
			printf("Casting error!");
			system("PAUSE");
			return 0;
		}*/
	user->loadCredentials(&crd);
	user->menu();
	delete user;
	system("cls");
	printf("\n\n\n\n\t\t\tThank you for using our services :)");
	fflush(stdin);
	getchar();
	return 0;
}




void headMessage()
{
	system("cls");
	system("color 6");
	printf("\t\t\t#############################################################################");
	printf("\n\t\t\t############                                                     ############");
	printf("\n\t\t\t############      Library management System Project in C++       ############");
	printf("\n\t\t\t############                                                     ############");
	printf("\n\t\t\t#############################################################################");
	printf("\n\t\t\t---------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\tcreated by: Yoan Tyankovski");
	printf("\n\t\t\t----------------------------------------------------------------------------");
}

void welcome()
{
	system("cls");
	headMessage();

	printf("\n\n\n\n");
	printf("\n\t\t\t  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	printf("\n\t\t\t        \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\t\t\t        \xB2\xB2              WELCOME             \xB2\xB2");
	printf("\n\t\t\t        \xB2\xB2                TO                \xB2\xB2");
	printf("\n\t\t\t        \xB2\xB2              LIBRARY             \xB2\xB2");
	printf("\n\t\t\t        \xB2\xB2            MANAGEMENT            \xB2\xB2");
	printf("\n\t\t\t        \xB2\xB2              SYSTEM              \xB2\xB2");
	printf("\n\t\t\t        \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\t\t\t  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("\n\n\n\t\t\t Press Enter to continue.....");
	fflush(stdin);
	getchar();
	fflush(stdin);
}