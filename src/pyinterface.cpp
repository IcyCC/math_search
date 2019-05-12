//
// Created by 苏畅 on 2019/5/12.
//
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include "interface.h"
namespace py = pybind11;

PYBIND11_MODULE(pyinterface, m) {
m.doc() = "pybind11 example plugin"; // optional module docstring

m.def("SegmentWords", &SegmentWords, "");
m.def("QueryComm", &QueryComm, "");
m.enum_<QueryType>("QueryType")
.value("CONCEPT", )
}