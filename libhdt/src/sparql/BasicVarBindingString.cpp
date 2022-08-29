#include "BasicVarBindingString.hpp"

namespace hdt {

size_t BasicVarBindingString::getVarIndex(const char *varName) {
  for (size_t i = 0; i < getNumVars(); i++) {
    if (strcmp(getVarName(i), varName) == 0) {
      return i;
    }
  }
  cerr << "Var name: " << varName << " not found" << endl;
  throw std::runtime_error("Var name does not exist");
}

BasicVarBindingString::BasicVarBindingString(
    map<string, TripleComponentRole> &varRole, VarBindingID *varID,
    Dictionary *dict)
    : varRole(varRole), varID(varID), dict(dict){};

BasicVarBindingString::~BasicVarBindingString() { delete varID; }

bool BasicVarBindingString::findNext() { return varID->findNext(); }

size_t BasicVarBindingString::getNumVars() { return varID->getNumVars(); }

string BasicVarBindingString::getVar(size_t numvar) {
  size_t id = varID->getVarValue(numvar);

  return dict->idToString(id, varRole.find(getVarName(numvar))->second);
}

const char *BasicVarBindingString::getVarName(size_t numvar) {
  return varID->getVarName(numvar);
}

void BasicVarBindingString::goToStart() { return varID->goToStart(); }

size_t BasicVarBindingString::estimatedNumResults() {
  return varID->estimatedNumResults();
}

} // namespace hdt
