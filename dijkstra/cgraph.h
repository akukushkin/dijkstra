#ifndef CGRAPH_H
#define CGRAPH_H

#include <typedef.h>

class CGraph {
private:
    adjacency_list_t adjacency_list;

    void dijkstraComputePaths(vertex_t source,
                              std::vector<weight_t> &min_distance,
                              std::vector<vertex_t> &previous);
    std::list<vertex_t> dijkstraGetShortestPathTo(vertex_t vertex,
                                                  const std::vector<vertex_t> &previous);
    void parseEdge(QXmlStreamReader& xgml, vertex_t &from, vertex_t &to, weight_t &weight);
public:
    CGraph(size_t cntVertex);
    CGraph(const std::string& inputFileName);
    ~CGraph();

    void addEdge(vertex_t from, vertex_t to, weight_t weight);
    std::list<vertex_t> getShortestPath(vertex_t start, vertex_t goal);
    ssize_t getMinDistance(vertex_t start, vertex_t goal);
    size_t getCountVertex() const;
};

#endif // CGRAPH_H
