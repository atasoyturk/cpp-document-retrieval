# Design Document for Document Indexing System

## Overview
This project implements a document indexing system in C++ to process text files, index unique words, and enable keyword searches. It uses a linked list for word storage and vectors for document IDs.

## Data Structures
- **Linked List**:
  - Chosen for sorted insertion of words, ensuring efficient search and insertion operations.
  - Each `Node` contains a word and a vector of document IDs.
- **Vector**:
  - Stores document IDs for each word, allowing fast retrieval of documents containing a specific word.
  - Preferred over other structures (e.g., set) for simplicity and sequential access.

## Threading
- A loading animation runs concurrently using `std::thread` to provide user feedback during file processing.
- Future improvements may include multi-threading for parallel file reading to reduce the 30-minute indexing time.

## File Processing
- The system processes up to 10,000 text files in the `data/AllDocs/` directory.
- Each file is read line by line, and words are cleaned (converted to lowercase, non-alphabetic characters removed) before indexing.

## Design Choices
- **Linked List vs. Map**: A linked list was chosen for simplicity and sorted storage. A `std::map` or `std::unordered_map` could improve search performance but was not implemented for this version.
- **Vector for Document IDs**: Ensures no duplicate document IDs and provides efficient iteration.

## Future Improvements
- Implement multi-threading for file processing.
- Replace linked list with a hash map for faster searches.
- Add support for case-insensitive searches and advanced queries (e.g., AND/OR operations).

## Challenges
- Processing 10,000 files takes ~30 minutes due to sequential file reading. Parallel processing is a planned optimization.
- Memory management is critical due to the large number of words and document IDs.
