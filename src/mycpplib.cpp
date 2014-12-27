#include <iostream>
#include <boost/python.hpp>

using namespace std;

void hello()
{
    cout << "Hello Python. I'm C++, looking forward to work with you!" << endl;
}



BOOST_PYTHON_MODULE(libmycpplib) // name has to match with the name in CMakeLists `add_library` + prefix 'lib'
{
   using namespace boost::python;
   def("hello", hello);
}
