#include <string>
#include <iostream>

using namespace std;

class Node 
{
    private:
    char data;
    Node* next;
    Node* prev;

    public:
    Node(char value) { 
        this->data = value; 
        this->next = nullptr;
        this->prev = nullptr;
    }

    void setNext(Node* newNext) { this->next = newNext; }

    void setPrev(Node* newPrev) { this->prev = newPrev; }

    char getData() { return this->data; }

    Node* getNext() { return this->next; }

    Node* getPrev() { return this->prev; }
};

class jbLinkedList
{
    private:
    Node* head;
    Node* tail;

    public:
    
    jbLinkedList() {
        this->head = nullptr;
    }

    bool isEmpty() { return this->head == nullptr; }

    Node* getLast() {
        Node* itr = this->head;
        
        if(this->isEmpty()) { return itr; }

        while (itr->getNext() != nullptr) {
            itr = itr->getNext();
        }
        return itr;
    }

    // Inserts a character at the front of the list
    void Insert(char value) {
        Node* newNode = new Node(value);

        if(isEmpty()) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            newNode->setNext(this->head);
            this->head->setPrev(newNode);
            this->head = newNode;
        }
    }


    // Inserts a character at the end of the list
    void Append(char value) {
        Node* newNode = new Node(value);
        
        if(isEmpty()) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            Node* lastNode = this->tail;
            lastNode->setNext(newNode);
            newNode->setPrev(lastNode);
            this->tail = newNode;
        }
    }

    // Deletes the first element in the list
    void DeleteFirst() {
        if (this->isEmpty()) { return; }

        if (this->tail == this->head) {
            delete this->head;
            this->head = nullptr;
            this->tail = nullptr;
            return;
        }

        this->head = this->head->getNext();

        delete this->head->getPrev();

        this->head->setPrev(nullptr);
    }


    // Deletes the last element in the list
    void DeleteLast() {        
        if (this->isEmpty()) { return; }

        if (this->tail == this->head) {
            delete this->head;
            this->head = nullptr;
            this->tail = nullptr;
            return;
        }

        Node* newTail = this->tail->getPrev();
        
        Node* oldTail = this->tail;
        delete oldTail;

        newTail->setNext(nullptr);
        this->tail = newTail;
    }


    // Deletes the character that is 
    // the given number of nodes from the tail of the list
    bool DeleteNegAt(int negIdx) {
        // contingency for if the list is empty
        if (this->isEmpty()) { return false; } 

        // if the index is zero, that means that the last character
        // is to be deleted and tail needs to be reallocated
        // this->DeleteLast() handles the reallocation of the tail pointer
        if (negIdx == 0) {
            this->DeleteLast();
            return true;
        }

        Node* itr = this->tail;
        
        // Traverses the list until it reaches the specified index
        // or the iterator reaches the front of the list
        while (itr != nullptr && negIdx > 0) {
            itr = itr->getPrev();
            negIdx--;
        }

        // If the iterator points to null, it means
        // it went to far forward meaning it failed to
        // find a place to insert; thus we exit with a fail
        if (itr == nullptr) { return false; }

        // If the iterator points to the head, 
        // the head pointer needs to be reallocated before 
        // current head gets deleted
        if (itr == this->head) {
            this->DeleteFirst();
            return true;
        }

        // If the index didn't point to the ends of the list, 
        // then delete the node that the iterator points to
        if (negIdx == 0) {
            Node* newPrev = itr->getPrev();
            Node* newNext = itr->getNext();

            if (newPrev != nullptr) { newPrev->setNext(newNext); }
            if (newNext != nullptr) { newNext->setPrev(newPrev); }

            return true;

        } 
        // If this is reached then there was a contingency that 
        // was not properly handled and we should
        // inform the user of the bug
        else { cout << " ERROR: INDEX OUT OF RANGE" << endl; }

        return false;
    }

    // Inserts a character after a given node
    // The given node is specified by negIdx
    // Idx dictates how many nodes to go back before insertion
    // Returns true if character was successfully inserted
    bool InsertNegAt(char value, int negIdx) {

        // Contingency check for if the list is empty
        if (this->isEmpty() || negIdx == 0) {
            this->Append(value);
            return true;
        }

        Node* itr = this->tail;             // iterator traverses the list
        Node* newNode = new Node(value);    // node to be inserted

        // Traverses the list until it reaches the specified index
        // or the iterator reaches the front of the list
        while (itr != this->head && negIdx > 0) {
            itr = itr->getPrev();
            negIdx--;
        }

        // If the index points to the front of the list, 
        // insert needs to be called to handle the 
        // reallocation of the this->head pointer
        if (itr == this->head && negIdx == 1) {
            this->Insert(value);
            return true;
        }

        // If the index reached zero before the iterator reached the front
        // of the list, then insert it after where the iterator stopped
        if (negIdx == 0) {
            Node* newPrev = itr;        
            Node* newNext = itr->getNext();

            newPrev->setNext(newNode);
            newNode->setPrev(newPrev);

            newNext->setPrev(newNode);
            newNode->setNext(newNext);

            return true;
        } 
        // If this is reached then there was a contingency that 
        // was not properly handled and we should
        // inform the user of the bug
        else { cout << " ERROR: INDEX OUT OF RANGE" << endl;}
        return false;
    }

    // Returns the elements in-order as a string
    string getString() {
        if (this->isEmpty()) { return ""; }

        string returnBuffer = "";
        Node* itr = this->head;

        while (itr != nullptr) {
            returnBuffer += itr->getData();
            itr = itr->getNext();
        }

        return returnBuffer;
    }
};