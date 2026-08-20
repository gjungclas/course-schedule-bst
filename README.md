# CS-300 Data Structures & Algorithms
## Project Overview & Problem Statement
In this course, the primary objective was to design an efficient Advising Assistance Software System for computer science students and academic adficsors. Advisors required a reliable, command-line tool capable of ingesting raw course data from a CSV file, parsing prerequisites, sorting courses alphanumerically, and looking up specific course details instantly.
To solve this, I evaluated multiple data structures—including vectors, hash tables, and binary search trees—to identify the optimal balance between time complexity and memory efficiency. Ultimately, I implemented a custom Binary Search Tree (BST) in C++ to store, sort, and retrieve course objects seamlessly.
## Technical Approach & The Importance of Data Structures
Selecting the right data structure is fundamental to scalable software engineering. While linear structures like vectors are simple, searching or maintaining order requires costly operations—either sorting repeatedly $(O(N log N))$ or linear searching $(O(N))$.
By choosing a Binary Search Tree:
- **Efficient Sorting**: An in-order traversal allows the application to print all computer science and math courses alphanumerically in $O(N)$ time without requiring a separate sorting algorithm.
- **Fast Lookups**: Course lookups and prerequisite verifications execute in average $O(log N)$ time, ensuring the system remains responsive even as the course catalog expands.
- **Data Organization**: Storing custom Course objects containing dynamic prerequisite vectors allowed for modular, real-world data representation.
## Overcoming Roadblocks
During implementation, key challenges centered on robust memory management, input parsing, and handling edge cases:
- **Memory Management**: To prevent memory leaks inherent with dynamic pointer allocation, I implemented a custom destructor (~BinarySearchTree()) using a post-order traversal (destroyTree) to systematically free nodes from the bottom up.
- **Input Sanitization & Exception Handling**: User input validations (such as lowercase text or extra spacing) were resolved by building helper functions using standard algorithms (std::remove_if and std::transform) wrapped in try/catch blocks handling std::logic_error.
- **Recursive Pointer Operations**: Debugging traversal helper functions required careful handling of pointer types and recursive boundary conditions to avoid infinite loops and segfaults.
## Evolution of Software Design & Program Maintainability
Working on these projects significantly boradened my perspective on writing maintenance-ready, professional software:
- **Maintainability & Readability**: Adhering to C++ best practices—such as clear inline documentation, consistent camelCase/PascalCase naming conventions, and modular funcitonal separation—ensures the codebase is readable and easily navigable for collaborators.
- **Adaptability & Defensive Programming**: Input validation logic, stream error clearing (cin.clear(), cin.ignore()), and pre-load execution guards prevent accidental program crashes when unexpected user input occurs.
- **Architectural Awareness**: Analyzing performance trade-offs in Project One reinforced the principle that code design begins before writing a single line of logic. Designing for algorithmic efficiency early saves significant refactoring time later.
