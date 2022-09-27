#pragma once
#include <vector>
#include <cstdint>
#include <set>
#include <future>
#include "Operators.hpp"
#include "Relation.hpp"
#include "Parser.hpp"
//---------------------------------------------------------------------------
class Joiner {

  /// Add scan to query
  std::shared_ptr<Operator> addScan(std::set<unsigned>& usedRelations,SelectInfo& info,QueryInfo& query);
  // std::vector<std::future<void>> asyncResult;
  // std::atomic<int> queryIndex;
  public:
  // Joiner(int thread_num) {
  //   asyncResult.reserve(256);
  // }
  /// The relations that might be joined
  std::vector<Relation> relations;
  /// Add relation
  void addRelation(const char* fileName);
  /// Get relation
  Relation& getRelation(unsigned id);
  /// Joins a given set of relations
  std::string join(QueryInfo& i);
};
//---------------------------------------------------------------------------
