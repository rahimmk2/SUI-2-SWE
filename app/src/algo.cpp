/**
 * @file algo.cpp
 */

#include "algo.h"

bool Algo::DFS(ConnectedTxs txs, string start, string goal) {
	stack<string> s;
	unordered_map<string, bool> visited;

	if (!txs.count(start)) {
		return false;
	}

	for (auto const& [tx, other_txs] : txs) { // vertex
		visited[tx] = false;
	}

	s.push(start);
	while (!s.empty()) {
		string tx = s.top();
		s.pop();

		if (!visited[tx]) {
			visited[tx] = true;
			for (auto const& [otx_tx, otx_obj_id] : txs[tx]) { // adjacent vertices
				if (!visited[otx_tx]) {
					s.push(otx_tx);
				}
			}
		}
	}

	return visited[goal];
}

// Function to find the minimum distance node from the set of
// nodes not yet included in shortest path tree
pair<string, int> Algo::shortestPath(
	unordered_map<string, int> &dist,
	unordered_map<string, bool> &visited
) {
	// Initialize min value
	int min_gas = 2147483647; // max int
	string min_node;

	for (const auto &[tx_digest, gas_used]: dist) {
		// cout << tx_digest << " " << gas_used << endl;
		if (!visited[tx_digest] && min_gas > gas_used) {
			min_gas = gas_used;
			min_node = tx_digest;
		}
	}

	return make_pair(min_node, min_gas);
}

// Function to print the shortest path and distance
// from source to destination using Dijkstra's algorithm
int Algo::djikstra(
	ConnectedTxs txs,
	string src,
	string dest
) {
	if (src == dest) return 0;

	unordered_map<string, int> dist;
	unordered_map<string, bool> visited;

	// Intialize all distances as arbitrary MAX and visited as false
	for (const auto &[tx_digest, adj] : txs) {
		dist[tx_digest] = 2147483647; // max int
		visited[tx_digest] = false;
	}

	dist[src] = 0; // start is at 0

	for (size_t i = 0; i < txs.size() - 1; i++) {
		const auto [min_node, min_gas] = Algo::shortestPath(dist, visited);

		visited[min_node] = true;

		// Update distance value of the adjacent nodes of the selected node
		for (const auto &[adj_tx_digest, adj_tx_data]: txs[min_node]) {
			const auto &[adj_tx_obj_id, adj_tx_gas] = adj_tx_data;
			// If the node is not visited and there is a path from source to the node 
			// through the selected node with distance less than the current distance of the node (< then update)
			if (!visited[adj_tx_digest] && (dist[min_node] + adj_tx_gas < dist[adj_tx_digest])) {
				dist[adj_tx_digest] = dist[min_node] + adj_tx_gas;
			}
		}
	}

	// dist 0 or 2147483647 is unfound
	return dist[dest] == 0 || dist[dest] == 2147483647 ? -1 : dist[dest];
}

void Algo::topo_sort_util(
	string tx,
	unordered_map<string, pair<string, int>> other_txs,
	unordered_map<string, bool> &visited,
	stack<string> &stack
) {
  visited[tx] = true;

  // Adjacent
	for (auto const& [tx, tx_data] : other_txs) {
    if (!visited[tx]) {
			Algo::topo_sort_util(tx, other_txs, visited, stack);
		}
	}

  // Push current node to stack
  stack.push(tx);
}

void Algo::topo_sort(ConnectedTxs txs) {
	stack<string> s;
	unordered_map<string, bool> visited;

	// initialize all nodes as not visited
	for (auto const& [tx, other_txs] : txs) {
		visited[tx] = false;
	}

	for (auto const& [tx, other_txs] : txs) {
		if (!visited[tx]) {
			Algo::topo_sort_util(tx, other_txs, visited, s);
		}
	}

	cout << "Topological sort: " << endl;
	while (!s.empty()) {
		cout << s.top();
		s.pop();
		if (!s.empty()) cout << " -> ";
	}
	cout << endl;
}

void Algo::print_adjacency_list(ConnectedTxs txs) {
	for (auto it = txs.begin(); it != txs.end(); it++) {
		cout << it->first << " -> ";
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			cout << it2->first << " ";
		}
		cout << endl;
	}
}
