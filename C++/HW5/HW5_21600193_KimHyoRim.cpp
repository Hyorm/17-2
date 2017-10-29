#include<iostream> 
#include <string>

using namespace std;

class People { 

	private: 

		string name; 

		string stuNo; 

	public: 

		People(){ }

		People(string name, string stuNo) { 
			
			this->name = name;
			this->stuNo = stuNo;	

		 }

		void setName(string name) { 

			this->name = name;

		 } 

		void setStuNo(string stuNo) { 
	
			this->stuNo = stuNo;

 		}

		string getName() { 

			return this->name;

		 } 

		string getStuNo() { 

			return this->stuNo;

		 } 

		void print() { 

			cout << "My name is " << this->name << " Stu no is " << this->stuNo << endl ;

		}
};

class Team { 

	private: 

		string name; 

		People member[30]; 

		int cnt=0;

	public: 
		
		Team(){ } 

		Team(string _name) { 

			this->name = _name;

		}

		void addMember(People people) { 
			
			if(cnt > 29) { 
		
				cout <<"full"; 

			} else {  

				this->member[cnt] = people;
			
				this->cnt++;

			} 
		
		} 

		void printMember() { 

			for(int i =0; i< this->cnt; i++)
				cout << "RC_Team's Member name is " << this->member[i].getName()<< endl;

		} 

};

int main() { 

	Team* team1 = new Team("RC_Team");

	People p1("Gildong", "21800123"); 

	p1.print(); // print : My name is Gildong stu no is 21800123

	p1.setName("Handong"); //your name 

	p1.setStuNo("21x00xxx"); //your student number 

	p1.print();	// change to your name     Gildong -> (your name), (21800123 -> 21x00xxx) 
			// print : My name is (Your name) Stu no is 21x00xxx

	team1 ->addMember(p1); 

	team1 -> printMember(); // print : RC_Team's Member name is (Your name)

}
