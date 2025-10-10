#ifndef DSNODE_H
#define DSNODE_H

template <class T>
class DSNode{
    public:
        DSNode* next = nullptr;
        DSNode* prev = nullptr;

        T data;

        /**
         * @brief DSNode - default constructor
         */
        DSNode();

        /**
         * @brief DSNode - constructor
         * @param data - value to set as this node's data
         */
        DSNode(T data);

        /**
         * @brief DSNode - copy consructor
         * @param other - node to copy
         */
        DSNode(const DSNode<T>& other);

        /**
         * @brief operator =
         * @param data - new data to replace current
         * @return reference to this node
         */
        DSNode<T>& operator=(const T data);

        /**
         * @brief ~6DSNode - default destructor
         */
        ~DSNode();
};

/**
 * @brief DSNode - default constructor
 */
template <class T>
DSNode<T>::DSNode(){

}

/**
 * @brief DSNode::DSNode - constrcutor
 * @param data - data of the new node
 */
template <class T>
DSNode<T>::DSNode(T data) : data(data){}

/**
 * @brief DSNode::DSNode - copy constructor
 * @param other - node to be copied
 */
template <class T>
DSNode<T>::DSNode(const DSNode<T>& other) : data(other.data){}

/**
 * @brief operator =
 * @param data - new data to replace current
 * @return reference to this node
 */
template <class T>
DSNode<T>& DSNode<T>::operator=(const T data){
    this->data = data;
}

/**
 * @brief ~DSNode - default destructor
 */
template <class T>
DSNode<T>::~DSNode(){

}

#endif // DSNODE_H
