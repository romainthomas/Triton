//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#include <stdexcept>
#include <api.hpp>
#include <cpuSize.hpp>
#include <smt2libPythonVisitor.hpp>
#include <symbolicExpression.hpp>
#include <symbolicVariable.hpp>

#include <algorithm>


namespace triton {
  namespace smt2lib {

    PythonVisitor::PythonVisitor(std::ostream& stream) :
      result(stream),
      currentId(0)
    {
      this->result << "# Python Eval" << std::endl;
    }


    PythonVisitor::~PythonVisitor() {
    }


    PythonVariable& PythonVisitor::getPyVariable(triton::smt2lib::smtAstAbstractNode* node) {
      if (this->variables.find(node) != std::end(this->variables)) {
        return this->variables[node];
      } else {
        this->eval(*node);
        return this->variables[node];
      }

    }


    PythonVariable& PythonVisitor::addPyVariable(triton::smt2lib::smtAstAbstractNode* node, uint32 size) {
      uint32 id = this->currentId++;
      std::string name = "x_" + std::to_string(id);;

      PythonVariable pyResult;
      pyResult
        .setId(id)
        .setSize(size)
        .setName(name);
      this->variables[node] = pyResult;
      return this->variables[node];
    }


    void PythonVisitor::eval(smtAstAbstractNode& e) {
      e.accept(*this);
    }


    void PythonVisitor::operator()(smtAstAbstractNode& e) {
      e.accept(*this);
    }


    void PythonVisitor::operator()(smtAstAssertNode& e) {
      throw std::runtime_error("smtAstAssertNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvaddNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::string op1_str, op2_str;

      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();
      op2_str = (op2->getKind() == BV_NODE or op2->getKind() == ZX_NODE or op2->getKind() == SX_NODE) ? std::string{pyOp2.value()} : pyOp2.name();

      result << pyResult.name() << " = (" << op1_str << " + " <<  op2_str << ") & mask_" << pyResult.size() << std::endl;


    }


    void PythonVisitor::operator()(smtAstBvandNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::string op1_str, op2_str;
      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();
      op2_str = (op2->getKind() == BV_NODE or op2->getKind() == ZX_NODE or op2->getKind() == SX_NODE) ? std::string{pyOp2.value()} : pyOp2.name();
      result << pyResult.name() << " = " << op1_str << " & " <<  op2_str  << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvashrNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvlshrNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvmulNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::string op1_str, op2_str;
      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();
      op2_str = (op2->getKind() == BV_NODE or op2->getKind() == ZX_NODE or op2->getKind() == SX_NODE) ? std::string{pyOp2.value()} : pyOp2.name();

      result << pyResult.name() << " = (" << op1_str << " * " <<  op2_str << ") & mask_" << pyResult.size() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvsmodNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvnandNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::string op1_str, op2_str;
      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();
      op2_str = (op2->getKind() == BV_NODE or op2->getKind() == ZX_NODE or op2->getKind() == SX_NODE) ? std::string{pyOp2.value()} : pyOp2.name();

      result << pyResult.name() << " = ~ (" << op1_str << " & " <<  op2_str << ") & mask_" << pyResult.size() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvnegNode& e) {
      auto op1 = e.getChilds()[0];
      auto pyOp1 = this->getPyVariable(op1);
      auto pyResult = this->addPyVariable(&e, pyOp1.size());

      std::string op1_str;
      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();


      result << pyResult.name() << " = (-" << op1_str  << ") & mask_" << pyResult.size() << std::endl;

    }


    void PythonVisitor::operator()(smtAstBvnorNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvnotNode& e) {
      auto op1 = e.getChilds()[0];
      auto pyOp1 = this->getPyVariable(op1);
      auto pyResult = this->addPyVariable(&e, pyOp1.size());

      std::string op1_str;
      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();


      result << pyResult.name() << " = (~" << op1_str  << ") & mask_" << pyResult.size() << std::endl;


    }


    void PythonVisitor::operator()(smtAstBvorNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::string op1_str, op2_str;
      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();
      op2_str = (op2->getKind() == BV_NODE or op2->getKind() == ZX_NODE or op2->getKind() == SX_NODE) ? std::string{pyOp2.value()} : pyOp2.name();

      result << pyResult.name() << " = (" << op1_str << " | " <<  op2_str << ") & mask_" << pyResult.size() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvrolNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvrorNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvsdivNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvsgeNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvsgtNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvshlNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvsleNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvsltNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvsremNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvsubNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::string op1_str, op2_str;
      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();
      op2_str = (op2->getKind() == BV_NODE or op2->getKind() == ZX_NODE or op2->getKind() == SX_NODE) ? std::string{pyOp2.value()} : pyOp2.name();

      result << pyResult.name() << " = " << op1_str << " - " <<  op2_str << " & mask_" << pyResult.size() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvudivNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvugeNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvugtNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvuleNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvultNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvuremNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvxnorNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvxorNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::string op1_str, op2_str;
      op1_str = (op1->getKind() == BV_NODE or op1->getKind() == ZX_NODE or op1->getKind() == SX_NODE) ? std::string{pyOp1.value()} : pyOp1.name();
      op2_str = (op2->getKind() == BV_NODE or op2->getKind() == ZX_NODE or op2->getKind() == SX_NODE) ? std::string{pyOp2.value()} : pyOp2.name();

      result << pyResult.name() << " = (" << op1_str << " ^ " <<  op2_str << ") & mask_" << pyResult.size() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvNode& e) {
      PythonVariable pyOp1;
      PythonVariable pyOp2;

      PythonVariable pyResult;

      smtAstDecimalNode* op1 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[0]); //value
      smtAstDecimalNode* op2 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[1]); //size

      pyResult
        .setSize(static_cast<uint32>(op2->getValue()))
        .setValue(op1->getValue());
      this->variables[&e] = pyResult;
    }


    void PythonVisitor::operator()(smtAstCompoundNode& e) {
      throw std::runtime_error("smtAstCompoundNode not implemented");
    }


    void PythonVisitor::operator()(smtAstConcatNode& e) {
      std::vector<smtAstAbstractNode*> childs = e.getChilds();

      triton::uint32 idx;
      uint32 size = 0;
      // First declare variables needed;
      for (auto child : childs) {
        auto pyResult = this->getPyVariable(child);
        size += pyResult.size();
      }

      auto pyResult = this->addPyVariable(&e, size);

      auto currentVariable = this->getPyVariable(childs[0]);
      result << pyResult.name() << " = ";
      result << "(" << currentVariable.name() << " << " << size - currentVariable.size() << ")";
      size -= currentVariable.size();

      //Child[0] is the LSB
      for (idx = 1; idx < childs.size(); idx++) {
          auto nextVar = this->getPyVariable(childs[idx]);
          if (size - nextVar.size() != 0) {
            result << " | (" << nextVar.name() << " << " << size - nextVar.size() << ")";
          } else {
            result << " | " << nextVar.name();
          }
          size -= nextVar.size();
      }
      result << std::endl;
      //auto pyResult = this->addPyVariable(&e, size);

    }


    void PythonVisitor::operator()(smtAstDecimalNode& e) {
      throw std::runtime_error("smtAstDecimalNode not implemented");
    }


    void PythonVisitor::operator()(smtAstDeclareNode& e) {
      throw std::runtime_error("smtAstDeclareNode not implemented");
    }

    void PythonVisitor::operator()(smtAstDistinctNode& e) {
    }


    void PythonVisitor::operator()(smtAstEqualNode& e) {
    }


    void PythonVisitor::operator()(smtAstExtractNode& e) {
      PythonVariable pyOp1;
      PythonVariable pyResult;

      auto op1 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[0]); // to
      auto op2 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[1]); // from
      auto op3 = e.getChilds()[2];

      if (this->variables.find(op3) != std::end(this->variables)) {
        pyOp1 = this->variables[op3];
      } else {
        this->eval(*op3);
        pyOp1 = this->variables[op3];
      }

    if (static_cast<uint32>(op1->getValue() - op2->getValue() + 1) != pyOp1.size()) {
      uint32 id = this->currentId++;
      std::string name = "x_" + std::to_string(id);;

      pyResult
        .setId(id)
        .setSize(static_cast<uint32>(op1->getValue() - op2->getValue() + 1))
        .setName(name);


        this->variables[&e] = pyResult;

        std::string op1_str = op3->getKind() == BV_NODE ? std::string{pyOp1.value()} : pyOp1.name();
        if (op2->getValue() != 0) {
          result << pyResult.name() << " = (" << op1_str << " >> " << op2->getValue() << ") & mask_" << pyResult.size() << std::endl;
        } else {
          result << pyResult.name() << " = " << op1_str << " & mask_" << pyResult.size() << std::endl;
        }
      } else {
        this->variables[&e] = pyOp1;
      }

    }


    void PythonVisitor::operator()(smtAstIteNode& e) {
    }


    void PythonVisitor::operator()(smtAstLandNode& e) {
    }


    void PythonVisitor::operator()(smtAstLnotNode& e) {
    }


    void PythonVisitor::operator()(smtAstLorNode& e) {
    }


    void PythonVisitor::operator()(smtAstReferenceNode& e) {
    }


    void PythonVisitor::operator()(smtAstStringNode& e) {
      throw std::runtime_error("smtAstStringNode not implemented");
    }


    void PythonVisitor::operator()(smtAstSxNode& e) {
      auto op1 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[0]); // size to extend
      auto op2 = e.getChilds()[1];
      auto pyOp2 = getPyVariable(op2);
      pyOp2.setSize(pyOp2.size() + static_cast<uint32>(op1->getValue()));
      this->variables[op2] = pyOp2;
      this->variables[&e]  = pyOp2;
    }


    void PythonVisitor::operator()(smtAstVariableNode& e) {

      PythonVariable pyResult;

      std::string varName = e.getValue();
      pyResult.setName(varName);
      triton::engines::symbolic::SymbolicVariable* symVar = triton::api.getSymbolicVariableFromName(varName);

      if (symVar == nullptr)
        throw std::runtime_error("smtAstVariableNode: can't get the symbolic variable (nullptr)");

      if (symVar->getSymVarSize() > QWORD_SIZE_BIT)
        throw std::runtime_error("smtAstVariableNode: size above 64 bits is not supported yet");

      if (symVar->getSymVarKind() == triton::engines::symbolic::MEM) {
        triton::uint32 memSize   = symVar->getSymVarSize();
        pyResult.setSize(memSize);
      }
      else if (symVar->getSymVarKind() == triton::engines::symbolic::REG) {
        pyResult.setSize(symVar->getSymVarSize());
      }
      else {
        throw std::runtime_error("smtAstVariableNode: UNSET");
      }


      this->variables[&e] = pyResult;
    }


    void PythonVisitor::operator()(smtAstZxNode& e) {

      auto op1 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[0]); // size to extend
      auto op2 = e.getChilds()[1];
      auto pyOp2 = getPyVariable(op2);
      pyOp2.setSize(pyOp2.size() + static_cast<uint32>(op1->getValue()));
      this->variables[op2] = pyOp2;
      this->variables[&e] = pyOp2;


    }

  }; /* smt2lib namespace */
}; /* triton namespace */
