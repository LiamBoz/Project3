#pragma once
#include <queue>
#include <vector>
#include <string>
#include <maze.h>

class bfs {
    std::vector<std::vector<int>> visited;
    std::vector<std::vector<std::pair<int, int>>> parents;
    Maze *maze;
    std::queue<std::pair<int, int>> vertex_queue;
    vector<pair<int, int>> direction_list = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; //up, right, down, left
    bool finished = false;
    int step = 0;
    pair<int,int> current_backtrack;
public:
    bfs(Maze* maze);
    bool can_visit_vertex(int x, int y, int direction);
    int step_forward();
};
