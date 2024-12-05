#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <random>
#include <SFML/Graphics.hpp>

constexpr float WINDOW_WIDTH = 1920.0f;
constexpr float WINDOW_HEIGHT = 1000.0f;
constexpr float MAZE_PIXEL_WIDTH = 950.0f;
constexpr float MAZE_PIXEL_HEIGHT = 950.0f;

using namespace std;
class Maze {
    std::vector<std::vector<char>> vertices;  //1 byte first 4 bits represent walls
    vector<pair<int, int>> direction_list = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}; //up, right, down, left
    sf::VertexArray lines;
    bool lines_generated = false;
public:
    vector<vector<sf::Color>> vertex_colors;
    vector<vector<sf::Color>> vertex_colors2;
    int width;
    int height;
    Maze(int width, int height);
    bool check_if_wall(int row, int col, int direction);  //right up left down for the bits
    void remove_wall(int row, int col, int direction);
    void print_maze();
    void show(sf::RenderWindow& window);
    void generate_maze();
    bool visitable_vertex(int x, int y);
    void reset();
    void make_lines();
};




