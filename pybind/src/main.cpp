#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

float sum(py::array_t<float> arr) {
    py::buffer_info buf = arr.request();
    float ret = 0.;
    float *arr_ptr = static_cast<float *>(buf.ptr);
    for (size_t i = 0; i < buf.size; ++i) {
        ret += arr_ptr[i];
    }
    return ret;
} 

PYBIND11_MODULE(python_example, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------
        .. currentmodule:: python_example
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers
        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers
        Some other explanation about the subtract function.
    )pbdoc");

    m.def("sum", &sum, "taking the sum of an array");
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
