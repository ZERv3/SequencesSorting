#pragma once

#include "../Hash/HashTable.h"

template <typename TKey, typename TValue>
class OGraph;

//Ребро
template <typename TKey>
class Edge {
private:
    TKey from; //Откуда
    TKey to; //Куда

public:
    //Базовый конструктор
    Edge(): from(TKey()), to(TKey()) {}
    
    Edge(TKey from, TKey to)
        : from(from), to(to) {}

    //Геттеры
    TKey GetFrom() const { return from; }
    TKey GetTo() const { return to; }
    
    friend std::ostream& operator<<(std::ostream& outStream, const Edge<TKey>& edge) {
        outStream << "(" << edge.GetFrom() << "->" << edge.GetTo() << ")";
        return outStream;
    }
};

//Вершина
template <typename TKey, typename TValue>
class Vertex {
    friend OGraph<TKey, TValue>;
private:
    TValue value; //Значение вершины
    LinkedList<Edge<TKey>> edges; //Набор ребер c индексами

public:
    Vertex() : value(TValue()) {}
    
    //Базовый конструктор
    explicit Vertex(const TValue& value) : value(value), edges(LinkedList<Edge<TKey>>()) {}

    //Геттер
    const TValue& GetValue() const { return value; }
    
    //Геттер ребер
    const LinkedList<Edge<TKey>>& GetEdges() const {
        return edges;
    }
    
    friend std::ostream& operator<<(std::ostream& outStream, const Vertex<TKey, TValue>& v) {
        outStream << "(";
        auto value = v.GetValue();
        outStream << "VALUE: [" << value << "]";
        auto edges = v.GetEdges();
        outStream << " | Edges: [" << edges << "]" << ")";

        return outStream;
    }
};

template <typename TKey, typename TValue>
class OGraph{
private:
    HashTable<TKey, Vertex<TKey, TValue>*> graph;
public:
    
    OGraph(): graph(HashTable<TKey, Vertex<TKey, TValue>*>(2)){}
    
    void AddVertex(TKey key, TValue value){
        this->graph.Add(key, new Vertex<TKey, TValue>(value));
    }
    
    void RemoveVertex(TKey key){
        this->graph.Remove(key);
    }
    
    Vertex<TKey, TValue>* GetVertex(TKey key){
        return this->graph.GetElement(key);
    }
    
    void Connect(TKey start, TKey end){
        auto startVertexPointer = this->GetVertex(start);
        startVertexPointer->edges.PushFront(Edge(start, end));
    }
    
    const HashTable<TKey, Vertex<TKey, TValue>*>& GetData() const {
        return this->graph;
    }
    
//    void Connect(TKey start, TKey end){
//        auto vertSource = this->graph.GetElement(start);
//        auto edge = Edge<TKey>(start, end);
//        vertSource.edges.PushFront(edge);
////        std::cout << vertSource << "\n";
//    }
    
    friend std::ostream& operator<<(std::ostream& outStream, const OGraph<TKey, TValue>& graph) {
        
        auto HT = graph.GetData();
        outStream << "GRAPH HT:" << std::endl;
        auto HTData = HT.GetData();
        for (int i = 0; i < HT.GetCapacity(); i++) {
            auto list = HTData[i];
            outStream << "\t";
            if (list.GetLength() != 0) {
                auto current = list.GetNode(0);
                while (current) {
                    
                    if (current->data) {
                        auto item = *(current->data);
                        
                        outStream << "[" << item.GetKey() << " , " << *(item.GetValue()) << "]";
                        
                        outStream << " | ";
                    }
                    else {
                        outStream << "nullptr | "; // Обработка null-указателей
                    }
                    
                    
                    current = current->next;
                }
            } else {
                outStream << "EMPTY";
            }
//            HTData[i]
            outStream << std::endl;
        }
//        outStream
        return outStream;
    }
};

