#include "Maze.h"

Maze::Maze(int width, int height) {
    this->width = width;
    this->height = height;

    this->vertices = vector<vector<char> >(height, vector<char>(width, 15)); // start with all walls.
    this->vertex_colors = vector<vector<sf::Color> >(height, vector<sf::Color>(width, sf::Color::White));
    this->vertex_colors2 = vector<vector<sf::Color> >(height, vector<sf::Color>(width, sf::Color::White));

    this->lines = sf::VertexArray(sf::Lines);
}

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distr(0, 3);

bool Maze::visitable_vertex(int x, int y) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        return false;
    }
    int num_walls = 0;

    for (int i = 0; i < 4; i++) {
        if (check_if_wall(y, x, i)) num_walls++;
    }

    if (num_walls >= 3) return true;
    return false;
}


void Maze::generate_maze() {
    stack<pair<int, int> > vertex_stack;
    vertex_stack.push(make_pair(0, 0));
    remove_wall(0, 0, 0);

    vector<vector<int> > visited(height, vector<int>(width, 0));

    bool first_move = true;

    while (!vertex_stack.empty()) {
        int x = vertex_stack.top().first;
        int y = vertex_stack.top().second;
        vector<bool> directions_guessed(4, false);
        int guess = 0;
        bool has_moved = false;
        while (guess < 4) {
            int dirIndex = distr(gen);

            if (first_move) {
                dirIndex = 1;
                first_move = false;
            }

            if (directions_guessed[dirIndex]) {
                continue;
            }

            directions_guessed[dirIndex] = true;
            guess++;

            int new_x = x + direction_list[dirIndex].first;
            int new_y = y + direction_list[dirIndex].second;

            if (visitable_vertex(new_x, new_y) && visited[new_y][new_x] == 0) {
                remove_wall(y, x, dirIndex);
                vertex_stack.push(make_pair(new_x, new_y));
                visited[new_y][new_x] = 1;
                has_moved = true;
                break;
            }
        }
        if (!has_moved) {
            vertex_stack.pop();
        }
    }
}

void Maze::make_lines() {
    lines.clear();
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            float line_width = MAZE_PIXEL_WIDTH / width;
            float line_height = MAZE_PIXEL_HEIGHT / height;

            float start_x = 20;
            float start_y = (WINDOW_HEIGHT - MAZE_PIXEL_HEIGHT) / 2;

            sf::RectangleShape rectangle(sf::Vector2f(line_width, line_height));
            rectangle.setPosition(start_x + line_width * (float) col, start_y + line_height * (float) row);

            if (check_if_wall(row, col, 0)) {
                sf::Vector2f pos = sf::Vector2f(start_x + line_width * (float) col,
                                                start_y + line_height * (float) row);

                lines.append(sf::Vertex(pos, sf::Color::Black));
                lines.append(sf::Vertex(pos + sf::Vector2f(line_width, 0), sf::Color::Black));
            }
            if (check_if_wall(row, col, 1)) {
                sf::Vector2f pos = sf::Vector2f(start_x + line_width * ((float) col + 1),
                                                start_y + line_height * (float) row);

                lines.append(sf::Vertex(pos, sf::Color::Black));
                lines.append(sf::Vertex(pos + sf::Vector2f(0, line_height), sf::Color::Black));
            }
            if (check_if_wall(row, col, 2)) {
                sf::Vector2f pos = sf::Vector2f(start_x + line_width * (float) col,
                                                start_y + line_height * ((float) row + 1));

                lines.append(sf::Vertex(pos, sf::Color::Black));
                lines.append(sf::Vertex(pos + sf::Vector2f(line_width, 0), sf::Color::Black));
            }
            if (check_if_wall(row, col, 3)) {
                sf::Vector2f pos = sf::Vector2f(start_x + line_width * (float) col,
                                                start_y + line_height * (float) row);

                lines.append(sf::Vertex(pos, sf::Color::Black));
                lines.append(sf::Vertex(pos + sf::Vector2f(0, line_height), sf::Color::Black));
            }
        }
    }
}


bool Maze::check_if_wall(int row, int col, int direction) {
    return (vertices[row][col] & ((char) pow(2, direction))) == ((char) pow(2, direction));
}

void Maze::remove_wall(int row, int col, int direction) {
    this->vertices[row][col] &= ~(char) pow(2, direction);
    int other_row = row + direction_list[direction].second;
    int other_col = col + direction_list[direction].first;
    if (other_row < 0 || other_col < 0 || other_row >= height || other_col >= width) return;
    direction += 2;
    direction %= 4;
    this->vertices[other_row][other_col] &= ~(char) pow(2, direction);
}

void Maze::print_maze() {
    std::string output;
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            output += std::to_string(((int) this->vertices[i][j]));
        }
        output += "\n";
    }
    std::cout << output << std::endl;
}

void Maze::show(sf::RenderWindow &window) {
    window.clear(sf::Color::White);
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            float line_width = MAZE_PIXEL_WIDTH / width;
            float line_height = MAZE_PIXEL_HEIGHT / height;
            //float start_x = (WINDOW_WIDTH - MAZE_PIXEL_WIDTH) / 2;
            float start_x = 20;
            float start_y = (WINDOW_HEIGHT - MAZE_PIXEL_HEIGHT) / 2;

            sf::RectangleShape rectangle(sf::Vector2f(line_width, line_height));
            rectangle.setPosition(start_x + line_width * (float) col, start_y + line_height * (float) row);

            if (vertex_colors[row][col] != sf::Color::White) {
                rectangle.setFillColor(vertex_colors[row][col]);
                window.draw(rectangle);
            }

            if (vertex_colors2[row][col] != sf::Color::White) {
                rectangle.setFillColor(vertex_colors2[row][col]);
                window.draw(rectangle);
            }
        }
    }
    //window.display();
    window.draw(lines);
}

void Maze::reset() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->vertices[i][j] = 15;
            this->vertex_colors[i][j] = sf::Color::White;
            this->vertex_colors2[i][j] = sf::Color::White;
        }
    }
}

void Maze::reset_colors() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->vertex_colors[i][j] = sf::Color::White;
            this->vertex_colors2[i][j] = sf::Color::White;
        }
    }
}
