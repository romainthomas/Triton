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

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " + " <<  pyOp2.name() << ") & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;

      this->maskUsed.insert(pyResult.size());


    }


    void PythonVisitor::operator()(smtAstBvandNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::stringstream expression;
      expression << pyOp1.name() << " & " << pyOp2.name();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;

    }


    void PythonVisitor::operator()(smtAstBvashrNode& e) {

      throw std::runtime_error("smtAstBvashrNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvlshrNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::stringstream expression;
      expression << pyOp1.name() << " >> " <<  pyOp2.name();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvmulNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " * " <<  pyOp2.name() << ") & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;

      this->maskUsed.insert(pyResult.size());
    }


    void PythonVisitor::operator()(smtAstBvsmodNode& e) {

      throw std::runtime_error("smtAstBvsmodNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvnandNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));


      std::stringstream expression;
      expression << "(~ (" << pyOp1.name() << " & " <<  pyOp2.name() << ")) & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;

      this->maskUsed.insert(pyResult.size());
    }


    void PythonVisitor::operator()(smtAstBvnegNode& e) {
      auto op1 = e.getChilds()[0];
      auto pyOp1 = this->getPyVariable(op1);
      auto pyResult = this->addPyVariable(&e, pyOp1.size());

      std::stringstream expression;
      expression << "(-" << pyOp1.name()  << ") & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;

      this->maskUsed.insert(pyResult.size());

    }


    void PythonVisitor::operator()(smtAstBvnorNode& e) {

      throw std::runtime_error("smtAstBvnorNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvnotNode& e) {
      auto op1 = e.getChilds()[0];
      auto pyOp1 = this->getPyVariable(op1);
      auto pyResult = this->addPyVariable(&e, pyOp1.size());


      std::stringstream expression;
      expression << "(~" << pyOp1.name()  << ") & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
      this->maskUsed.insert(pyResult.size());

    }


    void PythonVisitor::operator()(smtAstBvorNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " | " <<  pyOp2.name() << ") & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
      this->maskUsed.insert(pyResult.size());
    }


    void PythonVisitor::operator()(smtAstBvrolNode& e) {

      throw std::runtime_error("smtAstBvrolNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvrorNode& e) {

      throw std::runtime_error("smtAstBvrorNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvsdivNode& e) {

      throw std::runtime_error("smtAstBvsdivNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvsgeNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " >= " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvsgtNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);


      std::stringstream expression;
      expression << "(" << pyOp1.name() << " > " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvshlNode& e) {


      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " << " <<  pyOp2.name()  << " ) & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
      this->maskUsed.insert(pyResult.size());
      this->maskUsed.insert(pyResult.size());
    }


    void PythonVisitor::operator()(smtAstBvsleNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);
      std::stringstream expression;
      expression << "(" << pyOp1.name() << " <= " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvsltNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " < " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvsremNode& e) {

      throw std::runtime_error("smtAstBvsremNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvsubNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " - " <<  pyOp2.name() << ") & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
      this->maskUsed.insert(pyResult.size());
      this->maskUsed.insert(pyResult.size());
    }


    void PythonVisitor::operator()(smtAstBvudivNode& e) {

      throw std::runtime_error("smtAstBvudivNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvugeNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " >= " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvugtNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " > " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvuleNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " <= " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvultNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);
      std::stringstream expression;
      expression << "(" << pyOp1.name() << " < " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstBvuremNode& e) {

      throw std::runtime_error("smtAstBvuremNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvxnorNode& e) {

      throw std::runtime_error("smtAstBvxnorNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvxorNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, std::max(pyOp2.size(), pyOp1.size()));

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " ^ " <<  pyOp2.name() << ") & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;

      this->maskUsed.insert(pyResult.size());
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

      std::stringstream expression;
      expression << "(";
      expression << "(" << currentVariable.name() << " << " << size - currentVariable.size() << ")";
      size -= currentVariable.size();

      //Child[0] is the LSB
      for (idx = 1; idx < childs.size(); idx++) {
          auto nextVar = this->getPyVariable(childs[idx]);
          if (size - nextVar.size() != 0) {
            expression << " | (" << nextVar.name() << " << " << size - nextVar.size() << ")";
          } else {
            expression << " | " << nextVar.name();
          }
          size -= nextVar.size();
      }
      expression << " ) & mask_" << pyResult.size();

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;

      this->maskUsed.insert(pyResult.size());
    }


    void PythonVisitor::operator()(smtAstDecimalNode& e) {
      throw std::runtime_error("smtAstDecimalNode not implemented");
    }


    void PythonVisitor::operator()(smtAstDeclareNode& e) {
      throw std::runtime_error("smtAstDeclareNode not implemented");
    }

    void PythonVisitor::operator()(smtAstDistinctNode& e) {
      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " != " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;

    }


    void PythonVisitor::operator()(smtAstEqualNode& e) {
      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression << "(" << pyOp1.name() << " == " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());

      result << pyResult.name() << " = " << expression.str() << std::endl;
    }


    void PythonVisitor::operator()(smtAstExtractNode& e) {

      auto op1 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[0]); // to
      auto op2 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[1]); // from
      auto op3 = e.getChilds()[2];

      auto pyOp1 = this->getPyVariable(op3);

      if (static_cast<uint32>(op1->getValue() - op2->getValue() + 1) != pyOp1.size()) {
        auto pyResult = this->addPyVariable(&e, static_cast<uint32>(op1->getValue() - op2->getValue() + 1));

        std::stringstream expression;

        if (op2->getValue() != 0) {
          expression << "(" << pyOp1.name() << " >> " << op2->getValue() << ") & mask_" << pyResult.size();
          pyResult.setExpression(expression.str());
          result << pyResult.name() << " = " << expression.str() << std::endl;

        } else {
          expression << pyOp1.name() << " & mask_" << pyResult.size();
          pyResult.setExpression(expression.str());
          result << pyResult.name() << " = " << expression.str() << std::endl;
        }

        this->maskUsed.insert(pyResult.size());
      } else {
        this->variables[&e] = pyOp1;
      }

    }



    void PythonVisitor::operator()(smtAstIteNode& e) {

      // declare variables:
      auto cond   = e.getChilds()[0];
      auto itrue  = e.getChilds()[1];
      auto ifalse = e.getChilds()[2];

      auto pyCond = this->getPyVariable(cond);
      auto pyTrue = this->getPyVariable(itrue);
      auto pyFalse = this->getPyVariable(ifalse);
      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression << pyTrue.name() << " if " << pyCond.name() << " else " << pyFalse.name();

      pyResult.setExpression(expression.str());
      result << pyResult.name() << " = " << expression.str() << std::endl;

    }


    void PythonVisitor::operator()(smtAstLandNode& e) {

      auto op1 = e.getChilds()[0];
      auto op2 = e.getChilds()[1];

      auto pyOp1 = this->getPyVariable(op1);
      auto pyOp2 = this->getPyVariable(op2);

      auto pyResult = this->addPyVariable(&e, 1);

      std::stringstream expression;
      expression <<  "(" << pyOp1.name() << " and " << pyOp2.name() << ")";

      pyResult.setExpression(expression.str());
      result << pyResult.name() << " = " << expression.str() << std::endl;

    }


    void PythonVisitor::operator()(smtAstLnotNode& e) {
      throw std::runtime_error("Lnot to implement");
    }


    void PythonVisitor::operator()(smtAstLorNode& e) {

      throw std::runtime_error("smtAstLorNode to implement");
    }


    void PythonVisitor::operator()(smtAstReferenceNode& e) {

      throw std::runtime_error("smtAstReferenceNode to implement");
    }


    void PythonVisitor::operator()(smtAstStringNode& e) {
      throw std::runtime_error("smtAstStringNode not implemented");
    }


    void PythonVisitor::operator()(smtAstSxNode& e) {

#if 1
      auto op1 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[0]); // size to extend
      auto op2 = e.getChilds()[1];
      auto pyOp2 = getPyVariable(op2);

      uint32 size = pyOp2.size() + static_cast<uint32>(op1->getValue());
      auto pyResult = addPyVariable(&e, size);

      std::stringstream expression;
      expression << "sign_extend(" << pyOp2.name() << ", " << size << ")";

      pyResult.setExpression(expression.str());
      result << pyResult.name() << " = " << expression.str() << std::endl;

#else
      auto op1 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[0]); // size to extend
      auto op2 = e.getChilds()[1];
      auto pyOp2 = getPyVariable(op2);
      pyOp2.setSize(pyOp2.size() + static_cast<uint32>(op1->getValue()));

      this->variables[op2] = pyOp2;
      this->variables[&e] = pyOp2;
#endif
    }


    void PythonVisitor::operator()(smtAstVariableNode& e) {

      PythonVariable pyResult;

      std::string varName = e.getValue();

      this->variablesUsed.insert(varName);
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

      //auto op1 = reinterpret_cast<smtAstDecimalNode*>(e.getChilds()[0]); // size to extend
      auto op2 = e.getChilds()[1];
      auto pyOp2 = getPyVariable(op2);
      //pyOp2.setSize(pyOp2.size() + static_cast<uint32>(op1->getValue()));

      this->variables[op2] = pyOp2;
      this->variables[&e] = pyOp2;


    }

  }; /* smt2lib namespace */
}; /* triton namespace */
