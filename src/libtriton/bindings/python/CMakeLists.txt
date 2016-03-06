set(Python_ADDITIONAL_VERSIONS 2.7 3.4 3.5 3.6 3.7)
# Try to autodetect Python (can be overridden manually if needed)
if (NOT ${PYTHON_VERSION} STREQUAL "")
  find_package(PythonLibs ${PYTHON_VERSION} EXACT)
  if (NOT PythonLibs_FOUND)
    find_package(PythonLibs ${PYTHON_VERSION} REQUIRED)
  endif()
else()
  find_package(PythonLibs REQUIRED)
endif()


# Include path for Python header files
include_directories(${PYTHON_INCLUDE_DIR})

# Include path for pybind11 header files -- this may need to be changed depending on your setup

add_definitions(-std=c++11)

# Define source files
file(
    GLOB_RECURSE
    python_binding_source_files
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(pyTriton SHARED ${python_binding_source_files})
set_target_properties(pyTriton PROPERTIES PREFIX "" OUTPUT_NAME "triton")

set_property(TARGET pyTriton PROPERTY CXX_STANDARD 11)
set_property(TARGET pyTriton PROPERTY CXX_STANDARD_REQUIRED ON)

if (UNIX)
  set_target_properties(pyTriton PROPERTIES SUFFIX ".so")
endif()

target_link_libraries(pyTriton ${PROJECT_LIBTRITON} ${PYTHON_LIBRARY})

MESSAGE(STATUS "Python install directory: ${CMAKE_INSTALL_PREFIX}/lib/python${PYTHON_VERSION}/dist-packages")
install(TARGETS pyTriton LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python${PYTHON_VERSION}/dist-packages")


