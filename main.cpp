#include "Interface/Interface.h"

#include "Graph/OrientedGraph.h"
#include "Graph/VisualGraph.h"

template <typename TKey, typename TValue>
void PrintGraph(const OGraph<TKey, TValue>& graph){
    auto data = graph.GetData();
    std::cout << data;
}

int main() {
    auto graph = OGraph<int, int>();
    
    graph.AddVertex(1, 120);
    graph.AddVertex(2, 130);
    graph.AddVertex(3, 130);
        
//    auto v = graph.GetVertex(1);
    graph.Connect(1, 2);
    graph.Connect(1, 3);
    graph.Connect(2, 1);
    
    graph.RemoveVertex(2);
    
    std::cout << graph;

    return 0;
}
