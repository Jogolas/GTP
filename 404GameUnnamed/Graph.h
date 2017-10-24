#pragma once

#include <vector>
#include "glm.hpp"

typedef int node_t;
typedef int edge_t;

class CGraph
{
public:
	class CEdge
	{
	public:
		node_t first;
		node_t second;
		float weight;
	};

	class CNode
	{
	public:
		CNode()
		{
			seen = false;
			path_from = ~0;
			path_weight = FLT_MAX;
		}

		std::vector<edge_t> edges;
		bool seen;
		node_t path_from;
		float path_weight;

		glm::vec3 debug_position;
	};

	//inserts a node starting from index value 0
	void addNode();
	//connects an edge between node a, node b and gives a weight (use the index value of the node to connect the edge)
	void addEdge(node_t a, node_t b, float weight); 

	// finds the amount of nodes in the system
	int GetNumNodes();
	// finds the node at specific index
	CNode* GetNode(node_t i);

	// finds amount of edges in the system
	int GetNumEdges();
	// finds the edge at specific index
	CEdge* GetEdge(edge_t i);

	node_t FollowEdge(node_t node, edge_t edge);

protected:
	std::vector<CNode> nodes;
	std::vector<CEdge> edges;
};