#include "pybind11/functional.h"
#include "pybind11/pybind11.h"

#include "functions/AnalyticFunction.h"

using namespace mrcpp;
namespace py = pybind11;
using namespace pybind11::literals;

namespace vampyr {

void analytic_function(py::module &m, auto &repfunc) {
    const auto D = 3;


py::class_<AnalyticFunction<D>>(m, "AnalyticFunction", repfunc)
        .def(py::init<std::function<double(const Coord<D>&r)>, double *, double *>(), "r"_a = Coord<D>{}, "a"_a = nullptr, "b"_a = nullptr)
        .def("evalf", py::overload_cast<const Coord<D> &>(&AnalyticFunction<D>::evalf, py::const_), 
         "This function does not work properly since the input are raw pointers, for this function to work properly add input arrays in MRCPP");
}
} // namespace vampyr