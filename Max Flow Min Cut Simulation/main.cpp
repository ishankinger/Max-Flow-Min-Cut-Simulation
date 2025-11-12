#include "HomeWindow.hpp"
#include "FordFulkerson.hpp"

int main() {

	//int n = 11;
	//std::vector<std::vector<int>> edges_n11 = { {1, 2, 4, 0}, {2, 3, 5, 0}, { 3, 4, 2, 0},
	//											{4, 5, 1, 0}, {5, 6, 2, 0}, {6, 7, 4, 0}, 
	//											{7, 8, 8, 0} , {8, 9, 3, 0},  {9, 10, 4, 0},
	//											{10, 11, 2, 0}, {1, 7, 6, 0}, {2, 8, 2, 0}, 
	//											{3, 9, 3, 0}, {4, 10, 1, 0}, {5, 11, 3, 0} };
	
	std::ifstream input("take_input.txt");
	if (!input.is_open()) {
		std::cerr << "Error: could not open take_input.txt\n";
		return 1;
	}

	int n, m;
	input >> n >> m;

	std::vector<std::vector<int>> edges;

	for (int i = 0; i < m; ++i) {
		int u, v, w, x;
		input >> u >> v >> w >> x;
		edges.push_back({ u, v, w, x });
	}

	input.close();

	sf::Font mainFont;
	if (!mainFont.loadFromFile("./Quaaykop-DYE1R.ttf")) {
		std::cout << "Error loading the font file\n";
		return 0;
	}
	
	FordFulkerson ff(n, edges, mainFont);
	std::vector<Graph> &listOfGraphs = ff.getListOfGraphs();

	try {
		runSimuation(listOfGraphs, mainFont);
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}
	catch (...) {
		std::cout << "Unknonwn exception\n";
	}

	return 0;
}