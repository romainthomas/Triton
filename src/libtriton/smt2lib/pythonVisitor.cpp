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



namespace triton {
  namespace smt2lib {

    PythonVisitor::PythonVisitor(std::ostream& stream) :
      result(stream)
    {
    }


    PythonVisitor::~PythonVisitor() {
    }


    void PythonVisitor::eval(smtAstAbstractNode& e) {
      result << "# Python Eval" << std::endl;
      e.accept(*this);
    }


    void PythonVisitor::operator()(smtAstAbstractNode& e) {
      e.accept(*this);
    }


    void PythonVisitor::operator()(smtAstAssertNode& e) {
      throw std::runtime_error("smtAstAssertNode not implemented");
    }


    void PythonVisitor::operator()(smtAstBvaddNode& e) {
      //auto op1 = e.getChilds()[0];
      //auto op2 = e.getChilds()[1];

    }


    void PythonVisitor::operator()(smtAstBvandNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvashrNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvlshrNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvmulNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvsmodNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvnandNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvnegNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvnorNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvnotNode& e) {
    }


    void PythonVisitor::operator()(smtAstBvorNode& e) {
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
      //this->eval(*op1);
      //this->eval(*op2);
      result << "a" << " - " <<  "b" << " & mask_" << std::endl;
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
    }


    void PythonVisitor::operator()(smtAstBvNode& e) {
    }


    void PythonVisitor::operator()(smtAstCompoundNode& e) {
      throw std::runtime_error("smtAstCompoundNode not implemented");
    }


    void PythonVisitor::operator()(smtAstConcatNode& e) {
    }


    void PythonVisitor::operator()(smtAstDecimalNode& e) {
    }


    void PythonVisitor::operator()(smtAstDeclareNode& e) {
      throw std::runtime_error("smtAstDeclareNode not implemented");
    }


    void PythonVisitor::operator()(smtAstDistinctNode& e) {
    }


    void PythonVisitor::operator()(smtAstEqualNode& e) {
    }


    void PythonVisitor::operator()(smtAstExtractNode& e) {
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
    }


    void PythonVisitor::operator()(smtAstVariableNode& e) {
    }


    void PythonVisitor::operator()(smtAstZxNode& e) {
    }

  }; /* smt2lib namespace */
}; /* triton namespace */
