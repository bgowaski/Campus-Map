//#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <queue>
#include <stack>
#include <string>

using namespace std;
// Value to put at max distance if distance not found
#define MAX 9999

// Data structure to store graph edges
struct Edge {
	int start, finish, weight;
};

// data structure to store heap nodes
struct Node {
	int vertex, weight;
};

// class to represent a graph object
class Graph
{
public:
	// construct a vector of vectors of Edge to represent an adjacency list
	vector<vector<Edge>> adj;

	// Graph Constructor
	Graph(vector<Edge> const &edges, int N)
	{
		// resize the vector to N elements of type vector<Edge>
		adj.resize(N);

		// add edges to the undirected graph
		for (Edge const &edge : edges)
		{
			// insert at end
			adj[edge.start].push_back(edge);
		}
	}
};

void print_route(vector<int> const &prev, int i)
{
	string output;
	if (i < 0) {
		return;
	}
	// Print out route from stored prev vector
	print_route(prev, prev[i]);
	// If building entered is alphanumeric, convert!
	if (i == 19)
	{
		output = "23H";
	}
	else if (i == 18)
	{
		output = "23G";
	}
	else if (i == 17)
	{
		output = "23F";
	}
	else if (i == 16)
	{
		output = "23E";
	}
	else if (i == 15)
	{
		output = "23C";
	}
	else if (i == 14)
	{
		output = "23B";
	}
	else if (i == 13)
	{
		output = "23A";
	}
	else
	{
		output = to_string(i);
	}
	cout << output << "--";
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(const Node &lhs, const Node &rhs) const
	{
		return lhs.weight > rhs.weight;
	}
};

// Dijkstra implementation adapted from source:
// https://www.techiedelight.com/single-source-shortest-paths-dijkstras-algorithm/
// Run Dijkstra's algorithm on given graph
void dijkstra(Graph const& graph, int start,int end, int N, string sbegin, string sfin)
{
	// create min heap and push start node having distance 0
	priority_queue<Node, vector<Node>, comp> min_heap;
	min_heap.push({ start, 0 });

	// set infinite distance from start to v initially
	vector<int> dist(N, MAX);

	// distance from start to itself is zero
	dist[start] = 0;

	// boolean array to track vertices for which minimum
	// cost is already found
	vector<bool> done(N, false);
	done[0] = true;

	// previous vector to get next in path
	vector<int> prev(N, -1);

	// run till min_heap is not empty
	while (!min_heap.empty())
	{
		// Remove and return best vertex
		Node node = min_heap.top();
		min_heap.pop();

		// get vertex number
		int u = node.vertex;

		// do for each neighbor v of u
		for (auto i : graph.adj[u])
		{
			int v = i.finish;
			int weight = i.weight;

			// Relaxation step
			if (!done[v] && (dist[u] + weight) < dist[v])
			{
				dist[v] = dist[u] + weight;
				prev[v] = u;
				min_heap.push({ v, dist[v] });
			}
		}

		// marked vertex u as done so it will not get picked up again
		done[u] = true;
	}

		cout << "Path from building "<< sbegin <<" to building " << sfin << " is "
			 << dist[end] <<"feet long and the route is : ";
		print_route(prev, end);
		cout << "THE END!";
}

// main function
int main()
{
	ifstream file;
	stack <int> moves;
	string fileName;

	fileName = "campus_map.txt";
	file.open(fileName.c_str());
	// Read in the graph
	cout << "Reading graph" << endl;
	// node1, node2, weight of edge
	int i, j, w;
	// Number of nodes
	int n = 0;
	// Create a vector of edges to pass in to graph constructor
	vector<Edge> edges;
	// Print out list of edges
	//cout << "Edge	Node1	Node2	Weight\n";
	while (file.peek() != '.')
	{
		// start at 1st edge
		n++;
		file >> i >> j >> w;
		edges.push_back({ i,j,w });
		// Print out all edges
		//cout << n <<",	 "<< i << ",	" << j << ",	" << w << " \n";
	}

	// construct graph
	Graph graph(edges, edges.size());

	string begin;
	string fin;
	int ibegin = 0;
	int ifin = 0;
	// User will enter strings and they will be converted to ints if needed (i.e. 23H ->
	//23H--->19
	//23G--->18
	//23F--->17
	//23E--->16
	//23C--->15
	//23B--->14
	//23A--->13
	cout << "Please enter a numbered start location from campus map: ";
	cin >> begin;
	if (begin == "23H")
	{
		ibegin = 19;
	}
	else if (begin == "23G")
	{
		ibegin = 18;
	}
	else if (begin == "23F")
	{
		ibegin = 17;
	}
	else if (begin == "23E")
	{
		ibegin = 16;
	}
	else if (begin == "23C")
	{
		ibegin = 15;
	}
	else if (begin == "23B")
	{
		ibegin = 14;
	}
	else if (begin == "23A")
	{
		ibegin = 13;
	}
	else
	{
		ibegin = stoi(begin);
	}
	// Print out and match up with building
	cout << "Please enter a numbered end location from campus map: ";
	cin >> fin;
	if (fin == "23H")
	{
		ifin = 19;
	}
	else if (fin == "23G")
	{
		ifin = 18;
	}
	else if (fin == "23F")
	{
		ifin = 17;
	}
	else if (fin == "23E")
	{
		ifin = 16;
	}
	else if (fin == "23C")
	{
		ifin = 15;
	}
	else if (fin == "23B")
	{
		ifin = 14;
	}
	else if (fin == "23A")
	{
		ifin = 13;
	}
	else
	{
		ifin = stoi(fin);
	}
	// Run dijkstra to find distance from inputs
	// Input original strings so user can see output for map
	dijkstra(graph, ibegin, ifin, edges.size(), begin, fin);

	return 0;
}