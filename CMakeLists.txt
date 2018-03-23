cmake_minimum_required(VERSION 2.8.3)
project(boost_python_catkin_example)

find_package(catkin REQUIRED)

find_package(Boost REQUIRED COMPONENTS python)
find_package(PythonLibs 2.7 REQUIRED) # sets ${PYTHON_INCLUDE_DIRS}


catkin_python_setup() # this sets up the path /devel/lib/python2.7/dist-packages/boostpy_test

catkin_package()

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PYTHON_INCLUDE_DIRS}
)

add_library(mycpplib SHARED
  src/mycpplib.cpp
)
# change output directory, so python can find the module, and set prefix to ""
# to omit the default "lib".
set_target_properties(mycpplib PROPERTIES
  PREFIX ""
  LIBRARY_OUTPUT_DIRECTORY ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_PYTHON_DESTINATION}
)

target_link_libraries(mycpplib
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)


add_executable(use_pylib
  src/use_pylib.cpp
)

target_link_libraries(use_pylib
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${PYTHON_LIBRARIES}
)


#############
## Install ##
#############

install(TARGETS mycpplib
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_PYTHON_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_PYTHON_DESTINATION}
)

catkin_install_python(PROGRAMS scripts/use_cpplib.py
                      DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

