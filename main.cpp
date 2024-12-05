#include "bfs.h"
#include "Maze.h"
using namespace std;

// maze size, will be changed later but is 20x20 for ease of use
const int width = 317;
const int height = 317;

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <random>
#include <dfs.h>

using namespace std;

// directions to move in
vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// // random num gen credit: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range





int main() {
    //create a window with text about what this is with
    // string maze = generateMaze();
    // cout << maze;
    Maze m = Maze(width, height);
    m.generate_maze();
    m.remove_wall(m.height-1,m.width-1,2);
    auto window = sf::RenderWindow({(int)WINDOW_WIDTH, (int)WINDOW_HEIGHT}, "CMake SFML Project");
    m.show(window);

    window.setFramerateLimit(144);
    bool started = false;
    dfs d = dfs(&m);
    bfs b = bfs(&m);

    sf::Text text;
    sf::Font font;
    font.loadFromFile("NotoSans-VariableFont_wdth,wght.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Black);

    chrono::high_resolution_clock::time_point last_frame = std::chrono::high_resolution_clock::now();

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed) {
                // m.reset();
                // m.generate_maze();
                // m.remove_wall(m.height-1,m.width-1,2);
                //std :: cout << b.step_forward() << std::endl;
                started = true;
            }
        }
        chrono::high_resolution_clock::time_point now_frame = std::chrono::high_resolution_clock::now();
        int dt = std::chrono::duration_cast<std::chrono::milliseconds>(now_frame-last_frame).count();
        //std::cout << dt << std::endl;
        last_frame = now_frame;


        if(started) {
            double repeat = (dt / ((double)1000/ (double)1000)); // target framerate / how many moves to make a second
            std::cout<<repeat<<std::endl;
            for(int i = 0; i <= repeat; i++) {
                b.step_forward();
                d.step_forward();
            }
        }
        m.show(window);
        text.setString(to_string(b.steps_taken));
        text.setPosition(sf::Vector2f(1200,50));
        window.draw(text);
        text.setString(to_string(d.steps_taken));
        text.setPosition(sf::Vector2f(1400,50));
        window.draw(text);
        window.display();


    }
    return 0;
}
