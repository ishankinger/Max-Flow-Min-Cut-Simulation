#include "FordFulkerson.hpp"

FordFulkerson::FordFulkerson(int nodes, std::vector<std::vector<int>> edges, sf::Font &f) : font(f) {
	n = nodes;
	m = edges.size();
	flowNetwork.resize(n);
	for (int i = 0; i < m; i++) {
		edges[i][0]--;
		edges[i][1]--;
		int u = edges[i][0];
		int v = edges[i][1];
		int c = edges[i][2];
		flowNetwork[u].push_back({ v, c });
		flow[{u, v}] = 0;
	}
	listOfGraphs.emplace_back(nodes, edges, 0, font);
	constructResidualGraph();
	MaxFlow();
}

void FordFulkerson::constructResidualGraph() {
	std::vector<std::vector<std::vector<int>>> newResidualGraph(n);
	std::vector<std::vector<int>> resEdges;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)flowNetwork[i].size(); j++) {
			int u = i;
			int v = flowNetwork[i][j].first;
			int capacity = flowNetwork[i][j].second;

			int flowVal = flow[{u, v}];
			int leftFlow = capacity - flowVal;

			newResidualGraph[u].push_back({ v, leftFlow, 1 });
			newResidualGraph[v].push_back({ u, flowVal, 0 });

			resEdges.push_back({ u, v, leftFlow, flowVal });
		}
	}
	residualGraph = newResidualGraph;
	listOfGraphs.emplace_back(n, resEdges, 1, font);
}

bool FordFulkerson::dfs(int node, int minFlow, std::vector<int>& vis, int& bottleNeck, std::vector<std::vector<int>>& path) {
	vis[node] = 1;
	
	if (node == (int)vis.size() - 1) {
		bottleNeck = minFlow;
		return true;
	}

	for (auto neighbour : residualGraph[node]) {
		int neighbourNode = neighbour[0];
		int flow = neighbour[1];
		int edgeType = neighbour[2];

		if (flow == 0)
			continue;

		if (vis[neighbourNode])
			continue;

		path.push_back({ node, neighbourNode, edgeType });
		if (dfs(neighbourNode, std::min(minFlow, flow), vis, bottleNeck, path))
			return true;
		path.pop_back();
	}

	return false;
}

bool FordFulkerson::isAugementPath(std::vector<std::vector<int>>& path, int& bottleNeck) {
	std::vector<int> vis(n, 0);
	path = {};
	bottleNeck = -1;
	return dfs(0, 1e9, vis, bottleNeck, path);
}

void FordFulkerson::augement(std::vector<std::vector<int>>& path, int& bottleNeck) {
	std::vector<std::vector<int>> highlightEdges;
	for (int i = 0; i < (int)path.size(); i++) {
		int u = path[i][0];
		int v = path[i][1];
		int edgeType = path[i][2];

		if (edgeType) {
			highlightEdges.push_back({ u, v, 1 });
			flow[{u, v}] += bottleNeck;
		}
		else {
			highlightEdges.push_back({ v, u, 0 });
			flow[{v, u}] -= bottleNeck;
		}
	}
	listOfGraphs[listOfGraphs.size() - 1].highlightPath(highlightEdges);
	listOfGraphs[listOfGraphs.size() - 1].setBottleNeck(bottleNeck);

	std::vector<std::vector<int>> edges;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)flowNetwork[i].size(); j++) {
			int u = i;
			int v = flowNetwork[i][j].first;
			int capacity = flowNetwork[i][j].second;
			int flowVal = flow[{u, v}];
			edges.push_back({ u, v, capacity, flowVal });
		}
	}
	listOfGraphs.emplace_back(n, edges, 0, font);
}

void FordFulkerson::MaxFlow() {
	std::vector<std::vector<int>> path;
	int bottleNeck = 0, totalFlow = 0;
	while (isAugementPath(path, bottleNeck)) {
		augement(path, bottleNeck);
		totalFlow += bottleNeck;
		std::cout << "Total Flow : " << totalFlow << "  BottleNeck : " << bottleNeck << "\n";
		listOfGraphs[listOfGraphs.size() - 1].setNetFlow(totalFlow);
		constructResidualGraph();
	}
	listOfGraphs.pop_back();
	std::cout << "Maximum Flow: " << totalFlow << "\n";
}

std::vector<Graph>& FordFulkerson::getListOfGraphs() {
	return listOfGraphs;
}