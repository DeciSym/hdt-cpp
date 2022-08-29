#ifndef QUERYPROCESSOR_HPP_
#define QUERYPROCESSOR_HPP_

#include "joins.hpp"
#include <HDT.hpp>
#include <stdexcept>

namespace hdt {

class QueryProcessor {
  HDT *hdt;

public:
  QueryProcessor(HDT *hdt);
  virtual ~QueryProcessor();

  VarBindingString *searchJoin(vector<TripleString> &patterns,
                               set<string> &vars);
};

} // namespace hdt

#endif // QUERYPROCESSOR_HPP_
