# PA 2025 Project

The repository contains the project skeleton and the public tests.

## Structure

`include/`
The headers for the required modules.

`src/`
The files you need to complete.

`tests/public/`
Public tests for each step. Here you can find the input files and the expected output.

`build/`
Contains the binaries for running the public tests:
- `build/public_pas1`
- `build/public_pas2`
- `build/public_pas3`
- `build/public_pas4`

## Running the public tests

To run all the public tests:

```bash
make public-test
```

To run the public tests for only one step:

```bash
./build/public_pas1 tests/public/pas1/entitati.csv tests/public/pas1/relatii.csv tests/public/pas1/interogari.txt
./build/public_pas2 tests/public/pas2/entitati.csv tests/public/pas2/relatii.csv tests/public/pas2/interogari.txt
./build/public_pas3 tests/public/pas3/entitati.csv tests/public/pas3/relatii.csv tests/public/pas3/interogari.txt
./build/public_pas4 tests/public/pas4/entitati.csv tests/public/pas4/relatii.csv tests/public/pas4/interogari.txt
```

Each public test also has an `expected.txt` file with the expected result.

## Public tests and private tests

There are two types of tests:
- public tests, included in this repository;
- private tests, used for evaluation.

The fact that the public tests pass does not guarantee a maximum score.

## Implementation documentation

## General description
The application implements a weighted knowledge graph that stores entities, represented by people, companies, locations, or events, and the relationships between them. The data is read from CSV files, indexed for searching, and the queries are placed in a queue.

## Data structures used

### 1. Graph with adjacency lists
Structures: Graph, GraphNode, and EdgeNode.
The graph is represented by a dynamically allocated array of nodes, each node having its own adjacency list. Each entity becomes a node of the graph, initially with an empty edge list.

Why is it efficient?
The graph is sparse (it has the number of edges < n²). An adjacency matrix would have occupied more memory regardless of the number of edges, and in our case, the adjacency lists occupy O(n+m) space.

### 2. Singly linked list of entities
As it is read, each entity is added to a singly linked list, which serves as a kind of registry of all entities.

Why is it efficient?
The list allows repeated access to all entities without destroying them, and that is why using it is more efficient instead of a queue, for example.

### 3. Binary Search Tree indexed by name
Structures: BST and BSTNode.
The graph nodes are indexed in a BST by the names of the entities. The BST nodes contain only pointers into the graph array without duplicating the data.

Why is it efficient?
For searching through the list of entities, this is more efficient because it reduces the search to O(log n) in an average case.

### 4. Queue
Structures: Queue and QueueNode.
The queries read from the file are stored in a queue implemented with a singly linked list and processed in the order they are received.

Why is it efficient?
The queries must be processed in the order of processing, and this structure is the most suitable. Insertion and extraction are both O(1).

### 5. Min-Heap
Structures: MinHeap and HeapNode.
Used in Dijkstra's algorithm to efficiently find the node with the minimum distance from the source.

Why is it efficient?
Extracting the minimum from an unsorted array is O(n). The Min-Heap offers O(log n) for both insertion and extraction, reducing the total complexity for Dijkstra.

## The complexity of query operations
Operation: 'EXISTS'
Complexity: O(log n)
Justification: Searches in the BST by name

Operation: 'EDGE'
Complexity: O(log n + number of edges of the source)
Justification: Searches in the BST for the source node and traverses its list of edges

Operation: 'NEIGHBORS'
Complexity: O(log n + number of edges of the source)
Justification: Searches in the BST and traverses the complete list of outgoing edges

## The complexity of path algorithms

### PATH - BFS
Complexity: O(n+m)
Justification: BFS visits each node and each edge at most once. It uses a queue to explore the graph by levels, guaranteeing that the first found path has the minimum number of edges. The path is reconstructed by traversing the parent array kept from during the BFS.

### Dijkstra
Complexity: O((n+m) * log n)
Justification:
- n heap extractions, each taking O(log n)
- m edge relaxations, each taking O(log n)
=> Total: O((n+m) * log n)
A linear search would imply O(n) per extraction, being inefficient. The min-heap reduces the selection to O(log n), achieving efficiency.