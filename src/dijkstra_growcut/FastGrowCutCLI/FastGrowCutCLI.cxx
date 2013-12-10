#include "FastGrowCutCLICLP.h"

#include "FastGrowCut.h"
#include "itkTimeProbe.h"

int main(int argc, char** argv) {

     PARSE_ARGS;

     std::cout <<"segmenter initialzed?  " << strInitial <<std::endl;

     const unsigned short SrcDimension = 3;
     typedef float FPixelType;											// float type pixel for cost function
 //    typedef unsigned char  IPixelType;
     typedef short SPixelType;
     typedef itk::Image<SPixelType, SrcDimension> SrcImageType;
     typedef itk::Image<SPixelType, SrcDimension> LabImageType;
     typedef itk::Image<FPixelType, SrcDimension> DistImageType;
     bool bInitialized;

      itk::TimeProbe timer;

     timer.Start();
     SrcImageType::Pointer srcImg = FGC::readImage<SrcImageType>(sourceImageName.c_str());
     LabImageType::Pointer seedImg = FGC::readImage<LabImageType>(seedImageName.c_str());
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
//     segImg = fastGC.GetLabeImage();
     segImg = fastGC.GetForegroundmage();

     timer.Stop();

      if(!bInitialized)
          std::cout << "Initial fast growcut time: " << timer.GetMeanTime() << " seconds\n";
      else
          std::cout << "adaptive growcut time: " << timer.GetMeanTime() << " seconds\n";

//      FGC::writeImage<LabImageType>(segImg, labImageName.c_str());
      FGC::writeImage<LabImageType>(segImg, seedImageName.c_str());

     return EXIT_SUCCESS;
}
