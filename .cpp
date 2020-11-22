// DataStructuresProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<iomanip>
using namespace std;

struct Student{
	int sID;
	string fName;
	string lName;
	string dept;
	int busNo;
	Student *prev;
	Student *next;
};

struct Bus{
	int busNo;
	string plateNo;
	string route;
	int dID;
	double time;
};

struct driver{
	int dID;
	string fName;
	string lName;
	int busNo;
	driver *left;
	driver *right;
};

class WaitingList
{
private:
	Student* head;
	Student* tail;
	int counter;

public:
	WaitingList::WaitingList()
	{
		counter = 0;
		head = NULL;
		tail = NULL;
	}

	void WaitingList::enQueueStudent()
	{
		int n;
		cout << "How many students do you want to add?" << endl;
		cin >> n;
		counter = counter + n;
		ifstream myfile;
		myfile.open("studentdata.txt");
		cout << "Enter Student ID:" << endl;
		cout << "Enter First Name:" << endl;
		cout << "Enter Last Name:" << endl;
		cout << "Enter Department:" << endl;
		cout << "Enter bus number:" << endl;
		for (int i = 0; i < n; i++){
			Student* x = new Student();
			myfile >> x->sID;
			myfile >> x->fName;
			myfile >> x->lName;
			myfile >> x->dept;
			myfile >> x->busNo;
			x->next = NULL;
			x->prev = NULL;

			if (tail == NULL){
				head = x;
				tail = x;
			}

			else{
				tail->next = x;
				x->prev = tail;
				tail = x;
			}
		}
		myfile.close();
	}

	void WaitingList::DequeueStudent(){
	counter--;
	Student* tempfirst;
	tempfirst = head;
	if (head == NULL)
		cout << "List is empty" << endl;
	else{
		head = head->next;
		tempfirst = NULL;
	}
}

	void WaitingList::displayList(){
		ofstream outFile;
		outFile.open("studentdataoutput.txt");
		Student* temp;
		temp = head;
		cout << "SID	FName   LName   Dept   BusNo" << endl;
		while (temp != NULL){
			outFile << temp->sID << "\t" << temp->fName << "\t" << temp->lName << " \t" << temp->dept << " \t" << temp->busNo << " ";
			outFile << endl;
			cout << temp->sID << "\t" << temp->fName << "\t" << temp->lName << "\t" << temp->dept << "\t" << temp->busNo << " ";
			cout << endl;
			temp = temp->next;
		}
		cout << endl;
		outFile.close();
	}

	bool WaitingList::isEmpty(){
		if (head == NULL)
			return true;
		else
			return false;
	}

	void WaitingList::getSize(){
		cout << "The size of the list is: " << counter << endl; 
	}
};

class DriverList
{
private:
	driver* root;
    driver* makeEmpty(driver* t) {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

	driver* insert(int id, string fN, string lN, int bn, driver* t)
    {
        if(t == NULL)
        {
			t = new driver;
            t->dID = id;
			t->fName = fN;
			t->lName = lN;
			t->busNo = bn;
            t->left = t->right = NULL;
        }
        else if(bn < t->busNo)
			t->left = insert(id, fN, lN, bn, t->left);
		else if (bn > t->busNo)
			t->right = insert(id, fN, lN, bn, t->right);
        return t;
    }

	driver* findMin(driver* t)
    {
		while (t->left != NULL) 
		t = t->left;
		return t;
    }

	driver* findMax(driver* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

	driver* remove(int x, driver* t) {
		if (t == NULL)
			return t;
		else if (x < t->busNo)
			t->left = remove(x, t->left);
		else if (x > t->busNo)
			t->right = remove(x, t->right);
		else
		{
			if (t->left == NULL && t->right == NULL){
				delete t;
				t = NULL;
			}
			else if (t->left == NULL){
				driver* temp = t;
				t = t->right;
				delete temp;
			}
			else if (t->right == NULL){
				driver* temp = t;
				t = t->left;
				delete temp;
			}
			else{
				driver* temp = findMin(t->right);
				t->dID = temp->dID;
				t->fName = temp->fName;
				t->lName = temp->lName;
				t->busNo = temp->busNo;
				t->right = remove(t->busNo, t->right);
			}
		}
		return t;
	}

	void inorder(driver* t) {
        if(t == NULL)
            return;
        inorder(t->left);
		cout << t->dID << "\t" << t->fName << "\t" << t->lName << "\t" << t->busNo << " ";
		cout << endl;
        inorder(t->right);
    }

	driver* find(driver* t, int x) {
        if(t == NULL)
            return NULL;
        else if(x < t->busNo)
            return find(t->left, x);
        else if(x > t->busNo)
            return find(t->right, x);
        else
            return t;
    }

public:
    DriverList() {
        root = NULL;
    }

	~DriverList() {
        root = makeEmpty(root);
    }

	void insert(int id, string fN, string lN, int bn) {
		root = insert(id, fN, lN, bn, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
		cout << "ID	FName   LName   BusNo" << endl;
        inorder(root);
        cout << endl;
    }

    void search(int x) {
        root = find(root, x);
		if (root == NULL)
		cout << "Not found" << endl;
		else 
		cout << root->dID << "\t" << root->fName << "\t" << root->lName << "\t" << root->busNo << " "<<endl;
    }
};

class BusList{
private:
	int count;

public:
	BusList::BusList(){
		count = 20;
	}

	int BusList::getcounter(){
		return count;
	}

	void addBus(Bus B[]){
		ifstream myfile;
		myfile.open("data.txt");
		cout << "Enter bustag:" << endl;
		cout << "Enter plate number:" << endl;
		cout << "Enter destination:" << endl;
		cout << "Enter first name of driver:" << endl;
		cout << "Enter departure time:" << endl;
		int i;
		for (i = 0; i < 20; i++){
			myfile >> B[i].busNo;
			myfile >> B[i].plateNo;
			myfile >> B[i].route;
			myfile >> B[i].dID;
			myfile >> B[i].time;	
	}
		myfile.close();
	}

	int partition(Bus B[], int start, int end){
		double pivot = B[end].time;
		int partIndex = start;
		for (int j = start; j < end; j++){
			if (B[j].time <= pivot) {
				swap(B[j], B[partIndex]);
				partIndex++;
			}
		}
		swap(B[partIndex], B[end]);
		return (partIndex);
	}

	void Quicksort(Bus B[], int start, int end){
	 		if (start < end){
			int partIndex = partition(B, start, end);
			Quicksort(B, start, partIndex - 1);
			Quicksort(B, partIndex + 1, end);
			}
	}

	void displayBusInfo(Bus B[]){
		ofstream outFile;
		outFile.open("dataoutput.txt");
		cout << "Tag \t PLNo \t Destination \t DName \t Departure" << endl;
		for (int i = 0; i < 20; i++){
			outFile << B[i].busNo << " \t" << B[i].plateNo << "\t" << B[i].route << " \t" << B[i].dID << " \t" << B[i].time << " ";
			outFile << endl;
			cout << B[i].busNo << " \t" << B[i].plateNo << "\t" << B[i].route << " \t" << B[i].dID << " \t" << B[i].time << " ";
			cout << endl;
		}
		cout << endl;
		outFile.close();
	}

	void BusList::searchBusInfo(Bus B[], int bN){
		int i;
		for (int i = 0; i < 20; i++){
			if (B[i].busNo = bN)
				break;
		}
		cout << B[i].busNo << " \t" << B[i].plateNo << "\t" << B[i].route << " \t" << B[i].dID << " \t" << B[i].time << " ";
		cout << endl;
	}
};

//Interface Functions
void start(){
	cout << "********************************************************" << endl;
	cout << "*                                                      *" << endl;
	cout << "***WELCOME TO THE STUDENT TRANSPORT MANAGEMENT SYSTEM***" << endl;
	cout << "*                                                      *" << endl;
	cout << "********************************************************" << endl;

	cout << "What would you like to do today?" << endl;
	cout << "A) Student Management" << "\t" << "\t" << "B) Driver Management" << "\t" << "\t" << "C) Bus Management" << endl;
	cout << "* Add to waiting list" << "\t" << "\t" << "* Add driver details" << "\t" << "\t" << "* Add bus" << endl;
	cout << "* Remove from list" << "\t" << "\t" << "* Remove driver details" << "\t" << "\t" << "* Display Bus List" << endl;
	cout << "* Waiting list empty?" << "\t" << "\t" << "* Display driver list" << "\t" << "\t" << "* Sort Bus list" << endl;
	cout << "* View waiting list" << "\t" << "\t" << "* Search driver info" << "\t" << "\t" << "* Search for bus info" << endl;
	cout << "* See outstanding" << "\t" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{

	//start();
	/*Bus A[20];
	BusList PVBusList;
	PVBusList.addBus(A);
	PVBusList.displayBusInfo(A);
	//PVBusList.Quicksort(A, 0, 19);
	//PVBusList.displayBusInfo(A);*/

	/*WaitingList B;
	B.enQueueStudent();
	B.displayList();
	B.DequeueStudent();
	B.displayList();
	//B.isEmpty();
	B.getSize();*/

	/*DriverList C;
	C.insert(301, "Matthew", "Haley", 101);
	C.insert(302, "Mark", "Sidney", 100);
	C.insert(300, "Binta", "John", 108);
	C.insert(300, "Binta", "John", 110);
	C.insert(300, "Binta", "John", 103);
	C.insert(300, "Binta", "John", 107);
	C.display();
	
	//A.remove(101);
	//A.remove(107);
	//A.display();
	//A.search(108);*/

	return 0;
}
