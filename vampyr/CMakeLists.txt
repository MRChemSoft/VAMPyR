# create python module
pybind11_add_module(_vampyr MODULE THIN_LTO
    export_vampyr.cpp
  )

target_include_directories(_vampyr
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(_vampyr
  PUBLIC
    MRCPP::mrcpp
  )

add_subdirectory(bases)
add_subdirectory(functions)
add_subdirectory(operators)

file(RELATIVE_PATH _rel ${CMAKE_INSTALL_PREFIX}/${PYMOD_INSTALL_FULLDIR} ${CMAKE_INSTALL_PREFIX})
if(APPLE)
  set(_RPATH "@loader_path/${_rel}")
else()
  set(_RPATH "\$ORIGIN/${_rel}")
endif()

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/${PYMOD_INSTALL_FULLDIR})
# configure __init__.py
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py.in
  ${PROJECT_BINARY_DIR}/${PYMOD_INSTALL_FULLDIR}/__init__.py
  @ONLY
  )

set_target_properties(_vampyr
  PROPERTIES
    MACOSX_RPATH ON
    SKIP_BUILD_RPATH OFF
    BUILD_WITH_INSTALL_RPATH OFF
    INSTALL_RPATH "${_RPATH}lib"
    INSTALL_RPATH_USE_LINK_PATH ON
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${PYMOD_INSTALL_FULLDIR}
    RESOURCE "${PROJECT_BINARY_DIR}/${PYMOD_INSTALL_FULLDIR}/__init__.py"
  )

install(
  TARGETS
    _vampyr
  LIBRARY
    DESTINATION ${PYMOD_INSTALL_FULLDIR}
    COMPONENT lib
  RESOURCE
    DESTINATION ${PYMOD_INSTALL_FULLDIR}
    COMPONENT lib
  )
