/**
 * @file sui2swe.h
 */

#ifndef S2S_H
#define S2S_H

#include <fstream>
#include <sstream>

#include "algo.h"

// typedef unordered_map<string, unordered_map<string, string>> ConnectedTxs; // {tx_digest : {tx_dgiest : obj_id, ...}, ...}

class Sui2Swe {
	public:
		void file_to_graph(const string &filename);

		ConnectedTxs txs;
	
		// Graph graph;
	private:
};

#endif