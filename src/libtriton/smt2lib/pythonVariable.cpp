#include "smt2libPythonVisitor.hpp"

using namespace triton;
using namespace smt2lib;


const std::string& PythonVariable::getName(void) const {
  return this->name;
}


uint32 PythonVariable::getId(void) const {
  return this->id;
}


uint32 PythonVariable::getSize(void) const {
  return this->size;
}

PythonVariable& PythonVariable::setName(const std::string& name) {
  this->name = name;
  return *this;
}


PythonVariable& PythonVariable::setId(uint32 id) {
  this->id = id;
  return *this;
}


PythonVariable& PythonVariable::setSize(uint32 size) {
  this->size = size;
  return *this;
}
