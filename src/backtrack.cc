/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"
#include <algorithm>

Backtrack::Backtrack() {
    std::cout << "backtrack" << "\n";
}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  std::cout << "t " << query.GetNumVertices() << "\n";
  int uArr[query.GetNumVertices()][1];
  for (int i = 0; i < query.GetNumVertices(); i++){
      uArr[i][0] = 0;
  }

  // implement your code here.
  FindPartialEmbedding(data, query, cs, uArr, 0, query.root);

}

void Backtrack::FindPartialEmbedding(const Graph &data, const Graph &query, const CandidateSet &cs,
                                     int uArr[][1], int embeddingSize, int u) {

    std::cout << "u is " << u << "\n";
    std::cout << "embeddingSize " << embeddingSize << "\n";

    for (int i = 0; i < cs.GetCandidateSize(u); i++){
        int vCandidate = cs.GetCandidate(u, i);
        std::cout << "v is " << vCandidate << "\n";

        for (int j = 0; j < query.numParent[u]; j++){
            // 이미 나온 것 제거 해야됨
            if (!data.IsNeighbor(uArr[query.parentQuery[u][j]][0], vCandidate)){
                printf("not correct\n");
                return;
            }
        }
        printf("match success\n");

        if (embeddingSize + 1 == query.GetNumVertices()){
            uArr[u][0] = vCandidate;
            std::cout << "a";
            for (int i = 0; i < query.GetNumVertices(); i++){
                std::cout << " " << uArr[i][0];
            }
            std::cout << std::endl;
            return;
        }

        for (int k = 0; k < query.numChild[u]; k++){
            int newUArr[query.GetNumVertices()][1];
            std::copy(&uArr[0][0], &uArr[0][0] + query.GetNumVertices() * 1, &newUArr[0][0]);
            newUArr[u][0] = vCandidate;
            FindPartialEmbedding(data, query, cs, newUArr, embeddingSize+1, query.childQuery[u][k]);
        }
    }
}