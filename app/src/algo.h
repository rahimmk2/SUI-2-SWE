/**
 * @file algo.h
 */

#ifndef ALGO_H
#define ALGO_H

#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <set>
#include <unordered_map>
#include <string>

using namespace std;

typedef unordered_map<string, unordered_map<string, pair<string, int>>> ConnectedTxs; // {tx_digest : {tx_dgiest : (obj_id, gas_price), ...}, ...}

class Algo {
	public:
		static bool DFS(ConnectedTxs txs, string start, string goal);
		static pair<string, int> shortestPath(unordered_map<string, int> &dist, unordered_map<string, bool> &visited);
		static int djikstra(ConnectedTxs txs, string src, string dest);
		// static void topologicalSort();
		static void topo_sort(ConnectedTxs txs);
		static void topo_sort_util(string tx, unordered_map<string, pair<string, int>> other_txs, unordered_map<string, bool> &visited, stack<string> &stack);
		static void print_adjacency_list(ConnectedTxs txs);
};

#endif
