
# Project3

## Overview
We will create a **317x317 Maze-Based Matrix** featuring:
- **Entrance**: `[row/2, 0]` (middle-left).
- **Exit**: `[317, row/2]` (middle-right).
- A **sprite** starting at the entrance that traverses the maze live, followed by a tail sprite.
- **Live Statistics Counter** beneath the maze:
  - Nodes visited
  - Time taken
  - Memory and space usage
  - Other useful metrics (updated live and finalized at the end).

### Additional Features
- **Add Maze Button**: Adds a new maze, allowing selection of its traversal algorithm.
- **Start Button**: Runs all sprites traversing all mazes in sync.
- **Algorithms**: Initially supporting BFS and A*, with plans to expand to:
  - DFS
  - Dijkstra’s
  - Others in the future.

### To Be Decided:
- Will it be displayed in a website
- What language will be used
- What libraries/frameworks will be used
- Will we use a library for random maze generation?
---

## Contributing Guidelines
Our **primary branch** is `main`. When working on new features, please adhere to the following guidelines:

### Branch Naming
- Use the convention: `username/ticket-id` or `ticket-id` or if not a ticket, just the topic you're working on

### Workflow
1. **Branch off `main`** using the naming convention.
2. **Work on your feature**, focusing on functionality rather than a clean commit history.
3. **Open a Pull Request (PR)** against `main`:
   - Ensure the title is a clean commit message ([commit message guide](https://cbea.ms/git-commit/)).
4. **Resolve all feedback** and discussions on your PR.
5. **Get approval** from at least one other developer.
6. **Merge the PR**:
   - Use **Squash and Merge** unless the commit history adds significant value.

---

## Step-By-Step Guide
1. Branch off `main` (follow the naming convention).
2. Implement your feature.
3. Open a PR with a clean title.
4. Address feedback and resolve all comments.
5. Obtain approval.
6. Merge (squash or preserve history as appropriate).

---


## Building-and-Running

Follow these steps to build and run the project:

1. **Edit Maze Dimensions**  

   - Modify the maze dimensions in `main.cpp`.

2. **Build the Project**  

   - Create a build directory:  
  `mkdir build`

   - Navigate to the build directory:  
     `cd build`

   - Generate the CMake files:  
     `cmake ..`

   - Build:  
     `cmake -DCMAKE_BUILD_TYPE=Release ..`

3. **Run the Program**  

   - Execute the generated output file.

4. **Generate and Solve Mazes**  

   - Click within the program to generate a new maze.
5. **Enjoy Watching Maze Solutions**


## Credits
This project was created by:
- **Christian Luddy**
- **Veronika Matos**
- **Liam Bozarth**
