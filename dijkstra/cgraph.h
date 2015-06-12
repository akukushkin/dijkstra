#ifndef CGRAPH_H
#define CGRAPH_H

#include <vector>
#include <list>
#include <set>
#include <cmath>
#include <QXmlStreamReader>
#include <QFile>
#include <typedef.h>

class CGraph {
private:
    // presentation in the form of a graph adjacency list
    adjacency_list_t adjacency_list;

    // find shortest path and distance from source vertex to every vertexes of graph
    void dijkstraComputePaths(vertex_t source,
                              std::vector<weight_t> &min_distance,
                              std::vector<vertex_t> &previous);
    // find shortest path from source vertex to goal vertex
    std::list<vertex_t> dijkstraGetShortestPathTo(vertex_t goal,
                                                  const std::vector<vertex_t> &previous);
    // parse edge-section in xgml-file
    void parseEdge(QXmlStreamReader& xgml, vertex_t &from, vertex_t &to, weight_t &weight);
public:
    // constructor with parameter, cntVertex - number of vertexes
    CGraph(size_t cntVertex);
    // constructor with parameter, inputFileName - filename with the graph
    CGraph(const std::string& inputFileName);
    // destructor
    ~CGraph();

    // add edge in the graph
    void addEdge(vertex_t from, vertex_t to, weight_t weight);
    // find shortest path from source to goal vertexes
    std::list<vertex_t> getShortestPath(vertex_t source, vertex_t goal);
    // find shortest distance from source to goal vertexes
    ssize_t getMinDistance(vertex_t source, vertex_t goal);
    // get number of graph's vertexes
    size_t getCountVertex() const;
};

#endif // CGRAPH_H
