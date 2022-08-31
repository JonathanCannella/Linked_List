#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

template<typename T>
class LinkedList
{
	unsigned int nodeCount;

public:
	struct Node
	{
		Node* next;
		Node* prev;
		T data;
	};

	Node* head;
	Node* tail;

	//Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	//Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	Node* Find(const T& data);
	const Node* Find(const T& data) const;
	Node* GetNode(unsigned int index);
	const Node* GetNode(unsigned int index) const;
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	//Operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	bool operator==(const LinkedList<T>& rhs) const;

	//Removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(unsigned int index);
	void Clear();
	
	//construction/Destruction
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList<T>& list);

	//Insertion operations
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);
};

//=====construction=====//
template<typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	nodeCount = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	while (head) {
		Node* next = head->next;
		delete head;
		head = next;
	}
	head = nullptr;
	tail = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	this->head = nullptr;
	this->tail = nullptr;
	this->nodeCount = 0;
	Node* currentNode = list.head;
	for (unsigned int i = 0; i < list.NodeCount(); i++) {
		Node* newNode = new Node;
		newNode->data = currentNode->data;
		if (this->tail == nullptr) {
			newNode->next = nullptr;
			newNode->prev = nullptr;
			this->tail = newNode;
			this->head = newNode;
			this->nodeCount++;
		}
		else {
			newNode->prev = this->tail;
			this->tail->next = newNode;
			this->tail = newNode;
			this->nodeCount++;
		}
		currentNode = currentNode->next;

	}
}

//=====Behaviors=====//
template<typename T>
void LinkedList<T>::PrintForward() const
{
	Node* currentNode = head;
	while (currentNode != nullptr) {
		cout << currentNode->data << endl;
		currentNode = currentNode->next;
	}
}

template<typename T>
void LinkedList<T>::PrintReverse() const
{
	Node* currentNode = tail;
	while (currentNode != nullptr) {
		cout << currentNode->data << endl;
		currentNode = currentNode->prev;
	}
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	Node* print = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (print == node) {
			break;
		}
		print = print->next;
	}
	if (print == nullptr) {
		cout << "";
	}
	else {
		cout << print->data << endl;
		print = print->next;
		PrintForwardRecursive(print);
	}
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	Node* print = tail;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (print == node) {
			break;
		}
		print = print->prev;
	}
	if (print == nullptr) {
		cout << "";
	}
	else {
		cout << print->data << endl;
		print = print->prev;
		PrintReverseRecursive(print);
	}
}

//=====insertion=====//
template<typename T>
void LinkedList<T>::AddHead(const T& data)
{
	Node* newNode = new Node;
	newNode->data = data;
	if (head == nullptr) {
		newNode->next = nullptr;
		newNode->prev = nullptr;
		tail = newNode;
		head = newNode;
		nodeCount++;
	}
	else {
		newNode->next = head;
		newNode->prev = nullptr;
		head->prev = newNode;
		head = newNode;
		nodeCount++;
	}
}

template<typename T>
void LinkedList<T>::AddTail(const T& data)
{
	Node* newNode = new Node;
	newNode->data = data;
	if (tail == nullptr) {
		newNode->prev = nullptr;
		newNode->next = nullptr;
		tail = newNode;
		head = newNode;
		nodeCount++;
	}
	else {
		newNode->prev = tail;
		newNode->next = nullptr;
		tail->next = newNode;
		tail = newNode;
		nodeCount++;
	}
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count)
{
	for (unsigned int i = count; i > 0; i--) {
		Node* newNode = new Node;
		newNode->data = data[i - 1];
		if (head == nullptr) {
			newNode->next = nullptr;
			newNode->prev = nullptr;
			tail = newNode;
			head = newNode;
			nodeCount++;
		}
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
			nodeCount++;
		}
	}
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++) {
		Node* newNode = new Node;
		newNode->data = data[i];
		if (tail == nullptr) {
			newNode->prev = nullptr;
			newNode->next = nullptr;
			tail = newNode;
			head = newNode;
			nodeCount++;
		}
		else {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
			nodeCount++;
		}
	}
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	Node* newNode = new Node;
	newNode->data = data;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (node == GetNode(i)) {
			newNode->prev = node;
			newNode->next = node->next;
			node->next->prev = newNode;
			node->next = newNode;
			//node = newNode;
			break;
			nodeCount++;
		}
	}
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	Node* newNode = new Node;
	newNode->data = data;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (node == GetNode(i)) {
			newNode->next = node;
			newNode->prev = node->prev;
			node->prev->next = newNode;
			node->prev = newNode;
			//node = newNode;
			nodeCount++;
			break;

		}
	}
}

template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{
	Node* currentNode = head;
	if (index > NodeCount()) {
		throw out_of_range("invalid index");
	}
	if (index == 0) {
		AddHead(data);
	}
	else if(index == NodeCount()) {
		AddTail(data);
	}
	else {
		for (unsigned int i = 0; i < index; i++) {
			currentNode = currentNode->next;
		}  
		InsertBefore(currentNode, data);
	}
}

//=====Removal=====//
template<typename T>
bool LinkedList<T>::RemoveHead() 
{
	if (head == nullptr) {
		tail = nullptr;
		return false;
	}
	else if (nodeCount == 1) {
		delete head;
		head = nullptr;
		nodeCount--;
		return true;
	}
	else {
		Node* newHead = head->next;
		newHead->prev = nullptr;
		delete head;
		head = nullptr;
		head = newHead;
		nodeCount--;
		return true;
	}
}

template<typename T>
bool LinkedList<T>::RemoveTail() 
{
	if (tail == nullptr) {
		head = nullptr;
		return false;
	}
	else if (nodeCount == 1) {
		delete tail;
		tail = nullptr;
		nodeCount--;
		return true;
	}
	else {
		Node* newTail = tail->prev;
		newTail->next = nullptr;
		delete tail;
		tail = newTail;
		nodeCount--;
		return true;
	}
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{
	if (Find(data) == nullptr) {
		return 0;
	}
	else {
		vector<LinkedList<T>::Node*> nodes;
		FindAll(nodes, data);
		for (unsigned int i = 0; i < nodes.size(); i++) {
			if (nodes[i] == head) {
				RemoveHead();
			}
			else if (nodes[i] == tail) {
				RemoveTail();
			}
			else {
				nodes[i]->prev->next = nodes[i]->next;
				nodes[i]->next->prev = nodes[i]->prev;
				delete nodes[i];
				nodeCount--;
			}
		}
		return nodes.size();
	}
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
	bool tf = true;
	if (index >= nodeCount) {
		tf = false;
	}
	else if (index == 0) {
		RemoveHead();
	}
	else if (index == nodeCount - 1) {
		RemoveTail();
	}
	else {
		Node* currentNode = GetNode(index);
		currentNode->prev->next = currentNode->next;
		currentNode->next->prev = currentNode->prev;
		delete currentNode;
		nodeCount--;
	}
	return tf;
}

template<typename T>
void LinkedList<T>::Clear()
{
	while (RemoveTail()) {}
	head = nullptr;
	tail = nullptr;
}

//=====accessor=====//
template<typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return nodeCount;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	return head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	return tail;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	Node* currentNode = head;
	if (index >= nodeCount) {
		throw out_of_range("invalid index");
	}
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (i == index) {
			return currentNode;
		}
		currentNode = currentNode->next;
	}
	return currentNode;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
	Node* currentNode = head;
	if (index >= nodeCount) {
		throw out_of_range("invalid index");
		return nullptr;
	}
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (i == index) {
			return currentNode;
		}
		currentNode = currentNode->next;
	}
	return currentNode;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
	Node* currentNode = head;
	Node* returnPointer = nullptr;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentNode->data == data) {
			returnPointer = currentNode;
			break;
		}
		currentNode = currentNode->next;
	}
	return returnPointer;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
	Node* currentNode = head;
	Node* returnPointer = nullptr;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentNode->data == data) {
			returnPointer = currentNode;
			break;
		}
		currentNode = currentNode->next;
	}
	return returnPointer;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	Node* currentNode = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (currentNode->data == value) {
			outData.push_back(currentNode);
		}
		currentNode = currentNode->next;
	}
}

//=====operators=====//
template<typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	if (index >= nodeCount) {
		throw out_of_range("invalid index");
	}
	Node* currentNode = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (i == index) {
			return currentNode->data;
		}
		currentNode = currentNode->next;
	}
}

template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	if (index >= nodeCount) {
		throw out_of_range("invalid index");
	}
	Node* currentNode = head;
	for (unsigned int i = 0; i < nodeCount; i++) {
		if (i = index) {
			return currentNode->data;
		}
		currentNode = currentNode->next;
	}
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	if (this->NodeCount() > 0) {
		this->~LinkedList();
		this->head = nullptr;
		this->tail = nullptr;
		this->nodeCount = 0;
	}
	Node* currentNode = rhs.head;
	for (unsigned int i = 0; i < rhs.NodeCount(); i++) {
		Node* newNode = new Node;
		newNode->data = currentNode->data;
		if (this->tail == nullptr) {
			newNode->next = nullptr;
			newNode->prev = nullptr;
			this->tail = newNode;
			this->head = newNode;
			this->nodeCount++;
		}
		else {
			newNode->prev = this->tail;
			this->tail->next = newNode;
			this->tail = newNode;
			this->nodeCount++;
		}
		currentNode = currentNode->next;
	}
	return *this;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	bool equal = true;
	if (this->nodeCount != rhs.NodeCount()) {
		equal = false;
	}
	else {
		Node* currentNode = this->head;
		Node* compare = rhs.head;
		for (unsigned int i = 0; i < nodeCount; i++) {
			if (currentNode->data != compare->data) {
				equal = false;
			}
			currentNode = currentNode->next;
			compare = compare->next;
		}
	}
	return equal;
}
