#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

template <class T>
class CircularLinkedList {
private:
	class Node {
	private:
		T data;
		Node* next;
	public:
		Node(): next(nullptr){}
		~Node() {}

		Node(T data) {
			this->data = data;
		}

		T getData() {
			return data;
		}

		Node* getNext() {
			return next;
		}

		void setData(T data) {
			this->data = data;
		}

		void setNext(Node *next) {
			this->next = next;
		}
	};

	Node *head;

public:

	CircularLinkedList() {
		head = nullptr;
	}

	CircularLinkedList(int amount, T val,...) {
		head = nullptr;
		T* temp = &val;
		for (int i = 0; i < amount; i++, temp++) {
			addToList(*temp);
		}
	}
	
	~CircularLinkedList(){
		if (head != nullptr) {
			Node* tempNext = head->getNext();
			while (tempNext != head) {
				Node* tempNextNext = tempNext->getNext();
				delete tempNext; tempNext = tempNextNext;
			}
			delete head;
		}
	}

	Node* getNodeHead() {
		return head;
	}
	
	void addToList(T data);
	
	void printList();

	void deleteElement(T data);

	void printWantedAmountFromWantedElement(T data, int amount);
	
	int getSize();
};

int main(){
	auto list1 = new CircularLinkedList<char>();
	list1->addToList('a');
	list1->addToList('b');
	list1->addToList('c');
	list1->addToList('d');
	cout << "List of " << list1->getSize() << " elements<char>: ";
	list1->printList();
	char toDel1 = 'a', toDel2 = 'b';
	cout << "\nList of elements after deleting " << toDel1 << " and " << toDel2 << " : ";
	list1->deleteElement(toDel1);
	list1->deleteElement(toDel2);
	list1->printList();
	delete list1;
	cout << endl;

	char c[] = "hello allah akbar";
	char n[] = "bollo salem here there";
	char v[] = "gollo what the hell, ya?";
	char wtf[] = "hello allah akbar";

	auto lister = new CircularLinkedList<const char*>();
	lister->addToList(c);
	lister->addToList(n);
	lister->addToList(v);
	lister->printList();
	cout << endl;
	lister->deleteElement(wtf);
	lister->deleteElement("bollo salem here there");
	lister->printList();
	lister->deleteElement("gollo what the hell, ya?");
	lister->printList();
	delete lister;


	auto list3 = new CircularLinkedList<double>(4, 5.4, 6.4, 994.532, 543.6);
	list3->addToList(5323.5);
	list3->addToList(6.9);
	list3->addToList(777.666);
	list3->addToList(188.932);
	cout << "\nList of " << list3->getSize() << " elements<double>: ";
	list3->printList();
	double toDel4 = 188.932;
	cout << "\nList of elements(wanted number[10]) after deleting " << toDel4 << " : \n";
	list3->deleteElement(toDel4);
	list3->printWantedAmountFromWantedElement(list3->getNodeHead()->getData(), 10);
	delete list3;

	return 0;
}

template<class T>
void CircularLinkedList<T>::addToList(T data) {
	Node *newEl = new Node(data);
	Node* tempHead = head;
	
	if (head == nullptr) {
		head = newEl;
		head->setNext(head);
	}
	
	else {
		while (tempHead->getNext() != head)
			tempHead = tempHead->getNext();
		tempHead->setNext(newEl);
		newEl->setNext(head);
	}
}

template<class T>
void CircularLinkedList<T>::printList() {

	if (head == nullptr) {
		cout << "\nYour list is empty!\n";
		return;
	}

	Node *tempHead = head;
	cout << tempHead->getData() << " ";
	
	while (tempHead->getNext() != head) {
		cout << tempHead->getNext()->getData() << " ";
		tempHead = tempHead->getNext();
	}
}

template<>
void CircularLinkedList<const char*>::deleteElement(const char* data) {
	Node *tempHead = head;
	Node* tempHeadNext = head->getNext();
	
	if (!strcmp(tempHead->getData(), data)) {
	
		if (head->getNext() == head) {
			delete head;
			head = nullptr;
			return;
		}
		
		else {
			Node* prevHead = head;
			while (prevHead->getNext() != head)
				prevHead = prevHead->getNext();
			prevHead->setNext(tempHeadNext);
			delete tempHead;
			tempHead = head = tempHeadNext;
		}
	}

	while (tempHead->getNext() != head) {
		
		if (!strcmp(tempHead->getNext()->getData(), data)) {
			Node* tempNextNext = tempHead->getNext()->getNext();
			delete tempHead->getNext(); tempHead->setNext(tempNextNext);
		}
		tempHead = tempHead->getNext();
	}
}

template<>
void CircularLinkedList<const char*>::printWantedAmountFromWantedElement(const char* data, int amount) {
	Node *tempHead = head;

	while (strcmp(tempHead->getData(), data)) {
		tempHead = tempHead->getNext();
	} Node* tempHeadStarted = tempHead;
	
	for (int i = 0; i < amount; i++) {
		cout << tempHead->getData() << endl;
		tempHead = tempHead->getNext();
		
		if (tempHead == tempHeadStarted) {
			cout << "\nNow data will be printed from the place it started, so it's useless, stop printing.\n";
			return;
		}
	}
}

template<class T>
void CircularLinkedList<T>::deleteElement(T data) {
	Node *tempHead = head;
	Node* tempHeadNext = head->getNext();
	
	if (tempHead->getData() == data) {
	
		if (head->getNext() == head) {
			delete tempHead;
			head = nullptr;
			return;
		}
		
		else {
			Node* prevHead = head;
			
			while (prevHead->getNext() != head)
				prevHead = prevHead->getNext();
			
			prevHead->setNext(tempHeadNext);
			delete tempHead;
			tempHead = head = tempHeadNext;
		}
	}

	while (tempHead->getNext() != head) {
		
		if (tempHead->getNext()->getData() == data) {
			Node* tempNextNext = tempHead->getNext()->getNext();
			delete tempHead->getNext(); tempHead->setNext(tempNextNext);
		}
		tempHead = tempHead->getNext();
	}
}

template<class T>
void CircularLinkedList<T>::printWantedAmountFromWantedElement(T data, int amount) {
	Node *tempHead = head;

	while (tempHead->getData() != data) {
		tempHead = tempHead->getNext();
	} Node* tempHeadStarted = tempHead;
	
	for (int i = 0; i < amount; i++) {
		cout << tempHead->getData() << endl;
		tempHead = tempHead->getNext();
	
		if (tempHead == tempHeadStarted) {
			cout << "\nNow data will be printed from the place it started, so it's useless, stop printing.\n";
			return;
		}
	}
}

template<class T>
int CircularLinkedList<T>::getSize() {
	int size = 0;
	
	if (head == nullptr) {
		return size;
	}
	else size++;
	
	Node* tempHead = head;
	while (tempHead->getNext() != head) {
		size++;
		tempHead = tempHead->getNext();
	}
	return size;
}
