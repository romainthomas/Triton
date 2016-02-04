#include "smt2libPythonVisitor.hpp"

using namespace triton;
using namespace smt2lib;


const std::string& PythonVariable::name(void) const {
  return this->vName;
}


uint32 PythonVariable::id(void) const {
  return this->vId;
}


uint32 PythonVariable::size(void) const {
  return this->vSize;
}

uint128 PythonVariable::value(void) const {
  return this->vValue;
}

PythonVariable& PythonVariable::setName(const std::string& name) {
  this->vName = name;
  return *this;
}


PythonVariable& PythonVariable::setId(uint32 id) {
  this->vId = id;
  return *this;
}


PythonVariable& PythonVariable::setSize(uint32 size) {
  this->vSize = size;
  return *this;
}

PythonVariable& PythonVariable::setValue(uint128 value) {
  this->vValue = value;
  return *this;
}
