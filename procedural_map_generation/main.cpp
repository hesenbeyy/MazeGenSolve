#include <iostream>
#include <SFML/Graphics.hpp>
#include "stack.hpp"
#include "maze.hpp"

int main() {

	Maze maze;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Maze");
	sf::Vector2i mousePos;
	//bool isStartSelected = true;
	//bool isFinishSelected = true;
	bool isMazeCreated = false;
	bool pathComputed = false;
	bool solveMaze = false;


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (event.key.code == sf::Keyboard::S) solveMaze = true;
			}

			if (isMazeCreated && event.type == sf::Event::MouseButtonPressed) {
				mousePos = sf::Mouse::getPosition(window);

				int col = mousePos.x / CELL_SIZE;
				int row = mousePos.y / CELL_SIZE;

				if (!maze.isValid(row, col)) continue;

				if (!isStartSelected) {
					maze.setStart(row, col);
					isStartSelected = true;
				}
				else if (!isFinishSelected) {
					maze.setFinish(row, col);
					isFinishSelected = true;
				}
			}
		}
		/*
		window.clear(sf::Color::Black);
		maze.drawGrid(window);
		maze.drawStartFinish(window);
		window.display();
		*/
		if (!isMazeCreated) {
			maze.maze_generation(window);
			isMazeCreated = true;
		}
		

		if (!pathComputed && solveMaze) {
			auto start = std::chrono::high_resolution_clock::now();

			maze.djikstra(window);

			auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<double> elapsed = end - start;

			std::cout << "Time: " << elapsed.count() << " seconds\n";
			pathComputed = true;
		}
		window.clear(sf::Color::Black);
		maze.drawGrid(window);
		maze.drawStartFinish(window);
		window.display();
	}
	

	return 0;
}