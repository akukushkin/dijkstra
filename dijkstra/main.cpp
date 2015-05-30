#include <QCoreApplication>
#include <iostream>
#include <cgraph.h>

#define INPUT_NAME_FILE "test2.xgml"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CGraph graph(INPUT_NAME_FILE);
    if (!graph.getCountVertex()) {
        std::cout << "File not found or file is an incorrect!" << std::endl;
        return a.exec();
    }

    vertex_t start, goal;
    std::cout << "Enter start vertex ";
    std::cout << "(1 - " << graph.getCountVertex() << ") :";
    std::cin >> start;
    std::cout << "Enter goal vertex ";
    std::cout << "(1 - " << graph.getCountVertex() << ") :";
    std::cin >> goal;
    std::cout << std::endl;

    weight_t distance = graph.getMinDistance(start, goal);
    std::cout << "Information about path from " << start << " to " << goal << " :" << std::endl;
    if (distance > 0) {
        std::cout << "Distance : " << distance << std::endl;
        std::list<vertex_t> path = graph.getShortestPath(start, goal);
        std::cout << "Path : ";
        std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
        std::cout << std::endl;
    } else {
        std::cout << "Path doesn't exists." << std::endl;
    }

    return a.exec();
}
