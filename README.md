# DSA Project — GUI Based Search Engine (C++/CLI Windows Forms)

A simple **GUI-based local text search engine** built as a **DSA project** using **C++/CLI** and **Windows Forms** (Visual Studio).  
It indexes `.txt` files from a target directory, supports keyword search (including basic `AND` / `OR` behavior), shows ranked results, and maintains a searchable **query history**.

---

## Features

- **Indexes `.txt` files** from a directory (recursive traversal)
- Builds an **in-memory inverted index**:
  - `word -> priority queue of (file path, frequency)`
- **Search**
  - Single keyword search
  - Multi-keyword search defaults to an **AND-style intersection**
  - Supports explicit `and` / `or` in the query (basic handling)
- **Ranked results**
  - Higher word frequency appears first
  - Tie-breaker: filename ordering
- **Result viewer**
  - Double-click a result to open and display file contents
- **Search History**
  - Stores previous queries and their result sets
  - Double-click history result to open file viewer

---

## Tech Stack

- **Language:** C++/CLI
- **GUI:** Windows Forms
- **IDE:** Visual Studio
- **Core DSA Concepts / STL Used:**
  - `unordered_map`, `unordered_set`
  - `priority_queue`
  - multithreading with `std::thread` + `std::mutex`
  - filesystem traversal with `std::filesystem`

---

## Project Structure

- `DSA_Project.sln` — Visual Studio solution
- `DSA_Project/` — main project directory
  - `Controler.cpp` — app entry point (creates and runs the main form)
  - `SearchEngine.h` — main search UI (query input, results list, open results, open history)
  - `Memory.h` — indexing + search logic (inverted index + history storage)
  - `FileData.h` — file contents viewer + directory listing UI
  - `history.h` — history viewer UI

---

## How it Works (High-Level)

### Indexing
1. The app traverses a directory recursively using `std::filesystem::recursive_directory_iterator`.
2. Only files with extension **`.txt`** are indexed.
3. File contents are tokenized:
   - normalized to lowercase
   - non-alphabetic characters removed
   - common helper/stop words filtered (examples: `is`, `am`, `are`, `was`, `were`, `have`, `has`, etc.)
   - duplicates in a single line are avoided using a `seenwords` set (so each word is added once per line)

### Searching
- The query is split into keywords.
- If query contains `and` → performs intersection of results.
- If query contains `or` → performs union of results.
- Otherwise:
  - 1 keyword → single keyword lookup
  - multiple keywords → defaults to AND-style intersection

### Ranking
Each word maps to a priority queue of results sorted by:
1. Higher `wordfrequency`
2. Tie-breaker by file name ordering

### History
Each search query is stored in a `history` map:
- `query -> result priority_queue`

---

## Running the Project (Visual Studio)

1. Open `DSA_Project.sln` in **Visual Studio (Windows)**.
2. Ensure your environment supports **C++/CLI** (Desktop development with C++).
3. Build and run.

---

## Important Notes / Known Limitations

- **Hardcoded indexing path:**  
  In `SearchEngine.h` the indexing directory is hardcoded (example: `D:\all`).  
  You may need to change it to a valid folder on your system containing `.txt` files.

- **Hardcoded background image path:**  
  Background image is loaded from a hardcoded path (example: `D:\bf.jpg`).  
  If it doesn’t exist, the app shows an error message.

- **Index is in-memory only:**  
  No persistence; index rebuilds each time the app runs.

- **Windows-only:**  
  Uses Windows Forms / C++/CLI, intended for Visual Studio on Windows.

---

## Authors

- Sikandar Hussain (#405410)  
- Syed Adnan Aijaz (#432028)

---

## License

Add a license if you plan to distribute this project publicly (e.g., MIT).
