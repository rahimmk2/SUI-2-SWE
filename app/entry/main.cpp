#include "sui2swe.h"
#include "algo.h"

int main() {
	Sui2Swe s2s;

	s2s.file_to_graph("../../data/tx-data.csv");

	// Enable for printing tx data info
	// for (auto const& [tx_digest, other_txs] : s2s.txs) {
	// 	cout << "=====================================" << endl;
	// 	cout << ">>> TX: " << tx_digest << endl;
	// 	for (auto const& [otx_tx_digest, otx_obj] : other_txs) {
	// 		cout << "<< digest: " << otx_tx_digest << "\t-> obj id: " << otx_obj.first << "\t:: gas used " << otx_obj.second << endl;
	// 	}
	// }

	// Explore the lifetime of Object ID in our queried dataset
	string oid = "0x57e31e5ec13b10a548a957275b7d21504ddbba08";

	// Txs in our dataset that uses the oid
	string first_tx = "8ESwrhgyo6SeVqFPwFj5uUpMbusFASLocMEtUw9tWGCj";
	string middle_1_tx = "AvMjRZy6RmBihFPhsNFkU5zoQDinXWVEn3LZU5MKbjyh";
	string last_tx = "F5xDrnyUze5Dj292TU7t8PmNctJaVsYxdhr9CSVMCfst";
	string unrelated_tx = "Bw553zACeQr4tQct7AgwxRW3WcJAuSek41zFLGdXexKF";

	// Algo::topo_sort(s2s.txs);

	// RELATED, connected!
	cout << "====\n>> " << first_tx << " -> " << middle_1_tx << endl;
	string dfs_found = Algo::DFS(s2s.txs, first_tx, middle_1_tx) == 1 ? "true" : "false";
	cout << "<< DFS found: " << dfs_found << endl;
	cout << "<< Djikstra: " << Algo::djikstra(s2s.txs, first_tx, middle_1_tx) << " gas" << endl;

	// RELATED, connected!
	cout << "====\n>> " << first_tx << " -> " << last_tx << endl;
	dfs_found = Algo::DFS(s2s.txs, first_tx, last_tx) == 1 ? "true" : "false";
	cout << "<< DFS found: " << dfs_found << endl;
	cout << "<< Djikstra: " << Algo::djikstra(s2s.txs, first_tx, last_tx) << " gas" << endl;

	// RELATED, connected!
	cout << "====\n>> " << last_tx << " -> " << middle_1_tx << endl;
	dfs_found = Algo::DFS(s2s.txs, last_tx, middle_1_tx) == 1 ? "true" : "false";
	cout << "<< DFS found: " << dfs_found << endl;
	cout << "<< Djikstra: " << Algo::djikstra(s2s.txs, last_tx, middle_1_tx) << " gas" << endl;

	// UNRELATED, not connected!
	cout << "====\n>> " << first_tx << " -> " << unrelated_tx << endl;
	dfs_found = Algo::DFS(s2s.txs, first_tx, unrelated_tx) == 1 ? "true" : "false";
	cout << "<< DFS found: " << dfs_found << endl;
	cout << "<< Djikstra: " << Algo::djikstra(s2s.txs, first_tx, unrelated_tx) << " gas" << endl;

	// More examples

	// RELATED, connected!
	first_tx = "CbZ6LCaxhuESDQukoJPzFDXUziBNBGsTmxw3fPho4Tdg";
	last_tx = "2pCuh1RuBB2usgimXuz4vpszNwLfA8n36eib4kAiraK3";

	cout << "====\n>> " << first_tx << " -> " << last_tx << endl;
	dfs_found = Algo::DFS(s2s.txs, first_tx, last_tx) == 1 ? "true" : "false";
	cout << "<< DFS found: " << dfs_found << endl;
	cout << "<< Djikstra: " << Algo::djikstra(s2s.txs, first_tx, last_tx) << " gas" << endl;

	// UNRELATED, not connected!
	first_tx = "BdThF7SnZDgwiawyFBhSLB15XjjH4RnPMkh7WxQcxJYz";
	last_tx = "4HtQK2Eeo4EqUYTa7miP2AUgaBfQPQE9xZpgikZ484jk";

	cout << "====\n>> " << first_tx << " -> " << last_tx << endl;
	dfs_found = Algo::DFS(s2s.txs, first_tx, last_tx) == 1 ? "true" : "false";
	cout << "<< DFS found: " << dfs_found << endl;
	cout << "<< Djikstra: " << Algo::djikstra(s2s.txs, first_tx, last_tx) << " gas" << endl;
}