#include <iostream>
#include <string>
#include<iomanip>
#include <fstream>

using namespace std;

//DONE: ONE - 	make
struct book{

	string title;
	string p_Year;
	string author;
	string edition;
	string b_Person = "None";
	int l_Day = 0; 

};

void printMenu();

book *load();
void save(string fileName);
void print(book[] bookList);
book insert(string[] arr);
book *lend(book[] bookList);
book *passDay(book[] bookList);
book returned(book r_book);
int getExit();

int main(){

	int setExit = 1;

	book b_List[50];

	string openFile = "first.txt";

	while(setExit){

		b_List = load(openFile);

		string argLine, arg[4];

		enum menu {INSERT, Insert, insert, LEND, Lend, lend, SAVE, Save, save, RETURNED, Returned, returned, PASSDAY, Passday, passday, PRINT, Print, print, EXIT, Exit, exit};

		printMenu();

		getline(cin, argLine);

		switch(arg[0]){

		case INSERT:
		case Insert:
		case insert:	insert(b_List);
				break;
		case LEND:
		case Lend:
		case lend:	lend(b_List);
				break;
		case SAVE:
		case Save:
		case save:	save(arg[1]);
				break;
		case RETURNED:
		case Returned:
		case returned:	returned(b_List);
				break;
		case PASSDAY:
		case Passday:
		case passday:	passDay(b_List);
				break;
		case PRINT:
		case Print:
		case print:	print(b_List);
				break;
		case EXIT:
		case Exit:
		case exit:	setExit = getExit();
				break;
		}
		
	}

	return 0;
}

void printMenu(){
	
	cout << "  =============== Available Commend & Format ===============" << endl << endl;
	cout << "  1. INSERT BookTitle; Author; PubYear; Edition" << endl;
	cout << "  2. LEND BookTitle; Person Borrowing; How many days" << endl;
	cout << "  3. SAVE new_filename.txt" << endl;
	cout << "  4. RETURNED BookTitle" << endl;
	cout << "  5. PASSDAY" << endl;
	cout << "  6. PRINT" << endl;
	cout << "  7. EXIT" << endl << endl;
	cout << "  ==========================================================" << endl;
	cout << "  >>";
}

//TODO: THREE - function Load

book *load(string FileName){
	//open file and store list
	book[50] bookList;

	int i = 0;

	ifstream inData;
	inData.open(FileName.c_str())

	if(!inData){
		
		cout << FileName << " does not exist." << endl;
		
	}
	else{

		while(!inData.eof()){
		
			inData >> bookList[i].title >> bookList[i].p_Year >> bookList[i].author >> bookList[i].edition >> bookList[i].b_Person >> bookList[i].l_Day;
		
			i++;

		}

		print(bookList);
	}

	inData.cloase();

	return bookList;

}

//TODO: THREE - function Save

void save(string fileName){
	// use ofstream and save text file

}

//TODO: THREE - function Print
void print(book[] bookList){

	cout << "  ======================================== Book Catalog ========================================" << endl;
	cout << setw(8) << "Title" << setw(24) << "Author" << setw(28) << "Publised Year" << setw(10) << "Edition" << setw(10) << "Borrower" << setw(16) << "Days Borrowed" << endl;

	for(int i = 0; i < bookList.size() ; i++ ){

		cout << "   " << bookList[i].title << setw(24 - bookList[i].title.length()) << bookList[i].author << setw(28 - bookList[i].author.length()) << bookList[i].p_Year << setw(10 - bookList[i].p_Year.length()) << bookList[i].edition << setw(10 - bookList[i].edition.length()) << bookList[i].b_Person << setw(16 - bookList[i].b_Person.length()) << bookList[i].l_Day << endl;
	}

	cout << "  ============================================= End =============================================" << endl;

}

//TODO: THREE - function Insert
book insert(string[] arr){

	book newBook;
	
	return newBook;
	
}

//TODO: THREE - function Lend
book *lend(book[] bookList){

	return bookList;
}

//TODO: THREE - function Passday
book *passDay(book[] bookList){
	
	return bookList;
}

//TODO: THREE - function Returned
book returned(book r_book){

	return r_book;
}

//TODO: THREE - fundtion Exit
int getExit(){

	return 0;
	
}
