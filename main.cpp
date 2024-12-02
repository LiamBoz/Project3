#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stack>

using namespace std;

// maze size, will be changed later but is 20x20 for ease of use
const int width = 20;
const int height = 20;

bool visitableCell(int x, int y, const vector<vector<int>>& maze) {
  //make sure the DFS doesn't run into a wall
    if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1) {
        return false;
    }
  //make sure the cell is surrounded by walls

}






string generatemaze() {

    //TODO: loop to continue while stack is not empty,
    // pop the top of the stack and check if it is a dead end, if it is,
    // remove the wall and add the adjacent cell to the stack, if it is not, 
    //add the adjacent cell to the stack

    // 0 is a wall, 1 is a path
    vector<vector<int>> maze(width, vector<int>(height, 0));



    // directions to move in
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

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
    stack<pair<int, int>> currPosStack;
    pair<int, int> startCell = {0, middleY};
    currPosStack.push(startCell);
    
    while (!currPosStack.empty()) {
      currPosStack.pop();
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
    string maze = generatemaze();
    cout << maze;

    return 0;
}
