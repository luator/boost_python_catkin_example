Using Boost::Python with catkin
===============================

This is a minimal example of how to use Boost::Python in a catkin package.
As there is little helpful documentation about this topic on the internet, I try to summarize
all necessary steps here.

First you need some C++ code. `src/mycpplib.cpp` contains a simple hello world function that is
made available for Python using Boost::Python. (see documentation of Boost::Python for more
details on how to use it).

To compile it and make it available for python, some configuration in the CMakeLists.txt has to
be done:


Configure cmake
---------------

 1. You need Boost::Python and the path to the python include dirs:
        find_package(Boost REQUIRED COMPONENTS python)
        find_package(PythonLibs REQUIRED) # sets ${PYTHON_INCLUDE_DIRS}
    Make sure to add them to the include directories:
        include_directories(
          ${catkin_INCLUDE_DIRS}
          ${Boost_INCLUDE_DIRS}
          ${PYTHON_INCLUDE_DIRS}
        )
 2. uncomment `catkin_python_setup()`. This will set up the destination path of the python
    module. You also need a basic _setup.py_ in the packages root directory.
 3. add a library:
        add_library(mycpplib SHARED
          src/mycpplib.cpp
        )
        target_link_libraries(mycpplib
          ${catkin_LIBRARIES}
          ${Boost_LIBRARIES}
        )
        # change output directory, so python can find the module
        set_target_properties(mycpplib PROPERTIES
          LIBRARY_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_PYTHON_DESTINATION}
        )
    The last command is important because it will change the destination of the compiled library
    from `/catkin_ws/devel/lib/` to `/catkin_ws/devel/lib/python2.7/dist-packages/` so it can be
    found by python.
    Also don't forget the `SHARED` in `add_library`.


Use the module
--------------

After you compiled the package, you should be able to use the wrapped module in Python:

        import boostpy_test.libmycpplib as cpp
        cpp.hello()


References
----------

Some references that were helpful for me in one or the other way:

 * Boost::Python documentation: http://www.boost.org/doc/libs/1_57_0/libs/python/doc/index.html
 * Using Boost::Python with cmake: https://www.preney.ca/paul/archives/107
 * https://github.com/ethz-asl/Schweizer-Messer/wiki/Adding-boost::python-exports-to-your-ROS-package
 * http://wiki.ros.org/catkin/CMakeLists.txt, Section 7.2 (the `set_target_properties` command
   comes from there)
