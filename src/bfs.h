#pragma once
#include <queue>
#include <vector>
#include <string>
#include <maze.h>
#include <chrono>


class bfs {
    std::vector<std::vector<int>> visited;
    std::vector<std::vector<std::pair<int, int>>> parents;
    Maze *maze;
    std::queue<std::pair<int, int>> vertex_queue;
    vector<pair<int, int>> direction_list = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; //up, right, down, left
    bool finished = false;
    int step = 0;
    pair<int,int> current_backtrack;
    chrono::time_point<chrono::steady_clock> start_time;
    chrono::time_point<chrono::steady_clock> end_time;
public:
    int steps_taken = 0;
    bfs(Maze* maze);
    void reset();
    bool can_visit_vertex(int x, int y, int direction);
    int step_forward();
};
