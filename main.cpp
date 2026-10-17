//============================================================================
// Name        : project2.cpp
// Author      : Grace Jungclas, MA, AT Ret
// Version     : 2.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project 2 - CS 300 Data Structures and Algorithms
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
//====================================================================
// Global definitions visible to all methods and classes
//====================================================================

// define a structure to hold course information 
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
	// default constructor
	Course() {
        courseNumber = "";
        name = "";
        prerequisites.clear();
    }
};

// forward declarations
void displayCourse(Course course); 

// internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//====================================================================
// Binary Search Tree class definition
//====================================================================

/**
 * Class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    // helper methods
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void validatePrereqs(Node* node);
	void destroyTree(Node* node);

public:
    BinarySearchTree();
	~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
	void PrintSampleSchedule();
	void ValidatePrereqs();
};

/*
* Constructor for the BinarySearchTree class
*/
BinarySearchTree::BinarySearchTree() {
	// Initialize the root of the tree to nullptr
	root = nullptr;
}

/*
* Destructor for the BinarySearchTree class
*/
BinarySearchTree::~BinarySearchTree() {
	// call helper function to recursively delete all nodes in the tree
	destroyTree(root);
	root = nullptr; // Set root to nullptr after deletion
}

/*
* Adds a course node to the binary search tree
* @param node - the current node in the tree
* @param course - the course to insert
*/
void BinarySearchTree::addNode(Node* node, Course course) {
	// compare course numbers alphabetically
	if (course.courseNumber < node->course.courseNumber) {
		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		else {
			addNode(node->left, course);
		}
	}
	else {
		if (node->right == nullptr) {
			node->right = new Node(course);
		}
		else {
			addNode(node->right, course);
		}
	}
}

/*
* Performs an in-order traversal of the binary search tree
* @param node - the current node in the traversal
*/
void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr) {
		inOrder(node->left);
		displayCourse(node->course);
		inOrder(node->right);
	}
}

/*
* Recursively traverses tree nodes and verifies every listed prereq exists in the BST
* @param node - the current node in the traversal
*/
void BinarySearchTree::validatePrereqs(Node* node) {
	if (node != nullptr) {
		validatePrereqs(node->left);
		for (const auto& prereq : node->course.prerequisites) {
			Course prereqCourse = Search(prereq);
			if (prereqCourse.courseNumber.empty()) {
				cout << "Error: Prerequisite course " << prereq << " for course " << node->course.courseNumber << " does not exist." << endl;
			}
		}
		validatePrereqs(node->right);
	}
}

/*
* Recursive helper method to destroy the binary search tree and free all allocated memory
* uses post-order traversal to delete nodes from the bottom up
* @param node - the current node in the traversal
*/
void BinarySearchTree::destroyTree(Node* node) {
	// check if the node is not null before attempting to delete it
	if (node != nullptr) {
		// recursively delete left and right subtrees
		destroyTree(node->left);
		destroyTree(node->right);
		// delete the current node
		delete node;
	}
}

/*
* Inserts a course into the binary search tree
* @param course - the course to insert
*/ 
void BinarySearchTree::Insert(Course course) {
	if (root == nullptr) {
		root = new Node(course);
	}
	else {
		addNode(root, course);
	}
};

/*
* Search for course by courseNumber 0(log N) time
*/ 
Course BinarySearchTree::Search(string courseNumber) {
	Node* curr = root;
	
	// search for course in BST
	// loop until bottom of tree reached
	while (curr != nullptr) {
		// if match found, return current course
		if (curr->course.courseNumber == courseNumber) {
			return curr->course;
		}
		// if course is smaller than current node then traverse left
		else if (courseNumber < curr->course.courseNumber) {
			curr = curr->left;
		}
		// else larger so traverse right
		else {
			curr = curr->right;
		}
	}
	Course course; // create a default course object to return if not found
	return course; // not found
};

/*	
* Print sample schedule alphanumerically from lowest to highest.
*/
void BinarySearchTree::PrintSampleSchedule() {
	inOrder(root);
};

/*
* function to validate prerequisites for all courses in the BST
*/
void BinarySearchTree::ValidatePrereqs() {
	validatePrereqs(root);
};

//====================================================================
// Independent helper function definitions
//====================================================================

/**
 * Display information about a course
 * @param course - the course to display
 */
void displayCourse(Course course) {
	cout << "" << course.courseNumber << ", " << course.name << endl;
};

/*
* Function to load courses from a CSV file into the binary search tree
* 
* @param: filename - the name of the CSV file to load
* @param: coursesTree - pointer to the binary search tree to insert courses into
*/
void loadCoursesFromFile(const string& filename, BinarySearchTree* coursesTree) {
	// Guard against null pointer for coursesTree
	if (coursesTree == nullptr) {
		cerr << "Error: coursesTree is a null pointer." << endl;
		return;
	}
	
	// Step 1: Open, parse and load data into BST
	// Open the file
	ifstream file(filename);
	// Check if the file was opened successfully
	if (!file.is_open()) {
		// Handle error opening file
		cerr << "Error: Could not open file " << filename << endl;
		return;
	}

	// Step 2: Read each line from the file
	// Use a string to hold each line read from the file
	string line;

	// Use try catch to handle any exceptions thrown during parsing
	try {
		// [2.1] Read each line from the file until EOF
		while (getline(file, line)) {
			istringstream ss(line);
			string token;
			vector<string> tokens;
			// STEP 3: Parse the line into course data using exception handling
			try {
				// [3.1] Read line and split into tokens - uses comma as sep
				while (getline(ss, token, ',')) {
					// [3.1.1] Format each token by removing leading and trailing whitespace
					// remove leading whitespace from token
					token.erase(token.begin(), find_if(token.begin(), token.end(), [](unsigned char c) { return !isspace(c); }));
					// [3.1.2] remove trailing whitespace from token
					token.erase(find_if(token.rbegin(), token.rend(), [](unsigned char c) { return !isspace(c); }).base(), token.end());
					// [3.1.3] add token to vector of tokens
					tokens.push_back(token);
				}
				// [3.2] Validate the number of tokens and handle any format errors
				// SCENARIO 1: [3.2.1] if there are less than 2 tokens, then the line is missing course number or title
				if (tokens.size() < 2) {
					//	OUTPUT format error “Missing course number or title”
					cerr << "Format error: Missing course number or title in line: " << line << endl;
					// continue to the next line
					continue;
				}
				// SCENARIO 2: [3.2.2] if there are more than 5 tokens, then the line has too many prerequisites
				else if (tokens.size() > 5) {
					cerr << "Format error: Too many prerequisites in line: " << line << endl;
					continue;
				}
				/*
				* SCENARIO 3: [3.2.3] 3 or more tokens are present, 3rd is a prerequisite, 4th is a 2nd prerequisite,
				* 5th is a 3rd prerequisite, etc. (up to 3 prerequisites)
				*/
				// instantiate new course object instance
				Course currentCourse;
				// set course number and name from tokens
				currentCourse.courseNumber = tokens[0];
				currentCourse.name = tokens[1];
				// [3.3] handle prerequisite tokens(varies from 0-3 courses)
				for (size_t i = 2; i < tokens.size(); ++i) {
					// [3.3.1] as long as the token is not empty, add it to the prerequisites vector
					if (!tokens[i].empty()) {
						currentCourse.prerequisites.push_back(tokens[i]);
					}
				}

				// Step 4: Store completed Course object in the BST
				coursesTree->Insert(currentCourse);
			}
			catch (const std::exception& e) { // catch any exceptions thrown during parsing
				cerr << "Error parsing line: " << line << ". Exception: " << e.what() << endl;
			}
		}
		cout << "CSV file loaded successfully." << endl;
		cout << endl;
	}
	catch (const std::exception& e) { // catch any exceptions thrown during file reading
		// 
		cerr << "Error reading from file: " << filename << ". Exception: " << e.what() << endl;
	}	
	// Close the file after reading
	file.close();
}

/*
* Search for a course in the binary search tree and display its information
* @param coursesTree - pointer to the binary search tree containing courses
* @param courseNumber - the course number to search for
*/
void searchCourse(BinarySearchTree* coursesTree, const string& courseNumber) {
	// search using BinarySearchTree search function
	Course courseResult = coursesTree->Search(courseNumber);
	// Verify if course was found
	if (!courseResult.courseNumber.empty()) {
		// print out the course information
		cout << "" << courseResult.courseNumber << ", " << courseResult.name << endl;
		// check if course has prerequisites
		if (!courseResult.prerequisites.empty()) {
			cout << "Prerequisites: ";
			// print out the prerequisites
			for (size_t i = 0; i < courseResult.prerequisites.size(); ++i) {
				string prereqNum = courseResult.prerequisites[i];
				// search tree to fetch the course name for the prerequisite
				Course prereqCourse = coursesTree->Search(prereqNum);
				// if the course is found, print the course name
				if (!prereqCourse.courseNumber.empty()) {
					cout << prereqCourse.courseNumber << " (" << prereqCourse.name << ")";
				}
				// else print the course number
				else {
					cout << prereqNum;
				}
				// print a comma if there are more prerequisites to print
				if (i < courseResult.prerequisites.size() - 1) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		else {
			cout << "Prerequisites: None" << endl;
		}
	}
	else {
		// Course courseNumber not found in BST
		cerr << "Error: Course " << courseNumber << " not found." << endl;
	}
}

/*
* Function to format course number: strip whitespace, uppercase all letters, and remove any leading or trailing whitespace
*/
string formatCourseNumber(string& courseNumber) {
	try {
		// guard against empty course number
		if (courseNumber.empty()) {
			throw logic_error("Course number is empty.");
		}
		// remove all whitespaces
		courseNumber.erase(remove_if(courseNumber.begin(), courseNumber.end(), ::isspace), courseNumber.end());
		// convert to all characters to uppercase (cs300 -> CS300)
		transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
		// return formatted course number
		return courseNumber;
	}
	catch (const std::logic_error& e) {
		cerr << "Logic error formatting course number: " << courseNumber << ". Exception: " << e.what() << endl;
		return "";
	}
	catch (...) {
		cerr << "Unknown error formatting course number: " << courseNumber << endl;
		return "";
	}	
}

void menu() {
	cout << "1. Load Data Structure" << endl;
	cout << "2. Print Course List" << endl;
	cout << "3. Print Course" << endl;
	cout << "9. Exit" << endl;
	cout << endl;
	cout << "What would you like to do?";
}

/**
 * The one and only main() method
 */
int main() {
	// initialize binary search tree for courses
	BinarySearchTree* coursesTree = new BinarySearchTree();

	string filename;
	string courseNumToSearch;
	bool isLoaded = false;
	int choice = 0;

	// output menu
	cout << "Welcome to the Course Planner." << endl;
	cout << "Please select an option:" << endl;
	menu();
	cout << endl;
	// get user input for menu choice
	cin >> choice;
	// continue until user chooses to exit
	while (choice != 9) {
		// SCENARIO 1: user choice less than one, greater than eight, or equal to 4, 5, 6, or 7
		if (choice < 1 || choice > 9 || choice == 4 || choice == 5 || choice == 6 || choice == 7 || choice == 8) {
			cout << "" << choice << " is not a valid option." << endl;
			cout << endl;
			menu();
			cin >> choice;
			continue;
		}

		// SCENARIO 2: user choice not an integer
		if (cin.fail()) {
			cout << "Invalid input. Please enter a number." << endl;
			cin.clear(); // clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
			menu();
			cin >> choice;
			continue;
		}

		// SCENARIO 3: user choice is valid, so process the choice
		switch (choice) {
			//	CASE 1:
			case 1: {
				// prompt user for filename to load
				cout << "Enter the name of the CSV file to load: ";
				cin >> filename;
				// Load courses from CSV file into BST
				loadCoursesFromFile(filename, coursesTree);
				isLoaded = true;
				break;
			}
			case 2: {
				// conditionally validate prerequisites if courses have been loaded
				if (!isLoaded) {
					cout << "Please load the data structure first." << endl;
					break;
				}
				// print list of courses in alphanumeric order
				cout << "Here is a sample schedule: " << endl;
				coursesTree->PrintSampleSchedule();
				cout << endl;
				// continue loop
				break;
			}
			case 3: {
				// search for course and display its title and prerequisites
				// guard against searching before loading data
				if (!isLoaded) {
					cout << "Please load the data structure first." << endl;
					break;
				}
				// get user input for course number to search
				cout << "What course do you want to know about? ";
				cin >> courseNumToSearch;
				// call formatCourseNumber function to format the course number
				formatCourseNumber(courseNumToSearch);
				// call searchCourse function
				searchCourse(coursesTree, courseNumToSearch);
				cout << endl;
				break;
			}
			case 9: {
				// memory management
				delete coursesTree;
				// exit program
				cout << "Thank you for using the course planner." << endl;
				break;
			}
		}
		// continue loop until user chooses to exit
		menu();
		cin >> choice;
	}
	return 0;
}