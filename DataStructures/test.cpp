#include "catch.hpp"
#include <type_traits>

#include <fstream>
#include <iostream>

#include "DSString/dsstring.h"
#include "DSVector/dsvector.h"
#include "DSStack/dsstack.h"
#include "DSDoublyLL/dsdoublyll.h"
#include "DSAdjList/dsadjlist.h"

/*
 *  DSString
 */
TEST_CASE("Data_Structures_String", "[String][Data_Structures_Test]"){
    DSString testStringArray[3];

    testStringArray[0] = DSString("test1");
    testStringArray[1] = DSString("yo");
    testStringArray[2] = DSString();

    DSString testStr = "testStr";

    DSString nonPtrArray[1];
    nonPtrArray[0] = "nonPtr";

    SECTION("String concatination operators"){
        REQUIRE((testStringArray[0] += "yo") == "test1yo");
        testStringArray[0] = "test1";

        REQUIRE((testStringArray[1] += testStr) == "yotestStr");
        testStringArray[1] = "yo";

        REQUIRE((testStringArray[1] += 'x') == "yox");
        testStringArray[1] = "yo";
    }

    SECTION("String functions"){

        // size()
        REQUIRE(testStringArray[0].size() == 5);
        REQUIRE(testStringArray[2].size() == 0);

        // findChar(const char searchChar)
        REQUIRE(testStringArray[0].findChar('s') == 2);
        REQUIRE(testStringArray[0].findChar('y') == -1);

        // findChar(const char searchChar, const int numInstance)
        REQUIRE(testStringArray[0].findChar('t', 1) == 0);
        REQUIRE(testStringArray[0].findChar('t', 2) == 3);
        REQUIRE(testStringArray[0].findChar('t', 3) == -1);

        // deleteIndex(const int index)
        testStringArray[0].deleteIndex(1);
        REQUIRE(testStringArray[0] == "tst1");
        testStringArray[0].deleteIndex(3);
        REQUIRE(testStringArray[0] == "tst");
        testStringArray[0] = "test1";
    }

    SECTION("String Comparison Operators"){

        REQUIRE(!(testStringArray[2] == "notEmpty"));

        REQUIRE(testStr == "testStr");
        REQUIRE(nonPtrArray[0] == "nonPtr");


        REQUIRE(testStringArray[0] == "test1");
        REQUIRE(!(testStringArray[0] == testStringArray[1]));

        REQUIRE(!(testStringArray[0] < "test1"));
        REQUIRE(testStringArray[1] < testStringArray[0]);

        REQUIRE(!(testStringArray[0] > "test1"));
        REQUIRE(testStringArray[0] > testStringArray[1]);

        REQUIRE(testStringArray[0] <= "test1");
        REQUIRE(testStringArray[1] <= testStringArray[0]);

        REQUIRE(testStringArray[0] >= "test1");
        REQUIRE(testStringArray[0] >= testStringArray[1]);

        REQUIRE(testStringArray[2] == "");
    }

    SECTION("String Indexing"){
        REQUIRE((testStringArray[0])[0] == 't');
        REQUIRE((testStringArray[1])[1] == 'o');
        REQUIRE((testStringArray[2])[0] == '\0');
    }

    SECTION("Substrings"){
        REQUIRE(testStringArray[0].substring(1, 3) == "est");
        REQUIRE(testStringArray[1].substring(0, 1) == "y");

        REQUIRE(testStringArray[0].substring(3,0) == "");
        REQUIRE(testStringArray[0].substring(testStringArray[0].size() - 1, 3) == "");
        REQUIRE(testStringArray[0].substring(0, 0) == "");


        REQUIRE(testStringArray[0].substring(2, -5) == "tes");
        REQUIRE(testStringArray[0].substring(2, -2) == "es");
        REQUIRE(testStringArray[0].substring(0, -3) == "t");
        REQUIRE(testStringArray[0].substring(testStringArray[0].size() - 1, -2) == "t1");

        REQUIRE(testStringArray[0].substring(3, 999) == "t1");

        REQUIRE(testStringArray[0].substring(1) == "est1");
    }

    SECTION("c_string"){
        REQUIRE(testStringArray[0] == testStringArray[0].c_str());
        REQUIRE(testStringArray[0] == testStringArray[0].c_str());
    }

    SECTION("File input/output"){
        // output
        DSString filePath = "./testFile.txt";

        std::ofstream testOutFile;
        testOutFile.open(filePath.c_str());

        DSString testText1, testText2;
        testText1 = "hello";
        testText2 = "Test Test";

        testOutFile << DSString(testText1) << "\n";
        testOutFile << DSString(testText2) << std::endl;

        testOutFile.close();

        // input
        DSString fileTestString;

        std::ifstream testInFile;
        testInFile.open(filePath.c_str());

        testInFile >> fileTestString;
        REQUIRE(fileTestString == testText1);

        testInFile >> fileTestString;
        REQUIRE(fileTestString == testText2);

        testInFile.close();

        std::ofstream clearFile;
        clearFile.open(filePath.c_str());
        clearFile.close();
    }

    SECTION("Iteration"){
        // test1 with all characters ++
        DSString test = "uftu2";

        for(auto& it : test){
            it--;
        }

        REQUIRE(testStringArray[0] == test);
    }
}

/*
 *  DSVector
 */
TEST_CASE("Data_Structures_Vector", "[Vector][Data_Structures_Test]"){
    const int intArray1[3] = {0, 1, 2};
    int arr1StartSize = 3;
    const int intArray2[3] = {3, 4, 5};
    int arr2StartSize = 3;
    const int intArray3[6] = {0, 1, 2, 3, 4, 5};
    int arr3StartSize = 6;

    DSVector<int> numVect1(8);
    DSVector<int> numVect1Copy;
    DSVector<int> numVect2(3);
    DSVector<int> numVect3;

    for(int element : intArray1){
        numVect1.pushBack(element);
    }

    for(int element : intArray2){
        numVect2.pushBack(element);
    }

    for(int element : intArray3){
        numVect3.pushBack(element);
    }

    numVect1Copy = numVect1;

    DSVector<int> debugVect;
    DSVector<int> debugVectEqual;
    for(int element : intArray3){
        debugVect.pushBack(element);
        debugVectEqual.pushBack(element);
    }

    SECTION("Vector getters and setters"){
        // getters
        REQUIRE(numVect1.getNumIndexes() == 3);
        REQUIRE(numVect1.getCapacity() == 8);
        REQUIRE(numVect1.getResizeIncrement() == 8);

        // setters
        numVect1.setCapacity(9);
        numVect1.setResizeIncrement(10);
        REQUIRE(numVect1.getCapacity() == 9);
        REQUIRE(numVect1.getResizeIncrement() == 10);

        numVect1.setCapacity(8);
        numVect1.setResizeIncrement(8);
    }

    SECTION("Vector indexing"){
        REQUIRE(numVect1[0] == 0);
        REQUIRE(numVect1[2] == 2);
    }

    SECTION("Vector Comparison Operators"){
        REQUIRE(numVect1 == numVect1Copy);
        REQUIRE(numVect1 != numVect2);
    }

    SECTION("Vector Concatination"){
        numVect1 += numVect2;
        REQUIRE(numVect1 == numVect3);

        numVect1 = numVect1Copy;


        REQUIRE(numVect3 == (numVect1 + numVect2));
        REQUIRE(numVect1 == numVect1Copy);


        numVect1 += 3;
        numVect1 += 4;
        REQUIRE(numVect3 == (numVect1 + 5));

        numVect1 = numVect1Copy;

        // low capacities
        numVect1.setCapacity(2);
        numVect1 += numVect2;
        REQUIRE(numVect1 == numVect3);

        numVect1 = numVect1Copy;

        numVect1.setCapacity(2);
        REQUIRE(numVect3 == (numVect1 + numVect2));
        REQUIRE(numVect1 == numVect1Copy);

        numVect1.setCapacity(2);
        numVect1 += 3;
        numVect1 += 4;
        REQUIRE(numVect3 == (numVect1 + 5));

        numVect1 = numVect1Copy;
    }

    SECTION("Iteration"){
        for(auto& it : numVect1){
            it += 3;
        }

        REQUIRE(numVect1 == numVect2);

        numVect1 = numVect1Copy;
    }
}

/*
 *  DSDoublyLL
 */
TEST_CASE("Data_Structures_Doubly_Linked_List", "[Doubly_Linked_List][Data_Structures_Test]"){
    const int intArray1[3] = {0, 1, 2};
    int arr1StartSize = 3;
    const int intArray2[3] = {3, 4, 5};
    int arr2StartSize = 3;
    const int intArray3[6] = {0, 1, 2, 3, 4, 5};
    int arr3StartSize = 6;
    const int intArray4[3] = {1, 2, 4};
    int arr4StartSize = 3;
    const int intArray5[6] = {4, 5, 3, 2, 1, 0};
    int arr5StartSize = 6;

    DSDoublyLL<int> numList1, numList2, numList3, numList4, numList5;
    DSDoublyLL<int> numList1Copy;

    for(int element : intArray1){
        numList1.pushBack(element);
        numList1Copy.pushBack(element);
    }

    for(int element : intArray2){
        numList2.pushBack(element);
    }

    numList3 = DSDoublyLL<int>(intArray3, arr3StartSize);
    numList4 = DSDoublyLL<int>(intArray4, arr4StartSize);
    numList5 = DSDoublyLL<int>(intArray5, arr5StartSize);


    SECTION("Comparison Operators"){
        REQUIRE(numList1 == numList1Copy);

        for(int i = 0; i < numList2.getNumIndexes(); i++){
            numList1.pushBack(numList2[i]);
        }

        REQUIRE(numList1 == numList3);

        numList1 = numList1Copy;

        REQUIRE(numList1 != numList2);

        REQUIRE(numList3.unorderedEquals(numList5));
    }

    SECTION("indexing"){
        REQUIRE(numList1[0] == 0);
        REQUIRE(numList3[0] == 0);

        REQUIRE(numList1[2] == 2);
        REQUIRE(numList3[4] == 4);

        REQUIRE(numList1[-2] == 1);
        REQUIRE(numList3[-4] == 2);

        numList1[1] = 2;
        REQUIRE(numList1[1] == 2);
        numList1[1] = 1;
        REQUIRE(numList1[1] == 1);
    }

    SECTION("Other Operators"){
        // adding
        REQUIRE(numList3 == numList1 + numList2);
        REQUIRE(numList3 == numList1 + 3 + 4 + 5);

        // adding and setting equal
        numList1 += numList2;
        REQUIRE(numList3 == numList1);
        numList1 = numList1Copy;

        numList1 += 3;
        numList1 += 4;
        numList1 += 5;
        REQUIRE(numList3 == numList1);
        numList1 = numList1Copy;


        // size
        REQUIRE(numList1.size() == 3);
    }

    SECTION("Insertion and Removal"){
        // insertion
        numList4.insert(0, 0);
        numList4.insert(3, 3);
        numList4.insert(5, 5);

        REQUIRE(numList4 == numList3);

        // removal at index
        numList4.removeAt(5);
        numList4.removeAt(1);
        numList4.removeAt(0);
        numList4.removeAt(0);

        numList4.insert(2, 5);

        REQUIRE(numList4 == numList2);

        // removal of element
        numList1.pushBack(99);
        numList1.pushBack(99);
        numList1.insert(2, 99);
        numList1.insert(4, 99);
        numList1.insert(6, 99);

        numList1.remove(99, true);

        REQUIRE(numList1.size() == numList1Copy.size() + 4);
        REQUIRE(numList1[2] != 99);
        REQUIRE(numList1.contains(99));

        numList1.pushFront(99);
        numList1.pushFront(99);

        numList1.remove(99);

        REQUIRE(numList1 == numList1Copy);

        // reset list
        numList4.removeAt(2);
        numList4.removeAt(0);

        numList4.pushFront(2);
        numList4.pushFront(1);

        // clearing
        numList1.clear();

        REQUIRE(numList1 == DSDoublyLL<int>());

        numList1 = numList1Copy;

        numList1.removeAt(0);
        numList1.removeAt(0);
        numList1.removeAt(0);

    }

    SECTION("popping"){
        for(int i = 0; i < 3; i++){
            numList3.popBack();
        }
        REQUIRE(numList3 == numList1);

        numList3 += numList2;

        for(int i = 0; i < 3; i++){
            numList3.popFront();
        }
        REQUIRE(numList3 == numList2);

        numList3 = numList1 + numList2;
    }

    SECTION("other"){
        REQUIRE(numList1.contains(0));
        REQUIRE(!numList1.contains(6));

        numList1.removeAt(0);
        numList1.removeAt(0);
        numList1.removeAt(0);
    }

    SECTION("Iteration"){
        for(auto& it : numList1){
            it += 3;
        }

        REQUIRE(numList1 == numList2);

        numList1 = numList1Copy;

        for(auto i = numList3.begin(); i != numList3.end();){
            if(numList2.contains(*i)){
                i = numList3.removeAt(i);
            } else {
                i++;
            }
        }
        REQUIRE(numList3 == numList1);

        numList3 += numList2;
    }
}

/*
 *  DSStack
 */
TEST_CASE("Data_Structures_List_Stack", "[Stack][Data_Structures_Test]"){
    const int intArray1[3] = {0, 1, 2};
    int arr1StartSize = 3;
    const int intArray2[3] = {3, 4, 5};
    int arr2StartSize = 3;
    const int intArray3[6] = {0, 1, 2, 3, 4, 5};
    int arr3StartSize = 6;

    DSStack<int> numStack1;
    DSStack<int> numStack1Copy;
    DSStack<int> numStack2;
    DSStack<int> numStack3;

    for(int element : intArray1){
        numStack1.push(element);
        numStack1Copy.push(element);
    }

    for(int element : intArray2){
        numStack2.push(element);
    }

    for(int element : intArray3){
        numStack3.push(element);
    }

    SECTION("Operators"){

        REQUIRE(numStack1 == numStack1Copy);

        numStack1 = numStack2;

        REQUIRE(numStack1 == numStack2);

        numStack1 = numStack1Copy;
    }

    SECTION("Getters"){
        REQUIRE(numStack1.size() == 3);
    }

    SECTION("Peek and Pop"){
        REQUIRE(numStack1.peek() == 2);
        numStack1.pop();
        REQUIRE(numStack1.peek() == 1);
        numStack1.pop();
        REQUIRE(numStack1.peek() == 0);

        numStack1 = numStack1Copy;
    }

    SECTION("Push"){
        numStack1.push(3);
        REQUIRE(numStack1.size() == 4);
        REQUIRE(numStack1.peek() == 3);

        numStack1.push(4);
        REQUIRE(numStack1.size() == (5));
        REQUIRE(numStack1.peek() == 4);

        numStack1 = numStack1Copy;
    }
}

/*
 *  DSAdjList
 */
TEST_CASE("Data_Structures_Adjacency_List", "[Adjacency_List][Data_Structures_Test]"){
    char pairings1[6][2] = {{'A', 'B'}, {'A', 'C'}, {'A', 'D'},
                            {'B', 'D'}, {'B', 'C'},
                            {'D', 'E'}};
    int pairings1Count = 6;

    char pairings2[8][2] = {{'A', 'B'}, {'A', 'C'}, {'A', 'D'}, {'A', 'F'},
                            {'B', 'D'}, {'B', 'C'},
                            {'C', 'F'},
                            {'D', 'E'}};
    int pairings2Count = 8;

    char pairings1_2Difference[2][2] = {{'A', 'F'},{'C', 'F'}};

    DSAdjList<char> list1, list2;

    for(int i = 0; i < pairings1Count; i++){
        list1.addEdge(pairings1[i][0], pairings1[i][1]);
    }

    for(int i = 0; i < pairings2Count; i++){
        list2.addEdge(pairings2[i][0], pairings2[i][1]);
    }

    DSAdjList<char> list1Copy = list1;

    SECTION("Connection Retrieval"){
        char tempArr[3] = {'B', 'C', 'D'};
        DSDoublyLL<char> temp = DSDoublyLL<char>(tempArr, 3);

        DSDoublyLL<char> connections = list1.GetConnectedNodes('A');

        REQUIRE(connections == temp);
    }

    SECTION("Comparison Operators"){
        REQUIRE(list1 == list1Copy);

        REQUIRE(list1 != list2);
    }

    SECTION("Adding and Removing"){
        list1.addNode('F');
        list1.addEdge('A', 'F');
        list1.addEdge('C', 'F');

        REQUIRE(list1 == list2);

        list1.removeNode('F');

        REQUIRE(list1 == list1Copy);

        list1.addEdge('A', 'F');
        list1.addEdge('C', 'F');

        REQUIRE(list1 == list2);

        list1.removeEdge('A', 'F');
        list1.removeEdge('C', 'F');

        list1Copy.addNode('F');

        REQUIRE(list1 == list1Copy);

        list1.removeNode('F');
        list1Copy.removeNode('F');

        REQUIRE(list1 == list1Copy);
    }
}

















