#include <iostream>
#include <string>
#include<iomanip>
#include <fstream>

using namespace std;

book* load();
void save(string fileName);
void print(book[] bookList);
book insert(string[] arr);
book* lend(book[] bookList);
book* passDay(book[] bookList);
book returned(book r_book);
int getExit();

//DONE: ONE - 	make
struct book{

	string title;
	string p_Year;
	string author;
	string edition;
	string b_Person;
	int l_Day; 

};

int main(){

	int setExit = 1;

	book[50] bookList;

	while(exit){

	
		setExit = getExit();

	}

	return 0;
}

//TODO: THREE - function Load

book *load(){
	//open file and store list
	book[50] bookList;

	return bookList;

}

//TODO: THREE - function Save

void save(string fileName){
	// use ofstream and save text file

}

//TODO: THREE - function Print
void print(book[] bookList){


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
