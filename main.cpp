#include "bfs.h"
#include "Maze.h"
using namespace std;

const int width = 75; // maze width
const int height = 75; // maze height
const int mps = 144; // steps per second

#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <random>
#include <dfs.h>

using namespace std;

// directions to move in
vector<pair<int, int> > directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// // random num gen credit: https://stackoverflow.com/questions/7560114/random-number-c-in-some-range


int main() {
    //create a window with text about what this is with
    // string maze = generateMaze();
    // cout << maze;
    Maze m = Maze(width, height);
    m.generate_maze();
    m.remove_wall(m.height - 1, m.width - 1, 2);
    m.make_lines();

    auto window = sf::RenderWindow({(int) WINDOW_WIDTH, (int) WINDOW_HEIGHT}, "BFS vs DFS");
    m.show(window);

    window.setFramerateLimit(144);
    bool started = true;
    dfs d = dfs(&m);
    bfs b = bfs(&m);

    chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    double d_time = 0;
    double b_time = 0;

    start = std::chrono::high_resolution_clock::now();
    while (b.step_forward() == -1);
    finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = finish - start;
    b_time = duration.count();


    start = std::chrono::high_resolution_clock::now();
    while (d.step_forward() == -1);
    finish = std::chrono::high_resolution_clock::now();
    duration = finish - start;
    d_time = duration.count();

    d.reset();
    b.reset();
    m.reset_colors();


    m.reset_colors();

    sf::Text text;
    sf::Font font;
    font.loadFromFile("NotoSans-VariableFont_wdth,wght.ttf");
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::Black);

    chrono::high_resolution_clock::time_point last_frame = std::chrono::high_resolution_clock::now();

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                m.reset();
                m.generate_maze();
                m.remove_wall(m.height - 1, m.width - 1, 2);
                m.make_lines();
                b.reset();
                d.reset();
                //std :: cout << b.step_forward() << std::endl;
                //started = true;

                start = std::chrono::high_resolution_clock::now();
                while (b.step_forward() == -1);
                finish = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration = finish - start;
                b_time = duration.count();


                start = std::chrono::high_resolution_clock::now();
                while (d.step_forward() == -1);
                finish = std::chrono::high_resolution_clock::now();
                duration = finish - start;
                d_time = duration.count();

                d.reset();
                b.reset();
                m.reset_colors();

                start_time = std::chrono::high_resolution_clock::now();


                m.reset_colors();
            }
        }
        chrono::high_resolution_clock::time_point now_frame = std::chrono::high_resolution_clock::now();
        int dt = std::chrono::duration_cast<std::chrono::milliseconds>(now_frame - last_frame).count();
        //std::cout << dt << std::endl;
        last_frame = now_frame;


        if (started) {
            double repeat = (dt / ((double) 1000 / (double) mps)); // how many moves to make a second
            //std::cout << repeat << std::endl;
            for (int i = 0; i <= repeat; i++) {
                b.step_forward();
                d.step_forward();
            }
        }
        m.show(window);

        text.setString(to_string(b.steps_taken));
        text.setPosition(sf::Vector2f(1200, 50));
        window.draw(text);

        text.setString("BFS");
        text.setPosition(sf::Vector2f(1200, 150));
        window.draw(text);

        text.setString(to_string(b_time) + " ms");
        text.setPosition(sf::Vector2f(1100, 250));
        window.draw(text);

        text.setString(to_string(d.steps_taken));
        text.setPosition(sf::Vector2f(1600, 50));
        window.draw(text);

        text.setString("DFS");
        text.setPosition(sf::Vector2f(1600, 150));
        window.draw(text);

        text.setString(to_string(d_time) + " ms");
        text.setPosition(sf::Vector2f(1500, 250));
        window.draw(text);

        auto curr_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dur = curr_time - start_time;
        text.setString(to_string(dur.count()) + " s");
        text.setPosition(sf::Vector2f(1300, 800));
        window.draw(text);

        window.display();
    }
    return 0;
}
