//! \file

#include "init.hpp"

PYBIND11_PLUGIN(triton) {

  py::module Triton_module("triton", "Python API for libtriton");

  // Init the LIEF module
  init_Triton_Callbacks(Triton_module);

  return Triton_module.ptr();
}
