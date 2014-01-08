project(vtkSlicer${MODULE_NAME}ModuleLogic)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_MODULE_LOGIC_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  )


set(ADAP_DIJKSTRA_GC_SRCS
  fibheap.cpp
  fibheap.h
  utilities.h
  AdaptiveDijkstraSegmenter.hxx
  AdaptiveDijkstraSegmenter.h
  itkImageToVTKImageFilter.h
  itkImageToVTKImageFilter.txx
  itkVTKImageToImageFilter.h
  itkVTKImageToImageFilter.txx
  )

set(ADAP_DIJKSTRA_GC_LIBS
${ITK_LIBRARIES}
)


add_library(AdaptDijkstraLogic STATIC ${ADAP_DIJKSTRA_GC_SRCS})
target_link_libraries(AdaptDijkstraLogic ${ADAP_DIJKSTRA_GC_LIBS})


set(${KIT}_SRCS
  vtkSlicer${MODULE_NAME}Logic.cxx
  vtkSlicer${MODULE_NAME}Logic.h
  vtkAdaptDijkstraGC.cpp
  vtkAdaptDijkstraGC.h
#  fibheap.cpp
#  fibheap.h
#  utilities.h
#  AdaptiveDijkstraSegmenter.hxx
#  AdaptiveDijkstraSegmenter.h
#  itkImageToVTKImageFilter.h
#  itkImageToVTKImageFilter.txx
#  itkVTKImageToImageFilter.h
#  itkVTKImageToImageFilter.txx
  )

set(${KIT}_TARGET_LIBRARIES
AdaptDijkstraLogic
)

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleLogic(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )

#add_library(vtkAdaptiveDijkstra ${${KIT}_SRCS})
#link_directories(${KIT}_TARGET_LIBRARIES)
#target_link_libraries(vtkAdaptiveDijkstra ${${KIT}_TARGET_LIBRARIES})
