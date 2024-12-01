#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <random>

using namespace std;

// maze size, will be changed later but is 20x20 for ease of use
const int width = 50;
const int height = 50;

// directions to move in
vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// random num gen credit: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
//
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distr(0, 3);

// VISITABLE CELL must check 3 co
bool visitableCell(int currX, int currY, const vector<vector<int>>& maze) {
  //make sure the DFS doesn't run into a wall
    if (currX <= 0 || currX >= width - 1 || currY <= 0 || currY >= height - 1) {
        return false;
    }
    int numWalls = 0;
    //make sure the cell is surrounded by walls
    for (int i = 0; i < 4; i++) {
      int newX = currX + directions[i].first; 
      int newY = currY + directions[i].second;

      if (maze[newX][newY] == 0 && newX >= 0 && newX < width && newY >= 0 && newY < height) {
        numWalls++;
      }
    }
    if (numWalls >= 3) {
      return true;
    }
    else {
      return false;
    }

}

string generateMaze() {

    //TODO: loop to continue while stack is not empty,
    // pop the top of the stack and check if it is a dead end, if it is,
    // remove the wall and add the adjacent cell to the stack, if it is not, 
    //add the adjacent cell to the stack

    // 0 is a wall, 1 is a path
    vector<vector<int>> maze(width, vector<int>(height, 0));
    // stringstream to print the maze
    stringstream ss;

    // initialize the maze with walls
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            maze[x][y] = 0;
        }
    }

    // start and end points
    int middleY = height / 2;
    maze[0][middleY] = 1;
    maze[width - 1][middleY] = 1;

    // stack to keep track of current position
    stack<pair<int, int>> currPos;
    pair<int, int> startCell = {0, middleY};
    currPos.push(startCell);
   
    // Choose a random direction. Call visitableCell() on the cell in that direction. 
    // If visitableCell returns true, then we add it to the stack, remove the wall and the while loop repeats.
    // It becomes our new currPosStack.
    // If it doesn't, we choose a different random direction & call visitableCell on it.
    // We do this until
    //
    while (!currPos.empty()) {
      int currX = currPos.top().first;
      int currY = currPos.top().second;

      currPos.pop();

      bool directions_guessed[4] = {false, false, false, false};
      bool allTried = false;

      while (!allTried) {
        int dirIndex = distr(gen);

        directions_guessed[dirIndex] = true;

        int newX = currX + directions[dirIndex].first;
        int newY = currY + directions[dirIndex].second;

        if (visitableCell(newX, newY, maze)) {
          maze[newX][newY] = 1;

          currPos.push({newX, newY});
          break;
        }
        
        allTried = true;
        for (int i = 0; i < 4; i++) {
          if (!directions_guessed[i]) {
            allTried = false;
            break;
          }
        }
      }
    }



    // print the maze
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
          if (maze[x][y] == 1) {
            ss << "  ";
          } else {
            ss << "██";
          }
        }
        ss << "\n";
    }

    // return the maze
    return ss.str();
}



int main() {
    string maze = generateMaze();
    cout << maze;

    return 0;
}
