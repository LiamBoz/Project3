#pragma once
#include <queue>
#include <vector>
#include <string>
#include <maze.h>
#include <chrono>

using namespace std;
class dfs {
    std::vector<std::vector<int>> visited;
    std::vector<std::vector<std::pair<int, int>>> parents;
    Maze *maze;
    std::stack<std::pair<int, int>> vertex_stack;
    vector<pair<int, int>> direction_list = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; //up, right, down, left
    bool finished = false;
    int step = 0;
    pair<int,int> current_backtrack;
    std::chrono::steady_clock::time_point start_time, end_time;

public:
    int steps_taken = 0;
    dfs(Maze* maze);
    void reset();
    bool can_visit_vertex(int x, int y, int direction);
    int step_forward();  // make changes to update to the newest
};
