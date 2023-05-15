#include <iostream>
#include <vector>
#include "Webgraph.h"
using namespace std;

Webgraph::Webgraph()
{
	n = 0;
}

Webgraph::Webgraph(int size)
{
    n = size;
    graph.resize(size, std::vector<double>(size, 0));
    // Input values into the graph
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            graph[i][j] = 0;
        }
    }
}

void Webgraph::addEdge(int s, int d)
{
    if (s < 0 || d < 0)
        return;
    if (s > n || d > n)
        return;

    graph[s][d] = 1;

}

int Webgraph::getN()
{
    return n;
}

vector<vector<double>> Webgraph::getGraph()
{
    return graph;
}