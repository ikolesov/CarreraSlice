cmake_minimum_required(VERSION 3.5)

if(WIN32)
  set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING "extra compiler flags for debug" FORCE )
  set(CMAKE_C_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING "extra compiler flags for debug" FORCE )
else(WIN32)
  set(CMAKE_C_FLAGS_DEBUG "-pedantic " CACHE STRING "extra compiler flags for debug" FORCE )
  if(LINUX)
    set(CMAKE_C_FLAGS "-fPIC -g3 -Wall -pipe -DVTK_EXCLUDE_STRSTREAM_HEADERS -Wl,--no-undefined" CACHE STRING "compiler flags always used" FORCE)
    set(CMAKE_CXX_FLAGS "-fPIC -Wall -pipe -DVTK_EXCLUDE_STRSTREAM_HEADERS -Wl,--no-undefined" CACHE STRING "compiler flags always used" FORCE)
  else(LINUX)
    set(CMAKE_C_FLAGS "-fPIC -g3 -Wall -pipe -DVTK_EXCLUDE_STRSTREAM_HEADERS" CACHE STRING "compiler flags always used" FORCE)
    set(CMAKE_CXX_FLAGS "-fPIC -Wall -pipe -DVTK_EXCLUDE_STRSTREAM_HEADERS" CACHE STRING "compiler flags always used" FORCE)
  endif(LINUX)
  set(CMAKE_CXX_FLAGS_DEBUG "-g3 " CACHE STRING "extra compiler flags for debug" FORCE )
endif(WIN32)

#-----------------------------------------------------------------------------
set(MODULE_NAME FastGrowCutSegmenter)
set(MODULE_TITLE ${MODULE_NAME})

string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

#-----------------------------------------------------------------------------
add_subdirectory(Logic)

#-----------------------------------------------------------------------------
set(MODULE_EXPORT_DIRECTIVE "Q_SLICER_QTMODULES_${MODULE_NAME_UPPER}_EXPORT")

set(MODULE_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/Logic
  ${CMAKE_CURRENT_BINARY_DIR}/Logic
  )

set(MODULE_SRCS
  qSlicer${MODULE_NAME}Module.cxx
  qSlicer${MODULE_NAME}Module.h
  )

set(MODULE_MOC_SRCS
  qSlicer${MODULE_NAME}Module.h
  )

set(MODULE_UI_SRCS
  )

set(MODULE_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleLogic
  )

set(MODULE_RESOURCES
  )

#-----------------------------------------------------------------------------
slicerMacroBuildQtModule(
  NAME ${MODULE_NAME}
  TITLE ${MODULE_TITLE}
  EXPORT_DIRECTIVE ${MODULE_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${MODULE_INCLUDE_DIRECTORIES}
  SRCS ${MODULE_SRCS}
  MOC_SRCS ${MODULE_MOC_SRCS}
  UI_SRCS ${MODULE_UI_SRCS}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  RESOURCES ${MODULE_RESOURCES}
  WITH_GENERIC_TESTS
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

