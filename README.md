# C++ Document Retrieval System

A minimal yet functional document indexing and retrieval tool written in modern C++.  
This project was built as a practical exercise in file handling, basic data structures, and search algorithms.

---

## 📝 Overview

This tool allows you to:

- Scan and index multiple plain-text documents
- Search for specific words across those documents
- View word frequency statistics

It’s designed to be lightweight, easily extendable, and suitable for personal working.

---

## ⚙️ Getting Started

### Requirements

- C++17 compatible compiler (e.g., G++ or Clang)
- Terminal access (Linux, macOS, or Windows with WSL)
- Basic familiarity with C++ and command-line usage

### Build Instructions

```bash
git clone https://github.com/atasoyturk/cpp-document-retrieval.git
cd cpp-document-retrieval/src
g++ -std=c++17 -o retriever main.cpp indexer.cpp search.cpp
```
#### ▶️ Usage

-Place your .txt files inside the data/ folder.
-Run the compiled executable:

```bash
./retriever
```
##### 🚧 Future Improvements
- Implement TF-IDF scoring
- Add stopword filtering
- Support JSON or CSV export
- Integrate unit tests (e.g., with Catch2 or GoogleTest)
- Develop a minimal GUI (possibly using Qt or ImGui)

