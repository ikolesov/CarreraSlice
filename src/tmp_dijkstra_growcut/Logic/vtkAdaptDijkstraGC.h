
#ifndef KVIEWER_GUI_H
#define KVIEWER_GUI_H

//#include "vtkSlicerCarreraSliceModuleLogicExport.h"
#include "vtkImageData.h"

class VTK_SLICER_CARRERASLICE_MODULE_LOGIC_EXPORT vtkAdaptDijkstraGC : public vtkObject
{



public:
  static vtkAdaptDijkstraGC* New();
  vtkTypeRevisionMacro(vtkAdaptDijkstraGC,vtkObject);
  //vtkTypeMacro(vtkKSlice,vtkObject);


  //set parameters of grow cut
  vtkSetObjectMacro(SourceVol, vtkImageData);
  vtkSetObjectMacro(SeedVol, vtkImageData);
  vtkSetMacro(bInitialized, bool);

  //processing functions
  void RunADS();
  void PrintSelf(ostream &os, vtkIndent indent);

protected:
  vtkKSlice();
  virtual ~vtkKSlice();

private:
  //vtk image data (from slicer)
  vtkImageData* SourceVol;
  vtkImageData* SeedVol;

  bool bInitialized;
  std::string strInitial;
};
#endif
