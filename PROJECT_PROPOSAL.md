# Proposal

## Leading Question 
Sui is a nascent blockchain with an innovative, Directed Acyclic Graph (DAG) foundation. Due to its young age and immature structure, no tools exist to support the exploration of activities and connectivities on this blockchain. No existing blockchain tools can be extended to Sui either, as it implements a graph. This creates a problem in that users are deterred from use of Sui as the internal processes are unclear. In this project, we seek to create a general search tool for Sui. This will allow users to better understand and explore this blockchain solving the problem mentioned above. We also seek to expand our own understanding of the inner workings of blockchain throughout this project.
## Dataset Acquisition

## Data Format
As a blockchain, Sui is entirely public and free to download. Running a full Sui node will provide us with the entire dataset of Sui, which contains transactions, checkpoints, and epoch changes (blockchain state and history). With the blockchain in our possession, we can follow the instructions and specs documented by Sui to get the entire DAG or a portion of it. For the sake of this project, we plan to use a subset of the dataset - the entire blockchain would be too immense. We can arbitrarily choose any range of epochs (block numbers) and download all data in between the epochs to show that the algorithms we implement can be applied to any subset of Sui.

## Data Correction
The beauty of blockchain is that ALL data settled/finalized into the blockchain are decentrally verified by all participating validators (who are financially incentivized). Thus, no error-free values exist and all values downloaded are verified to be valid—this is the nature of blockchain technology. For local verification, we can execute a topological sorting/ordering of the collected data to verify that it’s a valid DAG (especially for a subset of the entire Sui DAG).

## Data Storage
When storing the data, we will simply use a relational database that maintains DAG relations. When loading the data onto the script, we will reconstruct the DAG from the relational database stored locally. Storing the data will take O(n) storage as we simply traverse and save all available transactions from Sui, without overlapping. Loading the data will take O(|V| + |E|) as it’s a DAG.

## Algorithm 
To analyze the Sui blockchain and present it in a way that's more understandable to the general public, these are the following algorithms we are going to implement.

DFS

This traversal will allow us to figure out all possible paths that can be taken for the completion of a transaction. The estimate of the worst case runtime of the traversal is O(n).

Dijkstra’s Algorithm

This algorithm will take a start node and end node from the DAG and find the shortest path between two nodes. This shows the user the shortest path from the original state to the end state (path independent), allowing users to better understand what’s happening. The time complexity is O(E logV), where E is the total number of edges and V is the number of vertices. Or, equivalently, O(N logN).

Graphic Output of Graph

This algorithm will take the DAG and create a graphical representation of it. This will allow users to visualize the transactions and support their understanding of Sui. Similar to Dijkstra’s, the time complexity is O(E logV).


## Timeline
The following timeline is a general plan on when we want to have the listed task done. In the case each task is completed before the given week, we will start working on the tasks planned for the following week. If the timeline includes a algorithm we need to implent, local test cases will be written and run on the same week.

Data Acquisition & processing: week ending 11/12

DFS & Dijkstra’s Algorithm : week ending 11/19

Week off: week ending 11/26

Graphic Output of Graph: week ending 12/3

Written report and final presentation: 12/8

