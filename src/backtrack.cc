/**
 * @file backtrack.cc
 *
 */

#include "backtrack.h"

Backtrack::Backtrack() {
    std::cout << "backtrack" << "";
}
Backtrack::~Backtrack() {}

void Backtrack::PrintAllMatches(const Graph &data, const Graph &query,
                                const CandidateSet &cs) {
  std::cout << "t " << query.GetNumVertices() << "\n";

  // implement your code here.
}
