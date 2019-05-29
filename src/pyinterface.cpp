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

py::class_<query::QueryResult> query_result(m, "QueryResult");

query_result.def(py::init<>());
query_result.def_readwrite("chapter", &query::QueryResult::chapter);
query_result.def_readwrite("id", &query::QueryResult::id);
query_result.def_readwrite("title", &query::QueryResult::title);
query_result.def_readwrite("summary", &query::QueryResult::summary);
query_result.def_readwrite("raw", &query::QueryResult::raw);


py::enum_<query::QueryResult::BlockType >(query_result, "BlockType")
.value("NATURE", query::QueryResult::BlockType::NATURE)
.value("CONCEPT", query::QueryResult::BlockType::CONCEPT)
.value("EXERCISES", query::QueryResult::BlockType::EXERCISES)
.value("TEXT", query::QueryResult::BlockType::TEXT)
.value("EXAMPLE", query::QueryResult::BlockType::EXAMPLE)
.export_values();

m.def("SegmentWords", &SegmentWords, "");
m.def("QueryCommPy", &QueryComm, "");

}