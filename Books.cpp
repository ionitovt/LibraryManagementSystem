#include "Books.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>

#define RETURNTIME 1 	// contains return date, etc 

FILE *fp, *ft, *fs;
char choice;

//**********************************************************
// CONSTRUCTOR
//**********************************************************
Books::Books(void){
	strcpy(catagories[0], "Mathematics");
	strcpy(catagories[1], "Psycology");
	strcpy(catagories[2], "Biology");
	strcpy(catagories[3], "Accounting");
	strcpy(catagories[4], "Economics");
	strcpy(catagories[5], "English");
	s = 0;
	findbook = '\0';
	r.id = 0;
	r.stname[0] = '\0';
	r.name[0] = '\0';
	r.Writer[0] = '\0';
	r.quantity = 0;
	r.Amount = 0.0;
	r.bookno = 0;
	r.cat[0] = '\0';
	r.issued.mm = 0;
	r.issued.dd = 0;
	r.issued.yy = 0;
	r.duedate.mm = 0;
	r.duedate.dd = 0;
	r.duedate.yy = 0;
}

//**********************************************************
// METHOD FOR ADDING BOOKS
//**********************************************************
void Books::addbooks(void)    //function to add books
{
	int i;		//local variable for switch option 
	fflush(stdin);
addbookspoint:
	system("cls");
	printf("\n\t\t\tSELECT CATEGOIES");
	printf("\n\t\t 1. Mathematics");
	printf("\n\t\t 2. Psycology");
	printf("\n\t\t 3. Biology");
	printf("\n\t\t 4. Accounting");
	printf("\n\t\t 5. Economics");
	printf("\n\t\t 6. English");
	printf("\n\t\t 7. Main menu");
	printf("\n\t\tEnter your choice:");
	scanf("%d", &s);
	if (s == 7) return;
	system("cls");
	if ((fp = fopen("Project.dat", "ab+")) == NULL){
		printf("\nError! Opening file");
		system("PAUSE");
		return;
	}
	if (getdata() == 1)
	{
		strcpy(r.cat, catagories[s - 1]);
		fseek(fp, 0, SEEK_END);			//fseek sets the file position of the given offset
		fwrite(&r, sizeof(r), 1, fp);		//size_r this is the unsigned integral type and is the result of the sizeof keyword.
		fclose(fp);
		printf("\n\t\tThe record is sucessfully saved");
		do{
			fflush(stdin);
			printf("\n\t\tSave any more?(Y / N):");
			choice = getch();
		} while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
		if (choice == 'n' || choice == 'N'){ fclose(fp); return; }
		fclose(fp);
		goto addbookspoint;
	}
}

//**********************************************************
// METHOD THAT DELETES FROM FILE FP
//**********************************************************
void Books::deletebooks()
{
	fflush(stdin);
	int d;
	system("cls");
	char another = 'y';
	while (another == 'y')  	//cause infinite loop
	{
		findbook == '\0';
		system("cls");
		printf("\n\t\tEnter the Book ID to  delete: ");
		scanf("%d", &d);
		if ((fp = fopen("Project.dat", "rb+")) == NULL){
			printf("\nError! Opening file");
			system("PAUSE");
			return;
		}
		rewind(fp);
		while (fread(&r, sizeof(r), 1, fp) == 1)
		{
			if (r.id == d)
			{

				printf("\n\t\tThe book record is available");
				printf("\n\t\tBook name is %s", r.name);
				printf("\n\t\tBook No. is %d", r.bookno);
				findbook = 't';
			}
		}
		if (findbook != 't')
		{
			printf("\n\t\tNo record is found to delete the search");
			if (getch())
				return;
		}
		if (findbook == 't')
		{
			do{
				fflush(stdin);
				printf("\n\t\tDo you want to delete it?(Y/N):");
				choice = getch();
			} while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
			if (choice == 'y' || choice == 'Y')
			{
				if ((ft = fopen("temp.dat", "wb+")) == NULL){  //deleting temporary files
					printf("\nError! Opening file");
					system("PAUSE");
					return;
				}
				rewind(fp);
				while (fread(&r, sizeof(r), 1, fp) == 1)
				{
					if (r.id != d)
					{
						fseek(ft, 0, SEEK_CUR);			//sets current position of file
						fwrite(&r, sizeof(r), 1, ft); 	  //write all items in temporary file except what we want to delete
					}
				}
				fclose(fp);
				fclose(ft);
				remove("Project.dat");
				rename("temp.dat", "Project.dat"); 		//read items from temporary file
				if ((fp = fopen("Project.dat", "rb+")) == NULL){
					printf("\nError! Opening file");
					system("PAUSE");
					return;
				}
				if (findbook == 't')
				{
					printf("\n\t\tThe record is sucessfully deleted");
					do{
						fflush(stdin);
						printf("\n\t\tDelete another record?(Y/N)");
						choice = getch();
					} while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
					if (choice == 'n' || choice == 'N'){ fclose(fp); return; }
					fclose(fp);
					another = 'y';
				}
			}
			else return;
			fflush(stdin);
			another = 'y';
		}
	}
	return;
}

//**********************************************************
// METHOD THAT SEARCHES ITEMS FROM FILE FP
//**********************************************************
void Books::searchbooks()
{
	if ((fp = fopen("Project.dat", "rb+")) == NULL){ 		//open file in read mode
		printf("\nError! Opening file");
		system("PAUSE");
		return;
	}
	fflush(stdin);
	int d;
searchbookspoint:
	system("cls");
	printf("\n\t\tSearch Books ");
	printf("\n\t\t 1. Search By ID");
	printf("\n\t\t 2. Search By Name");
	printf("\n\t\tEnter Your Choice");
	rewind(fp);   		//sets the file position to the beginning
	switch (getch())
	{
	case '1':
	{
				system("cls");
				printf("\n\t\tSearch Books By Id ");
				printf("\n\t\tEnter the book id:");
				scanf("%d", &d);
				printf("\n\t\tSearching........");
				while (fread(&r, sizeof(r), 1, fp) == 1)
				{
					if (r.id == d)
					{
						printf("\n\t\tThe Book is available");
						printf("\n\t\t ID:%d", r.id);
						printf("\n\t\t Name:%s", r.name);
						printf("\n\t\t Writer:%s ", r.Writer);
						printf("\n\t\t Qantity:%d ", r.quantity);
						printf("\n\t\t Amount:Rs.%.2f", r.Amount);
						printf("\n\t\t Book No:%d ", r.bookno);

						findbook = 't';
					}

				}
				if (findbook != 't')  		//it checks weather the condition is entered loop or not
				{
					printf("\r\n\t\tNo Record Found");
				}
				do{
					fflush(stdin);
					printf("\n\t\tTry another search?(Y/N)");
					choice = getch();
				} while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
				if (choice == 'n' || choice == 'N'){ fclose(fp); return; }
				fclose(fp);
				goto searchbookspoint;
				break;
	}
	case '2':
	{
				char s[15];
				system("cls");
				printf("\n\t\tSearch Books By Name ");
				printf("\n\t\tEnter Book Name:");
				scanf("%s", s);
				int d = 0;
				while (fread(&r, sizeof(r), 1, fp) == 1)
				{
					if (strcmp(r.name, (s)) == 0) 		//it checks weather r.name is equal to s or not
					{
						printf("\n\t\tThe Book is available");
						printf("\n\t\t ID:%d", r.id);
						printf("\n\t\t Name:%s", r.name);
						printf("\n\t\t Writer:%s", r.Writer);
						printf("\n\t\t Qantity:%d", r.quantity);
						printf("\n\t\t Amount:Rs.%.2f", r.Amount);
						printf("\n\t\t Book No:%d ", r.bookno);

						d++;
					}

				}
				if (d == 0)
				{
					printf("\r\n\t\tNo Record Found");
				}
				do{
					fflush(stdin);
					printf("\n\t\tTry another search?(Y/N)");
					choice = getch();
				} while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
				if (choice == 'n' || choice == 'N'){ fclose(fp); return; }
				fclose(fp);
				goto searchbookspoint;
				break;
	}
	default:
		getch();
		goto searchbookspoint;
	}
	fclose(fp);
}

//**********************************************************
// METHOD FOR ISSUING BOOKS
//**********************************************************
void Books::issuebooks(void)
{
	int t;		//local variable for switch option

	system("cls");
	printf("\n\t\t   ISSUE SECTION ");
	printf("\n\t\t 1. Issue a Book");
	printf("\n\t\t 2. View Issued Book");
	printf("\n\t\t 3. Search Issued Book");
	printf("\n\t\t 4. Remove Issued Book");
	printf("\n\t\t 5. Main menu");
	printf("\n\t\tEnter a Choice:");
	switch (getch())
	{
	case '1':  //issue book
	{
				   system("cls");
				   int c = 0;
				   char another = 'y';
				   while (another == 'y')		//infinite loop
				   {
					   system("cls");
					   printf("\n\t\t Issue Book section ");
					   printf("\n\t\tEnter the Book Id:");
					   scanf("%d", &t);
					   if ((fp = fopen("Project.dat", "rb")) == NULL){
						   printf("\nError! Opening file");
						   system("PAUSE");
						   return;
					   }
					   if ((fs = fopen("Issue.dat", "ab+")) == NULL){
						   printf("\nError! Opening file");
						   system("PAUSE");
						   return;
					   }
					   if (checkid(t) == 0) 		//check weather the book is available in library or not
					   {
						   printf("\n\t\tThe book record is available");
						   printf("\n\t\tThere are %d unissued books in library ", r.quantity);
						   printf("\n\t\tThe name of book is %s", r.name);
						   printf("\n\t\tEnter student name:");
						   scanf("%s", r.stname);
						   printf("\n\t\tIssued date=%d-%d-%d", r.issued.dd, r.issued.mm, r.issued.yy);	//for current date
						   printf("\n\t\tThe BOOK of ID %d is issued", r.id);
						   r.duedate.dd = r.issued.dd + RETURNTIME;   		//for return date
						   r.duedate.mm = r.issued.mm;
						   r.duedate.yy = r.issued.yy;
						   if (r.duedate.dd>30)
						   {
							   r.duedate.mm += r.duedate.dd / 30;
							   r.duedate.dd -= 30;

						   }
						   if (r.duedate.mm>12)
						   {
							   r.duedate.yy += r.duedate.mm / 12;
							   r.duedate.mm -= 12;

						   }
						   printf("\n\t\tTo be return:%d-%d-%d", r.duedate.dd, r.duedate.mm, r.duedate.yy);
						   fseek(fs, sizeof(r), SEEK_END);		//end of the file
						   fwrite(&r, sizeof(r), 1, fs);
						   fclose(fs);
						   c = 1;
					   }
					   if (c == 0)
					   {
						   printf("\n\t\tNo record found");
					   }
					   printf("\n\t\tIssue any more(Y/N):");
					   fflush(stdin);
					   another = getche();
					   fclose(fp);
				   }

				   break;
	}
	case '2':  	//case shows the issue books list
	{
					system("cls");
					int j = 4;
					printf("\n\t\t                          Issued book list                               ");
					printf("\n\t\tSTUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
					if ((fs = fopen("Issue.dat", "rb")) == NULL){
						printf("\nError! Opening file");
						system("PAUSE");
						return;
					}
					while (fread(&r, sizeof(r), 1, fs) == 1)
					{

						printf("\n\t\tStudent name: %s", r.stname);
						printf("\n\t\tCat: %s", r.cat);
						printf("\n\t\tID: %d", r.id);
						printf("\n\t\tBook name: %s", r.name);
						printf("\n\t\tDate issued: %d-%d-%d", r.issued.dd, r.issued.mm, r.issued.yy);
						printf("\n\t\tDue date: %d-%d-%d", r.duedate.dd, r.duedate.mm, r.duedate.yy);
						//printf("Current date=%d-%d-%d",d.day,d.month,d.year);
						j++;

					}
					fclose(fs);
					fflush(stdin);
					system("PAUSE");
	}
		break;
	case '3':   //search issued books by id
	{
					system("cls");
					printf("\n\t\tEnter Book ID:");
					int p, c = 0;
					char another = 'y';
					while (another == 'y')
					{

						scanf("%d", &p);
						if ((fs = fopen("Issue.dat", "rb")) == NULL){
							printf("\nError! Opening file");
							system("PAUSE");
							return;
						}
						while (fread(&r, sizeof(r), 1, fs) == 1)
						{
							if (r.id == p)
							{
								issuerecord();
								printf("\n\t\tPress any key.......");
								getch();
								issuerecord();
								c = 1;
							}

						}
						fflush(stdin);
						fclose(fs);
						if (c == 0)
						{
							printf("\n\t\tNo Record Found");
						}
						printf("\n\t\tTry Another Search?(Y/N)");
						another = getch();
					}
	}
		break;
	case '4':  	//case remove issued books from list
	{
					system("cls");
					int b;
					FILE *fg;  	//delete for temporary file is declared
					char another = 'y';
					while (another == 'y')
					{
						printf("\n\t\tEnter book id to remove:");
						scanf("%d", &b);
						if ((fs = fopen("Issue.dat", "rb+")) == NULL){
							printf("\nError! Opening file");
							system("PAUSE");
							return;
						}
						while (fread(&r, sizeof(r), 1, fs) == 1)
						{
							if (r.id == b)
							{
								issuerecord();
								findbook = 't';
							}
							if (findbook == 't')
							{
								printf("\n\t\tDo You Want to Remove it?(Y/N)");
								if (getch() == 'y')
								{
									if ((fg = fopen("record.dat", "wb+")) == NULL){
										printf("\nError! Opening file");
										system("PAUSE");
										return;
									}
									rewind(fs);
									while (fread(&r, sizeof(r), 1, fs) == 1)
									{
										if (r.id != b)
										{
											fseek(fs, 0, SEEK_CUR);
											fwrite(&r, sizeof(r), 1, fg);
										}
									}
									fclose(fs);
									fclose(fg);
									remove("Issue.dat");
									rename("record.dat", "Issue.dat");
									printf("\n\t\tThe issued book is removed from list");
								}
							}
							if (findbook != 't')
							{
								printf("\n\t\tNo Record Found");
							}
						}
						printf("\n\t\tDelete any more?(Y/N)");
						another = getch();
					}
	}
	case '5': return;
	default:
		printf("\nWrong Entry!!");
		getch();
		issuebooks();
		break;
	}
}

//**********************************************************
// METHOD THAT SHOWS THE LIST OF BOOKS AVAILABLE IN LABRARY	
//**********************************************************
void Books::bookslist(void)
{
	int i = 0, j;
	system("cls");
	printf("\n\t\t=======================================Book List=======================================\n");
	printf("\n\t\tCATEGORY       ID    BOOK NAME           WRITER              QTY    AMOUNT     BOOK NO");
	j = 4;
	if ((fp = fopen("Project.dat", "rb")) == NULL){
		printf("\nError! Opening file");
		system("PAUSE");
		return;
	}
	while (fread(&r, sizeof(r), 1, fp) == 1)
	{
		printf("\n\t\t%-15s", r.cat);
		printf("%-6d", r.id);
		printf("%-20s", r.name);
		printf("%-20s", r.Writer);
		printf("%-7d", r.quantity);
		printf("%-11.2f", r.Amount);
		printf("%d", r.bookno);
		j++;
		i = i + r.quantity;
	}
	printf("\n\n\t\tTotal Books =%d", i);
	fclose(fp);
	fflush(stdin);
	getch();
}

//**********************************************************
// METHOD TO EDID INFORMATION ABOUT BOOK
//**********************************************************
void Books::editbooks(void)
{
	system("cls");
	int c = 0;
	int d, e;
	printf("\n\t\t Edit Books Section");
	char another = 'y';
	while (another == 'y')
	{
		system("cls");
		printf("\n\t\tEnter Book Id to be edited:");
		scanf("%d", &d);
		if ((fp = fopen("Project.dat", "rb+")) == NULL){
			printf("\nError! Opening file");
			system("PAUSE");
			return;
		}
		while (fread(&r, sizeof(r), 1, fp) == 1)
		{
			if (checkid(d) == 0)
			{
				printf("\n\t\tThe book is availble");
				printf("\n\t\tThe Book ID:%d", r.id);
				printf("\n\t\tEnter new name:"); scanf("%s", r.name);
				printf("\n\t\tEnter new Writer:"); scanf("%s", r.Writer);
				printf("\n\t\tEnter new quantity:"); scanf("%d", &r.quantity);
				printf("\n\t\tEnter new amount:"); scanf("%f", &r.Amount);
				printf("\n\t\tEnter new bookno:"); scanf("%d", &r.bookno);
				printf("\n\t\tThe record is edited");
				fseek(fp, ftell(fp) - sizeof(r), 0);	//ftell returns the current file position of the given stream.
				fwrite(&r, sizeof(r), 1, fp);
				fclose(fp);
				c = 1;
			}
			if (c == 0)
			{
				printf("\n\t\tNo record found");
			}
		}
		printf("\n\t\tEdit another Record?(Y/N)");
		fflush(stdin);
		another = getch();
	}
}

//**********************************************************
// METHOD FOR ENTERING DATA FOR A BOOK
//**********************************************************
int Books::getdata()
{
	int t;
	printf("\n\t\tEnter the Information Below");
	printf("\n\t\tCategory:");
	printf(" %s", catagories[s - 1]);
	printf("\n\t\tBook ID:");
	scanf("%d", &t);
	if (checkid(t) == 0)
	{
		printf("\t\t\nThe book id already exists\n");
		getch();
		return 0;
	}
	r.id = t;
	printf("\t\tBook Name:");
	scanf("%s", r.name);
	printf("\t\tWriter:");
	scanf("%s", r.Writer);
	printf("\t\tQuantity:");
	scanf("%d", &r.quantity);
	printf("\t\tAmount:");
	scanf("%f", &r.Amount);
	printf("\t\tBook No:");
	scanf("%d", &r.bookno);
	return 1;
}

//**********************************************************
// METHOD FOR CHECKING IF BOOK EXIST IN LABRARY OR NOT
//**********************************************************
int Books::checkid(int t)
{
	rewind(fp);
	while (fread(&r, sizeof(r), 1, fp) == 1) //size_r is a unsigned integral type and is the result of the sizeof keyword.
	if (r.id == t)
		return 0;  		//return 0 if book exist
	return 1; 	//return 1 if book does not exist
}

//**********************************************************
// METHOD FOR ADDINT TIME
//**********************************************************
int Books::t(void)
{
	time_t t;
	time(&t);
	printf("\n\t\tDate and time:%s\n", ctime(&t));

	return 0;
}

//**********************************************************
// METHOD THAT DISPLAYES A BOOK'S INFORMATION
//**********************************************************
void Books::issuerecord()
{
	system("cls");
	printf("\n\t\tThe Book has taken by Mr. %s", r.stname);
	printf("\n\t\tIssued Date:%d-%d-%d", r.issued.dd, r.issued.mm, r.issued.yy);
	printf("\n\t\tReturning Date:%d-%d-%d", r.duedate.dd, r.duedate.mm, r.duedate.yy);
}