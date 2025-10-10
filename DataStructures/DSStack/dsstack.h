#ifndef DSLISTSTACK_H
#define DSLISTSTACK_H

#include "../DSDoublyLL/dsdoublyll.h"


template <class T>
class DSStack
{
public:
    /**
     * @brief DSStack - default constructor
     */
    DSStack();
    /**
     * @brief DSStack - copy constructor
     * @param other - reference to target stack
     */
    DSStack(const DSStack<T>& other);

    /**
     * @brief ~DSStack - destructor
     */
    ~DSStack();

    /**
     * @brief Getter - numIndexes
     */
    int size() const;

    /**
     * @brief push - adds an element to the top of the stack
     * @param element - element to add to stack
     */
    void push(const T element);

    /**
     * @brief pop - removes the top element of the stack
     */
    void pop();

    /**
     * @brief peek - returns the top element of the stack
     * @return top element of the stack
     */
    T peek() const;

    /**
     * @brief operator = :  Sets this stack equal to the passed in stack
     * @param other - reference to target stack
     * @return reference to this stack
     */
    DSStack<T>& operator=(const DSStack<T>& other);

    /**
     * @brief operator + : returns a stack combining this and the given stack
     * @param other - reference to given stack
     * @return combined stack of this and given stack
     */
    DSStack<T> operator+(const DSStack<T>& other) const;

    /**
     * @brief operator += : combines this stack with the given stack
     * @param other - reference to the given stack
     * @return this stack, after it has been combined with the given
     */
    DSStack<T>& operator+=(const DSStack<T>& other);

    /**
     * @brief operator == : compares this stack against another stack
     * @param other - reference to target stack
     * @return true if the stacks have equal values
     */
    bool operator==(const DSStack<T>& other) const;

private:
    DSDoublyLL<T> data;
};

/**
 * @brief DSStack - default constructor
 */
template <class T>
DSStack<T>::DSStack(){}
/**
 * @brief DSStack - copy constructor
 * @param other - reference to target stack
 */
template <class T>
DSStack<T>::DSStack(const DSStack<T>& other){
    data = other->data;
}

/**
 * @brief ~DSStack - destructor
 */
template <class T>
DSStack<T>::~DSStack(){}

/**
 * @brief Getter - numIndexes
 */
template <class T>
int DSStack<T>::size() const{
    return data.size();
}

/**
 * @brief push - adds an element to the top of the stack
 * @param element - element to add to stack
 */
template <class T>
void DSStack<T>::push(const T element){
    data.pushBack(element);
}

/**
 * @brief pop - removes the top element of the stack
 */
template <class T>
void DSStack<T>::pop(){
    data.popBack();
}

/**
 * @brief peek - returns the top element of the stack
 * @return top element of the stack
 */
template <class T>
T DSStack<T>::peek() const{
    return data[size() - 1];
}

/**
 * @brief operator = :  Sets this stack equal to the passed in stack
 * @param other - reference to target stack
 * @return reference to this stack
 */
template <class T>
DSStack<T>& DSStack<T>::operator=(const DSStack<T>& other){
    data = other.data;

    return *this;
}

/**
 * @brief operator + : returns a stack combining this and the given stack
 * @param other - reference to given stack
 * @return combined stack of this and given stack
 */
template <class T>
DSStack<T> DSStack<T>::operator+(const DSStack<T>& other) const{
    DSStack<T> result;
    result.data = data + other.data;

    return result;
}

/**
 * @brief operator += : combines this stack with the given stack
 * @param other - reference to the given stack
 * @return this stack, after it has been combined with the given
 */
template <class T>
DSStack<T>& DSStack<T>::operator+=(const DSStack<T>& other){
    data += other.data;
}


/**
 * @brief operator == : compares this stack against another stack
 * @param other - reference to target stack
 * @return true if the stacks have equal values
 */
template <class T>
bool DSStack<T>::operator==(const DSStack<T>& other) const{
    return data == other.data;
}

#endif // DSSTACK_H
