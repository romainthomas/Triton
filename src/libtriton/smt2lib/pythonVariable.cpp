#include "smt2libPythonVisitor.hpp"

using namespace triton;
using namespace smt2lib;


PythonVariable::PythonVariable(void) :
  vName{""},
  vId{0},
  vSize{0},
  vValue{0},
  visValue{false}
{}

std::string PythonVariable::name(void) const {
  if (this->isValue()) {
    return std::string{this->vValue};
  } else {
    return this->vName;
  }
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

bool PythonVariable::isValue(void) const {
  return this->visValue;
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
  this->visValue = true;
  return *this;
}


PythonVariable& PythonVariable::setIsValue(bool flag) {
  this->visValue = flag;
  return *this;
}
