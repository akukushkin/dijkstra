#include <QCoreApplication>
#include <iostream>
#include <cgraph.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 2) {
        std::cout << "Run: ./dijkstra file.xgm" << std::endl;
        return a.exec();
    }

    CGraph graph(argv[1]);
    if (!graph.getCountVertex()) {
        std::cout << "File not found or file is an incorrect!" << std::endl;
        return a.exec();
    }

    vertex_t start, goal;
    ssize_t countVertex = graph.getCountVertex();
    do {
        std::cout << "Enter start vertex ";
        std::cout << "(1 - " << countVertex << ") : ";
        std::cin >> start;
    } while (start < 1 || start > countVertex);
    do {
        std::cout << "Enter goal vertex ";
        std::cout << "(1 - " << countVertex << ") : ";
        std::cin >> goal;
    } while (goal < 1 || goal > countVertex);
    std::cout << std::endl;
    --start;
    --goal;

    weight_t distance = graph.getMinDistance(start, goal);
    std::cout << "Information about path from " << start + 1 << " to " << goal + 1 << " :" << std::endl;
    if (distance > 0) {
        std::cout << "Distance : " << distance << std::endl;
        std::list<vertex_t> path = graph.getShortestPath(start, goal);
        std::cout << "Path : ";
        for (std::list<vertex_t>::const_iterator i = path.begin(); i != path.end(); ++i) {
            std::cout << *i + 1 << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Path doesn't exists." << std::endl;
    }

    return a.exec();
}
