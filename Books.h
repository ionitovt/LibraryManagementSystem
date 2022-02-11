#ifndef BOOKS_H
#define BOOKS_H

//**********************************************************
// STRUCTURE FOR DATE
//**********************************************************
struct meroDate
{
	int mm, dd, yy;
};
//**********************************************************
// STRUCTURE FOR BOOK
//**********************************************************
typedef struct
{
	int id;
	char stname[20];
	char name[20];
	char Writer[20];
	int quantity;
	float Amount;
	int bookno;
	char cat[16];
	struct meroDate issued;
	struct meroDate duedate;
}book;

//**********************************************************
// THIS CLASS CONTAINS FUNCTIONS RELATED TO BOOKS
//**********************************************************

class Books{
private:
	char catagories[20][16];
	int s;
	char findbook;
	book r;
public:
	Books(void);
	void addbooks(void);		//declaration for the add function
	void deletebooks(void);		//declaration for the delete function
	void editbooks(void);		//declaration for the edit function
	void searchbooks(void);		//declaration for search function
	void issuebooks(void);		//declaration for issuing function
	void bookslist(void);		//declaration for viewing bok list function
	int  getdata();
	int  checkid(int);
	int t(void);
	void issuerecord();			//declaration for issuing record
};

#endif