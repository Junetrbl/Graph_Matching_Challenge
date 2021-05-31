/**
 * @file main.cc
 *
 */

#include "backtrack.h"
#include "candidate_set.h"
#include "common.h"
#include "graph.h"

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cerr << "Usage: ./program <data graph file> <query graph file> "
                 "<candidate set file>\n";
    return EXIT_FAILURE;
  }

  std::string data_file_name = argv[1];
  std::string query_file_name = argv[2];
  std::string candidate_set_file_name = argv[3];

//  std::cout << data_file_name << " " << query_file_name << " " << candidate_set_file_name << "\n";
//
//  data_file_name = "../data/lcc_hprd.igraph";
//  query_file_name = "../query/lcc_hprd_n1.igraph";
//  candidate_set_file_name = "../candidate_set/lcc_hprd_n1.cs";
//
//  std::cout << data_file_name << " " << query_file_name << " " << candidate_set_file_name << "\n";

  Graph data(data_file_name);
  Graph query(query_file_name, true);
  query.buildDAG(data);

//  CandidateSet candidate_set(candidate_set_file_name);
//
//  Backtrack backtrack;
//
//  backtrack.PrintAllMatches(data, query, candidate_set);

  return EXIT_SUCCESS;
}
