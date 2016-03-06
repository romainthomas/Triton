#ifndef _PY_INIT_H_
#define _PY_INIT_H_

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>);

void init_Triton_Callbacks(py::module&);

#endif
