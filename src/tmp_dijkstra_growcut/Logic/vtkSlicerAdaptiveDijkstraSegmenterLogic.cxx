/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// AdaptiveDijkstraSegmenter Logic includes
#include "vtkSlicerAdaptiveDijkstraSegmenterLogic.h"
//#include "AdaptiveDijkstraSegmenterCLICLP.h"
#include "AdaptiveDijkstraSegmenter.h"
#include "itkTimeProbe.h"

// MRML includes

// VTK includes
#include <vtkNew.h>
#include <vtkIntArray.h>
#include <vtkMRMLScene.h>

// STD includes
#include <cassert>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerAdaptiveDijkstraSegmenterLogic);

//----------------------------------------------------------------------------
vtkSlicerAdaptiveDijkstraSegmenterLogic::vtkSlicerAdaptiveDijkstraSegmenterLogic()
{
}

//----------------------------------------------------------------------------
vtkSlicerAdaptiveDijkstraSegmenterLogic::~vtkSlicerAdaptiveDijkstraSegmenterLogic()
{
}

//----------------------------------------------------------------------------
void vtkSlicerAdaptiveDijkstraSegmenterLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

void vtkSlicerAdaptiveDijkstraSegmenterLogic::RunADS(){
    const unsigned short SrcDimension=3;

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

//---------------------------------------------------------------------------
void vtkSlicerAdaptiveDijkstraSegmenterLogic::SetMRMLSceneInternal(vtkMRMLScene * newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}

//-----------------------------------------------------------------------------
void vtkSlicerAdaptiveDijkstraSegmenterLogic::RegisterNodes()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerAdaptiveDijkstraSegmenterLogic::UpdateFromMRMLScene()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerAdaptiveDijkstraSegmenterLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
}

//---------------------------------------------------------------------------
void vtkSlicerAdaptiveDijkstraSegmenterLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
}

