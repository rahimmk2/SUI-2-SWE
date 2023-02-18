## Write up

Sui is a nascent blockchain with an innovative, Directed Acyclic Graph (DAG) foundation. Due to its young age and unique structure, no existing blockchain tools can be extended to Sui. This creates a problem in that users are deterred from use of Sui as the internal processes are unclear. In this project, we seek to create a general search tool for Sui. This will allow users to better understand and explore this blockchain solving the problem mentioned above. For the project, we had implemented 4 major functions - data parsing, DFS traversal, Dijkstra's algorithm, and topological search.

## Data Parsing  

The code takes an input csv file that holds the data from the Sui blockchain. The each line in the input csv file represents one transaction with the order of the comma delimited item as follows: 
	
Transaction_digest: ID of transaction

Timestamp_ms: time of transaction

Shared_objects_str: a list of object IDs used in this transaction, with each object having tx_digest of its latest usage

Created_str: a list of object IDs created in this transaction, where each object has   tx_digest = transaction_digest since this transaction created the object

Mutated_str: a list of object IDs used in this transaction, with each object having tx_digest of its latest usage

Gas_used: Amount of cryptocurrency used in making the transaction


The collection of the data is done through a python script that calls an api to acquire the data directly from the blockchain.

For the implementation of the other algorithms we used the Transaction_digest, Created_str, and Gas_used to build an adjacency set to represent a weighted directed acyclic graph. The data is stored in an unordered_map<string, unordered_map<string, pair<string, int>>> using the function File_to_graph(). The node of the graph is the transaction and the edge between two nodes represents the gas used in making the transaction from the first node to the second. We did not have to have a code to strain the input data to exclude wrong inputs as due to the nature of the source of the data - the data from a blockchain is error free as monetarily incentivised individuals work to maintain the validity of the data.

## Depth First Search: 

The DFS, or Depth-First Search, is an algorithm for traversing a graph or tree data structure. It starts at the root node and explores as far as possible along each subtree before backtracking. DFS is useful for searching a graph or tree to find a specific node or checking if a path between two nodes exists. Our implementation of the DFS takes two nodes - which in our case is two different transactions - and returns a boolean value based on if there is a valid path from the first node to the second node. As the Sui blockchain is in the format of a DAG (directed acyclic graph), the order of the input nodes matter.

The time complexity of DFS is O(V+E), where E is the number of edges in the graph. This is because the algorithm checks each vertex and edge of the graph exactly once, with a time complexity of O(C) to make each check.

To test the integrity of the DFS we constructed small test DAGs - one simple (only one node without a predecessor), and one twisted (multiple nodes without predecessors) and ran DFS with the pair of nodes that:

Are part of a valid path, returning true

Are not part of a valid path, returning false

And run on an empty DAG, also returning false.



## Dijkstra's Algorithm: 

Dijkstra's algorithm is a graph search algorithm that is designed to find the shortest path between two nodes on a graph. The algorithm works by starting at the starting node and exploring its neighbors, then moving to the neighbor with the lowest cost and repeats this process until it reaches the destination node. Therefore, we can see it as a greedy algorithm. In our implementation of this algorithm, we take two input nodes and return an int that represents the minimum total gas use between the two nodes. If there isn’t a valid path between the two nodes, the function returns -1. 
	
The time complexity of Dijkstra's algorithm is O((V+E)logV), with V and E representing the number of vertices and edges within the graph, respectively. This happens because the algorithm needs to traverse the adjacency set to find the minimum cost edge at each step.

We used the same test DAGs constructed in the testing of the DFS to test the DAG. The specific test cases included two nodes that:

Have a valid connection from node a to node b, thus returning the total weight of the path with the lowest gas use

Are equal one another (the same node), thus returning 0

Does not have a valid connection from node a to node b, thus returning -1

Are connected but with the edge directed in the opposite direction, also returning -1.

## Data Visualization via Topological Sort:

A topological sort algorithm is an algorithm that takes a directed graph and returns an array of the nodes where each node appears before all the nodes it points to. A topological sort’s role in the context of the Sui blockchain is that it can be used to determine the order in which the transactions need to be made. Our version of the algorithm depends on a process similar to our depth first search algorithm - however, it returns an array of transactions instead of a boolean.

Likewise, the time complexity of the topological search is O(V+E) with the reasoning being similar to that of the DFS -  each vertex and edge of the graph is visited once with each visit resulting in a runtime of O(C).

We used the same test DAGs constructed in the testing of the DFS to test the topological sort, running topological sort on both to see if the return arrays were valid topological sorts.

	
## Conclusion

By taking on this project we were able to create a set of algorithms that could make the approach to the Sui blockchain a bit easier for potential users. We were also to meet our initial goal to some degree - creating a program that makes the inner workings of Sui completely transparent and understandable turned out to be far out of the scope of the project and our abilities, but we were able to create code that makes the most important parts of Sui more accessible. 
However, we had problems implementing an algorithm to create a graphical representation of the DAG. Our group was unable to come up with a way that would make sense in terms of the accuracy of the visual representation of the data and our ability to code within the given timeframe. Therefore, we made a change in our plans to write an algorithm for the topological sort - another algorithm that can fulfill the role of presenting the data in an understandable manner. 

Considering that the majority of the group started off with close to no knowledge regarding blockchains and the replacement algorithm remained with the scope of our project, we still see that the project has been successful in meeting the initial goals we have set - to create algorithms that could make the Sui blockchain more approachable.

We think that this project has enabled us to appreciate and understand the beauty of how the Sui blockchain functions. We also got to better understand where different types of data structures really shine to make the system more efficient. If given more time to explore this topic and build on our code, the goal for us would be to do what we had failed to do this time - create a way to visualize the DAG in an intuitive way and implement it C++.
