//
// Created by 박윤수 on 2021/05/28.
//

#ifndef SUBGRAPH_MATCHING_DAG_H
#define SUBGRAPH_MATCHING_DAG_H


#include "graph.h"

class Dag{
public:
    explicit Dag(Graph q, Graph G);
    ~Dag();

private:
    int root;
    static Graph q;
    Graph G = static_cast<Graph>(NULL);
    int findRoot();

    void buildDAG(Graph q, Graph G);
    static bool sortByDegreeQuery(int aNode1, int aNode2) {
        return q.GetDegree(aNode1) > q.GetDegree(aNode2);
    };
    static bool sortByLabelFreqQuery(int aNode1, int aNode2){
        return q.GetLabelFrequency(aNode1) < q.GetLabelFrequency(aNode2);
    };

    int** childQuery = NULL;
    int** parentQuery = NULL;
    int* numChild = NULL;
    int* numParent = NULL;
};

#endif //SUBGRAPH_MATCHING_DAG_H
