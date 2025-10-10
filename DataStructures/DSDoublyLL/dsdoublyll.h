#ifndef DSDOUBLYLL_H
#define DSDOUBLYLL_H

#include "dsnode.h"

template <class T>
class DSDoublyLL{
    private:
        /**
         * @brief The iterator struct - iterator for the vector class
         */
        struct iterator{
            public:
                friend class DSDoublyLL;

                /**
                 * @brief iterator - constructor
                 * @param ptr - pointer to the node which to start iteration from
                 */
                iterator(DSNode<T>* ptr): ptr(ptr){};

                /**
                 * @brief operator * - dereferences pointer and returns node's data
                 * @return reference of the class T at the pointer's location
                 */
                T& operator*() const{
                    return ptr->data;
                }

                /**
                 * @brief operator -> returns the address of the data of the node pointed to
                 * @return address to a node's data
                 */
                T* operator->() const{
                    return &(ptr->data);
                }

                /**
                 * @brief operator ++ - iterates to next node
                 * @return this iterator after iteration
                 */
                iterator operator++(){
                    ptr = ptr->next;
                    return *this;
                }

                /**
                 * @brief operator ++ - iterates to next pointer
                 * @return a reference to an iterator before iteration
                 */
                iterator operator++(int){
                    iterator tmp = *this;
                    ptr = ptr->next;
                    return tmp;
                }

                /**
                 * @brief operator -- : iterates to previous pointer
                 * @return this iterator after iteration
                 */
                iterator operator--(){
                    ptr = ptr->prev;
                    return *this;
                }

                /**
                 * @brief operator -- :  iterates to previous  pointer
                 * @return a reference to an iterator before iteration
                 */
                iterator operator--(int){
                    iterator tmp = *this;
                    ptr = ptr->prev;
                    return tmp;
                }

                /**
                 * @brief operator == compares if two iterators are equal
                 * @param a - first iterator to compare
                 * @param b - second iterator to compare
                 * @return true if the two iterators are equal
                 */
                friend bool operator==(const iterator& a, const iterator& b){
                    return a.ptr == b.ptr;
                }

                /**
                 * @brief operator != compares if two iterators are equal
                 * @param a - first iterator to compare
                 * @param b - second iterator to compare
                 * @return true if the two iterators are not equal
                 */
                friend bool operator!=(const iterator& a, const iterator& b){
                    return a.ptr != b.ptr;
                }
            private:
                DSNode<T>* ptr;
        };
    public:
        /**
         * @brief DSDoublyLL - default constructor
         */
        DSDoublyLL();

        /**
         * @brief DSDoublyLL - constructor
         * @param data - pointer to array of size elements
         * @param size - size of data array
         */
        DSDoublyLL(const T* data, const int size);

        /**
         * @brief DSDoublyLL - copy constructor
         * @param other - reference of list to copy
         */
        DSDoublyLL(const DSDoublyLL<T>& other);


        /**
         * @brief getNumIndexes - Getter: numIndexes
         * @return numIndexes
         */
        int getNumIndexes() const;

        /**
         * @brief pushFront - adds element data to the front of the list
         * @param data - data to be added
         */
        void pushFront(const T data);

        /**
         * @brief pushBack - adds data to the front of the list
         * @param data - data to be added
         */
        void pushBack(const T data);

        /**
         * @brief insert - inserts data in list at given index
         * @param data - data to be added
         * @param index - index to insert data
         */
        void insert(int index, const T data);

        /**
         * @brief remove - removes data from list at given index
         * @param index - index to be removed
         */
        void removeAt(int index);

        /**
         * @brief removeAt - removes data from given node location
         * @param index - location of node to be removed
         */
        iterator removeAt(iterator index);

        /**
         * @brief remove - removes given data from list
         * @param onlyFirst - if true, only the first instance is deleted
         */
        void remove(const T element, bool onlyFirst = false);

        /**
         * @brief clear - removes all data from list
         */
        void clear();

        /**
         * @brief popFront - removes first node from list
         */
        void popFront();

        /**
         * @brief popBack - removes last node from list
         */
        void popBack();

        /**
         * @brief contains - returns true if the given item is in the list
         * @param query - item to search for
         * @return true if item is in the list
         */
        bool contains(const T query) const;

        /**
         * @brief size - returns the size of the list
         * @return size of the list
         */
        int size() const;

        /**
         * @brief unorderedEquals - compares two lists by seeing if they contain the same elements
         * @param other - list to compare against
         * @return true if both lists contain the same elements
         */
        bool unorderedEquals(const DSDoublyLL<T>& other) const;

        /**
         * @brief DSDoublyLL::operator [] - returns data at passed index
         * @param index - index to retrieve data
         * @return data at passed index
         */
        T& operator[](int index) const;

        /**
         * @brief operator = :  sets this list equal to the list passed in
         * @param other - reference to target list
         * @return returns this
         */
        DSDoublyLL<T>& operator=(const DSDoublyLL<T>& other);

        /**
         * @brief operator + : returns a linked list combining this and the given list
         * @param other - reference to given list
         * @return combined linked list of this and given list
         */
        DSDoublyLL<T> operator+(const DSDoublyLL<T>& other) const;

        /**
         * @brief operator += : combines this
         * @param other
         * @return
         */
        DSDoublyLL<T>& operator+=(const DSDoublyLL<T>& other);

        /**
         * @brief operator == :  compares this list against another list
         * @param other - reference to target list
         * @return true if the lists have equal values
         */
        bool operator==(const DSDoublyLL<T>& other) const;

        /**
         * @brief operator != : compares this list against another list
         * @param other - reference to target list
         * @return false if the lists have equal values
         */
        bool operator!=(const DSDoublyLL<T>& other) const;

        /**
         * @brief ~DSDoublyLL - default destructor
         */
        ~DSDoublyLL();

        /**
         * @brief begin - returns an iterator for the first element of the list
         * @return iterator for the first element of the list
         */
        inline iterator begin() {
            return iterator(head);
        };

        /**
         * @brief begin - returns an iterator for the element after the last element of the list, nullptr
         * @return iterator for the element after the last element of the list, nullptr
         */
        inline iterator end() {
            return iterator(nullptr);
        }

    private:
        DSNode<T>* head = nullptr;
        DSNode<T>* tail = nullptr;

        int numIndexes = 0;

        /**
         * @brief getNodeAt: returns node at given index
         * @param index - index at which the node is
         * @return node pointer
         */
        DSNode<T>* getNodeAt(int index) const;
};

/**
 * @brief DSDoublyLL - default constructor
 */
template <class T>
DSDoublyLL<T>::DSDoublyLL(){}

/**
 * @brief DSDoublyLL - constructor
 * @param data - pointer to array of size elements
 * @param size - size of data array
 */
template <class T>
DSDoublyLL<T>::DSDoublyLL(const T* data, const int size){
    for(int i = 0; i < size; i++){
        pushBack(data[i]);
    }
}

/**
 * @brief DSDoublyLL - copy constructor
 * @param other - reference to the list to copy
 */
template <class T>
DSDoublyLL<T>::DSDoublyLL(const DSDoublyLL& other){
    for(DSNode<T>* n = other.head; n != nullptr; n = n->next){
        pushBack(n->data);
    }
}


/**
 * @brief getNumIndexes - Getter: numIndexes
 * @return numIndexes
 */
template <class T>
int DSDoublyLL<T>::getNumIndexes() const{
    return numIndexes;
}

/**
 * @brief pushFront - creates a node with data and has the current head point to it as prev, and makes it the new head
 * @param data - data to be added
 */
template <class T>
void DSDoublyLL<T>::pushFront(const T data){
    numIndexes++;
    DSNode<T>* newNode = new DSNode<T>;
    newNode->data = data;

    if(head == nullptr){
        head = newNode;
        tail = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;

        head = newNode;
    }
}

/**
 * @brief pushBack - creates a node with data and has the current tail point to it as next, and makes it the new tail
 * @param data - data to be added
 */
template <class T>
void DSDoublyLL<T>::pushBack(const T data){
    numIndexes++;
    DSNode<T>* newNode = new DSNode<T>;
    newNode->data = data;

    if(tail == nullptr){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;

        tail = newNode;
    }
}

/**
 * @brief DSDoublyLL::insert - adds a node at an index and links the next and previous nodes to the new node
 * @param data - data of the new node
 * @param index - index of the new node
 */
template <class T>
void DSDoublyLL<T>::insert(int index, const T data){
    if(index == 0){
        pushFront(data);
        return;
    }

    if(index == numIndexes){
        pushBack(data);
        return;
    }

    DSNode<T>* nodeBefore = getNodeAt(index - 1);

    DSNode<T>* newNode = new DSNode<T>(data);

    newNode->next = nodeBefore->next;
    newNode->prev = nodeBefore;

    nodeBefore->next = newNode;

    newNode->next->prev = newNode;

    numIndexes++;
}

/**
 * @brief DSDoublyLL::remove - removes and deletes the node at an index and links the next and previous nodes together
 * @param index - index where the node will be removed
 */
template <class T>
void DSDoublyLL<T>::removeAt(int index){
    if(index >= numIndexes || index < 0){
        return;
    }

    if(numIndexes == 1){
        delete head;
        numIndexes--;

        head = nullptr;
        tail = nullptr;

        return;
    }

    if(index == 0){
        if(head == tail){
            delete head;

            head == nullptr;
            tail == nullptr;
        } else{
            DSNode<T>* temp = head->next;
            delete head;

            head = temp;
            head->prev = nullptr;
        }

        numIndexes--;
        return;
    }

    if(index == numIndexes - 1){
        DSNode<T>* temp = tail->prev;
        delete tail;
        numIndexes--;

        tail = temp;
        tail->next = nullptr;

        return;
    }

    DSNode<T>* target = getNodeAt(index);

    target->prev->next = target->next;

    if(target->next != nullptr){
        target->next->prev = target->prev;
    } else {
        tail = target->prev;
    }

    delete target;
    numIndexes--;
}

/**
 * @brief DSDoublyLL::removeAt - remove element at the given iterator
 * @param index - iterator pointing to the target element
 */
template<class T>
typename DSDoublyLL<T>::iterator DSDoublyLL<T>::removeAt(iterator index){
    if(numIndexes <= 0){
        return iterator(head);
    }

    if(numIndexes == 1 && head == index.ptr){
        head = nullptr;
        tail = nullptr;

        delete index.ptr;
        numIndexes = 0;

        return iterator(head);
    }

    if(head == index.ptr){
        head = head->next;
        head->prev = nullptr;

        delete index.ptr;
        numIndexes--;

        return iterator(head);
    }

    if(tail == index.ptr){
        tail = tail->prev;
        tail->next = nullptr;

        delete index.ptr;
        numIndexes--;

        return iterator(nullptr);
    }

    index.ptr->prev->next = index.ptr->next;
    index.ptr->next->prev = index.ptr->prev;

    iterator output = iterator(index.ptr->next);

    delete index.ptr;
    numIndexes--;

    return output;
}

/**
 * @brief DSDoublyLL::remove - iterates through list and removes the given element
 * @param element - element to remove
 */
template<class T>
void DSDoublyLL<T>::remove(const T element, bool onlyFirst)
{
    while(head->data == element){
        if(head == tail){
            delete head;

            head == nullptr;
            tail == nullptr;
            numIndexes--;
            return;
        } else{
            DSNode<T>* temp = head->next;
            delete head;

            head = temp;
            head->prev = nullptr;

            numIndexes--;
            if(onlyFirst){
                return;
            }
        }
    }

    for(DSNode<T>* current = head->next; current != tail; current = current->next){
        if(current->data == element){
            current->prev->next = current->next;
            current->next->prev = current->prev;

            DSNode<T>* temp = current;
            current = current->prev;
            delete temp;

            numIndexes--;
            if(onlyFirst){
                return;
            }
        }
    }

    while(tail->data == element){
        DSNode<T>* temp = tail->prev;
        delete tail;

        tail = temp;
        tail->next = nullptr;

        numIndexes--;
        if(onlyFirst){
            return;
        }
    }
}

/**
 * @brief clear - removes all data from list
 */
template <class T>
void DSDoublyLL<T>::clear(){
    DSNode<T>* next;
    DSNode<T>* current = head;
    while(current != nullptr){
        next = current->next;
        delete current;
        current = next;
    }

    numIndexes = 0;
    head = nullptr;
    tail = nullptr;
}

/**
 * @brief DSDoublyLL::popFront - deletes the first node and sets it to nullptr
 */
template <class T>
void DSDoublyLL<T>::popFront(){
    if(head == nullptr){
        return;
    }

    numIndexes--;

    if(numIndexes == 0){
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }

    if(numIndexes == 1){
        delete head;
        head = tail;
        head->prev = nullptr;
        return;
    }

    head = head->next;
    delete head->prev;
    head->prev = nullptr;
}

/**
 * @brief DSDoublyLL::popBack - deletes the last node and sets it to nullptr
 */
template<class T>
void DSDoublyLL<T>::popBack(){
    if(tail == nullptr){
        return;
    }

    numIndexes--;

    if(numIndexes == 0){
        delete tail;
        head = nullptr;
        tail = nullptr;
        return;
    }

    if(numIndexes == 1){
        delete tail;
        tail = head;
        tail->next = nullptr;
        return;
    }

    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
}

/**
 * @brief contains - iterates through data and returns true if query is found
 * @param query - item to search for in data
 * @return true if query is in data
 */
template<class T>
bool DSDoublyLL<T>::contains(const T query) const
{
    for(DSNode<T>* current = head; current != nullptr; current = current->next){
        if(current->data == query){
            return true;
        }
    }

    return false;
}

/**
 * @brief DSDoublyLL::size - itterates through the list and counts the number of nodes
 * @return the number of nodes in the list
 */
template<class T>
int DSDoublyLL<T>::size() const
{
    return numIndexes;
}

/**
 * @brief DSDoublyLL::unorderedEquals - returns true if this and the given list contain the same elements
 * @param other - a list to compare against
 * @return true if both lists contain the same elements reguardless of order
 */
template<class T>
bool DSDoublyLL<T>::unorderedEquals(const DSDoublyLL<T> &other) const
{
    if(numIndexes != other.numIndexes){
        return false;
    }

    if(numIndexes == 0){
        return true;
    }

    DSDoublyLL<T> temp = other;

    for(DSNode<T>* i = head; i != nullptr; i = i->next){
        DSNode<T>* match = nullptr;

        for(DSNode<T>* j = temp.head; j != nullptr; j = j->next){
            if(i->data == j->data){
                match = j;
                break;
            }
        }

        if(match == nullptr){
            return false;
        }

        if(match == temp.head){
            temp.head = match->next;
        } else{
            match->prev->next = match->next;
        }

        delete match;
    }

    return true;
}

/**
 * @brief DSDoublyLL::operator [] - returns data of node at passed index
 * @param index - index to retrieve data
 * @return data of node at passed index
 */
template <class T>
T& DSDoublyLL<T>::operator[](int index) const{
    return getNodeAt(index)->data;
}

/**
 * @brief operator = :  copy constructor
 * @param other - reference to target list
 * @return returns this
 */
template <class T>
DSDoublyLL<T>& DSDoublyLL<T>::operator=(const DSDoublyLL<T>& other){
    DSNode<T>* dataI = head;
    DSNode<T>* otherI = other.head;

    while(otherI != nullptr){
        if(dataI == nullptr){
            break;
        } else {
            dataI->data = otherI->data;
            dataI = dataI->next;
            otherI = otherI->next;
        }
    }

    while(otherI != nullptr){
        pushBack(otherI->data);
        otherI = otherI->next;
    }

    if(dataI != nullptr){
        DSNode<T>* next;
        tail = dataI->prev;
        tail->next = nullptr;

        while(dataI != nullptr){
            next = dataI->next;
            delete dataI;
            dataI = next;
            numIndexes--;
        }
    }

    return *this;
}


/**
 * @brief operator + : returns a linked list combining this and the given list
 * @param other - reference to given list
 * @return combined linked list of this and given list
 */
template <class T>
DSDoublyLL<T> DSDoublyLL<T>::operator+(const DSDoublyLL<T>& other) const{
    DSDoublyLL<T> result;

    for(DSNode<T>* current = this->head; current != nullptr; current = current->next){
        result.pushBack(current->data);
    }

    for(DSNode<T>* current = other.head; current != nullptr; current = current->next){
        result.pushBack(current->data);
    }

    return result;
}

/**
 * @brief operator += : sets data equal to this and the given doubly linked list
 * @param other - the list to be added to this
 * @return a reference to this
 */
template <class T>
DSDoublyLL<T>& DSDoublyLL<T>::operator+=(const DSDoublyLL<T>& other){
    for(DSNode<T>* current = other.head; current != nullptr; current = current->next){
        pushBack(current->data);
    }

    return *this;
}

/**
 * @brief operator == :  compares this list against another list
 * @param other - reference to target list
 * @return true if the lists have equal values
 */
template <class T>
bool DSDoublyLL<T>::operator==(const DSDoublyLL<T>& other) const{
    if(numIndexes != other.numIndexes){
        return false;
    }

    DSNode<T>* i = head;
    for(DSNode<T>* j = other.head; i != nullptr; i = i->next, j = j->next){
        if(i->data != j->data){
            return false;
        }
    }

    return true;
}

/**
 * @brief operator != :  pipes to operator== and flips the return
 * @param other - reference to target list
 * @return opposite of operator==
 */
template <class T>
bool DSDoublyLL<T>::operator!=(const DSDoublyLL<T>& other) const{
    return !(*this == other);
}

/**
 * @brief ~DSDoublyLL - default destructor
 */
template <class T>
DSDoublyLL<T>::~DSDoublyLL(){
    DSNode<T>* next;
    DSNode<T>* current = head;
    while(current != nullptr){
        next = current->next;
        delete current;
        current = next;
    }
}

/**
 * @brief getNodeAt: returns node at given index
 * @param index - index at which the node is
 * @return node pointer
 */
template <class T>
DSNode<T>* DSDoublyLL<T>::getNodeAt(int index) const{
    DSNode<T>* current;
    if(index < 0){
        index = numIndexes + index;
    }
    if(index > (numIndexes / 2) - 1){
        index = index - numIndexes;
    }


    if(index < 0){
        current = tail;

        for(int i = -1; i > index; i--){
            current = current->prev;
        }
    } else {
        current = head;

        for(int i = 0; i < index; i++){
            current = current->next;
        }
    }

    return current;
}

#endif // DSDOUBLYLL_H
