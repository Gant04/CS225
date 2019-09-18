/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>
#include <string>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
	maxFlow_=0;
	vector<Vertex> vertices= g_.getVertices();
	vector<Edge> edges= g_.getEdges();
	for(size_t i=0;i<vertices.size();i++){
		flow_.insertVertex(vertices[i]);
		residual_.insertVertex(vertices[i]);
	}
	for(size_t i=0;i<edges.size();i++){
		Vertex source=edges[i].source;
		Vertex dest=edges[i].dest;
		int weight=edges[i].getWeight();
		//Edge edge1(source,dest,0,std::to_string(weight));
		flow_.insertEdge(source,dest);
		flow_.setEdgeWeight(source,dest,0);
		flow_.setEdgeLabel(source,dest,std::to_string(weight));

		residual_.insertEdge(source,dest);
		residual_.setEdgeWeight(source,dest,weight);
		residual_.insertEdge(dest,source);
		residual_.setEdgeWeight(dest,source,0);

	}
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
	int sum=residual_.getEdgeWeight(path[0],path[1]);
	for(unsigned int i=0;i<path.size()-1;i++){
		int weight=residual_.getEdgeWeight(path[i],path[i+1]);
		if(weight<sum){
			sum=weight;
		}
	}
  return sum;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
	std::vector<Vertex> path;

	while(findAugmentingPath(source_,sink_,path)){
		int capacity=pathCapacity(path);
		Edge test;
		for(size_t i=0;i<path.size()-1;i++){
			//Edge edge=flow_.getEdge(path[i],path[i+1]);
			if(!flow_.edgeExists(path[i],path[i+1])){
				int weight=flow_.getEdgeWeight(path[i+1],path[i]);
				flow_.setEdgeWeight(path[i+1],path[i],weight-capacity);
			} else{
				int weight=flow_.getEdgeWeight(path[i],path[i+1]);
				flow_.setEdgeWeight(path[i],path[i+1],weight+capacity);
			}
			int weight=residual_.getEdgeWeight(path[i],path[i+1]);
			residual_.setEdgeWeight(path[i],path[i+1],weight-capacity);
			weight=residual_.getEdgeWeight(path[i+1],path[i]);
			residual_.setEdgeWeight(path[i+1],path[i],weight+capacity);

		}
	}
	vector<Edge> edges=flow_.getEdges();
	for(size_t i=0;i<edges.size();i++){
			if(edges[i].dest==sink_){
					maxFlow_+=edges[i].getWeight();
			}
	}


  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

