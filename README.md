# Academic Advising & Course Prerequisite Engine
> [!NOTE]
> 🚧 **Work in Progress:** This project is actively being populated and refactored for production standards. Core endpoints and documentation will be fully available soon.

> A high-performance C++ command-line tool utilizing a custom Binary Search Tree (BST) for sub-linear prerequisite resolution, recursive lifecycle management, and alphanumeric schedule generation.

---

## Technical Highlights
* **Algorithmic Efficiency:** Employs a custom Binary Search Tree to deliver $\mathcal{O}(\log n)$ average-case search and insertion times alongside $\mathcal{O}(n)$ in-order sorted traversal.
* **Explicit Memory Lifecycle:** Implements RAII principles and a recursive post-order destructor (`~BinarySearchTree()`) to systematically eliminate dynamic pointer memory leaks.
* **Defensive Input Engineering:** Incorporates tokenization sanitation via `std::remove_if`, `std::transform`, stream recovery (`cin.clear()`, `cin.ignore()`), and `std::logic_error` boundary guards.

---

## System Overview & Architecture
The Advising Assistance Engine is a specialized CLI tool engineered to ingest raw institutional curriculum data, validate complex prerequisite dependency chains, and provide instantaneous course lookups for academic advisors. 

When evaluating architecture candidates (dynamic arrays, separate-chaining hash tables, and search trees), the system required an optimal trade-off between lookup latency and ordered reporting:
* **Vectors** offered predictable ingestion but forced an $\mathcal{O}(n)$ linear search penalty or an $\mathcal{O}(n \log n)$ sorting tax.
* **Hash Tables** delivered near-constant lookup time ($\mathcal{O}(1)$ average) but maintained no internal key ordering, requiring auxiliary arrays and additional memory allocations to sort schedules.
* **Binary Search Tree:** Selected as the primary engine structure, natively supporting both logarithmic course search ($\mathcal{O}(\log n)$) and ordered schedule output ($\mathcal{O}(n)$) without auxiliary sorting overhead.

---

## Core Capabilities
* **Dynamic Prerequisite Resolution:** Recursively traverses tree nodes to verify and cross-reference course prerequisites against primary course records.
* **In-Order Schedule Generation:** Streams all enrolled department courses in strict alphanumeric order via left-root-right depth-first traversal.
* **Pre-load Execution Guards:** State-driven execution flags prevent invalid tree traversal operations if menu queries are attempted prior to dataset ingestion.
* **Fault-Tolerant String Normalization:** Case-insensitive search parsing automatically formats input (e.g., stripping whitespace, handling mixed case) into standardized catalog identifiers.

---

## Engineering Challenges & Solutions

| Challenge | Technical Bottleneck | Engineered Solution |
| :--- | :--- | :--- |
| **Pointer Leakage** | Dynamic heap allocation per tree node risk leaving orphaned memory on application teardown. | Engineered a bottom-up post-order cleanup helper (`destroyTree`) triggered automatically by the class destructor. |
| **Input Ingestion Faults** | CSV files presenting missing titles, irregular commas, or extraneous spaces could corrupt tokens. | Implemented token-length verification along with standard algorithm transforms (`remove_if`, `isspace`, `toupper`) protected by targeted `try/catch` handlers. |
| **CLI Stream Desynchronization** | Non-numeric input types in menu selection induce stream failure flags, triggering infinite display loops. | Integrated automated stream state validation using `cin.fail()`, resetting stream flags with `cin.clear()`, and flushing the buffer via `cin.ignore()`. |

---

## Quickstart & Execution

### Prerequisites
* C++17 compatible compiler (`g++`, `clang++`, or MSVC)
* Standard C++ runtime library

### Build & Run
```bash
# Clone the repository
git clone [https://github.com/](https://github.com/)<your-username>/academic-course-planner.git
cd academic-course-planner

# Compile using C++17 optimization
g++ -std=c++17 -O2 project2.cpp -o course_planner

# Launch the CLI application
./course_planner
```

### Dataset Format
The ingestion engine parses comma-delimited flat files structured with course keys, course titles, and zero to three prerequisites:
```text
CS100,Introduction to Computer Science
CS200,Data Structures,CS100
CS300,Advanced Algorithms,CS200,MATH201
```

