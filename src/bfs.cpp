#include "bfs.h"


bfs::bfs(Maze *maze){
    this->visited = std::vector<std::vector<int>>(maze->height, std::vector<int>(maze->width, 0));
    this->parents = std::vector<std::vector<std::pair<int,int>>>(maze->width, std::vector<std::pair<int,int>>(maze->width, make_pair(0,0)));
    this->maze = maze;
    vertex_queue = std::queue<std::pair<int,int>>();
    vertex_queue.emplace(make_pair(0,0));
    start_time = std::chrono::steady_clock::time_point::min();
    end_time = std::chrono::steady_clock::time_point::min();
}

bool bfs::can_visit_vertex(int x, int y, int direction) {
    int new_x = x + direction_list[direction].first;
    int new_y = y + direction_list[direction].second;
    if(new_x < 0 || new_y < 0 || new_x >= maze->width || new_y >= maze->height) return false;
    if(visited[new_y][new_x] == 1) return false;

    return !maze->check_if_wall(y,x, direction);
}

int bfs::step_forward() {

    if (start_time == std::chrono::steady_clock::time_point::min()) {
        start_time = std::chrono::steady_clock::now();
    }

    if(vertex_queue.empty()) return 0;
    if(finished) {
        maze->vertex_colors[current_backtrack.first][current_backtrack.second] = {10,200,150, 100};
        if(current_backtrack.first == 0 && current_backtrack.second == 0) {
            return 1;
        }
        current_backtrack = parents[current_backtrack.first][current_backtrack.second];
        return 1;
    }
    int x = vertex_queue.front().first;
    int y = vertex_queue.front().second;
    if(maze->vertex_colors[y][x] == sf::Color::White) {
        //maze->vertex_colors[y][x] = {0,0,0};
    }
    if(y == maze->height - 1 && x == maze->width-1) {
        finished = true;
        current_backtrack.first = y;
        current_backtrack.second = x;
        return 1;
    }

    maze->vertex_colors[y][x] = {10,100,200, 100};
    steps_taken++;

    vertex_queue.pop();

    for(int i = 0; i < 4; i ++) {
        if(can_visit_vertex(x,y,i)) {
            int new_x = x + direction_list[i].first;
            int new_y = y + direction_list[i].second;
            visited[new_y][new_x] = 1;
            vertex_queue.push(make_pair(new_x,new_y));
            parents[new_y][new_x] = make_pair(y,x);
        }
    }
    return -1;
}
