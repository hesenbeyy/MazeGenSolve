#ifndef MAZE_HPP
#define MAZE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include "structs.hpp"
#include "macros.hpp"
#include "stack.hpp"


class Maze {
private:
	std::vector<Cell> grid;
	Stack<int> stack;
	int startIndex = -1;
	int finishIndex = -1;

public:
	Maze() {
		grid.resize(MAX_SIZE);
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				int index = getIndex(i, j);
				grid[index].row = i;
				grid[index].col = j;
			}
		}
	}

	inline int getIndex(int row, int col) const { return row * COLS + col; }

	const Cell& getCell(int index) const { return grid[index]; }

	Cell& getCell(int index) { return grid[index]; }

	void setStart(int row, int col) { startIndex = getIndex(row, col); }
	void setFinish(int row, int col) { finishIndex = getIndex(row, col); }

	inline bool isValid(int row, int col) const { return row >= 0 && row < ROWS && col >= 0 && col < COLS; }

	void drawStartFinish(sf::RenderWindow& window) {

		float padding = 2.0f;
		sf::RectangleShape rect(sf::Vector2f(CELL_SIZE - padding, CELL_SIZE - padding));

		if (startIndex != -1) {
			Cell& start = getCell(startIndex);

			rect.setPosition(start.col * CELL_SIZE + (padding / 2), start.row * CELL_SIZE + (padding / 2));
			rect.setFillColor(sf::Color::Red);
			window.draw(rect);
		}
		if (finishIndex != -1) {
			Cell& finish = getCell(finishIndex);
			rect.setPosition(finish.col * CELL_SIZE + (padding / 2), finish.row * CELL_SIZE + (padding / 2));
			rect.setFillColor(sf::Color::Green);
			window.draw(rect);
		}
	}

	inline void drawCell(const Cell& c, sf::RenderWindow& window) {
		int x = c.col * CELL_SIZE;
		int y = c.row * CELL_SIZE;

		if (c.path) {
			sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			rect.setPosition(float(x), float(y));
			rect.setFillColor(sf::Color(227, 38, 54, 255));
			window.draw(rect);
		}
		else if (c.visited_djikstra) {
			sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			rect.setPosition(float(x), float(y));
			rect.setFillColor(sf::Color(255, 165, 0, 150));
			window.draw(rect);
		}

		else if (c.visited) {
			sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
			rect.setPosition(float(x), float(y));
			rect.setFillColor(sf::Color(100, 100, 100));
			window.draw(rect);
		}

		if (c.walls[TOP]) {
			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(x,y), sf::Color::White),
				sf::Vertex(sf::Vector2f(x + CELL_SIZE, y), sf::Color::White)
			};

			window.draw(line, 2, sf::Lines);
		}

		if (c.walls[BOTTOM]) {
			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(x, y + CELL_SIZE), sf::Color::White),
				sf::Vertex(sf::Vector2f(x + CELL_SIZE, y + CELL_SIZE), sf::Color::White)
			};

			window.draw(line, 2, sf::Lines);
		}

		if (c.walls[LEFT]) {
			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(x,y), sf::Color::White),
				sf::Vertex(sf::Vector2f(x,y + CELL_SIZE), sf::Color::White)
			};

			window.draw(line, 2, sf::Lines);
		}

		if (c.walls[RIGHT]) {
			sf::Vertex line[] = {
				sf::Vertex(sf::Vector2f(x + CELL_SIZE,y), sf::Color::White),
				sf::Vertex(sf::Vector2f(x + CELL_SIZE, y + CELL_SIZE), sf::Color::White)
			};

			window.draw(line, 2, sf::Lines);
		}
	}

	inline void drawCell(const Cell& c, sf::RenderWindow& window, sf::Color color) {
		int x = c.col * CELL_SIZE;
		int y = c.row * CELL_SIZE;

		sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		rect.setPosition(float(x), float(y));
		rect.setFillColor(color);
		window.draw(rect);
	}

	inline void drawGrid(sf::RenderWindow& window) {
		for (int x = 0; x < COLS; x++) {
			for (int y = 0; y < ROWS; y++) {
				drawCell(getCell(getIndex(y, x)), window);
			}
		}
	}

	inline std::vector<int> getUnvisitedNeighbours(int currentIndex) const {
		std::vector<int> neighbours;
		const Cell& current = getCell(currentIndex);
		int r = current.row;
		int c = current.col;

		// Bottom
		if (isValid(r + 1, c) && !getCell(getIndex(r + 1, c)).visited) {
			neighbours.push_back(getIndex(r + 1, c));
		}

		// Top
		if (isValid(r - 1, c) && !getCell(getIndex(r - 1, c)).visited) {
			neighbours.push_back(getIndex(r - 1, c));
		}

		// Left
		if (isValid(r, c - 1) && !getCell(getIndex(r, c - 1)).visited) {
			neighbours.push_back(getIndex(r, c - 1));
		}

		// Right
		if (isValid(r, c + 1) && !getCell(getIndex(r, c + 1)).visited) {
			neighbours.push_back(getIndex(r, c + 1));
		}

		return neighbours;
	}

	inline void removeWalls(Cell& current, Cell& neighbour) {
		int dx = current.col - neighbour.col;
		int dy = current.row - neighbour.row;

		Wall direction;
		if (dx == 1) direction = LEFT;
		else if (dx == -1) direction = RIGHT;
		else if (dy == 1) direction = TOP;
		else if (dy == -1) direction = BOTTOM;

		current.walls[direction] = false;
		neighbour.walls[(direction + 2) % 4] = false;

		return;
	}

	inline void maze_generation(sf::RenderWindow& window) {

		srand(static_cast<unsigned int>(time(NULL)));
		int currentIndex{ 0 };
		int neighbourIndex{ 0 };
		stack.push(currentIndex);
		getCell(currentIndex).visited = true;

		while (!stack.isEmpty()) {
			currentIndex = stack.peek();
			std::vector<int> neighbours = getUnvisitedNeighbours(currentIndex);
			

			if (neighbours.size()) {

				neighbourIndex = neighbours[rand() % neighbours.size()];
				removeWalls(getCell(currentIndex), getCell(neighbourIndex));
				getCell(neighbourIndex).visited = true;
				stack.push(neighbourIndex);
				
			}
			else {
				stack.pop();
			}

			// COMMENT THIS PART IF YOU DESIRE MOMENTARY VISUALIZATION

			window.clear(sf::Color::Black);
			drawGrid(window);

			if (!stack.isEmpty()) {
				drawCell(getCell(stack.peek()), window, sf::Color(255, 165, 0, 255));
			}

			window.display();

			// COMMENT THIS PART IF YOU DESIRE MOMENTARY VISUALIZATION
		}


		// UNCOMMENT THIS PART IF YOU DESIRE MOMENTARY VISUALIZATION
		
		/* 
		window.clear(sf::Color::Black);
		drawGrid(window);
		drawCell(getCell(isCurrent ? currentIndex : neighbourIndex), window, sf::Color(255, 165, 0, 255));
		window.display(); 
		*/

		// UNCOMMENT THIS PART IF YOU DESIRE MOMENTARY VISUALIZATION

		return;
	}

	std::vector<int> getAccesibleNeighbours(int index) {
		std::vector<int> neighbours;
		Cell& current = getCell(index);
		int r = current.row;
		int c = current.col;

		// TOP 
		if (isValid(r - 1, c) && !getCell(getIndex(r - 1, c)).visited_djikstra && !current.walls[TOP]) {
			neighbours.push_back(getIndex(r - 1, c));
		}

		// BOTTOM
		if (isValid(r + 1, c) && !getCell(getIndex(r + 1, c)).visited_djikstra && !current.walls[BOTTOM]) {
			neighbours.push_back(getIndex(r + 1, c));
		}

		// LEFT
		if (isValid(r, c - 1) && !getCell(getIndex(r, c - 1)).visited_djikstra && !current.walls[LEFT]) {
			neighbours.push_back(getIndex(r, c - 1));
		}

		// RIGHT
		if (isValid(r, c + 1) && !getCell(getIndex(r, c + 1)).visited_djikstra && !current.walls[RIGHT]) {
			neighbours.push_back(getIndex(r, c + 1));
		}

		return neighbours;
	}

	std::vector<int> reconstructPath() {
		std::vector<int> path;
		int currentIndex = finishIndex;
		while (currentIndex != -1) {
			getCell(currentIndex).path = true;
			path.push_back(currentIndex);
			currentIndex = getCell(currentIndex).previous;
		}

		std::reverse(path.begin(), path.end());
		return path;
	}

	

	void djikstra(sf::RenderWindow& window) {

		std::priority_queue<
			std::pair<int, int>,
			std::vector<std::pair<int, int>>,
			std::greater<std::pair<int, int>>
		> pq;

		getCell(startIndex).distance = 0;
		pq.push({ 0, startIndex });

		while (!pq.empty()) {
			auto [dist, currentIndex] = pq.top();
			pq.pop();

			Cell& current = getCell(currentIndex);
			if (current.visited_djikstra) continue;
			current.visited_djikstra = true;
			window.clear(sf::Color::Black);
			drawGrid(window);
			drawStartFinish(window);
			window.display();

			if (currentIndex == finishIndex) break;

			for (int neighbourIndex : getAccesibleNeighbours(currentIndex)) {
				Cell& neighbour = getCell(neighbourIndex);
				int newDist = current.distance + 1;
				if (newDist < neighbour.distance) {
					neighbour.distance = newDist;
					neighbour.previous = currentIndex;
					pq.push({ newDist, neighbourIndex });
				}
			}
		}

		reconstructPath();
		window.clear(sf::Color::Black);
		drawGrid(window);
		window.display();
	}
};

#endif