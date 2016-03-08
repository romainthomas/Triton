#include "../init.hpp"

#include <z3++.h>
#include <ast.hpp>
void init_Memory_class(py::module& m) {
  //
  // Binary object
  //
  py::class_<triton::arch::MemoryOperand, std::shared_ptr<triton::arch::MemoryOperand>>(m, "MemoryOperand")
    //.def("evaluate",
    //.def("getBitvectorMask",
    //.def("getBitvectorSize",
    //.def("getChilds",
    //.def("getHash",
    //.def("getKind",
    //.def("getParent",
    //.def("getValue",
    //.def("isSigned",
    //.def("isSymbolized",
    //.def("setChild"
    .def("__add__", [](triton::ast::AbstractNode *a, triton::ast::AbstractNode *b) { return triton::ast::bvadd(a, b); });

  //py::implicitly_convertible<std::weak_ptr<LIEF::Section>, ELF::Section>();

}
