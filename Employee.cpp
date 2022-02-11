#include "Employee.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//**********************************************************
// MENU WITH ALL THE FEATURES AVAILABLE FOR EMPLOYEES
//**********************************************************
int Employee::menu(void){

here:
	system("cls");
	system("color 9");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t\t----Please choose one of the options below----\n");
	printf("\n\n\t\t< 1 > Add Books");
	printf("\n\t\t< 2 > Delete books");
	printf("\n\t\t< 3 > Search Books");
	printf("\n\t\t< 4 > Issue Books");
	printf("\n\t\t< 5 > Book list");
	printf("\n\t\t< 6 > Edit Book's Record");
	printf("\n\t\t< 7 > Create a new account");
	printf("\n\t\t< 8 > Remove an existing account");
	printf("\n\t\t< 9 > Exit\n");
	fflush(stdin);
	switch (getch()){
	case '1':
		addbooks();
		break;
	case '2':
		deletebooks();
		break;
	case '3':
		searchbooks();
		break;
	case '4':
		issuebooks();
		break;
	case '5':
		bookslist();
		break;
	case '6':
		editbooks();
		break;
	case '7':
		if (!createAccount()){ printf("\n\n\t\t Something went wrong!"); fflush(stdin); getch(); }
		break;
	case '8':
		if (!deleteAccount()){ printf("\n\n\t\t Something went wrong!"); fflush(stdin); getch(); }
		break;
	case '9':
		return 0;
	default:
		printf("\nWrong Entry!!");
		break;
	}
	goto here;
}

//**********************************************************
// FUNCTION FOR CREATING NEW ACCOUNTS
//**********************************************************
int Employee::createAccount(void){
	int i, numTries = 0;
	char password[150];
	char tempChar;
	do{
		fflush(stdin);
		system("cls");
		tempChar = ' ';
		printf("\n\n\n\t\t\t ENTER PASSWORD TO CONTINUE\n\n\n\n");
		printf("\n\t\t\tUSERNAME: ");
		puts(credentials.username);
		printf("\n\t\t\tPASSWORD: ");
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
		if ((strcmp(password, credentials.password) == 0))
		{
			printf("\n\n\t\t Success!");
			getch();
			return signUp();
		}
		else
		{
			printf("\n\n\t\tInvalid password");
			printf("\n\t\t%d attempts left!", (2 - numTries));
			getch();
			numTries++;
		}

	} while (numTries < 3);
	return 0;
}

//**********************************************************
// FUNCTION TO WRITE THE DATA OF AN ACCOUNT IN A FILE
// Creating employee account not added!
//**********************************************************
int Employee::signUp(void){
	char choice;
	char tempChar = ' ';
	int flag, i;
	char username[50], password[150], buffer[150];
	buffer[0] = ' ';
	FILE *file;
	if ((file = fopen("Credentials.txt", "r+")) == NULL){
		printf("\nError! Opening file");
		system("PAUSE");
		return 0;
	}
	do{
		choice = ' ';
		fflush(stdin);
		system("cls");
		printf("\n\n\t\tMember or employee?(M / E):");
		choice = getch();
		if (choice == 'e' || choice == 'E'){
			do{
				fflush(stdin);
				printf("\n\n\t\tAre you sure?(Y / N):");
				choice = getch();
			} while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
			if (choice == 'n' || choice == 'N') choice = 0;
			else choice = 'y';
		}
		else if (choice == 'm' || choice == 'M') choice = 'm';
		else choice = 0;
	} while (!choice);

	if (choice == 'y'){
		system("cls");
		printf("\n\n\t\tSorry, this feature is not available yet.");
		fflush(stdin);
		getch();
		return 1;
	}
	else{
		do{
			flag = 0;
			fflush(stdin);
			system("cls");
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

			fseek(file, 0, SEEK_SET);
			while (tempChar != EOF){
				for (i = 0; (tempChar = fgetc(file)) != EOF && (tempChar != ' '); i++)
					buffer[i] = tempChar;
				buffer[i] = '\0';

				if (strcmp(username, buffer) == 0){
					printf("\n\n\t\tSorry, username already in use.");
					fflush(stdin);
					getch();
					flag = 1;
					break;
				}
				for (i = 0; (tempChar = fgetc(file)) != EOF && (tempChar != ' '); i++)
					buffer[i] = tempChar;
			}
		} while (flag);
		//*****************************************************************************************
		do{
			flag = 0;
			tempChar = 0;
			fflush(stdin);
			system("cls");
			printf("\n\t\tENTER PASSWORD : ");
			for (i = 0; tempChar != 13; i++){
				password[i] = getch();
				tempChar = password[i];
				if (i >= 150 && tempChar != 13 && tempChar != 8){
					password[i] = '\0';
					i--;
					printf("\b \b");
					fflush(stdin);
				}
				if (tempChar >= 0 && tempChar <= 32 && tempChar != 13){
					password[i] = '\0';
					i--;
					if (tempChar == 8 && i >= 0){
						password[i] = '\0';
						i--;
						printf("\b \b");
					}
					fflush(stdin);
				}
				else printf("*");
			}password[i - 1] = '\0';
			tempChar = 0;
			fflush(stdin);
			printf("\n\t\CONFIRM PASSWORD : ");
			for (i = 0; tempChar != 13; i++){
				buffer[i] = getch();
				tempChar = buffer[i];
				if (i >= 150 && tempChar != 13 && tempChar != 8){
					buffer[i] = '\0';
					i--;
					printf("\b \b");
					fflush(stdin);
				}
				if (tempChar >= 0 && tempChar <= 32 && tempChar != 13){
					buffer[i] = '\0';
					i--;
					if (tempChar == 8 && i >= 0){
						buffer[i] = '\0';
						i--;
						printf("\b \b");
					}
					fflush(stdin);
				}
				else printf("*");
			}buffer[i - 1] = '\0';
			//*****************************************************************************************
			//Making sure the password is entered correctly
			if (strcmp(password, buffer) != 0){
				printf("\n\n\t\tIncorrect entry!");
				fflush(stdin);
				getch();
				flag = 1;
			}
		} while (flag);

		fseek(file, 0, SEEK_END);
		for (i = 0; username[i] != '\0'; i++)
			fputc(username[i], file);
		fputc(' ', file);

		for (i = 0; password[i] != '\0'; i++)
			fputc(password[i], file);
		fputc(' ', file);

		printf("\n\n\t\tThe record is sucessfully saved");
		fflush(stdin);
		getch();

		fclose(file);
	}
	return 1;
}

//**********************************************************
// FUNCTION FOR DELETING ACCOUNTS
//**********************************************************
int Employee::deleteAccount(void){
	int i, numTries = 0, flag/*, size, startPossition, endPossition*/;
	char username[50], password[150], buffer[150];
	char tempChar, choice;
	FILE *file;
	do{
		fflush(stdin);
		system("cls");
		tempChar = ' ';
		printf("\n\n\n\t\t\t ENTER PASSWORD TO CONTINUE\n\n\n\n");
		printf("\n\t\t\tUSERNAME: ");
		puts(credentials.username);
		printf("\n\t\t\tPASSWORD: ");
		for (i = 0; tempChar != 13; i++){
			password[i] = getch();
			tempChar = password[i];
			if (i >= 150 && tempChar != 13 && tempChar != 8){
				password[i] = '\0';
				i--;
				printf("\b \b");
				fflush(stdin);
			}
			if (tempChar >= 0 && tempChar <= 32 && tempChar != 13){
				password[i] = '\0';
				i--;
				if (tempChar == 8 && i >= 0){
					password[i] = '\0';
					i--;
					printf("\b \b");
				}
				fflush(stdin);
			}
			else printf("*");
		}password[i - 1] = '\0';
		if ((strcmp(password, credentials.password) == 0))
		{
			printf("\n\n\t\t Success!");
			getch();
			if ((file = fopen("Credentials.txt", "r+")) == NULL){
				printf("\nError! Opening file");
				system("PAUSE");
				return 0;
			}
			do{
				flag = 0;
				fflush(stdin);
				system("cls");
				printf("\n\t\tENTER USERNAME : ");
				for (i = 0; tempChar != 13; i++){
					username[i] = getch();
					tempChar = username[i];
					if (i >= 50 && tempChar != 13 && tempChar != 8){
						username[i] = '\0';
						i--;
						printf("\b \b");
						fflush(stdin);
					}
					if (tempChar >= 0 && tempChar <= 32 && tempChar != 13){
						username[i] = '\0';
						i--;
						if (tempChar == 8 && i >= 0){
							username[i] = '\0';
							i--;
							printf("\b \b");
						}
						fflush(stdin);
					}
					else printf("%c", username[i]);
				}username[i - 1] = '\0';

				fseek(file, 0, SEEK_SET);
				while (tempChar != EOF){
					for (i = 0; (tempChar = fgetc(file)) != EOF && (tempChar != ' '); i++)
						buffer[i] = tempChar;
					buffer[i] = '\0';

					if (strcmp(username, buffer) == 0){
						do{
							fflush(stdin);
							printf("\n\n\t\tAre you sure you want to remove this account?(Y / N):");
							choice = getch();
						} while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
						if (choice == 'n' || choice == 'N') return 0;
						system("cls");
						printf("\n\n\t\tSorry, this feature is not available yet.");
						fflush(stdin);
						getch();
						/*
						fseek(file, -sizeof(username)*strlen(username), SEEK_CUR);
						startPossition = ftell(file);
						fseek(file, 0, SEEK_END);
						size = ftell(file);
						rewind(file);
						text = (char*)malloc(sizeof(char)*(size + 999));
						fread(text, sizeof(char), size, file);
						text[size] = '\0';

						free(text);*/
						flag = 1;
						break;
					}
					for (i = 0; (tempChar = fgetc(file)) != EOF && (tempChar != ' '); i++)
						buffer[i] = tempChar;
				}
			} while (flag);



			printf("\n\n\t\tThe record is sucessfully saved");
			fflush(stdin);
			getch();

			fclose(file);
		}
		else
		{
			printf("\n\n\t\tInvalid password");
			printf("\n\t\t%d attempts left!", (2 - numTries));
			getch();
			numTries++;
		}

	} while (numTries < 3);
	return 0;
}