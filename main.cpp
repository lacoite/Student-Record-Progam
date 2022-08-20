//Include necessary libraries
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
//Defined Student class for program organization and functions
#include "Student.h"

using namespace std;

//Defines file streams that allows both reading and writing to contain student data
fstream studentRecords, updateRecords;

string firstName, lastName, query;
int ID, age, year;
double GPA;

void printAllRecords(){
	//Opens StudentRecord text file in input mode
	studentRecords.open("StudentRecords.txt", ios::in); 
	
	if(studentRecords.is_open()){
		cout << endl;
		string studentData;
		while(getline(studentRecords, studentData)){
			cout << studentData << endl;
		}
		cout << endl;
		studentRecords.close();
	}
}

int generateID(){
	bool flag;
	int _ID, ID;
	do{
		do{
			flag = 0;
			srand(time(0));
			_ID = rand() % 10000000;
			if (_ID > 99999 && _ID < 1000000){
				flag = 0;
			}
			else{
				flag = 1;
			}
		}while(flag != 0);
	
		studentRecords.open("StudentRecords.txt", ios::in);
		if(studentRecords.is_open()){
			string studentData;
			while(getline(studentRecords, studentData)){
				ID = (int)NULL;
				for(int c = 0; c < 6; c++){
					ID+=studentData[c];
				}
				if(_ID == ID){
					flag = 1;
					break;
				}
			}
			studentRecords.close();
		}
	}while(flag != 0);
	
	return _ID;
}

void enrollStudent(){
	bool exception;
	
	cout << "Generating Student ID. Please Wait...\n" << endl;
	
	//Using Student object to handle incorrect data entry in set methods
	Student *record = new Student();
	
	record -> setID(generateID());
	cout << "Enter Student Information...\n" << endl;
	
	cout << "First Name: ";
	cin >> firstName;
	record -> setFirstName(firstName);
	
	cout << "Last Name: ";
	cin >> lastName;
	record -> setLastName(lastName);

	
	cout << "Year (1.Freshman, 2.Sophomore, 3.Junior, 4.Senior): ";
	cin >> year;
	record->setYear(year);
	
	cout << "\aAge: ";
	cin >> age;
	record -> setAge(age);
	
	cout << "GPA: ";
	cin >> GPA;
	record -> setGPA(GPA);

	//Open StudentRecords text file
	studentRecords.open("StudentRecords.txt", ios::app);

	//Print student information from Student object into text file
	if(studentRecords.is_open()){
		studentRecords << record->getID() << " " << record->getFirstName() << " " << record->getLastName() << " " << record->getYear() << " " << record->getAge() << " " << record->getGPA() << endl;
	}
	studentRecords.close();

	cout << "\n	Student " << record->getID() << " Added \n" << endl;
}

void removeStudent(string _ID){
	studentRecords.open("StudentRecords.txt", ios::in);
	updateRecords.open("updateRecords.txt", ios::out);
	bool found = 0;
	if(studentRecords.is_open()){
		string studentData;
		while(getline(studentRecords, studentData)){
			if(studentData.find(_ID) != std::string::npos){
				found = 1;
				continue;
			}
			else{
				if(updateRecords.is_open()){
					updateRecords << studentData << endl;
				}
			}
		}
	}
	if(found == 1){
		std::rename("updateRecords.txt", "StudentRecords.txt");
		cout << "Student " << _ID << " Removed\n" << endl;
	}
	else{
		cout << "ID " << _ID << " Not Found\n" << endl;
	}
	updateRecords.close();
	studentRecords.close();
}

void searchRecords(string _string){
	Student *record = new Student();

	studentRecords.open("StudentRecords.txt", ios::in);
	bool results = 1;
	if (studentRecords.is_open()){
		string studentData;
		string data;
		
		cout << "\nSearch Results: \n" << endl;
			while(getline(studentRecords, studentData)){
				if(studentData.find(_string) != std::string::npos){
					cout << studentData << endl;
					results = 0;
				}
			}
		studentRecords.close();
	}
	if(results == 1){
		cout << "No Matching Records" << endl;
	}
	else{
		cout << "\nEnd of Matching Records\n" << endl;
	}
}

void validateID(string _ID){
	int ID;
	bool exception;
	do{
		exception = 0;
		try{
			//Throws error if entered ID is not an integer
			ID = std::stoi(_ID);
			bool flag;
				do{	
					flag = 0;
					if (ID < 99999 || ID > 999999){
						flag = 1;
						throw ID;
					}
				}while(flag != 0);
		}
 
		catch(...){
			exception = 1;
			cout << "Invalid Student ID\nEnter 6 Digit Student ID: ";
			cin >> _ID;
		}
	}while(exception != 0);
	query = _ID;
}

//Validates entry of name during Search By Student Name
void validateNameQuery(string _name){
	bool flag;
	do{
		flag = 0;
		for(int c = _name.length()-1; c >= 0; c--){
			if((isalpha(_name[c]) == 0) && (isspace(_name[c]) == 0)){
				flag =1 ;
			}
		}
		if(flag == 1){
			cout << "Invalid Student Name (Enter Only Alphabet Characters)\nName: ";
			cin >> _name;
		}
	}while(flag != 0);
	query = _name;
}


int main() {
	//Define variables for menu selection
	int selection;

	//Main Menu
	while(selection != 0){
		cout << "	STUDENT RECORD PROGRAM\n" << endl;
		cout << "1. View Records" << endl;
		cout << "2. Enroll New Student" << endl;
		cout << "3. Remove Existing Student" << endl;
		cout << "0. Exit Program" << endl;
		cout << "\n	Enter Operation Number: ";
		cin >> selection;
		
		switch(selection){
			//View Records Menu
			case 1:
				int newSelection;
				while(newSelection != 0){
					cout << "\n	VIEW RECORDS\n" << endl;
					cout << "1. View All Records" << endl;
					cout << "2. Search Records" << endl;
					cout << "0. Back to Main Menu" << endl;
					cout << "\n	Enter Operation Number: ";
					cin >> newSelection;

					switch(newSelection)
						{
							//View All Records
							case 1:
								printAllRecords();
								break;
							//Search Menu
							case 2:{
									int searchSelection;
									while(searchSelection != 0){
										cout << "\n	SEARCH BY...\n" << endl;
										cout << "1. Student ID" << endl;
										cout << "2. Student Name" << endl;
										cout << "0. Back to Previous Menu" << endl;	
										cout << "\n	Enter Query Type Number: ";
										cin >> searchSelection;
										
										switch(searchSelection){
											case 1:{
												cout << "Enter Student ID: ";
												cin >> query;
												validateID(query);
												searchRecords(query);
												break;
											}
											case 2:{
												cout << "Enter Student Name: ";
												cin.ignore();
												getline(cin, query);
												validateNameQuery(query);
												searchRecords(query);
												break;
											}
											case 0:
												cout << "\n	Exiting to Previous Menu\n" << endl;
												break;
											default:
												cout << "\nInvalid Selection\n" << endl;
										}
										if(searchSelection == 0){
											searchSelection = 9;
											break;
										}
									}
									break; }
							case 0:
								cout << "\n	Exiting to Main Menu\n" << endl;
								break;
							default:
								cout << "\nInvalid Operation\n" << endl;
							}
					if(newSelection == 0){
						newSelection = 9;
						break;
					}
				}
			break;

			//Enroll New Student Operation
			case 2:
				cout << "\n	ENROLL A NEW STUDENT\n" << endl;
				enrollStudent();
				break;
			//Remove Existing Student Operation
			case 3: cout << "\n REMOVE EXISTING STUDENT\n" << endl;
				cout << "Enter Student ID: ";\
				cin >> query;
				validateID(query);
				removeStudent(query);
				break;
			break;
			//Exit Program
			case 0:
				cout << "\nProgram Exited\n" << endl;
				return 0;
			default:
				cout << "\nInvalid Operation\n" << endl;
				break;
		}
	}	
	return 0;
}