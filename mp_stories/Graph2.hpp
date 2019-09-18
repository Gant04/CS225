#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>
#include<limits>
#include<iostream>

using std::unordered_map;
/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;

  unordered_map<std::string,double> distances;
  unordered_map<std::string,std::string> predecessor;

  for( auto it=vertexMap.begin();it!=vertexMap.end();it++){
    if(it->first==start){
      distances[it->first]=0;
    } else{
      distances[it->first]=std::numeric_limits<double>::max()-1;
    }
    //predecessor[it->first]="";
  }
  predecessor[start]="";

  for(size_t i=0;i<numVertices();i++){
      for(auto it=edgeList.begin();it!=edgeList.end();it++){
        const Edge & edge= (*it);
        if(distances[edge.dest().key()]>distances[edge.source().key()]+1){
          distances[edge.dest().key()]=distances[edge.source().key()]+1;
          predecessor[edge.dest().key()]=edge.source().key();
        }
        if(distances[edge.source().key()]>distances[edge.dest().key()]+1){
          distances[edge.source().key()]=distances[edge.dest().key()]+1;
          predecessor[edge.source().key()]=edge.dest().key();
        }
      }
  }

  std::string current=end;
  while(current!=""){

    path.push_front(current);
    //std::cout<<current<<end<<std::endl;
    current=predecessor[current];

  }
 // path.push_front(start);

  return path;
}
