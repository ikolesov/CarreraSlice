#include <iostream>
#include "vtkAdaptDijkstraGC.h"

#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"


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

  delete this->ksegmentor;
  std::cout<<"AdaptDijkstraGC destroyed"<<std::endl;
}

void vtkAdaptDijkstraGC::RunADS(){
    const unsigned short SrcDimension=3;

    typedef float FPixelType;											// float type pixel for cost function
    typedef short SPixelType;

    //itk images, as growcut currently needs (converted from vtk data above)
    typedef itk::Image<SPixelType, SrcDimension> SrcImageType;
    typedef itk::Image<SPixelType, SrcDimension> LabImageType;
    typedef itk::Image<FPixelType, SrcDimension> DistImageType;



    //std::cout <<"segmenter initialzed?  " << strInitial <<std::endl;

    itk::TimeProbe timer;

    timer.Start();
    //SrcImageType::Pointer srcImg = FGC::readImage<SrcImageType>(sourceImageName.c_str());
    //LabImageType::Pointer seedImg = FGC::readImage<LabImageType>(seedImageName.c_str());
    //LabImageType::Pointer segImg;

    SrcImageType::Pointer srcImg = FGC::convertImgToITK<SrcImageType>(this->SourceVol);
    LabImageType::Pointer seedImg = FGC::convertImgToITK<LabImageType>(this->SeedVol);
    LabImageType::Pointer segImg;


    bInitialized = strInitial == "yes" ? true : false;

    FGC::FastGrowCut<SrcImageType, LabImageType, DistImageType> fastGC;

    // Initialization
    fastGC.SetSourceImage(srcImg);
    fastGC.SetSeedlImage(seedImg);
    fastGC.SetWorkMode(bInitialized);

    // Do Dijkstra-based grow cut classification
    fastGC.DoSegmentation();

    // Get output image
    //segImg = fastGC.GetLabeImage();
    segImg = fastGC.GetForegroundmage();

    timer.Stop();

    if(!bInitialized)
        std::cout << "Initial Dijkstra segmentation time: " << timer.GetMeanTime() << " seconds\n";
    else
        std::cout << "adaptive Dijkstra segmentation time: " << timer.GetMeanTime() << " seconds\n";

    //FGC::writeImage<LabImageType>(segImg, labImageName.c_str());
    //FGC::writeImage<LabImageType>(segImg, seedImageName.c_str());

    return;
}
