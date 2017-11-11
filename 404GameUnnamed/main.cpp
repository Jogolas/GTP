#include "Graph.h"
#include "Renderer.h"
#include <iostream>

using namespace std;

int main()
{
	CGraph testGraph = CGraph();
	char test;


	testGraph.addNode(); // node index 0
	testGraph.addNode(); // node index 1
	testGraph.addNode(); // node index 2
	testGraph.addEdge(0, 1, 4); //add edge index 0
	testGraph.addEdge(0, 2, 7); //add edge index 1
	
	testGraph.GetNode(0)->debug_position = glm::vec3(0, 1, -5);
	testGraph.GetNode(1)->debug_position = glm::vec3(1, 0, -5);
	testGraph.GetNode(2)->debug_position = glm::vec3(2, 1, -5);

	cout << testGraph.GetNode(0)->debug_position.x << endl;
	cout << testGraph.GetNode(1)->debug_position.x << endl;
	cout << testGraph.GetNode(2)->debug_position.x << endl;

	cin >> test;

	return 0;
}