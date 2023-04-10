#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>
#include "dict.h"
#include <iostream>

using TypedData = Data<int, std::string>;

namespace py = pybind11;

namespace pybind11
{
    namespace detail
    {

        template <>
        struct type_caster<TypedData>
        {
        public:
            PYBIND11_TYPE_CASTER(TypedData, const_name("TypedData"));

            // Conversion part 1 (C++ -> Python): convert a C++ type into a PyObject
            static handle cast(const TypedData &d, return_value_policy, handle)
            {
                std::cerr << "cast" << std::endl;
                switch (d.index())
                {
                case 0:
                    return py::cast(d.get<int>()).inc_ref();
                case 1:
                    return py::cast(d.get<std::string>()).inc_ref();
                }

                throw std::runtime_error("Unreachable");
            }

            // Conversion part 2 (Python->C++): convert a PyObject into a C++ type
            bool load(handle src, bool)
            {
                if (isinstance<py::int_>(src))
                {
                    std::cerr << "int" << std::endl;
                    value = TypedData(py::cast<int>(src));
                }
                else if (isinstance<py::str>(src))
                {
                    std::cerr << "str" << std::endl;
                    value = TypedData(py::cast<std::string>(src));
                }
                else
                    return false;
                return true;
            }
        };

    } // namespace detail
} // namespace pybind11

// 定义模块并导出Data类
PYBIND11_MODULE(example, m)
{
    // py::class_<TypedData>(m, "TypedData")
    //     // .def(py::init<std::variant<int, std::string>>());
    //     .def(py::init<int>());

    m.def("py2cpp", [](TypedData &d) {
        std::cerr << "test" << std::endl;
        switch (d.index())
        {
        case 0:
            std::cerr << d.get<int>() << std::endl;
            break;
        case 1:
            std::cerr << d.get<std::string>() << std::endl;
            break;
        }
    });
    m.def("cpp2py", []() {
        return TypedData(1);
    });
}
