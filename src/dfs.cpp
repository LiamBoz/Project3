// #include "dfs.h"
// #include <chrono>
// #include <__filesystem/path.h>
//
// std::chrono::steady_clock::time_point start_time, end_time;
//
// bfs::bfs(Maze *maze){
//     this->visited = std::vector<std::vector<int>>(maze->height, std::vector<int>(maze->width, 0));
//     this->parents = std::vector<std::vector<std::pair<int,int>>>(maze->width, std::vector<std::pair<int,int>>(maze->width, make_pair(-1,-1)));
//     this->maze = maze;
//     vertex_queue = std::queue<std::pair<int,int>>();
//     vertex_queue.emplace(make_pair(0,0));
// }
//
// bool bfs::can_visit_vertex(int x, int y, int direction) {
//     int new_x = x + direction_list[direction].first;
//     int new_y = y + direction_list[direction].second;
//     if(new_x < 0 || new_y < 0 || new_x >= maze->width || new_y >= maze->height) return false;
//     if(visited[new_y][new_x] == 1) return false;
//
//     return !maze->check_if_wall(y,x, direction);
// }
//
// int bfs::step_forward() {
//
//     if (!finished && vertex_queue.empty()) {
//         start_time = std::chrono::steady_clock::now();
//     }
//
//     if (finished) {
//         end_time = std::chrono::steady_clock::now();
//         auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
//         std::cout << "Elapsed time: " << elapsed_time.count() << " milliseconds" << std::endl;
//     }
//
//     if(vertex_queue.empty()) return 0;
//     if(finished) {
//         maze->vertex_colors[current_backtrack.first][current_backtrack.second] = {10,100,50, 100};
//         if(current_backtrack.first == 0 && current_backtrack.second == 0) {
//             return 1;
//         }
//         current_backtrack = parents[current_backtrack.first][current_backtrack.second];
//         return 1;
//     }
//     int x = vertex_queue.front().first;
//     int y = vertex_queue.front().second;
//     if(y == maze->height - 1 && x == maze->width-1) {
//         finished = true;
//         maze->vertex_colors[y][x] = {10,200,5, 100};
//         current_backtrack.first = y;
//         current_backtrack.second = x;
//         return 1;
//     }
//     std::cout << y << " " << x << std::endl;
//     maze->vertex_colors[y][x] = {10,50,100, 100};
//     vertex_queue.pop();
//
//     for(int i = 0; i < 4; i ++) {
//         if(can_visit_vertex(x,y,i)) {
//             int new_x = x + direction_list[i].first;
//             int new_y = y + direction_list[i].second;
//             visited[new_y][new_x] = 1;
//             vertex_queue.push(make_pair(new_x,new_y));
//             parents[new_y][new_x] = make_pair(y,x);
//         }
//     }
//     return -1;
// }
