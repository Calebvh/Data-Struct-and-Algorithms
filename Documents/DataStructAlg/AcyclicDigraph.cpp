// Homework4.cpp : Defines the entry point for the console application.
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
#include <stack>
#include <queue>
#include <vector>

std::stack<int> GlobalStack;
std::vector<int> Globalvector;

///////////////////////////////////////////////////////
// Structure and Class for t0he adjacency
//////////////////////////////////////////////////////

struct ListNode {
	bool IsPointedAt;
	int adjacentNodes;
	struct ListNode* next;

};

///////////////////////////////////////////////////////
// Structure and Class for the Main Linked list
//////////////////////////////////////////////////////
struct MainListNodes {
	int actualNode;
	bool visited;
	struct MainListNodes* next;
	struct ListNode* connections;
	std::string task;

};

class MainList {

public:
	MainListNodes *head;
	MainListNodes *tail;

	MainList() {
		head = NULL;
		tail = NULL;
	}
};

///////////////////////////////////////////////////////
// Digraph Class
//////////////////////////////////////////////////////

class Digraph {
private:
	MainListNodes* mainHeader;

public:
	void edgeAddition(int,int);
	void edgeDeletion(int,int);
	void deleteHelper(ListNode*, ListNode*, int);
	void acyclicCheck(MainListNodes*, int);
	void topsortHelp(MainListNodes*);
	void topsort(int);

	void addNodes(int);
	void printLinkedList();
	MainListNodes* find(int);
	ListNode* findAdj(ListNode*, int);
	ListNode* findPrev(ListNode*, int);
	MainListNodes* getHeader();

	Digraph() {
		mainHeader = NULL;
	}

};

///////////////////////////////////////////////////////
// Finds the Size of the List
//////////////////////////////////////////////////////

//Iterates Through main linked list to find the size
int FindSize(MainListNodes* header) { 
	int size = 0;
	while (header != NULL) {
		size = header->actualNode;
		header = header->next;
	}
	return size;
}


//Iterates Through adjacent linked list to find the size
int FindSizeAdj(ListNode* header) {
	int size = 0;
	while (header != NULL) {
		size++;
		header = header->next;
	}
	return size;
}


///////////////////////////////////////////////////////
// Digraph functions
//////////////////////////////////////////////////////

//Returns the main header of the Class
MainListNodes* Digraph::getHeader() {
	return mainHeader;
}

//Creates all of the vectors to be used in your graph
void Digraph::addNodes(int size) {
	MainList newList;
	char t[100];
	for (int i = 1; i <= size; i++) {
		MainListNodes *temp = new MainListNodes;
		temp->actualNode = i; //Setting Vertex to iteration number
		temp->next = NULL;  //Rest of values initialized to NULL
		temp->connections = NULL;
		temp->visited = false;
		std::cout << "Please indicate Task " << i-1 << " : ";
		if( i == 1) std::cin.ignore();
		std::cin.getline(t, 100);
		temp->task = t;
		if (newList.head == NULL) {
			newList.head = temp; //Setting Vertex to the Head of the class
			newList.tail = temp;

		}
		else { //Adding Vertex to the end of the List
			newList.tail->next = temp;
			newList.tail = temp;

		}
	}

	mainHeader = newList.head; //Setting Digraph's mainHeader to the Vertex list head
}

///////////////////////////////////////////////////////
// Prints out Graph
//////////////////////////////////////////////////////
void Digraph::printLinkedList(){
	MainListNodes* helper = mainHeader; //Get Main Header
	std::cout << "-----------------------------------------" << std::endl;
	while (helper != NULL) { 
		
		std::cout << "Header: |" << helper->actualNode -1 << "|"; //Get Vertex
		ListNode* helperAdj = helper->connections; //Go to Vertex's adjacency list
		while (helperAdj != NULL) {
			
			std::cout << " -> " << helperAdj->adjacentNodes - 1 ; //Print out Adjacent nodes
			//A one is subtracted because 0's are stored as ones to avoid any NULL confusion
			helperAdj = helperAdj->next;
			
		}
		std::cout << std::endl;
		helper = helper->next; //Go to next Vertex

	}

	std::cout << "-----------------------------------------" << std::endl;
	std::cout << std::endl;

}


///////////////////////////////////////////////////////
// Finds vertex based on a value
//////////////////////////////////////////////////////
MainListNodes* Digraph::find(int whichNode) {
	MainListNodes* helper = mainHeader; //Get main header
	while (helper != NULL) {

		if (helper->actualNode == whichNode) { //If pointer is the Vertex searched for
			return helper;
		}
		else {
			helper = helper->next; // Go to the Next Vertex
		}
	}

	std::cout << "Sorry the Node is not in this graph" << std::endl;
	return 0;

}


///////////////////////////////////////////////////////
// Finds adjacent vertex based on a value
//////////////////////////////////////////////////////
ListNode* Digraph::findAdj(ListNode* header, int whichNode) {
	ListNode* helper = header; //Header of adjacent list
	while (helper != NULL) {

		if (helper->adjacentNodes == whichNode) { //If pointer is the Vertex searched for
			return helper; 
		}
		else {
			helper = helper->next; //Next adjacent node
		}
	}

	std::cout << "Sorry the Edge is not in this graph" << std::endl;
	return 0;

}

///////////////////////////////////////////////////////
// Finds the previous vertex based on a value
//////////////////////////////////////////////////////
ListNode* Digraph::findPrev(ListNode* header, int whichNode) {
	int count = 0;
	ListNode* helper = header;
	ListNode* prev = header;


	while (helper != NULL) {
		if (helper->adjacentNodes == whichNode) {
			return prev;
		}
		else {
			helper = helper->next;
			if (count != 0) prev = prev->next; //If it is the first node then
			//Don't increment the previous pointer 
			// This puts the prev point one node behind the helper
		}
	}

	std::cout << "This Shouldn't Occur" << std::endl;
	return 0;

}

///////////////////////////////////////////////////////
// Creates an edge from Vertex to Vertex
//////////////////////////////////////////////////////
void Digraph::edgeAddition(int from, int to) {
	MainListNodes* VertexFrom = find(from); //Find vertex
	if (VertexFrom == 0) {
		std::cout << "Returning to menu" << std::endl;
		return;
	}

	//Attach the "to" node to the Adj list
	//---------------------------------------------------
	if (VertexFrom->connections == NULL) {  //If list is empty, add it to the front
		ListNode* temp = new ListNode;
		temp->IsPointedAt = true;
		temp->adjacentNodes = to;
		temp->next = NULL;
		VertexFrom->connections = temp;
	}
	else { //else push the list back and add node as the first in the Adj list
		ListNode* temp = new ListNode;
		temp->IsPointedAt = true;
		temp->adjacentNodes = to;
		ListNode* temp1 = VertexFrom->connections;
		VertexFrom->connections = temp;
		temp->next = temp1;

	}
	//Attach the "from" node to the Adj list
	//------------------------------------------------------
	MainListNodes* VertexTo = find(to);
	if (VertexTo == 0) {
		std::cout << "Returning to menu" << std::endl;
		return;
	}

	if (VertexTo->connections == NULL) { //If list is empty, add it to the front
		ListNode* temp = new ListNode;
		temp->IsPointedAt = false;
		temp->adjacentNodes = from;
		temp->next = NULL;
		VertexTo->connections = temp;
		std::cout << "You created the edge: " << from -1 << "->" << to -1 << std::endl;
	}
	else { //else push the list back and add node as the first in the Adj list
		ListNode* temp = new ListNode;
		temp->IsPointedAt = false;
		temp->adjacentNodes = from;
		ListNode* temp1 = VertexTo->connections;
		VertexTo->connections = temp;
		temp->next = temp1;
		std::cout << "You created the edge: " << from -1 << "->" << to-1 << std::endl;

	}
}


///////////////////////////////////////////////////////
// Deletes an Existing Edge
//////////////////////////////////////////////////////
void Digraph::edgeDeletion(int from, int to) {
	
	//Deleting the "to" Node
	//-------------------------------------------------------------------------
	MainListNodes* VertexFrom = find(from); //Find Vertex with adjacent "to" node"
	if (VertexFrom == 0) { //If node doesn't exist
		std::cout << "Returning to menu" << std::endl;
		return;
	}
	if (VertexFrom->connections == NULL) { //If Vertex is found but Adjacency List is Empty
		std::cout << "This Edge does not exist" << std::endl;
		return;
	}
	if (to == VertexFrom->connections->adjacentNodes) { //if "to" is found in "from"'s adjacency list in the first location
		if (VertexFrom->connections->next != NULL) {  //If the Adjacencents Vertex had more than one node
			ListNode* temp = VertexFrom->connections; //Reconnect List and delete node
			VertexFrom->connections = temp->next;
			delete(temp);
		}
		else {
			ListNode* temp = VertexFrom->connections; //If there is only one node in the adjacency list
			VertexFrom->connections = NULL;			//Delete node
			delete(temp);
		}
	}
	else { //Find the Node in the Adjacency list
		bool correct = false;
		ListNode* nodeToBeDeleted = NULL;
		MainListNodes* VertexFrom = find(from); //Find "from" Vertex
		if (VertexFrom == 0) {
			std::cout << "Returning to menu..." << std::endl;
			return;
		}
		ListNode* help = VertexFrom->connections; //helper pointer
		while (!correct) {

			nodeToBeDeleted = findAdj(help, to); //Find the adjacent Node
			if (nodeToBeDeleted == 0) {
				std::cout << "Returning to menu..." << std::endl;
				return;
			}
			if (nodeToBeDeleted->IsPointedAt == true) { //If it is the correct vector
				correct = true;
			}
			help = help->next; //Else move the pointer
		}
		deleteHelper(VertexFrom->connections, nodeToBeDeleted, to); //Find The node and delete it
	}

	//Deleting the "from" Node
	//-------------------------------------------------------------------------
	//This is the same as the previous deletion of the "to" node
	MainListNodes* VertexTo = find(to);
	if (VertexTo == 0) {
		std::cout << "Returning to menu" << std::endl;
		return;
	}
	if (VertexFrom->connections == NULL) { //If Vertex is found but Adjacency List is Empty
		std::cout << "This Edge does not exist" << std::endl;
		return;
	}
	if (from == VertexTo->connections->adjacentNodes) {
		if (VertexTo->connections->next != NULL) {
			ListNode* temp = VertexTo->connections;
			VertexTo->connections = temp->next;
			delete(temp);
		}
		else {
			ListNode* temp = VertexTo->connections;
			VertexTo->connections = NULL;
			delete(temp);
		}
		std::cout << "You deleted the edge: " << from -1 << "->" << to -1 << std::endl;
	}
	else {
		bool correct = false;
		ListNode* nodeToBeDeleted1 = NULL;
		MainListNodes* VertexTo = find(to);
		if (VertexTo == 0) {
			std::cout << "Returning to menu" << std::endl;
			return;
		}
		ListNode* help = VertexTo->connections;
		while (!correct) {

			nodeToBeDeleted1 = findAdj(help, from);
			if (nodeToBeDeleted1 == 0) {
				std::cout << "Returning to menu" << std::endl;
				return;
			}

			if (nodeToBeDeleted1->IsPointedAt == false) {
				correct = true;
			}
			else if (help->next != NULL) help = help->next;

		}
		deleteHelper(VertexTo->connections, nodeToBeDeleted1, from);
		std::cout << "You deleted the edge: " << from-1 << "->" << to-1 << std::endl;
	}
}

//Helps to delete the Nodes
void Digraph::deleteHelper(ListNode* header, ListNode* node, int num) { 
	if (node->next == NULL) { //If the node is at the end of the list
		std::cout << "The previous node is: " << std::endl;
		ListNode* prev = findPrev(header, num); //find the previous node
		prev->next = NULL; //Set its pointer to NULL 
		delete(node); 
	}
	else { //Else reconnect the pointers around the node and then delete
		ListNode* prev = findPrev(header, num);
		
		prev->next = node->next;
		delete(node);
	}
}


///////////////////////////////////////////////////////
//Checks to see if Graph is Acyclic
//////////////////////////////////////////////////////
void Digraph::acyclicCheck(MainListNodes* Vertex, int start) {
	
	MainListNodes* helperheader = mainHeader; //Get Headers
	ListNode* vertexAdjHelper = Vertex->connections;
	
	int size = FindSizeAdj(vertexAdjHelper); //Find the size of Adj list
	vertexAdjHelper = Vertex->connections; 
	for (int j = 1; j <= size; j++) {
		if (vertexAdjHelper->IsPointedAt == true) { //If the node is pointed too
			//Then we can travel to that node
			MainListNodes* Node = find(vertexAdjHelper->adjacentNodes);
			if (Node == 0) {
				std::cout << "Returning to menu" << std::endl;
				return;
			}

			if (Node->actualNode == start) { //If node is the one we are looking for then 
				Globalvector.push_back(0); //Then push back a 0 indicating a cycle
				return;
			}
			acyclicCheck(Node, start); //Else travel to that node and repeat
			
		}
		
		vertexAdjHelper = vertexAdjHelper->next; //Else check the next node in the list
	}

	//std::cout << "This Graph is Acyclic!" << std::endl;
	Globalvector.push_back(1);
	return;
}


///////////////////////////////////////////////////////
// Recursive function used to sort 
//////////////////////////////////////////////////////
void Digraph::topsortHelp(MainListNodes* Vertex) { 

	ListNode* vertexAdjHelper = Vertex->connections; //Get front of Adj list
	int size1 = FindSizeAdj(vertexAdjHelper); //Find size of the list
	
	vertexAdjHelper = Vertex->connections;
	for (int j = 1; j <= size1; j++) {
		if (vertexAdjHelper->IsPointedAt == true) { //If the node is being pointed at
			MainListNodes* Node = find(vertexAdjHelper->adjacentNodes); //travel to that Vertex

			if (Node->visited == false) { //And if it hasn't been visited
				topsortHelp(Node); //Visit it and repeat
			}
				
		}
		vertexAdjHelper = vertexAdjHelper->next;//Else go to next node in adj list
	}
	Vertex->visited = true; //Once all adj have been visited, original vertext is set to visited
	GlobalStack.push(Vertex->actualNode); //push onto the stack

}

///////////////////////////////////////////////////////
// Main Sorting algorithm
//////////////////////////////////////////////////////
void Digraph::topsort(int start) {
	int size = 0;
	int size1 = 0;
	MainListNodes* headerHelper = mainHeader;
	while (headerHelper != NULL) { //Sets all nodes to not visited and finds size
		headerHelper->visited = false;
		size = headerHelper->actualNode;
		headerHelper = headerHelper->next;
	}

	MainListNodes* Vertex = find(start); //Finds the Vertex Where the sort is started
	if (Vertex == 0) {
		std::cout << "Returning to menu" << std::endl;
		return;
	}
	if (Vertex->visited == false) {
		topsortHelp(Vertex);
	}
	

	for (int i = 1; i <= size; i++) { //For every node in the Graph, perform the same sort	

		MainListNodes* Vertex = find(i); //Travel to that node next to be sorted
		
		if (Vertex->visited == false && Vertex->connections != NULL) {
			topsortHelp(Vertex);
		}
	}
	
	std::queue<int> temp;
	//Unload Stack and show the sorted order. 
	while (GlobalStack.empty() == false) {
		std::cout << GlobalStack.top()- 1 << " ";
		
		temp.push(GlobalStack.top());
		GlobalStack.pop();
	}

	std::cout << std::endl;
	std::cout << std::endl;
	while (temp.empty() == false) {
		std::cout << "Task " << temp.front() - 1 <<" : ";
		MainListNodes* vector = find(temp.front());
		std::cout << vector->task << std::endl;
		temp.pop();
	}


	std::cout << std::endl;

}

///////////////////////////////////////////////////////
// Checks all Vertexes for Acyclic and then returns a bool
//////////////////////////////////////////////////////
bool Acyclic(Digraph Graph) {
	MainListNodes* head = Graph.getHeader(); //Get headers
	MainListNodes* headerHelper = head;
	int size = FindSize(headerHelper); //find size of graph

	for (int j = 1; j <= size; j++) { //Performs a check of the graph from all verteces
		MainListNodes* head = Graph.find(j); 
		Graph.acyclicCheck(head, j);
		//Search the vector and if there is a 0 then return false
		for (std::vector<int>::const_iterator i = Globalvector.begin(); i != Globalvector.end(); ++i) {
			if (*i == 0) {
				return false;
			}
		}
	}
	//Else return true
	Globalvector.clear();
	return true;

}

///////////////////////////////////////////////////////
//User Interface Functions
///////////////////////////////////////////////////////

void Start() {
	std::cout << "=============================================================================" << std::endl;
	std::cout << "Welcome to Homework 4: Topography Search Trees" << std::endl;
	std::cout << "Authors: " << std::endl;
	std::cout << "Caleb van Haaren " << std::endl;
	std::cout << "Marcin Zubrowski " << std::endl;
	std::cout << std::endl;
	std::cout << "In this program you will create an Directed Acyclic Graph (DAG)" << std::endl;
	std::cout << "by created Vertex's and edges that the program will use to Sort the graph" << std::endl;
	std::cout << "=============================================================================" << std::endl;
	std::cout << std::endl;
}

int operations() {
	int temp;
	std::cout << "================================" << std::endl;
	std::cout << " DAG Operations" << std::endl;
	std::cout << " 1. Create vectors" << std::endl;
	std::cout << " 2. Create Edges " << std::endl;
	std::cout << " 3. Delete Edges" << std::endl;
	std::cout << " 4. Print out the graph" << std::endl;
	std::cout << " 5. Topography Sort" << std::endl;
	std::cout << " 6. Quit" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << " Enter your operation: ";
	std::cin >> temp;
	return temp;
}

int AskNumVectors() {
	int last;
	std::cout << "Please enter the number of vectors in your Graph:" << std::endl;
	std::cin >> last;
	return last;
}


int AskEdgeFrom() {
	int edge;
	std::cout << "Please enter the number your edge is pointing from:" << std::endl;
	std::cin >> edge;
	return edge;
}

int AskEdgeTo() {
	int edge;
	std::cout << "Please enter the number your edge is pointing To:" << std::endl;
	std::cin >> edge;
	return edge;
}

int AskStartPoint() {
	int edge;
	std::cout << "Please enter the vector you wish to start your sort at:" << std::endl;
	std::cin >> edge;
	return edge;
}


///////////////////////////////////////////////////////
// Main 
//////////////////////////////////////////////////////

int main()
{
	Start();
	Digraph Graph;


	bool cont = true;

	while (cont == true) { //Loops until user wants to quit
		int i = operations(); //Takes in users input for which function

		switch (i) {
		case 1:
		{
			std::cout << "You have chosen to Create your vectors" << std::endl;
			std::cout << "==============================================" << std::endl;
			int num = AskNumVectors();
			Graph.addNodes(num);
			std::cout << "Created " << num << " vectors" << std::endl;
			break;
		}
		case 2:
		{
			std::cout << "You have chosen to create an edge" << std::endl;
			std::cout << "==============================================" << std::endl;
			int from = AskEdgeFrom();
			int to = AskEdgeTo();

			Graph.edgeAddition(from + 1, to + 1);
			break;
		}
		case 3:
		{
			std::cout << "You have chosen to Delete an Edge" << std::endl;
			std::cout << "==============================================" << std::endl;
			int from = AskEdgeFrom();
			int to = AskEdgeTo();
			
			Graph.edgeDeletion(from + 1, to +1 );

			break;
		}
		case 4:
		{
			std::cout << "You have chosen to Print out the Graph" << std::endl;
			std::cout << "==============================================" << std::endl;
			std::cout << "  Vectors   	       Adjacent Vectors" << std::endl;
			std::cout << "==============================================" << std::endl;
			Graph.printLinkedList();
			std::cout << std::endl;

			break;
		}
		case 5:
		{
			std::cout << "You have chosen to Sort the Graph" << std::endl;
			std::cout << "==============================================" << std::endl;
			int start = AskStartPoint();
			bool A = Acyclic(Graph);
			if (A == true) {
				std::cout << "Your graph is Acyclic!" << std::endl;
				std::cout << "Sorting......"<<std::endl;
				Graph.topsort(start + 1);
			}
			else {
				std::cout << "Sorry your graph is Not Acyclic..." << std::endl;
			}
			break;
		}
		case 6:
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

/*	

	Graph.addNodes(15);
	
	Graph.edgeAddition(2, 12);
	Graph.edgeAddition(2, 11);
	Graph.edgeAddition(2, 1);
	
	Graph.edgeAddition(3, 2);
	Graph.edgeAddition(3, 4);
	
	Graph.edgeAddition(5, 4);
	
	Graph.edgeAddition(6, 15);
	Graph.edgeAddition(6, 14);
	Graph.edgeAddition(6, 13);
	Graph.edgeAddition(6, 7);
	Graph.edgeAddition(6, 5);

	Graph.edgeAddition(7, 12);

	Graph.edgeAddition(8, 12);
	Graph.edgeAddition(8, 11);
	Graph.edgeAddition(8, 10);
	Graph.edgeAddition(8, 9);
	Graph.edgeAddition(8, 7);

	Graph.edgeAddition(9, 1);

	Graph.edgeAddition(11, 12);
	Graph.edgeAddition(11, 1);
	
	Graph.edgeAddition(14, 3);
	Graph.edgeAddition(14, 2);
	
	Graph.edgeAddition(15, 5);
	Graph.edgeAddition(15, 3);
	
	bool A = Acyclic(Graph);

	Graph.printLinkedList();
	Graph.topsort(5);*/

    return 0;
}

