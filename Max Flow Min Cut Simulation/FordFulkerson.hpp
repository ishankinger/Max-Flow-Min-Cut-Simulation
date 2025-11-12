#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "HomeWindow.hpp"

class FordFulkerson {
private:
	int n;
	int m;
	std::vector<std::vector<std::pair<int, int>>> flowNetwork;
	std::vector<std::vector<std::vector<int>>> residualGraph;
	std::map<std::pair<int, int>, int> flow;
	std::vector<Graph> listOfGraphs;
	sf::Font& font;

public:
	FordFulkerson(int n, std::vector<std::vector<int>> edges, sf::Font& f);
	void constructResidualGraph();
	bool dfs(int node, int minFlow, std::vector<int>& vis, int& bottleNeck, std::vector<std::vector<int>>& path);
	bool isAugementPath(std::vector<std::vector<int>>& path, int& bottleNeck);
	void augement(std::vector<std::vector<int>>& path, int& bottleNeck);
	void MaxFlow();
	std::vector<Graph>& getListOfGraphs();
};