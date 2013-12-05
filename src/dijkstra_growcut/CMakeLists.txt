cmake_minimum_required(VERSION 2.8.9)

set(MODULE_NAME "DijkstraGrowCut")

project(vtkSlicer${MODULE_NAME}ModuleLogic)

set(KIT ${PROJECT_NAME})

enable_testing()

set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_MODULE_LOGIC_EXPORT")



#-----------------------------------------------------------------------------
set(EXTENSION_HOMEPAGE "http://www.slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/FastGrowCutCLI")
set(EXTENSION_CATEGORY "Testing")
set(EXTENSION_CONTRIBUTORS "Liangjia Zhu, Ivan Kolesov, Yi Gao, and Allen Tannenbaum")
set(EXTENSION_DESCRIPTION "This is the intial version of fast grow cut module")
#set(EXTENSION_ICONURL "http://viewvc.slicer.org/viewvc.cgi/Slicer4/trunk/Extensions/Testing/FastGrowCutCLI/FastGrowCutCLI.png?revision=21745&view=co")
#set(EXTENSION_SCREENSHOTURLS "http://wiki.slicer.org/slicerWiki/images/a/ab/Slicer-r19441-FastGrowCutCLI-screenshot.png http://wiki.slicer.org/slicerWiki/images/1/1e/Slicer-r19441-FastGrowCutCLI-screenshot-2.png")

#-----------------------------------------------------------------------------
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})


message(STATUS "Slicer_SOURCE_DIR is:  [ ${Slicer_SOURCE_DIR} ]...")

set(${KIT}_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/../../KSegmentor/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/../../KViewerMain/include/
  ${CMAKE_CURRENT_SOURCE_DIR}/../../util/vrcl/include/
  )


#-----------------------------------------------------------------------------
add_subdirectory(FastGrowCutCLI)

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})

set(${KIT}_SRCS
  #vtkSlicer${MODULE_NAME}Logic.cxx
  #vtkSlicer${MODULE_NAME}Logic.h
  vtkSlicerKSliceLogic.h
  vtkSlicerKSliceLogic.cxx
  vtkKSlice.cpp
  vtkKSlice.h
)



set(${KIT}_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
)



#-----------------------------------------------------------------------------
SlicerMacroBuildModuleLogic(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
