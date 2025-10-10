#ifndef DSADJLIST_H
#define DSADJLIST_H

#include "../DSDoublyLL/dsdoublyll.h"

template <class T>
class DSAdjList
{
private:
    DSDoublyLL<DSDoublyLL<T>> data;
public:
    /**
     * @brief DSAdjList - default constructor
     */
    DSAdjList();

    /**
     * @brief DSAdjList - copy constructor
     * @param other - list to copy
     */
    DSAdjList(DSAdjList<T>& other);

    /**
     * @brief GetConnectedNode - returns all nodes connected to the given node
     * @param nodeData - data of the source node for connections
     * @return doubly linked list of nodes
     */
    DSDoublyLL<T> GetConnectedNodes(T nodeData);

    /**
     * @brief addNode - adds a new node to the list
     * @param nodeData - the value of the new node
     */
    void addNode(T nodeData);

    /**
     * @brief addEdge - adds a connection between two nodes and adding the nodes if needed
     * @param node1 - first node of the edge
     * @param node2 - second node of the edge
     */
    void addEdge(T node1, T node2);

    /**
     * @brief remove - removes a node and all of its edges
     * @param nodeData - the value of the node
     */
    void removeNode(T nodeData);

    /**
     * @brief removeEdge - removes an edge from the list
     * @param node1 - first node of the edge
     * @param node2 - second node of the edge
     */
    void removeEdge(T node1, T node2);

    /**
     * @brief contains - returns true if the given node is in the list
     * @param node - node to search for
     * @return true if node is in the list
     */
    bool contains(T node);

    /**
     * @brief operator = :  sets this list equal to the list passed in
     * @param other - reference to target list
     * @return returns this
     */
    DSAdjList<T>& operator=(const DSAdjList<T>& other);

    /**
     * @brief operator == :  compares this list against another list
     * @param other - reference to target list
     * @return true if the lists have equal values
     */
    bool operator==(const DSAdjList<T>& other) const;

    /**
     * @brief operator != : compares this list against another list
     * @param other - reference to target list
     * @return false if the lists have equal values
     */
    bool operator!=(const DSAdjList<T>& other) const;

    /**
     * @brief ~DSAdList - default destructor
     */
    ~DSAdjList();
};


/**
 * @brief DSAdjList - default constructor
 */
template <class T>
DSAdjList<T>::DSAdjList(){}

/**
 * @brief DSAdjList - copy constructor
 * @param other - list to copy
 */
template <class T>
DSAdjList<T>::DSAdjList(DSAdjList<T>& other){
    data = other.data;
}

/**
 * @brief GetConnectedNode - returns all linked list that is the tail of the given element's list
 * @param nodeData - data of the source node for connections
 * @return doubly linked list of nodes
 */
template <class T>
DSDoublyLL<T> DSAdjList<T>::GetConnectedNodes(T nodeData){
    for(auto list : data){
        if(list[0] == nodeData){
            DSDoublyLL<T> output = list;
            output.removeAt(0);
            return output;
        }
    }

    return DSDoublyLL<T>();
}

/**
 * @brief addNode - creates a new list at the end of the data list for the given node
 * @param nodeData - the value of the new node
 */
template <class T>
void DSAdjList<T>::addNode(T nodeData){
    if(contains(nodeData)){
        return;
    }

    DSDoublyLL<T> newNode;
    newNode.pushBack(nodeData);
    data.pushBack(newNode);
}

/**
 * @brief addEdge - adds the given nodes to eachother's lists
 * @param node1 - first node of the edge
 * @param node2 - second node of the edge
 */
template <class T>
void DSAdjList<T>::addEdge(T node1, T node2){
    bool node1Found = false;
    bool node2Found = false;

    for(auto i = data.begin(); i != data.end() && (!node2Found || !node1Found); i++){
        if((*i)[0] == node1){
            if(i->contains(node2)){
                return;
            }
            i->pushBack(node2);
            node1Found = true;
        } else if((*i)[0] == node2){
            if(i->contains(node1)){
                return;
            }
            i->pushBack(node1);
            node2Found = true;
        }
    }

    if(!node1Found){
        addNode(node1);
        data[data.size() - 1].pushBack(node2);
    }

    if(!node2Found){
        addNode(node2);
        data[data.size() - 1].pushBack(node1);
    }
}

/**
 * @brief remove - removes a node's list and all of its occurances in other lists
 * @param nodeData - the value of the node
 */
template <class T>
void DSAdjList<T>::removeNode(const T nodeData){
    for(auto i = data.begin(); i != data.end();){
        if((*i)[0] == nodeData){
            i = data.removeAt(i);
        } else {
            i->remove(nodeData, true);
            i++;
        }
    }
}

/**
 * @brief removeEdge - removes the given nodes from each others lists
 * @param node1 - first node of the edge
 * @param node2 - second node of the edge
 */
template <class T>
void DSAdjList<T>::removeEdge(const T node1, const T node2){
    for(auto& list : data){
        if(list[0] == node1){
            list.remove(node2, true);
        } else if(list[0] == node2){
            list.remove(node1, true);
        }
    }
}

/**
 * @brief contains - iterates through data and returns true if node is the head of any list
 * @param query - nade to search for in data
 * @return true if node is in data
 */
template<class T>
bool DSAdjList<T>::contains(T query)
{
    for(auto list : data){
        if(list[0] == query){
            return true;
        }
    }

    return false;
}

/**
 * @brief operator = :  sets this list equal to the list passed in
 * @param other - reference to target list
 * @return returns this
 */
template <class T>
DSAdjList<T>& DSAdjList<T>::operator=(const DSAdjList<T>& other){
    data = other.data;
}

/**
 * @brief operator == :  compares this list against another list by checking for the same nodes and connections
 * @param other - reference to target list
 * @return true if the list contains the same connections
 */
template <class T>
bool DSAdjList<T>::operator==(const DSAdjList<T>& other) const{
    if(data.size() != other.data.size()){
        return false;
    }

    if(data.size() == 0){
        return true;
    }

    DSDoublyLL<DSDoublyLL<T>> tempData = data;
    DSDoublyLL<DSDoublyLL<T>> tempOther = other.data;

    for (auto i = tempData.begin(); i != tempData.end(); i++) {
        auto match = tempOther.end();

        for (auto j = tempOther.begin(); j != tempOther.end(); j++){
            if (i->unorderedEquals(*j)) {
                match = j;
                break;
            }
        }

        if (match == tempOther.end()) {
            return false;
        }

        tempOther.removeAt(match);
    }

    return true;
}

/**
 * @brief operator != :  pipes to operator== and flips the return
 * @param other - reference to target list
 * @return opposite of operator==
 */
template <class T>
bool DSAdjList<T>::operator!=(const DSAdjList<T>& other) const{
    return !(*this == other);
}

/**
 * @brief ~DSAdList - default destructor
 */
template <class T>
DSAdjList<T>::~DSAdjList(){}

#endif // DSADJLIST_H
