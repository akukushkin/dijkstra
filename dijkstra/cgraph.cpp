#include "cgraph.h"

void CGraph::dijkstraComputePaths(vertex_t source,
                                  std::vector<weight_t> &min_distance,
                                  std::vector<vertex_t> &previous)
{
    size_t n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, INFINITY);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));

    weight_t dist;
    vertex_t u;
    vertex_t v;
    weight_t weight;
    weight_t distance_through_u;
    while (!vertex_queue.empty()) {
        dist = vertex_queue.begin()->first;
        u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
        const std::vector<neighbor> &neighbors = adjacency_list[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            v = neighbor_iter->target;
            weight = neighbor_iter->weight;
            distance_through_u = dist + weight;

            if (distance_through_u < min_distance[v]) {
                vertex_queue.erase(std::make_pair(min_distance[v], v));

                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(std::make_pair(min_distance[v], v));
            }
        }
    }
}


std::list<vertex_t> CGraph::dijkstraGetShortestPathTo(vertex_t vertex,
                                                      const std::vector<vertex_t> &previous)
{
    std::list<vertex_t> path;
    while (vertex != -1) {
        path.push_front(vertex);
        vertex = previous[vertex];
    }
    return path;
}

void CGraph::parseEdge(QXmlStreamReader &xgml,
                      vertex_t &from,
                      vertex_t &to,
                      weight_t &weight)
{
    xgml.readNext();
    xgml.readNext();
    xgml.readNext();
    from = xgml.text().toUInt();
    xgml.readNext();
    xgml.readNext();
    xgml.readNext();
    xgml.readNext();
    to = xgml.text().toUInt();
    xgml.readNext();
    xgml.readNext();
    xgml.readNext();
    xgml.readNext();
    weight = xgml.text().toDouble();
}

CGraph::CGraph(size_t cntVertex) {
    adjacency_list.resize(cntVertex);
}

CGraph::CGraph(const std::string &inputFileName) {
    QFile* file = new QFile(inputFileName.c_str());

    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QXmlStreamReader xgml(file);
    QXmlStreamAttributes attributes;
    vertex_t from, to;
    weight_t weight;
    size_t numVertex = 0;

    while (!xgml.atEnd() && !xgml.hasError()) {
        QXmlStreamReader::TokenType token = xgml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement) {
            if (xgml.name() == "section") {
                attributes = xgml.attributes();
                if (attributes.hasAttribute("name")) {
                    if (attributes.value("name").toString() == "node") {
                        ++numVertex;
                        adjacency_list.resize(numVertex);
                    }
                    if (attributes.value("name").toString() == "edge") {
                        parseEdge(xgml, from, to, weight);
                        addEdge(from, to, weight);
                    }
                }
            }
        }
    }
}

CGraph::~CGraph() {}

void CGraph::addEdge(vertex_t from,
                     vertex_t to,
                     weight_t weight)
{
    adjacency_list[from].push_back(neighbor(to, weight));
}

std::list<vertex_t> CGraph::getShortestPath(vertex_t start,
                                            vertex_t goal)
{
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;

    dijkstraComputePaths(start, min_distance, previous);
    if (min_distance[goal] != INFINITY && min_distance[goal] >= 0)
        return dijkstraGetShortestPathTo(goal, previous);
    return std::list<vertex_t>();
}

ssize_t CGraph::getMinDistance(vertex_t start,
                           vertex_t goal)
{
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;

    dijkstraComputePaths(start, min_distance, previous);

    if (min_distance[goal] != INFINITY && min_distance[goal] >= 0)
        return min_distance[goal];
    return -1;
}

size_t CGraph::getCountVertex() const {
    return adjacency_list.size();
}
