
#ifndef KVIEWER_GUI_H
#define KVIEWER_GUI_H

#include "vtkSlicerAdaptiveDijkstraSegmenterModuleLogicExport.h"
#include "vtkImageData.h"
#include "AdaptiveDijkstraSegmenter.h"


const unsigned short SrcDimension = 3;
typedef float FPixelType;											// float type pixel for cost function
typedef short SPixelType;
typedef itk::Image<SPixelType, SrcDimension> SrcImageType;
typedef itk::Image<SPixelType, SrcDimension> LabImageType;

class VTK_SLICER_ADAPTIVEDIJKSTRASEGMENTER_MODULE_LOGIC_EXPORT vtkAdaptDijkstraGC : public vtkObject
{



public:
  static vtkAdaptDijkstraGC* New();
  vtkTypeRevisionMacro(vtkAdaptDijkstraGC,vtkObject);
  //vtkTypeMacro(vtkKSlice,vtkObject);


  //set parameters of grow cut
  vtkSetObjectMacro(SourceVol, vtkImageData);
  vtkSetObjectMacro(SeedVol, vtkImageData);
  //vtkSetObjectMacro(OutputVol, vtkImageData);

  vtkSetMacro(bInitialized, bool);

  //processing functions
  void Initialize();
  void RunADS();
  void PrintSelf(ostream &os, vtkIndent indent);

protected:
  vtkAdaptDijkstraGC();
  virtual ~vtkAdaptDijkstraGC();

private:
  //vtk image data (from slicer)
  vtkImageData* SourceVol;
  vtkImageData* SeedVol;

  //converted itk images
  //SrcImageType::Pointer srcImg;
  //LabImageType::Pointer seedImg;
  //LabImageType::Pointer segImg;

  //logic code
  FGC::FastGrowCut *fastGC;

  //state variables
  bool bInitialized;
  std::string strInitial;
};
#endif
