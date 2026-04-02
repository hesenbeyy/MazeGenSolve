#include <iostream>
#include <SFML/Graphics.hpp>
#include "stack.hpp"
#include "maze.hpp"

int main() {

	Maze maze;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Maze");
	sf::Vector2i mousePos;
	bool isStartSelected = false;
	bool isFinishSelected = false;
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

		window.clear(sf::Color::Black);
		maze.drawGrid(window);
		maze.drawStartFinish(window);
		window.display();

		if (!isMazeCreated) maze.maze_generation(window);
		isMazeCreated = true;

		if (isStartSelected && isFinishSelected && !pathComputed && solveMaze) {
			maze.djikstra(window);
			pathComputed = true;
		}
	}
	return 0;
}