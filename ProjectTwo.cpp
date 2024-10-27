//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Jennifer Rebella
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : ABCU Courses
//============================================================================
#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include <Windows.h>
#include <vector>
#include <parser.h>

#include "CSVparser.hpp"

using namespace std;

const unsigned int DEFAULT_SIZE = 8;
//Course struct to hold course information
struct Course {
    string courseID;
    string courseName;
    vector<string> prerecList;
};
//Hash Table creation
class HashTable {
private:
    //Define structures to hold the courses
    struct Node {
        Course course;
        unsigned int key;
        Node* next;
        //default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }
        //initialize with a course
        Node(Course aCourse) : Node() {
            course = aCourse;
        }
        //initialize with a course and a key
        Node(Course aCourse, unsigned int aKey) : Node(aCourse) {

        }
    };
    vector<Node> nodes;
    unsigned int tableSize = DEFAULT_SIZE;
    unsigned int hash(int key);
public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Course course);
    void PrintAll();
    void Remove(string courseID);
    Course Search(string courseID);
    size_t Size();
};
/**
 * Default constructor
 */
HashTable::HashTable() {
    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    // resize nodes size
    this->tableSize = size;
    nodes.resize(size);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // erase nodes beginning
    nodes.erase(nodes.begin());
}
//load courses
void loadCourses(string csvPath, HashTable* courseList) {
    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);
    vector<string> stringTokens;
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Course aCourse;
            aCourse.courseID = file[i][1];
            aCourse.courseName = file[i][0];


            for (unsigned int i = 2; i < stringTokens.size(); i++) {

                aCourse.prerecList.push_back(stringTokens.at(i));
            }


            // push this bid to the end
            courseList->Insert(aCourse);
        }
    }
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */

unsigned int HashTable::hash(int key) {
        // return key tableSize
    return key % tableSize;
    }

//Splits by comma code from from www.codegrepper.com/code-examples/cpp/c%2B%2B+split+string+by+delimiter
vector<string> Split(string lineFeed) {

    char delim = ',';

    lineFeed += delim; //includes a delimiter at the end so last word is also read
    vector<string> lineTokens;
    string temp = "";
    for (int i = 0; i < lineFeed.length(); i++) {
        if (lineFeed[i] == delim) {
            lineTokens.push_back(temp); //store words in token vector
            temp = "";
            i++;
        }
        temp += lineFeed[i];
    }
    return lineTokens;
}

    /**
     * Print a course
     */
void PrintCourse(Course aCourse) {
    // output courseID, courseName, and cout << "Prerequisites: ";
    cout << aCourse.courseID << " | " << aCourse.courseName << endl;
    cout << "Prerequisites: ";
    if (aCourse.prerecList.empty()) {
        cout << "None" << endl;
    }
    else {
        for (unsigned int i = 0; i < aCourse.prerecList.size(); i++) {
            cout << aCourse.prerecList.at(i);
            // if more than more prerecquiste prints a comma
            if (aCourse.prerecList.size() > 1 && i < aCourse.prerecList.size() - 1) {
                cout << ", ";
            }
            }
        }    cout << endl;
}

void convertCase(string& toConvert) {
    for (unsigned int i = 0; i < toConvert.length(); i++) {
        if (isalpha(toConvert[i])) {
            toConvert[i] = toupper(toConvert[i]);
        }
    }
}
 HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    // resize nodes size
    this->tableSize = size;
    nodes.resize(size);
}

    /**
    * Insert a course
    *
    * @param course The course to insert
    */
void HashTable::Insert(Course course) {
// create the key for the given course
    unsigned key = hash(atoi(course.courseID.c_str()));
    // retrieve node using key
    Node* oldNode = &(nodes.at(key));
    // if no entry found for the key
    if (oldNode == nullptr) {
            // assign this node to the key position
            Node* newNode = new Node(course, key);
            nodes.insert(nodes.begin() + key, (+newNode));
        }
        // else if node is not used
        else {
            // assing old node key to UNIT_MAX, set to key, set old node to course and old node next to null pointer
            if (oldNode->key == UINT_MAX) {
                oldNode->key = key;
                oldNode->course = course;
                oldNode->next = nullptr;
            }
            // else find the next open node
            else {
                while (oldNode->next != nullptr) {
                    //Collision,find next open node
                    oldNode = oldNode->next;
                }
                // add new newNode to end
                oldNode->next = new Node(course, key);
            }
        }
    }
/*
*
*Print all course
*/
void HashTable::PrintAll() {
    Course aCourse;
    // for node begin to end iterate
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        //   if key not equal to UINT_MAx
        if (it->key != UINT_MAX) {
            // output key, bidID, title, amount and fund
            cout << aCourse.courseID << " | " << aCourse.courseName << endl;
            cout << "Prerequisites: ";
            if (aCourse.prerecList.empty()) {
                cout << "None" << endl;
            }
            else {
                for (unsigned int i = 0; i < aCourse.prerecList.size(); i++) {
                    cout << aCourse.prerecList.at(i);
                    // if more than more prerecquiste prints a comma
                    if (aCourse.prerecList.size() > 1 && i < aCourse.prerecList.size() - 1) {
                        cout << ", ";
                    }
                }
            }
            cout << endl;
            // node is equal to next iter
            Node* node = it->next;
            // while node not equal to nullptr
            while (node != nullptr) {
                // output key, bidID, title, amount and fund
                cout << aCourse.courseID << " | " << aCourse.courseName << endl;
                cout << "Prerequisites: ";
                if (aCourse.prerecList.empty()) {
                    cout << "None" << endl;
                }
                else {
                    for (unsigned int i = 0; i < aCourse.prerecList.size(); i++) {
                        cout << aCourse.prerecList.at(i);
                        // if more than more prerecquiste prints a comma
                        if (aCourse.prerecList.size() > 1 && i < aCourse.prerecList.size() - 1) {
                            cout << ", ";
                        }
                    }
                }    cout << endl;
                // node is equal to next node
                node = node->next;
            }
        }
    }
}
    /**
    *
    * @param courseID The course id to search for a course
    */
    void HashTable::Remove(string courseID) {
        // set key equal to hash atoi courseID cstring
        unsigned int key = hash(atoi(courseID.c_str()));
        Node* node = &(nodes.at(key));
        if (node->key != UINT_MAX) {
            if (node->course.courseID.compare(courseID) == 0){
                // erase node begin and key
                std::cout << "remove begining nodes for " << courseID << std::endl;
                if (node->next == nullptr) {
                    node->key = UINT_MAX;
                    return;
                }
                else {
                    nodes.at(key) = *(node->next);
                    return;
                }
            }
            else {
                Node* cur = node->next;
                Node* pre = node;
                while (cur != nullptr) {
                    if (cur->course.courseID.compare(courseID) == 0) {
                        //deleting node
                        pre->next = cur->next;
                        delete cur;
                        cur = nullptr;
                        return;
                    }
                    pre = cur;
                    cur = cur->next;
                }
            }
        }
    }

/**
* Search for the specified courseID
*
* @param courseID The course id to search for
*/
Course HashTable::Search(string courseID) {
    Course course;
    // create the key for the given course
    unsigned int key = hash(atoi(courseID.c_str()));
    Node* node = &(nodes.at(key));
    // if entry found for the key
    if (node == nullptr || node->key == UINT_MAX) {
    //return node course
    return course;
    }
    // if no entry found for the key
    if (node != nullptr && node->key != UINT_MAX && node->course.courseID.compare(courseID) == 0) {
        // return course
        return node->course;
    }
    // while node not equal to nullptr
    while (node != nullptr) {
    // if the current node matches, return it
        if (node->key != UINT_MAX && node->course.courseID.compare(courseID) == 0) {
            return node->course;
        }
        //node is equal to next node
        node = node->next;
    }
    return course;
}

int main(int argc, char* argv[]){
    string csvPath, aCourseKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    case 3:
        csvPath = argv[1];
        aCourseKey = argv[2];
        break;
    default:
        csvPath = "CS 300 ABCU_Advising_Program_Input.csv";
    }

    // Define a table to hold all the courses
    HashTable* courseList = new HashTable();

    Course course;
    bool goodInput;
    int choice = 0;

    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  4. Remove Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";

        aCourseKey = ""; //clear the string        
        string anyKey = " "; //clear the string
        choice = 0; //clear the choice

        try {
            cin >> choice;

            if ((choice > 0 && choice < 5) || (choice == 9)) {// limit the user menu inputs to good values
                goodInput = true;
            }
            else {//throw error for catch
                goodInput = false;
                throw 1;
            }

            switch (choice) {
            case 1:

                // Complete the method call to load the courses
                loadCourses(csvPath, courseList);
                cout << courseList->Size() << " courses read" << endl;

                break;

            case 2:
                courseList->PrintAll();

                cout << "\nEnter \'y\' to continue..." << endl;

                cin >> anyKey;

                break;

            case 3:

                cout << "\nWhat course do you want to know about? " << endl;
                cin >> aCourseKey;

                convertCase(aCourseKey); //convert the case of user input

                course = courseList->Search(aCourseKey);

                if (!course.courseID.empty()) {
                    PrintCourse(course);
                }
                else {
                    cout << "\nCourse ID " << aCourseKey << " not found." << endl;
                }

                break;

            case 4:

                cout << "\nWhat course do you want delete? " << endl;
                cin >> aCourseKey;

                convertCase(aCourseKey); //convert the case of user input

                courseList->Remove(aCourseKey);


                break;

            case 9:
                exit;
                break;

            default:

                throw 2;
            }
        }

        catch (int err) {

            std::cout << "\nPlease check your input." << endl;
        }

        //need to clear the cin operator of extra input, e.g., 9 9, or any errors generated by bad input, e.g., 'a'
        cin.clear();
        cin.ignore();
    }

    return 0;
}