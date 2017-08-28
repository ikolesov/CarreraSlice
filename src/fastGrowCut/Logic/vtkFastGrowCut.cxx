
#include "vtkFastGrowCut.h"

// VTK includes
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>

// ITK includes
#include <itkTimeProbe.h>

// STD includes
#include <iostream>

#include "FastGrowCutSegmenter.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkFastGrowCut);

//----------------------------------------------------------------------------
vtkFastGrowCut::vtkFastGrowCut( ) {

    SourceVol   = NULL;
    SeedVol   = NULL;
    m_fastGC = NULL;
}

//----------------------------------------------------------------------------
vtkFastGrowCut::~vtkFastGrowCut() {

    //these functions decrement reference count on the vtkImageData's (incremented by the SetMacros)
    if (this->SourceVol)
    {
      this->SetSourceVol(NULL);
    }

    if (this->SeedVol)
    {
      this->SetSeedVol(NULL);
    }

    if(m_fastGC != NULL) {
         delete m_fastGC;
    }
}

//----------------------------------------------------------------------------
void vtkFastGrowCut::Initialization() {

    InitializationFlag = false;
    if(m_fastGC == NULL) {
        m_fastGC = new FGC::FastGrowCut<SrcPixelType, LabPixelType>();
    }
}

//----------------------------------------------------------------------------
void vtkFastGrowCut::RunFGC(){

    itk::TimeProbe timer;
    timer.Start();

    // Find ROI
    if(!InitializationFlag) {
        FGC::FindVTKImageROI<LabPixelType>(SeedVol, m_imROI);
        std::cout << "image ROI = [" << m_imROI[0] << "," << m_imROI[1] << "," << m_imROI[2] << ";"  \
                     << m_imROI[3] << "," << m_imROI[4] << "," << m_imROI[5] << "]" << std::endl;
        FGC::ExtractVTKImageROI<SrcPixelType>(SourceVol, m_imROI, m_imSrcVec);
    }

    FGC::ExtractVTKImageROI<LabPixelType>(SeedVol, m_imROI, m_imSeedVec);

    // Initialize FastGrowCut
    std::vector<long> imSize(3);
    for(int i = 0; i < 3; i++) {
        imSize[i] = m_imROI[i + 3] - m_imROI[i];
    }

    m_fastGC->SetSourceImage(m_imSrcVec);
    m_fastGC->SetSeedlImage(m_imSeedVec);
    m_fastGC->SetImageSize(imSize);
    m_fastGC->SetWorkMode(InitializationFlag);

    // Do Segmentation
    m_fastGC->DoSegmentation();
    m_fastGC->GetForegroundmage(m_imLabVec);

    // Update result
    FGC::UpdateVTKImageROI<LabPixelType>(m_imLabVec, m_imROI, SeedVol);

    timer.Stop();

    if(!InitializationFlag)
        std::cout << "Initial fast GrowCut segmentation time: " << timer.GetMean() << " seconds\n";
    else
        std::cout << "Adaptive fast GrowCut segmentation time: " << timer.GetMean() << " seconds\n";

}

//----------------------------------------------------------------------------
void vtkFastGrowCut::PrintSelf(ostream &os, vtkIndent indent){
    std::cout<<"This function has been found"<<std::endl;
}
