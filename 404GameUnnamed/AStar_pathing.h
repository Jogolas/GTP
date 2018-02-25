#pragma once
#include "AbstractAI.h"
#include "Graph.h"

class AStar
{
public:
	AStar() {}
	void reset();
	void Step();
	void Complete();

public:
	AbstractAI* AI;

	typedef enum
	{
		GRAPHSTEP_BEGIN,
		GRAPHSTEP_FINDLOWEST,
		GRAPHSTEP_CALCULATENEIGHBORS,
		GRAPHSTEP_RECONSTRUCT,
	} graph_step_t;

	graph_step_t graphStep;

	node_t m_currentNode;

	CGraph m_Graph;
	CGraph::CNode* m_targetNode;

	std::vector<node_t> m_aiUnvisitedNodes;
	std::vector<node_t> m_aiPathStack;

};