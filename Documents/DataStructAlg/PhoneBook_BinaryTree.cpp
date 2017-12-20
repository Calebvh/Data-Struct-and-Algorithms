// DataStuctHw3.cpp : Defines the entry point for the console application.
//Authors:
//Caleb van Haaren
//Marcin Zubrowski
//Group 13

#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <assert.h>


/////////////////////////////////////////////////////////////////////////////////
class person {  //Node for each person in the Book
public:
	std::string firstName;
	std::string lastName;

	std::string phoneNumber;

	class person *left;
	class person *right;

	person();
	person(std::string, std::string, std::string);

};

//constructor1
person::person() {
	left = right = NULL;
}

//constructor2
person::person(std::string first, std::string last, std::string number) {
	firstName = first;
	lastName = last;
	phoneNumber = number;
	left = right = NULL;
}

/////////////////////////////////////////////////////////////////////////////////

class Book { //Class that performs all of the Phone book operations
public:
	void add(std::string, std::string, std::string);
	void del(std::string, std::string);
	person* find(std::string, std::string);
	person* findp(std::string, std::string);
	void change(std::string, std::string, std::string);
	void clear(person*);
	void inorder(person*);
	void display();
	void display1();
	void clearHelp();
	void save(person*);
	int nameParser(std::string, std::string, int);
	person* findInsertionSpot(std::string, std::string);
	person* findParentSpot(std::string, std::string);
	person* findReplacement(person*);

	person* root;

	Book::Book() {
		root = NULL;
	}

	~Book() {
		delete root;
	}
};
/////////////////////////////////////////////////////////////////////////////////
// Userinterface Prompt
////////////////////////////////////////////////////////////////////////////////
class userInterface {

public:
	void Start();
	int operations();
	std::string askFirstName();
	std::string askLastName();
	std::string askNum();

};

/////////////////////////////////////////////////////////////////////////////////
// Adds a New Contact to the book
////////////////////////////////////////////////////////////////////////////////
void Book::add(std::string firstName, std::string lastName, std::string number) {
	int newval, parentval;
	if (root == NULL) { //If it is the first entry set it as the root
		root = new person(firstName, lastName, number);
		std::cout << "Adding " << lastName << " , " << firstName << " as the Root" << std::endl;
	}
	else {
		person* p = findInsertionSpot(firstName, lastName); //Find where to put this person
		if (p == 0) { //If the spot is empty
			person* parent = root;
			if (p != root) {
				parent = findParentSpot(firstName, lastName); //Find the new persons parent node
			}
			int index = -1;
			do {
				index++;
				newval = nameParser(firstName, lastName, index);
				parentval = nameParser(parent->firstName, parent->lastName, index);
			} while (newval == parentval); //Parse the names so that the program can find the correct spot

			if (newval > parentval) { //send new person right if letter value is greater than parent
				parent->right = new person(firstName, lastName, number);
				std::cout << "Adding " << lastName << " , " << firstName << " To the right" << std::endl;
			}
			else { //send new person left if letter value is greater than parent
				parent->left = new person(firstName, lastName, number);
				std::cout << "Adding " << lastName << " , " << firstName << " To the left" << std::endl;
			}
		}

	}

}

/////////////////////////////////////////////////////////////////////////////////
// Deletes a Contact from the book
////////////////////////////////////////////////////////////////////////////////

void Book::del(std::string firstName, std::string lastName) {
	int newval, parentval;
	person* p = find(firstName, lastName);
	if (p != 0) { //If the node exists
		if (p->left == NULL && p->right == NULL) { //If the deleted node has no children
			if (p != root) { //If you aren't deleting the root
				person* parent = findp(firstName, lastName);

				int index = -1;
				do { //Parse the names if names have similar letters
					index++;
					newval = nameParser(firstName, lastName, index);
					parentval = nameParser(parent->firstName, parent->lastName, index);
				} while (newval == parentval); //Do this while the name values are still the same

				if (newval < parentval) { //If deletion is taking place left of the parent
					parent->left = NULL; //Reset pointer to null because there are no children to adopt
				}
				else { //If deletion is taking place left of the parent
					parent->right = NULL; //Reset pointer to null because there are no children to adopt
				}
			}
			else {
				root = NULL;
			}
			std::cout << std::endl;
			std::cout << "Deleting: " << lastName << ", " << firstName << "....." << std::endl;
			std::cout << std::endl;
			delete (p); //Delete the node
		}
		else if (p->left != NULL&&p->right == NULL) { //If the deleted node only has a left child
			if (p != root) { //If you aren't deleting the root
				person* parent = findp(firstName, lastName);

				int index = -1;
				do { //Parse the names if names have similar letters
					index++;
					newval = nameParser(firstName, lastName, index);
					parentval = nameParser(parent->firstName, parent->lastName, index);
				} while (newval == parentval); //Do this while the name values are still the same

				if (newval < parentval) { //If deletion is taking place left of the parent
					parent->left = p->left; //The left side takes the deleted node's children
				}
				else { //If deletion is taking place right of the parent
					parent->right = p->left; //The right side takes the deleted node's children
				}
			}
			else {
				root = NULL;
			}
			std::cout << std::endl;
			std::cout << "Deleting: " << lastName << ", " << firstName << "....." << std::endl;
			std::cout << std::endl;
			delete (p); //Delete the node
		}
		else if (p->left == NULL&&p->right != NULL) { //If the deleted node only has a right child
			if (p != root) { //If you aren't deleting the root
				person* parent = findp(firstName, lastName);

				int index = -1;
				do { //Parse the names if names have similar letters
					index++;
					newval = nameParser(firstName, lastName, index);
					parentval = nameParser(parent->firstName, parent->lastName, index);
				} while (newval == parentval); //Do this while the name values are still the same

				if (newval < parentval) { //If deletion is taking place left of the parent
					parent->left = p->right; //The left side takes the deleted node's children
				}
				else { //deletion is taking place right of the parent
					parent->right = p->right; //The right side takes the deleted node's children
				}
			}
			else {
				root = NULL;
			}
			std::cout << std::endl;
			std::cout << "Deleting: " << lastName << ", " << firstName << "....." << std::endl;
			std::cout << std::endl;
			delete (p); //Delete the node
		}
		else { //If the deleted node only has two children
			person* lowestGreatest = findReplacement(p->right); //Find the lowest number that is greater than the node being deleted
			person* parent = findp(lowestGreatest->firstName, lowestGreatest->lastName); //Find the parent of the lowest greater number
			std::cout << std::endl;
			std::cout << "Deleting: " << lastName << ", " << firstName << "....." << std::endl;
			std::cout << std::endl;
			p->firstName = lowestGreatest->firstName; //Swap the data in the node being "deleted"
			p->lastName = lowestGreatest->lastName;
			p->phoneNumber = lowestGreatest->phoneNumber;
			if (parent != p) { //If the data from lowest greatest hasn't replaced its parent nodes data then
				parent->left = lowestGreatest->right; //Parent takes the children of the node that has moved up
			}
			else { //If the data from lowest greatest has just replaced its parent nodes data i.e the right node moved up one spot
				p->right = lowestGreatest->right; //The right node takes in the old right person's children. 
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Iterates through a name based on the index
////////////////////////////////////////////////////////////////////////////////

int Book::nameParser(std::string firstName, std::string lastName, int index) {
	int value = 0;
	char temp = 0;

	if (index <= (lastName.length() - 1)) { //If the index is within the lenght of the person's last name
		value = lastName.at(index);
		temp = lastName.at(index);
	}
	else { //Switch to the first name to find searching value
		index = index - lastName.length();
		if (index <= (firstName.length() - 1)) {
			value = firstName.at(index);
			temp = firstName.at(index);
		}
		else { //If index exceeds length of the entire name. 
			assert("ERROR: You are trying to reach an a letter that doesn't exist");
			return 0;
		}
	}

	if (value > 122 || value < 65 || (value > 90 && value < 97)) { //Send out an error if there are incorrect characters entered
		assert("ERROR: You entered in your name incorrectly");
		return 0;
	}

	if (value > 96) { //If letter is a lowercase then change its value to its corresponding uppercase value
		value -= 32;
	}


	//std::cout << "Character: " << temp << "  Number : " << value << std::endl;
	return value;

}

/////////////////////////////////////////////////////////////////////////////////
// Finds where the node should be placed
////////////////////////////////////////////////////////////////////////////////
person* Book::findInsertionSpot(std::string first, std::string last) {
	person* p = root;
	int index = 0;
	while (p != NULL) { //While p is not Null
		int letter = nameParser(first, last, index); //Use name parser to find location by value
		if (letter < nameParser(p->firstName, p->lastName, index)) {
			p = p->left;
			index = 0;
		}
		else if (letter > nameParser(p->firstName, p->lastName, index)) { //Use name parser to find location by value
			p = p->right;
			index = 0;
		}
		else {  //(letter == nameParser(p->firstName, p->lastName, index)) //Increase index because values are the same
			index++;
			letter = nameParser(first, last, index);
		}
	}
	return p; //Return the node where p will be placed
}

/////////////////////////////////////////////////////////////////////////////////
// Finds where the parent of where the node should be placed
//Same operation as findInsertionSpot but takes a previous value of p
////////////////////////////////////////////////////////////////////////////////
person* Book::findParentSpot(std::string first, std::string last) {
	person* p = root;
	person* q = 0;
	int index = 0;
	while (p != NULL) {
		q = p;
		int letter = nameParser(first, last, index);
		if (letter < nameParser(p->firstName, p->lastName, index)) {
			p = p->left;
			index = 0;
		}
		else if (letter > nameParser(p->firstName, p->lastName, index)) {
			p = p->right;
			index = 0;
		}
		else { //(letter == nameParser(p->firstName, p->lastName, index)) {
			index++;
			letter = nameParser(first, last, index);
		}
	}
	return q;
}


/////////////////////////////////////////////////////////////////////////////////
// Finds a node based on the Name
////////////////////////////////////////////////////////////////////////////////
person* Book::find(std::string first, std::string last) {
	person* p = root;
	int index = 0;
	while (p != NULL) {
		int letter = nameParser(first, last, index);
		if (letter < nameParser(p->firstName, p->lastName, index)) {
			if (p->left == NULL) { //If the location where the node should be is empty
				return NULL;
			}
			p = p->left; //Searching left
			index = 0;
		}
		else if (letter > nameParser(p->firstName, p->lastName, index)) {
			if (p->right == NULL) { //If the location where the node should be is empty
				return NULL;
			}
			p = p->right; //Searching right
			index = 0;
		}
		else {  //(letter == nameParser(p->firstName, p->lastName, index)) {
			int length = first.length() + last.length();

			if (p->firstName == first && p->lastName == last) { //Checks if this is the node being searched for 
				return p;
			}

			index++; //Otherwise continue searching
			letter = nameParser(first, last, index);
		}
	}
	return p;
}

/////////////////////////////////////////////////////////////////////////////////
// Finds a node's parent based on the Name
// same operation as find but takes a the previous value of p when it finishes
////////////////////////////////////////////////////////////////////////////////
person* Book::findp(std::string first, std::string last) {
	person* p = root;
	person* q = p;
	int index = 0;
	while (p != NULL) {
		int letter = nameParser(first, last, index);
		if (letter < nameParser(p->firstName, p->lastName, index)) {
			if (p->left == NULL) { //If the location where the node should be is empty
				std::cout << "Could not find Parent" << std::endl;
				return p;
			}
			q = p;
			p = p->left; //Searching left
			index = 0;
		}
		else if (letter > nameParser(p->firstName, p->lastName, index)) {
			if (p->right == NULL) { //If the location where the node should be is empty
				std::cout << "Could not find Parent" << std::endl;
				return p;
			}
			q = p;
			p = p->right; //Searching right
			index = 0;
		}
		else {  //(letter == nameParser(p->firstName, p->lastName, index)) {
			int length = first.length() + last.length();

			if (p->firstName == first && p->lastName == last) { //Checks if this is the node being searched for 
				return q;
			}

			index++; //Otherwise continue searching
			letter = nameParser(first, last, index);
		}
	}
	return p;

}

/////////////////////////////////////////////////////////////////////////////////
// Traverses the Tree using the inorder traversal
////////////////////////////////////////////////////////////////////////////////
int number = 0;
void Book::inorder(person* p) {
	if (p != NULL) {
		inorder(p->left);
		int length = p->firstName.length() + p->lastName.length();
		int spacing = 30 - length; //Finds a number that will set all of the phone numbers flush
		number++;
		if (number < 10)std::cout << number << ".  "; //adjusting for spacing from the numbers
		if (number >= 10)std::cout << number << ". ";
		std::cout << p->lastName << ", ";
		std::cout << p->firstName;
		for (int i = 0; i < spacing; i++) std::cout << " "; // implements the number of spaces that will set all of the phone numbers flush
		std::cout << p->phoneNumber << std::endl;
		inorder(p->right);
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Traverses the Tree and deletes the nodes
///////////////////////////////////////////////////////////////////////////////
void Book::clear(person* p) { //Uses postorder to delete the entire tree
	if (p != NULL) {
		clear(p->left);
		clear(p->right);
		del(p->firstName, p->lastName);
	}
}

void Book::clearHelp() {
	clear(root);
}

/////////////////////////////////////////////////////////////////////////////////
// Easier function to call inorder
////////////////////////////////////////////////////////////////////////////////
void Book::display() {
	inorder(root);
}

/////////////////////////////////////////////////////////////////////////////////
// Easier function to call Save
////////////////////////////////////////////////////////////////////////////////
void Book::display1() {
	save(root);
}

/////////////////////////////////////////////////////////////////////////////////
// function to find what node is replacing the deleted node in the tree
////////////////////////////////////////////////////////////////////////////////
person* Book::findReplacement(person* delNode) { //Gets the right child of the deleted node
	person* replacement = delNode;

	while (replacement->left != NULL) { //Finds the lowest value on that side of the tree
		replacement = replacement->left;
	}
	return replacement; //Returns that lowest value that is greater than the value being deleted
}

/////////////////////////////////////////////////////////////////////////////////
// Function that finds a person and changes his number
////////////////////////////////////////////////////////////////////////////////
void Book::change(std::string first, std::string last, std::string newnum) {
	person* p = find(first, last);
	p->phoneNumber = newnum;
	std::cout << p->firstName << "'s number has been sucessfully changed" << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////
// Function that saves the entire Tree
////////////////////////////////////////////////////////////////////////////////
std::ofstream myfile;
void Book::save(person* p) {
	if (p != NULL) {
		save(p->left); //Uses inorder to traverse tree
		std::cout << "Saving......" << std::endl;
		std::cout << p->firstName << " ";
		std::cout << p->lastName << std::endl;
		//std::cout << p->phoneNumber << std::endl;
		myfile.open("saved.txt", std::ios_base::app); //Opens the file that is storing the book
		myfile << p->firstName;
		myfile << " ";
		myfile << p->lastName; //Insert name and number in the correct readable format
		myfile << "\n";
		myfile << p->phoneNumber;
		myfile << "\n";
		myfile.close(); //Close the file until the next value needs to be saved. 
		save(p->right); //Traverse tree using inorder
	}
}

/////////////////////////////////////////////////////////////////////////////////
// Clears the saved file for another save to occur
////////////////////////////////////////////////////////////////////////////////
void clearFile() {
	std::ofstream myfile("saved.txt");
	myfile.close();
}



/////////////////////////////////////////////////////////////////////////////////

void userInterface::Start() {
	std::cout << "=============================================================================" << std::endl;
	std::cout << "Welcome to Homework 3: Binary Search Trees and Implementing" << std::endl;
	std::cout << "an Electronic Phone Book" << std::endl;
	std::cout << "Authors: " << std::endl;
	std::cout << "Caleb van Haaren " << std::endl;
	std::cout << "Marcin Zubrowski " << std::endl;
	std::cout << std::endl;
	std::cout << "In this program you will create a electronic phone book using a" << std::endl;
	std::cout << " binary tree, by entering in names and phone numbers for the program to sort" << std::endl;
	std::cout << "=============================================================================" << std::endl;
	std::cout << std::endl;
}

int userInterface::operations() {
	int temp;
	std::cout << "================================" << std::endl;
	std::cout << " Phonebook Operations" << std::endl;
	std::cout << " 1. Add Contact" << std::endl;
	std::cout << " 2. Delete Contact" << std::endl;
	std::cout << " 3. Find Contact" << std::endl;
	std::cout << " 4. Change Contact's Number" << std::endl;
	std::cout << " 5. Printout Phone Book" << std::endl;
	std::cout << " 6. Restore saved phone book" << std::endl;
	std::cout << " 7. Create Starter phone book" << std::endl;
	std::cout << " 8. Save phone book" << std::endl;
	std::cout << " 9. Quit" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << " Enter your operation: ";
	std::cin >> temp;
	return temp;

}

/////////////////////////////////////////////////////////////////////////////////
// Asks user for the first name
////////////////////////////////////////////////////////////////////////////////
std::string userInterface::askFirstName() {
	std::string first;
	std::cout << "Please enter the first name:" << std::endl;
	std::cin >> first;
	return first;
}

/////////////////////////////////////////////////////////////////////////////////
// Asks user for the last name
////////////////////////////////////////////////////////////////////////////////
std::string userInterface::askLastName() {
	std::string last;
	std::cout << "Please enter the last name:" << std::endl;
	std::cin >> last;
	return last;
}

/////////////////////////////////////////////////////////////////////////////////
// Asks user for the phone number
////////////////////////////////////////////////////////////////////////////////
std::string userInterface::askNum() {
	std::string num;
	std::cout << "Please enter the phone number:" << std::endl;
	std::cin >> num;
	return num;
}


/////////////////////////////////////////////////////////////////////////////////

int main()
{
	Book Tree;
	userInterface User;

	User.Start();
	bool cont = true;

	while (cont == true) { //Loops until user wants to quit
		int i = User.operations(); //Takes in users input for which function

		switch (i) {
		case 1:
		{
			std::cout << "You have chosen to Add a contact" << std::endl;
			std::string first = User.askFirstName();
			std::string last = User.askLastName();
			std::string num = User.askNum();

			person* temp = Tree.find(first, last);
			if (temp == NULL) {
				Tree.add(first, last, num);
			}
			else {
				std::cout << std::endl;
				std::cout << "Sorry, This name already exists in the tree" << std::endl;
			}

			break;
		}
		case 2:
		{
			std::cout << "You have chosen to Delete a contact" << std::endl;
			std::string first = User.askFirstName();
			std::string last = User.askLastName();

			Tree.del(first, last);
			break;
		}
		case 3:
		{
			std::cout << "You have chosen to Find a contact" << std::endl;
			std::string first = User.askFirstName();
			std::string last = User.askLastName();

			person* temp = Tree.find(first, last);
			if (temp == NULL) {
				std::cout << "Sorry this name does not exist in the tree" << std::endl;
			}
			else {
				std::cout << std::endl;
				std::cout << "This name exists in the tree" << std::endl;
			}
			break;
		}
		case 4:
		{
			std::cout << "You have chosen to Change a contact's number" << std::endl;
			std::string first = User.askFirstName();
			std::string last = User.askLastName();
			std::string num = User.askNum();

			person* temp = Tree.find(first, last);
			if (temp == NULL) {
				Tree.change(first, last, num);
			}
			else {
				std::cout << std::endl;
				std::cout << "Sorry, This name already exists in the tree" << std::endl;
			}
			break;
		}
		case 5:
		{
			std::cout << "You have chosen to Print out the Phonebook" << std::endl;
			std::cout << "==============================================" << std::endl;
			std::cout << "   Last Name, First Name	       Number" << std::endl;
			std::cout << "==============================================" << std::endl;
			number = 0;
			Tree.display();
			break;
		}
		case 6:
		{
			std::cout << "You have chosen to Restore a saved phonebook" << std::endl;
			Tree.clearHelp();

			std::ifstream inFile;
			std::string x, first, last, num;
			int index = 0;

			inFile.open("saved.txt");
			if (!inFile) {
				std::cout << "Unable to open file" << std::endl;
				exit(1); // terminate with error
			}
			if (inFile.is_open()) {
				while (!inFile.eof()) {
					inFile >> x;

					if (index == 0) {
						first = x;
						index++;
					}
					else if (index == 1) {
						last = x;
						index++;
					}
					else if (index == 2) {
						num = x;
						person* temp = Tree.find(first, last);
						if (temp == NULL) {
							Tree.add(first, last, num);
						}
						else {
							std::cout << std::endl;
							std::cout << "Sorry, This name already exists in the tree" << std::endl;
						}
						index = 0;
					}
				}
			}

			break;
		}
		case 7:
		{
			std::cout << "You have chosen to create a starter phonebook" << std::endl;
			Tree.clearHelp();
			std::ifstream inFile;
			std::string x, first, last, num;
			int index = 0;

			inFile.open("test.txt");
			if (!inFile) {
				std::cout << "Unable to open file" << std::endl;
				exit(1); // terminate with error
			}
			if (inFile.is_open()) {
				while (!inFile.eof()) {
					inFile >> x;

					if (index == 0) {
						first = x;
						index++;
					}
					else if (index == 1) {
						last = x;
						index++;
					}
					else if (index == 2) {
						num = x;
						Tree.add(first, last, num);
						index = 0;
					}
				}
			}
			break;
		}
		case 8:
		{
			std::cout << "You have chosen to save your phonebook" << std::endl;
			clearFile();
			Tree.display1();
			break;
		}

		case 9:
			std::cout << "Quitting...." << std::endl;
			cont = false;

			break;
		default:
			std::cout << "That was not a Correct value" << std::endl;
			std::cout << "Quitting...." << std::endl;
			cont = false;
			break;
		}
	}

	return 0;
}


