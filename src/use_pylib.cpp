/**
 * \file
 * \brief Simple example on how to call a Python function from C++ code.
 *
 * Useful resources:
 *  - Actually the boost python documentation starts to get a bit better:
 *    http://www.boost.org/doc/libs/1_61_0/libs/python/doc/html/tutorial/tutorial/embedding.html
 *  - A bit outdated but contains a function to extract traceback from
 *    exceptions: https://wiki.python.org/moin/boost.python/EmbeddingPython
 */
#include <iostream>
#include <string>
#include <boost/python.hpp>

using namespace boost::python;

int main( int argc, char ** argv ) {
    // It is important to initialize the Python interpreter before running any
    // Python code.
    Py_Initialize();

    try
    {
        // based on the example from
        // http://www.boost.org/doc/libs/1_46_0/libs/python/doc/v2/exec.html

        // Retrieve the main module.
        object main = import("__main__");

        // Retrieve the main module's namespace
        object global(main.attr("__dict__"));

        // Import my module
        object mypylib = import("boost_python_catkin_example.mypylib");

        // Create a reference to the hello function in the module.
        object hello = mypylib.attr("hello");
        object SomeClass = mypylib.attr("SomeClass");

        // Call it.
        std::string message = extract<std::string>(hello());
        std::cout << message << std::endl;

        object some_class_obj = SomeClass();
        some_class_obj.attr("set_value")(42);
        int value = extract<int>(some_class_obj.attr("get_value")());
        std::cout << "Value: " << value << std::endl;
    }
    catch (const error_already_set &)
    {
        // When the Python code raises an error, this will result in a
        // boost::python::error_already_set exception in C++.  Unfortunately
        // this exception does not contain any information about the nature of
        // the error, so we need to interface with the Python C API to get more
        // information.
        PyErr_Print();

        // To handle based on exception type:
        //if (PyErr_ExceptionMatches(PyExc_ZeroDivisionError))
        //{
        //    // handle ZeroDivisionError specially
        //}

        return 1;
    }
    return 0;
}
