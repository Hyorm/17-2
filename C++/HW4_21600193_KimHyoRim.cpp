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
	int index = 0;

};

void printMenu();
string * p_Arg(string line);
book *load_m(string FileName);
void save_m(string fileName, book * bookList);
void print_m(book * bookList);
book insert_m(string * arg);
book *lend_m(book * bookList, string * arg);
book *passDay_m(book * bookList);
book * returned_m(book * bookList, string * arg);

int getExit();

int main(){

	int setExit = 1;

	book * b_List;

	string openFile = "input.txt";

	b_List = load_m(openFile);

	while(setExit){

		string argLine, * arg;

		printMenu();

		getline(cin, argLine);

		arg = p_Arg(argLine);

		char n1 = arg[0][0];
		char n2 = arg[0][1];

		switch(toupper(n1)){

		case 'I':	
						insert_m(arg);
						break;
		case 'L' :
						lend_m(b_List, arg);
						break;
		case 'S':
						save_m(arg[1], b_List);
						break;
		case 'R':
						returned_m(b_List, arg);
						break;
		case 'P':	
					switch (toupper(n2)) {
			
						case 'A':	passDay_m(b_List);
									break;

						case 'R':	print_m(b_List);
									break;
					}
					break;
		case 'E':	
						setExit = getExit();
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

string * p_Arg(string line){
	
	int f_col, i = 0;
	
	static string arg[6];

	while(1){

		if (i == 0) {
			f_col = line.find(" ");
			arg[i] = line.substr(0, f_col);
			line.erase(0, f_col + 1);
			i++;
		}
		else {
			if (line.length() > 0) {
				f_col = line.find(";");
				if (f_col == -1) {
					arg[i] = line;
					break;
				}
				arg[i] = line.substr(0, f_col);
				line.erase(0, f_col + 2);
				i++;
			}
			else
				break;
		}
	}

	return arg;

}


//TODO: THREE - function Load

book *load_m(string FileName){
	//open file and store list
	static book bookList[50];

	int i = 0;


	string line;

	ifstream inData;
	inData.open(FileName.c_str());

	if(!inData){
		
		cout << FileName << " does not exist." << endl;
		
	}
	else{

		while(!inData.eof()){
		
			getline(inData, line);

			int f_col, j = 0;
			string arr[6];
	
			while(1){

				if (line.length() > 0) {
					f_col = line.find(";");
					if (f_col == -1) {
						arr[j] = line;
						break;
					}
					arr[j] = line.substr(0, f_col);
					line.erase(0, f_col+2);
					j++;
		        }
		        else
                		break;
				
			}	

			bookList[i].title = arr[0];
			bookList[i].author = arr[1];
			bookList[i].p_Year = arr[2];
			bookList[i].edition = arr[3];
			bookList[i].b_Person = arr[4];
			bookList[i].l_Day = stoi(arr[5]);
		
			i++;

		}
		i--;
		bookList[0].index = i;
		print_m(bookList);
	}

	inData.close();


	return bookList;

}

//TODO: THREE - function Save

void save_m(string fileName, book * bookList){
	// use ofstream and save text file
	ofstream outData;

	int i = 0;

	outData.open(fileName.c_str());

	while (i < bookList[0].index - 1) {

		outData << bookList[i].title << bookList[i].p_Year << bookList[i].author << bookList[i].edition << bookList[i].b_Person << bookList[i].l_Day << endl;
		
		i++;

	}

	outData << bookList[i].title << bookList[i].p_Year << bookList[i].author << bookList[i].edition << bookList[i].b_Person << bookList[i].l_Day;

	outData.close();
}

//DONE: THREE - function Print
void print_m(book * bookList){

	cout << "  ======================================== Book Catalog ========================================" << endl;
	cout << setw(8) << "Title" << setw(24) << "Author" << setw(28) << "Publised Year" << setw(10) << "Edition" << setw(10) << "Borrower" << setw(16) << "Days Borrowed" << endl;

	for(int i = 0; i < bookList[0].index ; i++ ){

		cout << "   " << bookList[i].title << setw(24 - bookList[i].title.length()) << bookList[i].author << setw(28 - bookList[i].author.length()) << bookList[i].p_Year << setw(10 - bookList[i].p_Year.length()) << bookList[i].edition << setw(10 - bookList[i].edition.length()) << bookList[i].b_Person << setw(16 - bookList[i].b_Person.length()) << bookList[i].l_Day << endl;
	}

	cout << "  ============================================= End =============================================" << endl;

}

//TODO: THREE - function Insert
book insert_m(string * arg){

	book newBook;
	
	return newBook;
	
}

//TODO: THREE - function Lend
book *lend_m(book * bookList, string * arg){

	return bookList;
}

//TODO: THREE - function Passday
book *passDay_m(book * bookList){
	
	return bookList;
}

//TODO: THREE - function Returned
book * returned_m(book * bookList, string * arg){

	return bookList;
}

//TODO: THREE - fundtion Exit
int getExit(){

	return 0;
	
}
