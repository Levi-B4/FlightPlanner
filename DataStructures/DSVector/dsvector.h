#ifndef DSVECTOR_H
#define DSVECTOR_H

template <class T>
class DSVector
{
private:
    /**
     * @brief The iterator struct - iterator for the vector class
     */
    struct iterator{
    public:
        /**
         * @brief iterator - constructor
         * @param ptr - pointer to start iteration from
         */
        iterator(T* ptr): ptr(ptr){}

        /**
         * @brief operator * - dereferences pointer
         * @return - reference of the class T at the pointer's location
         */
        T& operator*(){
            return *ptr;
        }

        /**
         * @brief operator ++ - iterates to next pointer
         * @return this iterator after iteration
         */
        iterator operator++(){
            ++ptr;
            return *this;
        }

        /**
         * @brief operator ++
         * @return a reference to an iterator before iteration
         */
        iterator operator++(int){
            iterator tmp = *this;
            ++ptr;
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
        T* ptr;
    };
    public:
        //default constructor - params: int resizeIncrement = 5
        DSVector(int resizeIncrement = 5);

        // constructor - params: DSVector<T>& other
        DSVector(const DSVector<T>& other);

        // getter - numIndexes
        int getNumIndexes() const;

        // setter - capacity
        void setCapacity(const int capacity);
        // getter - capacity
        int getCapacity() const;

        // setter - resizeIncrement
        void setResizeIncrement(const int resizeIncrement);
        // getter - resizeIncrement
        int getResizeIncrement() const;

        // adds element to back of data array - params: T newElement
        void pushBack(const T& newelement);

        // removes last element of data array
        void removeLast();

        // creates new vector with capacity equal to numIndexes
        void shrink();

        // deletes data and creates an empty array in its place
        void clear();

        // returns the first element of data array
        T& front() const;

        // returns last element of data array
        T& back() const;

        // returns pointer to first element of data
        T* getData() const;


        // sets this to the passed in vector - params: const DSVector<T>& other
        DSVector<T>& operator=(const DSVector<T>& other);

        // adds then returns passed in vector to the end of this - params: const DSVector<T>& other
        DSVector<T>& operator+=(const DSVector<T>& other);
        // adds then returns passed in element to the end of this - params: const T& element
        DSVector<T>& operator+=(const T& element);

        // returns this vector added to the passed in vector - params: const DSVector<T>& other
        DSVector<T> operator+(const DSVector<T>& other) const;
        // returns this vector added to the passed in element - params: const T& element
        DSVector<T> operator+(const T& element) const;


        // returns true if passed in vector has the same values as data - params: const DSVector<T>& other
        bool operator==(const DSVector<T>& other) const;

        // returns true if passed in vector does not have the same values as data - params: const DSVector<T>& other
        bool operator!=(const DSVector<T>& other) const;


        // returns the value at the passed in index - params: const int index
        T operator[](const int index) const;


        // default destructor
        ~DSVector();


        inline iterator begin(){
            return iterator(data);
        }

        inline iterator end(){
            return iterator(data + numIndexes);
        }

    private:
        T* data;
        int capacity;
        int numIndexes;
        int resizeIncrement;
};

// default constructor - params: int resizeIncrement = 5
template <class T>
DSVector<T>::DSVector(int resizeIncrement){
    this->resizeIncrement = resizeIncrement;
    numIndexes = 0;
    capacity = this->resizeIncrement;
    data = new T[capacity];
}

// constructor - params: DSVector<T>& other
template <class T>
DSVector<T>::DSVector(const DSVector<T>& other){
    numIndexes = other.numIndexes;
    capacity = other.capacity;
    resizeIncrement = other.resizeIncrement;
    data = new T[capacity];

    for(int i = 0; i < numIndexes; i++){
        this->data[i] = other.data[i];
    }
}

// getter - numIndexes
template <class T>
int DSVector<T>::getNumIndexes() const{
    return numIndexes;
}

// setter - resizeIncrement (no data change till resize occurs)
template <class T>
void DSVector<T>::setResizeIncrement(const int resizeIncrement){
    this->resizeIncrement = resizeIncrement;
}

// getter - resizeIncrement
template <class T>
int DSVector<T>::getResizeIncrement() const{
    return resizeIncrement;
}

// getter - capacity
template <class T>
int DSVector<T>::getCapacity() const{
    return capacity;
}

// setter - capacity
template <class T>
void DSVector<T>::setCapacity(const int capacity){
    if(this->capacity == capacity){
        return;
    }

    if(capacity <= numIndexes){
        this->capacity = numIndexes;
    } else {
        this->capacity = capacity;
    }

    T* tempArray = new T[this->capacity];

    for(int i = 0; i < numIndexes; i++){
        tempArray[i] = data[i];
    }

    delete[] data;

    data = tempArray;
}

// creates new vector with capacity equal to numIndexes
template <class T>
void DSVector<T>::shrink(){
    setCapacity(numIndexes);
}

// adds element to back of data array - params: T newElement
template <class T>
void DSVector<T>::pushBack(const T& newElement){
    // expand data if needed
    if(numIndexes == capacity){
        capacity = numIndexes + resizeIncrement - (numIndexes % resizeIncrement);

        T* tempArray = new T[capacity];

        for(int i = 0; i < numIndexes; i++){
            tempArray[i] = data[i];
        }

        delete[] data;

        data = tempArray;
    }

    data[numIndexes++] = newElement;

}

// removes last element of data array
template <class T>
void DSVector<T>::removeLast(){
    numIndexes--;
}

// deletes data and creates an empty array in its place
template <class T>
void DSVector<T>::clear(){
    delete[] data;

    numIndexes = 0;

    data = new T[capacity];
}

// returns the first element of data array
template <class T>
T& DSVector<T>::front() const{
    return data[0];
}

// returns last element of data arary
template <class T>
T& DSVector<T>::back() const{
    return data[numIndexes - 1];
}

// returns pointer to first element of data
template <class T>
T* DSVector<T>::getData() const{
    return data;
}

// sets this to the passed in vector - params: const DSVector<T>& other
template <class T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T>& other){
    delete[] data;

    numIndexes = other.numIndexes;
    capacity = other.capacity;
    resizeIncrement = other.resizeIncrement;

    data = new T[capacity];

    for(int i = 0; i < numIndexes; i++){
        data[i] = other.data[i];
    }

    return *this;
}

// adds then returns passed in vector to the end of this - params: const DSVector<T>& other
template <class T>
DSVector<T>& DSVector<T>::operator+=(const DSVector<T>& other){
    int oldSize = numIndexes;
    numIndexes += other.numIndexes;

    // keep capacity as a multiple of the resizeIncrement
    int newCap = numIndexes + resizeIncrement - (numIndexes % resizeIncrement);

    if(capacity < newCap){
        capacity = newCap;

        T* tempArray = new T[newCap];

        for(int i = 0; i < oldSize; i++){
            tempArray[i] = data[i];
        }

    delete[] data;

        data = tempArray;
    }

    for(int i = oldSize; i < numIndexes; i++){
        data[i] = other.data[i - oldSize];
    }

    return *this;
}

// adds then returns passed in element to the end of this - params: const T& element
template <class T>
DSVector<T>& DSVector<T>::operator+=(const T& element){
    if(capacity == numIndexes){
        capacity += resizeIncrement;
        
        T* tempArray = new T[capacity];
        
        for(int i = 0; i < numIndexes; i++){
            tempArray[i] = data[i];
        }
        delete[] data;

        data = tempArray;
    }

    data[numIndexes++] = element;

    return *this;
}

// returns this vector added to the passed in vector - params: const DSVector<T>& other
template <class T>
DSVector<T> DSVector<T>::operator+(const DSVector<T>& other) const{
    DSVector<T> result = *this;
    result += other;
    return result;
}

// returns this vector added to the passed in element - params: const T& element
template <class T>
DSVector<T> DSVector<T>::operator+(const T& element) const{
    DSVector<T> result = *this;
    result += element;
    return result;
}

// returns true if passed in vector has the same values as data - params: const DSVector<T>& other
template <class T>
bool DSVector<T>::operator==(const DSVector<T>& other) const{
    if(numIndexes != other.numIndexes){
        return false;
    }

    for(int i = 0; i < numIndexes; i++){
        if(data[i] != other.data[i]){
            return false;
        }
    }

    return true;
}

// returns true if passed in vector does not have the same values as data - params: const DSVector<T>& other
template <class T>
bool DSVector<T>::operator!=(const DSVector<T>& other) const{
    return !(*this == other);
}

// returns the value at the passed in index - params: const int index
template <class T>
T DSVector<T>::operator[](const int index) const{
    return data[index];
}

// default destructor
template<class T>
DSVector<T>::~DSVector(){
    delete[] data;
}

#endif // DSVECTOR_H
