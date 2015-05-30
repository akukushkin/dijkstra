#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <vector>
#include <sys/types.h>
#include <string>
#include <list>
#include <set>
#include <cmath>
#include <QXmlStreamReader>
#include <QFile>

typedef ssize_t vertex_t;
typedef double weight_t;

struct neighbor {

    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

#endif // TYPEDEF_H
