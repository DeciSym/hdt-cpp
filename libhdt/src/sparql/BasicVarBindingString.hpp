#ifndef BASICVARBINDINGSTRING_HPP_
#define BASICVARBINDINGSTRING_HPP_

#include <HDT.hpp>

namespace hdt {

class BasicVarBindingString : public VarBindingString {
private:
  map<string, TripleComponentRole> varRole;
  VarBindingID *varID;
  Dictionary *dict;

  size_t getVarIndex(const char *varName);

public:
  BasicVarBindingString(map<string, TripleComponentRole> &varRole,
                        VarBindingID *varID, Dictionary *dict);

  virtual ~BasicVarBindingString();

  virtual bool findNext();

  virtual size_t getNumVars();

  virtual string getVar(size_t numvar);

  virtual const char *getVarName(size_t numvar);

  virtual void goToStart();

  virtual size_t estimatedNumResults();
};

} // namespace hdt

#endif // BASICVARBINDINGSTRING_HPP_
