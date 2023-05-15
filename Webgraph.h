#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Webgraph
{
private:
	vector<vector<double>> graph;
	int n; // number of webpages

public:
	Webgraph();
	Webgraph(int size);
	void addEdge(int s, int d);
	int getN();
	vector<vector<double>> getGraph();


};