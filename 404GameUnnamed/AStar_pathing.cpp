#include "AStar_pathing.h"
#include <algorithm>

bool smaller_weight(const node_t& l, const node_t& r)
{
	auto& graph = AStar().m_Graph;
	return graph.GetNode(l)->path_weight > graph.GetNode(r)->path_weight;
}

void AStar::reset()
{
	graphStep = GRAPHSTEP_BEGIN;
	m_aiUnvisitedNodes.clear();
	m_aiPathStack.clear();
	m_currentNode = -1;
}

void AStar::Step()
{
	if (graphStep == GRAPHSTEP_BEGIN) {
		m_currentNode = 0;
		m_Graph.GetNode(m_currentNode)->seen = true;
		m_Graph.GetNode(m_currentNode)->path_weight = 0;

		for (int i = 1; i < m_Graph.GetNumNodes(); i++)
			m_aiUnvisitedNodes.push_back(i);

		graphStep = GRAPHSTEP_CALCULATENEIGHBORS;
	}
	else if (graphStep == GRAPHSTEP_CALCULATENEIGHBORS) {
		CGraph::CNode* current_node = m_Graph.GetNode(m_currentNode);

		size_t i;
		for (i = 0; i < current_node->edges.size(); i++) {
			edge_t edge = current_node->edges[i];

			node_t test_node = m_Graph.FollowEdge(m_currentNode, edge);

			if (m_Graph.GetNode(test_node)->seen)
				continue;

			float g_weight = m_Graph.GetEdge(edge)->weight + current_node->path_weight;
			float h_weight = (m_Graph.GetNode(test_node)->debug_position - m_targetNode->debug_position).length();

			float f_weight = g_weight + h_weight;

			if (f_weight < m_Graph.GetNode(test_node)->path_weight) {
				m_Graph.GetNode(test_node)->path_weight = f_weight;
				m_Graph.GetNode(test_node)->path_from = m_currentNode;
			}
		}

		std::make_heap(m_aiUnvisitedNodes.begin(), m_aiUnvisitedNodes.end(), smaller_weight);

		graphStep = GRAPHSTEP_FINDLOWEST;
	}
	else if (graphStep == GRAPHSTEP_FINDLOWEST) {

		if (!m_aiUnvisitedNodes.size())
			return;

		std::pop_heap(m_aiUnvisitedNodes.begin(), m_aiUnvisitedNodes.end(), smaller_weight);

		node_t lowest_path_node = m_aiUnvisitedNodes.back();
		float lowest_path_weight = m_Graph.GetNode(lowest_path_node)->path_weight;

		m_aiUnvisitedNodes.pop_back();

		if (lowest_path_node < 0)
			return;

		m_currentNode = lowest_path_node;
		m_Graph.GetNode(m_currentNode)->seen = true;

		if (m_Graph.GetNode(lowest_path_node) == m_targetNode)
		{
			graphStep = GRAPHSTEP_RECONSTRUCT;
			return;
		}
		
		graphStep = GRAPHSTEP_CALCULATENEIGHBORS;
	}
	else if (graphStep = GRAPHSTEP_RECONSTRUCT) {
		node_t current_node = m_currentNode;
		m_aiPathStack.push_back(current_node);

		while (m_Graph.GetNode(current_node)->path_from != ~0) {
			current_node = m_Graph.GetNode(current_node)->path_from;
			m_aiPathStack.push_back(current_node);
		}
	}
}

void AStar::Complete()
{
	reset();

	node_t current_node_index = 0;
	m_Graph.GetNode(current_node_index)->seen = true;
	m_Graph.GetNode(current_node_index)->path_weight = 0;

	for (int i = 1; i < m_Graph.GetNumNodes(); i++)
		m_aiUnvisitedNodes.push_back(i);

	while (m_aiUnvisitedNodes.size()) {
		CGraph::CNode* current_node = m_Graph.GetNode(current_node_index);

		size_t i;
		for (i = 0; i < current_node->edges.size(); i++) {
			edge_t edge = current_node->edges[i];
			node_t test_node = m_Graph.FollowEdge(current_node_index, edge);

			if (m_Graph.GetNode(test_node)->seen)
				continue;

			float g_weight = m_Graph.GetEdge(edge)->weight + current_node->path_weight;
			float h_weight = (m_Graph.GetNode(test_node)->debug_position - m_targetNode->debug_position).length();

			float f_weight = g_weight + h_weight;

			if (f_weight < m_Graph.GetNode(test_node)->path_weight)
			{
				m_Graph.GetNode(test_node)->path_weight = f_weight;
				m_Graph.GetNode(test_node)->path_from = current_node_index;
			}
		}

		std::make_heap(m_aiUnvisitedNodes.begin(), m_aiUnvisitedNodes.end(), smaller_weight);

		std::pop_heap(m_aiUnvisitedNodes.begin(), m_aiUnvisitedNodes.end(), smaller_weight);

		node_t lowest_path_node = m_aiUnvisitedNodes.back();
		float lowest_path_weight = m_Graph.GetNode(lowest_path_node)->path_weight;

		m_aiUnvisitedNodes.pop_back();

		if (lowest_path_node < 0)
			return;

		current_node_index = lowest_path_node;
		m_Graph.GetNode(current_node_index)->seen = true;

		if (m_Graph.GetNode(lowest_path_node) == m_targetNode) {

			m_aiPathStack.push_back(current_node_index);

			while (m_Graph.GetNode(current_node_index)->path_from != ~0) {
				current_node_index = m_Graph.GetNode(current_node_index)->path_from;
				m_aiPathStack.push_back(current_node_index);
			}

			return;
		}
	}
}