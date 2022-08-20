#include "Student.h"
#include <iostream>
#include <fstream>

Student::Student()
{
	setID(999999);
	setFirstName("New");
	setLastName("Student");
	setYear(1);
	setAge(18);
	setGPA(4.00);
}

Student::Student(int _ID, string _firstName, string _lastName, int _year, int _age, double _GPA)
{
	setID(_ID);
	setFirstName(_firstName);
	setLastName(_lastName);
	setYear(_year);
	setAge(_age);
	setGPA(_GPA);
}

int Student::getID() const {
	return ID;
}

string Student::getFirstName() const {
	return firstName;
}

string Student::getLastName() const {
	return lastName;
}

string Student::getYear() const {
	return year;
}

int Student::getAge() const {
	return age;
}

double Student::getGPA() const {
	return GPA;
}


void Student::setID(int _ID) {
	ID = _ID;
}

//This function ensures that the entered string only has alphabet charaters -- displays error message and accepts user input otherwise
void Student::setFirstName(string _firstName) {
	bool flag;
	do{
		flag = 0;
		for(int c = _firstName.length()-1; c >= 0; c--){
			if(isalpha(_firstName[c]) == 0){
				flag =1 ;
			}
		}
		if(flag == 1){
			cout << "Invalid Student First Name (Enter Only Alphabet Characters)\nFirst Name: ";
			cin >> _firstName;
		}
	}while(flag != 0);
	firstName = _firstName;
}

//This function ensures that the entered string only has alphabet charaters -- displays error message and accepts user input otherwise
void Student::setLastName(string _lastName) {
	bool flag;
	do{
		flag = 0;
		for(int c = _lastName.length()-1; c >= 0; c--){
			if(isalpha(_lastName[c]) == 0){
				flag = 1;
			}
		}
		if(flag == 1){
			cout << "Invalid Student Last Name (Enter Only Alphabet Characters)\nLast Name: ";
			cin >> _lastName;
		}
	}while(flag != 0);
	lastName = _lastName;
}

//This function converts the numerical input value to the corresponding year term -- displays error message and accepts user input otherwise
void Student::setYear(int _year) {
	do{
		while(cin.fail()){
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Student Year (Enter 1, 2, 3, or 4)\nYear: ";
			cin >> _year;
		};
		switch(_year){
			case 1: year = "Freshman"; break;
			case 2: year = "Sophomore"; break;
			case 3: year = "Junior"; break;
			case 4: year = "Senior"; break;
			default:
				cout << "Invalid Student Year (Enter 1, 2, 3, or 4)\nYear: ";
				cin >> _year;
			}
		}while(_year < 1 || _year > 4);
}

//This function ensures that the entered number is within 18 and 100 -- displays error message and accepts user input otherwise
void Student::setAge(int _age) {
	bool flag;
	do{

		flag = 0;
			if(_age < 18 || _age > 100){
				flag = 1;
			}
			if(cin.fail()){
				flag = 1;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			if(flag == 1)
			{
				cout << "Invalid Student Age\nAge: ";
				cin >> _age;
			}
		}while(flag != 0);
	age = _age;
}

//This function ensures that the entered number is within 0 and 4 -- displays error message and accepts user input otherwise
void Student::setGPA(double _GPA) {
	bool flag;
	do{
		flag = 0;
		if(_GPA < 0 || _GPA > 4){
			flag = 1;
		}
		if(cin.fail()){
			flag = 1;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		if(flag == 1){
			cout << "Invalid Student GPA (Enter On 4.0 Scale)\nGPA: ";
			cin >> _GPA;
		}
	}while(flag != 0);
	GPA = _GPA;
}