Using Boost::Python with cmake
==============================

The official boost documentation uses boosts own build tool `bjam`. To integrate it into a catkin build, I have to use
cmake, though.
This page looks like a very nice and detailed tutorial: https://www.preney.ca/paul/archives/107

Maybe even better:
https://github.com/ethz-asl/Schweizer-Messer/wiki/Adding-boost::python-exports-to-your-ROS-package

Form http://wiki.ros.org/catkin/CMakeLists.txt:
7.2 Custom output directory
While the default output directory for executables and libraries is usual set to a reasonable
value it must be customized in certain cases. I.e. a library containing Python bindings must be
placed in a different folder to be importable in Python:

    set_target_properties(python_module_library PROPERTIES
      LIBRARY_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_PYTHON_DESTINATION}
    )
