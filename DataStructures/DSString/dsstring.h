#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>

class DSString
{
private:
    /**
     * @brief The iterator struct - iterator for the string class
     */
    struct iterator{
    public:
        /**
         * @brief iterator - constructor
         * @param ptr - pointer to start iteration from
         */
        iterator(char* ptr): ptr(ptr){}

        /**
         * @brief operator * - dereferences pointer
         * @return - reference of the character at the pointer's location
         */
        char& operator*(){
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
        char* ptr;
    };

public:
    /**
     * @brief DSString - default constructor
     */
    DSString();

    /**
     * @brief DSString - constructor
     * @param data - c-string to turn into string
     */
    DSString(const char* data);

    /**
     * @brief DSString - copy constructor
     * @param other - string to copy
     */
    DSString(const DSString& other);

    /**
     * @brief findChar - find the first instance of a character in string
     * @param searchChar - character to find
     * @return
     */
    int findChar(const char searchChar) const;

    /**
     * @brief findChar - finds the location of the numInstance instance of the passed char
     * @param searchChar - character to search for
     * @param numInstance - n'th instance to search for
     * @return index of found char
     */
    int findChar(const char searchChar, const int numInstance) const;

    /**
     * @brief deleteIndex - removes character from given index
     * @param index - index in which to remove
     */
    void deleteIndex(const int index);

    /**
     * @brief ~DSString - Default destructor
     */
    ~DSString();

    /**
     * @brief operator = : assignment operator
     * @param data - character array to set this equal to
     * @return
     */
    DSString& operator=(const char* data);
    // assignment operator - params: const DSString& other
    DSString& operator=(const DSString& other);

    // concatination operator - params: const char* data
    DSString operator+(const char* data) const;
    // concatination operator - params: const char data
    DSString operator+(const char data) const;
    // concatination operator - params: const DSString& data
    DSString operator+(const DSString& data) const;

    // assign/concat operator - params: const char* data
    DSString& operator+=(const char* data);
    // assign/concat operator - params: const char data
    DSString& operator+=(const char data);
    // assign/concat operator - params: const DSString& other
    DSString& operator+=( const DSString& other);

    // Comparison operator - params: const char* other
    bool operator==(const char* other) const;
    // Comparison operator - params: const DSString& other
    bool operator==(const DSString& other) const;

    // less than operator - params: const char* other
    bool operator<(const char* other) const;
    // less than operator - params: const DSString& other
    bool operator<(const DSString& other) const;

    // greater than operator - params: const char* other
    bool operator>(const char* other) const;
    // greater than operator - params: const DSString& other
    bool operator>(const DSString& other) const;

    // less than or equal operator - params: const char* other
    bool operator<=(const char* other) const;
    // less than or equal operator - params: const DSString& other
    bool operator<=(const DSString& other) const;

    // greater than or equal operator - params: const char* other
    bool operator>=(const char* other) const;
    // greater than or equal operator - params: const DSString& other
    bool operator>=(const DSString& other) const;

    // index operator - params: const int index
    char& operator[](const int index) const;


    // returns size of data array
    int size() const;

    // returns sub-string between the given indexes
    DSString substring(int startingIndex, int len) const;
    // returns sub-string starting at the given index
    DSString substring(int startingIndex) const;

    // returns data cstring
    char* c_str() const;

    friend std::ostream& operator<<(std::ostream& stream, const DSString& theString);

    friend std::istream& operator>>(std::istream& stream, DSString& theString);

    inline iterator begin(){
        return iterator(data);
    }

    inline iterator end(){
        return iterator(data + size());
    }

private:
    char* data;
};

#endif // DSSTRING_H
