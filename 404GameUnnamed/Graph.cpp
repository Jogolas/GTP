#include "graph.h"
#include <iostream>

void CGraph::addNode()
{
	CGraph::nodes.push_back(CNode());
}

void CGraph::addEdge(node_t a, node_t b, float weight)
{
	edges.push_back(CGraph::CEdge());
	edges.back().first = a;
	edges.back().second = b;
	edges.back().weight = weight;

	nodes[a].edges.push_back(edges.size() - 1);
	nodes[b].edges.push_back(edges.size() - 1);
}

int CGraph::GetNumNodes() //finds the amount of nodes currently in the game
{
	return nodes.size();
}

CGraph::CNode* CGraph::GetNode(node_t i)
{
	return &nodes[i];
}

int CGraph::GetNumEdges()
{
	return edges.size();
}

CGraph::CEdge* CGraph::GetEdge(edge_t i)
{
	return &edges[i];
}

////First parameter takes the index of the node and the second the index of the edge
////Index count starts at 0
node_t CGraph::FollowEdge(node_t node, edge_t edge)
{
	//return null if edge or node index does not exist.
	if(node == NULL || edge == NULL) {
		
		if (node == NULL) std::cout << "ERROR: Node index does not exist." << std::endl;
		if (edge == NULL) std::cout << "ERROR: Edge index does not exist." << std::endl;
		return NULL;
	}

	if (edges[edge].first == node)
		return edges[edge].second;
	else
		return edges[edge].first;
}