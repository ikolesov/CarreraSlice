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

