#include <catch2/catch_test_macros.hpp>

#include "sui2swe.h"
#include "algo.h"

typedef unordered_map<string, unordered_map<string, pair<string, int>>> ConnectedTxs;

ConnectedTxs txs_empty = {};

ConnectedTxs txs_simple = {
	{
		"tx1", {
			{"tx2", make_pair("obj2", 1)},
			{"tx3", make_pair("obj3", 5)},
		},
	},
	{
		"tx2", {
			{"tx4", make_pair("obj4", 2)},
		},
	},
	{
		"tx3", {
			{"tx5", make_pair("obj5", 3)},
		},
	},
	{
		"tx4", {
			{"tx5", make_pair("obj6", 1)},
		},
	},
	{
		"tx5", {
			{"tx1", make_pair("obj1", 1)},
		},
	},
	{
		"tx6", {},
	},
};

ConnectedTxs txs_twisted = {
	{
		"tx1", {
			{"tx4", make_pair("obj2", 1)},
			{"tx5", make_pair("obj3", 5)},
		},
	},
	{
		"tx2", {
			{"tx1", make_pair("obj4", 2)},
		},
	},
	{
		"tx3", {
			{"tx1", make_pair("obj5", 3)},
		},
	},
	{
		"tx4", {
			{"tx5", make_pair("obj6", 0)},
		},
	},
	{
		"tx5", {
			{"tx6", make_pair("obj1", 1)},
		},
	},
	{
		"tx6", {},
	},
};

TEST_CASE("test dfs empty", "[weight=5][algo=dfs][type=dummy]") {
	bool found = Algo::DFS(txs_empty, "tx1", "tx5");
	REQUIRE(!found);
}

TEST_CASE("test dfs find", "[weight=5][algo=dfs][type=dummy]") {
	bool found = Algo::DFS(txs_simple, "tx1", "tx5");
	REQUIRE(found);
}

TEST_CASE("test dfs NO find", "[weight=5][algo=dfs][type=dummy]") {
	bool found = Algo::DFS(txs_simple, "tx2", "tx6");
	REQUIRE(!found);
}

TEST_CASE("test dfs find twisted", "[weight=5][algo=dfs][type=dummy]") {
	bool found = Algo::DFS(txs_twisted, "tx2", "tx6");
	REQUIRE(found);
}

TEST_CASE("test djikstra empty", "[weight=5][algo=djikstra][type=dummy]") {
	int num = Algo::djikstra(txs_empty, "tx1", "tx5");
	REQUIRE(num == -1);
}

TEST_CASE("test djikstra invalid", "[weight=5][algo=djikstra][type=dummy]") {
	int num = Algo::djikstra(txs_simple, "tx1", "tx6");
	REQUIRE(num == -1);
}

TEST_CASE("test djikstra self", "[weight=5][algo=djikstra][type=dummy]") {
	int num = Algo::djikstra(txs_simple, "tx1", "tx1");
	REQUIRE(num == 0);
}

TEST_CASE("test djikstra find simple 1", "[weight=5][algo=djikstra][type=dummy]") {
	int num = Algo::djikstra(txs_simple, "tx1", "tx4");
	REQUIRE(num == 3);
}

TEST_CASE("test djikstra find simple 2", "[weight=5][algo=djikstra][type=dummy]") {
	int num = Algo::djikstra(txs_simple, "tx2", "tx5");
	REQUIRE(num == 3);
}

TEST_CASE("test djikstra find twisted 1", "[weight=5][algo=djikstra][type=dummy]") {
	int num = Algo::djikstra(txs_simple, "tx2", "tx5");
	// tx2 -(2)-> tx1 -(1)-> tx4 -(0)-> tx5 << shortest path
	// tx2 -(2)-> tx1 -(5)-> tx5
	REQUIRE(num == 3);
}

// TEST_CASE("test dfs NO find", "[weight=5][algo=dfs][type=dummy]") {
// 	bool found = Algo::DFS(graph, "tx2", "tx3");
// 	REQUIRE(!found);
// }

TEST_CASE("test topo simple", "[weight=5][type=topo]") {
	Algo::topo_sort(txs_simple);
}

TEST_CASE("test topo twisted", "[weight=5][type=topo]") {
	Algo::topo_sort(txs_twisted);
}

TEST_CASE("test print adjacency list", "[weight=5][type=print]") {
	Algo::print_adjacency_list(txs_simple);
}