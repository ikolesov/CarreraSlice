#include <iostream>
#include "vtkAdaptDijkstraGC.h"

#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"

#include "itkImage.h"
#include "itkTimeProbe.h"

#include "AdaptiveDijkstraSegmenter.h"

vtkCxxRevisionMacro(vtkAdaptDijkstraGC, "$Revision$"); //necessary?
vtkStandardNewMacro(vtkAdaptDijkstraGC); //for the new() macro

//----------------------------------------------------------------------------


vtkAdaptDijkstraGC::vtkAdaptDijkstraGC( ) {
    strInitial="no";

    SourceVol   = NULL;
    SeedVol   = NULL;
}


vtkAdaptDijkstraGC::~vtkAdaptDijkstraGC() {
  //these functions decrement reference count on the vtkImageData's (incremented by the SetMacros)
  if (this->SourceVol)
  {
    this->SetSourceVol(NULL);
  }

  if (this->SeedVol)
  {
    this->SetSeedVol(NULL);
  }

  //delete this->ksegmentor;
  std::cout<<"AdaptDijkstraGC destroyed"<<std::endl;
}

void vtkAdaptDijkstraGC::Initialize(){
    fastGC= new FGC::FastGrowCut(SourceVol, SeedVol);
}

void vtkAdaptDijkstraGC::RunADS(){

    //itk images, as growcut currently needs (converted from vtk data above)

    //std::cout <<"segmenter initialzed?  " << strInitial <<std::endl;

    itk::TimeProbe timer;

    timer.Start();

    bInitialized = strInitial == "yes" ? true : false;


    fastGC->SetWorkMode(bInitialized);

    // Do Dijkstra-based grow cut classification
    fastGC->DoSegmentation();

    timer.Stop();





    // Output preparation
    // Get output image
    // segImg = fastGC.GetLabeImage();
    //segImg = fastGC->GetForegroundmage();


    if(!bInitialized)
        std::cout << "Initial Dijkstra segmentation time: " << timer.GetMeanTime() << " seconds\n";
    else
        std::cout << "adaptive Dijkstra segmentation time: " << timer.GetMeanTime() << " seconds\n";

    //FGC::writeImage<LabImageType>(segImg, labImageName.c_str());
    //FGC::writeImage<LabImageType>(segImg, seedImageName.c_str());
    //OutputVol = FGC::convertImgToVTK<LabImageType>(this->SeedVol);

    std::cout<<"Ran ADS done"<<std::endl;
    return;
}

void vtkAdaptDijkstraGC::PrintSelf(ostream &os, vtkIndent indent){
    std::cout<<"This function has been found"<<std::endl;
}
