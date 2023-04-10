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

    void Insert(char value) {
        Node* newNode = new Node(value);

        if(isEmpty()) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            Node* firstNode = this->head;
            newNode->setNext(this->head);
            this->head->setPrev(newNode);
            this->head = newNode;
        }
    }

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
        if (this->isEmpty()) { return false; }

        if (negIdx == 0) {
            this->DeleteLast();
            return true;
        }

        Node* itr = this->tail;

        while (itr != nullptr && negIdx > 0) {
            cout << "Negative IDX: " << negIdx 
                 << " Character: " << itr->getData() << endl;
            itr = itr->getPrev();
            negIdx--;
        }

        if (itr == nullptr) { return false; }

        if (itr == this->head) {
            this->DeleteFirst();
            return true;
        }

        if (negIdx == 0) {
            cout << endl << "Deleting Character: " 
                 << itr->getData() << endl;
            Node* newPrev = itr->getPrev();
            Node* newNext = itr->getNext();

            if (newPrev != nullptr) { newPrev->setNext(newNext); }
            if (newNext != nullptr) { newNext->setPrev(newPrev); }

            return true;

        } else {
            cout << " ERROR: INDEX OUT OF RANGE" << endl;
        }

        return false;
    }

    bool InsertNegAt(char value, int negIdx) {
        if (this->isEmpty() || negIdx == 0) {
            this->Append(value);
            return true;
        }

        Node* itr = this->tail;
        Node* newNode = new Node(value);

        while (itr != this->head && negIdx > 0) {
            cout << "Negative IDX: " << negIdx << endl;
            itr = itr->getPrev();
            negIdx--;
        }

        if (itr == this->head) {
            this->Insert(value);
            return true;
        }

        if (negIdx == 0) {
            cout << endl << "Inserting Character..." << endl;
            if (itr == this->head) {
                this->head->setPrev(newNode);
                this->head = this->head->getPrev();
                return true;
            }

            Node* newPrev = itr;
            Node* newNext = itr->getNext();

            newPrev->setNext(newNode);
            newNode->setPrev(newPrev);

            newNext->setPrev(newNode);
            newNode->setNext(newNext);

            return true;
            
            /*
            if (newPrev != nullptr) { newPrev->setNext(newNext); }
            if (newNext != nullptr) { newNext->setPrev(newPrev); }
            */
        } else {
            cout << " ERROR: INDEX OUT OF RANGE" << endl;
        }
        return false;
    }

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