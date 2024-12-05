#include "dfs.h"
#include <chrono>
//#include <__filesystem/path.h>

// std::chrono::steady_clock::time_point start_time, end_time;

dfs::dfs(Maze *maze){
    this->visited = std::vector<std::vector<int>>(maze->height, std::vector<int>(maze->width, 0));
    this->parents = std::vector<std::vector<std::pair<int,int>>>(maze->width, std::vector<std::pair<int,int>>(maze->width, make_pair(-1,-1)));
    this->maze = maze;  //stack update
    vertex_stack = std::stack<std::pair<int,int>>();  //stack
    vertex_stack.emplace(make_pair(0,0));  //starting point
}

void dfs::reset() {
    this->visited = std::vector<std::vector<int>>(maze->height, std::vector<int>(maze->width, 0));
    this->parents = std::vector<std::vector<std::pair<int,int>>>(maze->width, std::vector<std::pair<int,int>>(maze->width, make_pair(-1,-1)));
    vertex_stack = std::stack<std::pair<int,int>>();  //stack
    vertex_stack.emplace(make_pair(0,0));  //starting point
    start_time = std::chrono::steady_clock::time_point::min();
    end_time = std::chrono::steady_clock::time_point::min();
    step = 0;
    steps_taken = 0;
    finished = false;
}



bool dfs::can_visit_vertex(int x, int y, int direction) {
    int new_x = x + direction_list[direction].first;
    int new_y = y + direction_list[direction].second;
    if(new_x < 0 || new_y < 0 || new_x >= maze->width || new_y >= maze->height) return false;
    if(visited[new_y][new_x] == 1) return false;

    return !maze->check_if_wall(y,x, direction);
}

int dfs::step_forward() {

    if (!finished && vertex_stack.empty()) {

        //start_time = std::chrono::steady_clock::now();
    }

    if (finished) {
        //ending here
        //end_time = std::chrono::steady_clock::now();
        //auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        //std::cout << "Elapsed time: " << elapsed_time.count() << " milliseconds" << std::endl;
    }

    if(vertex_stack.empty()) return 0;
    if(finished) {
        maze->vertex_colors2[current_backtrack.first][current_backtrack.second] = {200,10,50, 100};
        if(current_backtrack.first == 0 && current_backtrack.second == 0) {
            return 1;
        }
        current_backtrack = parents[current_backtrack.first][current_backtrack.second];
        return 1;
    }
    int x = vertex_stack.top().first;
    int y = vertex_stack.top().second;
    if(y == maze->height - 1 && x == maze->width-1) {
        finished = true;
        current_backtrack.first = y;
        current_backtrack.second = x;
        return 1;
    }

    //std::cout << y << " " << x << std::endl;

    maze->vertex_colors2[y][x] = {200,130,5, 100};

    for(int i = 0; i < 4; i ++) {  // checks each direction to go in
        if(can_visit_vertex(x,y,i)) {
            int new_x = x + direction_list[i].first;
            int new_y = y + direction_list[i].second;
            visited[new_y][new_x] = 1;
            vertex_stack.push(make_pair(new_x,new_y));
            steps_taken++;
            //maze->vertex_colors[new_y][new_x] ={200,130,5, 200};
            parents[new_y][new_x] = make_pair(y,x);
            return -1;
        }
    }

    maze->vertex_colors2[y][x] *= {255,255,255,100};

    vertex_stack.pop();

    return -1;
}
