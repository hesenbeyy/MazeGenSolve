# 🧩 Maze Generator & Pathfinding Visualizer (C++ / SFML)

A visual maze generation and pathfinding project built using C++ and SFML.

This project demonstrates algorithmic maze generation and shortest-path finding with real-time, step-by-step visualization. It allows users to watch the computer carve out a perfect maze, interactively select their start and finish points, and watch Dijkstra's algorithm hunt for the most efficient route.

## 🎥 Demos

**Part 1: Maze Generation** 📌 A video showcasing the Recursive Backtracking generation process step-by-step.

https://github.com/user-attachments/assets/61156c85-00ab-4ce3-bcb0-a7358b895ac1



**Part 2: Dijkstra's Pathfinding** 📌 A video showcasing the shortest path search and path reconstruction.


https://github.com/user-attachments/assets/96ea997c-0b7e-4e48-80bd-ef9a58bd4e76



---

## 🎮 Interactive Controls

Once the maze is fully generated, you can interact with the grid:

* **Left Click (1st time):** Sets the **Start** point (Red).
* **Left Click (2nd time):** Sets the **Finish** point (Green).
* **Press `S`:** Starts the Dijkstra Pathfinding visualization.
* **Press `ESC`:** Closes the window.

---

## 📌 Project Overview

This project is divided into two main, fully completed parts:

### 🟢 Part 1 — Maze Generation (Completed ✅)

The maze is generated using the **Recursive Backtracking** algorithm (Depth-First Search with a stack). It creates a "perfect maze" (a maze with no loops and exactly one path between any two cells).

**🔎 How It Works:**

1. Start from the first cell and mark it as visited.
2. Randomly select one unvisited neighboring cell.
3. Remove the wall between the current cell and the neighbor.
4. Push the neighbor onto the stack and move to it.
5. If a cell has no unvisited neighbors, backtrack using the stack.
6. Repeat until all cells are visited.

**✨ Features:**

* Real-time visualization of the generation process.
* Visited cells are colored grey, and the active cell is highlighted.
* Walls are dynamically removed on screen.

### 🔵 Part 2 — Dijkstra’s Algorithm (Completed ✅)

Finds the absolute shortest path between the user-selected start and finish cells using a **Priority Queue**.

**🔎 How It Works:**

1. Assigns a distance value to every cell (infinity initially, 0 for the start cell).
2. Explores unvisited accessible neighbors (where walls don't block the path) starting from the lowest distance.
3. Updates the neighbors' distances and records the "previous" cell to remember the path.
4. Once the finish cell is reached, it backtracks through the "previous" cell records to reconstruct and draw the final shortest path.

**✨ Features:**

* Step-by-step visualization of the search radius (explored cells highlighted in orange).
* Accounts for generated walls (will not cross unbroken wall lines).
* Final shortest path is reconstructed and painted red.

---

## 🏗 Project Structure

```text
.
├── main.cpp        # Entry point, event handling, and main loop
├── maze.hpp        # Maze class: grid logic, generation, pathfinding, drawing
├── stack.hpp       # Custom Stack implementation for DFS backtracking
├── structs.hpp     # Cell structure (walls, visited states, row/col mapping)
├── macros.hpp      # Constants (CELL_SIZE, ROWS, COLS, directions)
└── CMakeLists.txt

```

---

## 🛠 Technologies & Concepts Used

* **C++**
* **SFML** (Simple and Fast Multimedia Library) for 2D rendering.
* **Graph Traversal Algorithms:** Depth-First Search (DFS) & Dijkstra's Algorithm.
* **Data Structures:** Stacks, Vectors, and Priority Queues.
* **Grid Mathematics:** 2D (row/col) to 1D array index mapping.

---

## 🚀 How to Run

1. **Install SFML:** Ensure you have the SFML library installed and configured on your system.
2. **Clone the repository:**
```bash
git clone https://github.com/noryzenn/procedural_map_generation.git

```


3. **Build and Run:** Compile the project using your preferred C++ compiler, making sure to link the SFML Graphics, Window, and System modules.

---

## 💡 Author Notes

This project was built to strengthen my understanding of:

* Graph traversal algorithms
* Algorithm visualization
* Clean class architecture
* Real-time rendering loops

---
