
#include "FastGrowCut.h"

#include "itkImageRegionIterator.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkNumericTraits.h"
#include "itkRegionOfInterestImageFilter.h"


namespace FGC {

void HeapNode::Print() {
    FibHeapNode::Print();
//    mexPrintf( "%f (%d)" , N , IndexV );
}

void HeapNode::operator =(double NewKeyVal) {
    HeapNode Tmp;
    Tmp.N = N = NewKeyVal;
    FHN_Assign(Tmp);
}

void HeapNode::operator =(FibHeapNode& RHS) {
    FHN_Assign(RHS);
    N = ((HeapNode&) RHS).N;
}

int  HeapNode::operator ==(FibHeapNode& RHS) {
    if (FHN_Cmp(RHS)) return 0;
    return N == ((HeapNode&) RHS).N ? 1 : 0;
}

int  HeapNode::operator <(FibHeapNode& RHS) {
    int X;
    if ((X=FHN_Cmp(RHS)) != 0)
        return X < 0 ? 1 : 0;
    return N < ((HeapNode&) RHS).N ? 1 : 0;
}



template<typename SrcImageType, typename LabImageType, typename DistImageType>
FastGrowCut<SrcImageType, LabImageType, DistImageType>
::FastGrowCut() {

     m_heap = NULL;
     m_hpNodes = NULL;
     m_bSegInitialized = false;

     m_fnROI = "/tmp/FGC_ROI.txt";
     m_fnDistPre = "/tmp/FGC_DistPre.txt";
     m_fnLabPre = "/tmp/FGC_LabPre.txt";
 }

template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
::SetSourceImage(const typename SrcImageType::Pointer srcImg) {

    m_srcImg = srcImg;
}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
::SetSeedlImage(const typename LabImageType::Pointer seedImg) {

    m_seedImg = seedImg;
}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
::SetWorkMode(bool bSegUnInitialized ) {

    m_bSegInitialized = bSegUnInitialized;
}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
FastGrowCut<SrcImageType, LabImageType, DistImageType>
    ::~FastGrowCut() {

        if(m_heap != NULL) {
            delete m_heap;
        }
        if(m_hpNodes != NULL) {
            delete []m_hpNodes;
        }
	}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
:: DoSegmentation() {


     FindROI();

     // Initialize class variables
     InitializationAHP();

     DijkstraBasedClassificationAHP();

    // Save distance and label information to tempary files
    FGC::WriteVectorIntoFile<char>(m_fnLabPre.c_str(), m_labels);
    FGC::WriteVectorIntoFile<float>(m_fnDistPre.c_str(), m_dist);
}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
typename LabImageType::Pointer
FastGrowCut<SrcImageType, LabImageType, DistImageType>
:: GetLabeImage() {

    // Dijstra label image
    typename LabImageType::Pointer labImg = LabImageType::New();
    labImg->CopyInformation(m_seedImg);
    labImg->SetBufferedRegion(m_seedImg->GetBufferedRegion());
    labImg->Allocate();
    labImg->FillBuffer(0);

    typedef itk::ImageRegionIterator<LabImageType>  LabelIterator;
    LabelIterator labIt(labImg, m_outRegion);

//       std::vector<DKElement>::iterator itDK;
    long index = 0;
    for(labIt.GoToBegin(); !labIt.IsAtEnd(); ++labIt) {
        labIt.Set(m_labels[index++]);
    }


 return labImg;
}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
typename DistImageType::Pointer
FastGrowCut<SrcImageType, LabImageType, DistImageType>
:: GetDistImage() {

    // Dijstra distance image
    typename DistImageType::Pointer distImg = DistImageType::New();
    distImg->CopyInformation(m_seedImg);
    distImg->SetBufferedRegion(m_seedImg->GetBufferedRegion());
    distImg->Allocate();
    distImg->FillBuffer(DIST_INF);

    typedef itk::ImageRegionIterator<DistImageType>  DistIterator;
    DistIterator distIt(distImg, m_outRegion);

    long index = 0;
    for(distIt.GoToBegin(); !distIt.IsAtEnd(); ++distIt) {
        distIt.Set(m_dist[index++]);
    }


 return distImg;
}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
::InitializationHP() {

     m_imSize = m_srcImgROI->GetLargestPossibleRegion().GetSize();
     m_DIMX = m_imSize[0];
     m_DIMY = m_imSize[1];
     m_DIMZ = m_imSize[2];
     m_DIMXY = m_DIMX*m_DIMY;
     m_DIMXYZ = m_DIMXY*m_DIMZ;

    if((m_heap = new FibHeap) == NULL || (m_hpNodes = new HeapNode[m_DIMXYZ+1]) == NULL) {
        std::cerr << "Memory allocation failed-- ABORTING.\n";
        raise(SIGABRT);
    }
    m_heap->ClearHeapOwnership();

    // Compute index offset
    m_indOff.clear();
    long ix,iy,iz;
    for(ix = -1; ix <= 1; ix++)
        for(iy = -1; iy <= 1; iy++)
            for(iz = -1; iz <= 1; iz++) {
                if(!(ix == 0 && iy == 0 && iz == 0)) {
                    m_indOff.push_back(ix + iy*m_DIMX + iz*m_DIMXY);
                }
            }

    // Construct Graph Vertices
    m_NBSIZE = std::vector<unsigned char>(m_DIMXYZ, 0);
    m_imvec.resize(m_DIMXYZ);
    m_labels.resize(m_DIMXYZ);
    m_dist.resize(m_DIMXYZ);

    typedef itk::ImageRegionIterator<LabImageType>  SeedIterator;
    SeedIterator seedIt(m_seedImgROI, m_seedImgROI->GetBufferedRegion());
    typedef itk::ImageRegionIterator<SrcImageType>  SrcIterator;
    SrcIterator srcIt(m_srcImgROI, m_srcImgROI->GetBufferedRegion());
    IndexType imIndex;
    long index;

    for( seedIt.GoToBegin(), srcIt.GoToBegin(); !seedIt.IsAtEnd(); ++seedIt, ++srcIt) {
       imIndex = seedIt.GetIndex();
       index = imIndex[0] + imIndex[1]*m_DIMX + imIndex[2]*m_DIMXY;
       m_imvec[index] = srcIt.Get();
       m_labels[index] = seedIt.Get();

       if(m_labels[index] == 0) {
           m_hpNodes[index] = (float)DIST_INF;
           m_dist[index] = DIST_INF;
       }
       else {
          m_hpNodes[index] = (float)DIST_EPSION;
          m_dist[index] = DIST_EPSION;
       }

       m_heap->Insert(&m_hpNodes[index]);
       m_hpNodes[index].SetIndexValue(index);
   }

   long  i,j,k;
   for(i = 1; i < m_DIMX - 1; i++)
       for(j = 1; j < m_DIMY - 1; j++)
           for(k = 1; k < m_DIMZ - 1; k++) {
               index = i + j*m_DIMX + k*m_DIMXY;
               m_NBSIZE[index] = NNGBH;
           }

}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
::InitializationAHP() {

     m_imSize = m_srcImgROI->GetLargestPossibleRegion().GetSize();
     m_DIMX = m_imSize[0];
     m_DIMY = m_imSize[1];
     m_DIMZ = m_imSize[2];
     m_DIMXY = m_DIMX*m_DIMY;
     m_DIMXYZ = m_DIMXY*m_DIMZ;

    if((m_heap = new FibHeap) == NULL || (m_hpNodes = new HeapNode[m_DIMXYZ+1]) == NULL) {
        std::cerr << "Memory allocation failed-- ABORTING.\n";
        raise(SIGABRT);
    }
    m_heap->ClearHeapOwnership();

    // Compute index offset
    m_indOff.clear();
    long ix,iy,iz;
    for(ix = -1; ix <= 1; ix++)
        for(iy = -1; iy <= 1; iy++)
            for(iz = -1; iz <= 1; iz++) {
                if(!(ix == 0 && iy == 0 && iz == 0)) {
                    m_indOff.push_back(ix + iy*m_DIMX + iz*m_DIMXY);
                }
            }

    // Determine neighborhood size at each vertice
    m_NBSIZE = std::vector<unsigned char>(m_DIMXYZ, 0);
    long  i,j,k, index;
    for(i = 1; i < m_DIMX - 1; i++)
        for(j = 1; j < m_DIMY - 1; j++)
            for(k = 1; k < m_DIMZ - 1; k++) {
                index = i + j*m_DIMX + k*m_DIMXY;
                m_NBSIZE[index] = NNGBH;
            }

    // Extract status at each vertice
    m_imvec.resize(m_DIMXYZ);
    typedef itk::ImageRegionIterator<SrcImageType>  SrcIterator;
    SrcIterator srcIt(m_srcImgROI, m_srcImgROI->GetBufferedRegion());
    IndexType imIndex;

    for( srcIt.GoToBegin(); !srcIt.IsAtEnd();  ++srcIt) {
        imIndex = srcIt.GetIndex();
        index = imIndex[0] + imIndex[1]*m_DIMX + imIndex[2]*m_DIMXY;
        m_imvec[index] = srcIt.Get();
    }

    m_labels.resize(m_DIMXYZ);
    m_dist.resize(m_DIMXYZ);
    typedef itk::ImageRegionIterator<LabImageType>  SeedIterator;
    SeedIterator seedIt(m_seedImgROI, m_seedImgROI->GetBufferedRegion());

    if(!m_bSegInitialized) {
        for( seedIt.GoToBegin(); !seedIt.IsAtEnd(); ++seedIt) {
           imIndex = seedIt.GetIndex();
           index = imIndex[0] + imIndex[1]*m_DIMX + imIndex[2]*m_DIMXY;
           m_labels[index] = seedIt.Get();

           if(m_labels[index] == 0) {
               m_hpNodes[index] = (float)DIST_INF;
               m_dist[index] = DIST_INF;
           }
           else {
              m_hpNodes[index] = (float)DIST_EPSION;
              m_dist[index] = DIST_EPSION;
           }

           m_heap->Insert(&m_hpNodes[index]);
           m_hpNodes[index].SetIndexValue(index);
       }
    }
    else {
        m_labelsPre.clear();
        m_distPre.clear();
        FGC::LoadVectorIntoFile<char>(m_fnLabPre.c_str(), m_labelsPre, m_DIMXYZ);
        FGC::LoadVectorIntoFile<float>(m_fnDistPre.c_str(), m_distPre, m_DIMXYZ);
        for( seedIt.GoToBegin(); !seedIt.IsAtEnd(); ++seedIt) {

             imIndex = seedIt.GetIndex();
             index = imIndex[0] + imIndex[1]*m_DIMX + imIndex[2]*m_DIMXY;

             // Only update the difference seeds
             // TODO: check seedPre is a subset of seed!!
             if(seedIt.Get() != 0 && m_distPre[index] >  DIST_EPSION) {
                 m_hpNodes[index] = (float)DIST_EPSION;
                 m_dist[index] = DIST_EPSION;
                 m_labels[index] = seedIt.Get();
//                 std::cout << "seed found\n";
             }
             else {
                 m_hpNodes[index] = (float)DIST_INF;
                 m_dist[index] = DIST_INF;
                 m_labels[index] = 0;
             }
             m_heap->Insert(&m_hpNodes[index]);
             m_hpNodes[index].SetIndexValue(index);
         }
    }
  }

template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
::DijkstraBasedClassificationAHP() {

    HeapNode *hnMin, hnTmp;
    float t, tOri, tSrc;
    long i, index, indexNgbh;
    char labSrc;
    int pixCenter;

    // Insert 0 then extract it, which will balance heap
    m_heap->Insert(&hnTmp); m_heap->ExtractMin();

    long k = 0;

    // Adpative Dijkstra
    if(m_bSegInitialized) {
        while(!m_heap->IsEmpty()) {
            hnMin = (HeapNode *) m_heap->ExtractMin();
            index = hnMin->GetIndexValue();
            tSrc = hnMin->GetKeyValue();

            // stop propagation when the new distance is larger than the previous one
            if(tSrc == DIST_INF) break;
            if(tSrc > m_distPre[index]) {
                m_dist[index] = m_distPre[index];
                m_labels[index] = m_labelsPre[index];
                continue;
            }

            labSrc = m_labels[index];
            m_dist[index] = tSrc;

             // Update neighbors
            pixCenter = m_imvec[index];
            for(i = 0; i < m_NBSIZE[index]; i++) {

                    indexNgbh = index + m_indOff[i];
                    tOri = m_dist[indexNgbh];
                    t = std::abs(pixCenter - m_imvec[indexNgbh]) + tSrc;
                    if(tOri > t) {
                        m_dist[indexNgbh] = t;
                        m_labels[indexNgbh] = labSrc;

                        hnTmp = m_hpNodes[indexNgbh];
                        hnTmp.SetKeyValue(t);
                        m_heap->DecreaseKey(&m_hpNodes[indexNgbh], hnTmp);
                    }

            }

            k++;

        }

    //    std::cout << "all = " << k << std::endl;

        // Update previous labels and distance information
        for(long i = 0; i < m_DIMXYZ; i++) {
            if(m_dist[i] < DIST_INF) {
                m_labelsPre[i] = m_labels[i];
                m_distPre[i] = m_dist[i];
            }
        }
        std::copy(m_labelsPre.begin(), m_labelsPre.end(), m_labels.begin());
        std::copy(m_distPre.begin(), m_distPre.end(), m_dist.begin());
    }

    // Normal Dijkstra to be used in initializing the segmenter for the current image
    else {
        while(!m_heap->IsEmpty()) {
            hnMin = (HeapNode *) m_heap->ExtractMin();
            index = hnMin->GetIndexValue();
            tSrc = hnMin->GetKeyValue();
            labSrc = m_labels[index];
            m_dist[index] = tSrc;

    //        if(labSrc != 0) std::cout << "label at" << index << std::endl;

             // Update neighbors
            pixCenter = m_imvec[index];
            for(i = 0; i < m_NBSIZE[index]; i++) {

                    indexNgbh = index + m_indOff[i];
                    tOri = m_dist[indexNgbh];
                    t = std::abs(pixCenter - m_imvec[indexNgbh]) + tSrc;
                    if(tOri > t) {
                        m_dist[indexNgbh] = t;
                        m_labels[indexNgbh] = labSrc;

                        hnTmp = m_hpNodes[indexNgbh];
                        hnTmp.SetKeyValue(t);
                        m_heap->DecreaseKey(&m_hpNodes[indexNgbh], hnTmp);
                    }

            }

            k++;

        }

    }

}

template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
::DijkstraBasedClassificationHP() {

    HeapNode *hnMin, hnTmp;
    float t, tOri, tSrc;
    long i, index, indexNgbh;
    char labSrc;
    int pixCenter;

    // Insert 0 then extract it, which will balance heap
    m_heap->Insert(&hnTmp); m_heap->ExtractMin();

    long k = 0;
    while(!m_heap->IsEmpty()) {
        hnMin = (HeapNode *) m_heap->ExtractMin();
        index = hnMin->GetIndexValue();
        tSrc = hnMin->GetKeyValue();
        labSrc = m_labels[index];
        m_dist[index] = tSrc;

//        if(labSrc != 0) std::cout << "label at" << index << std::endl;

         // Update neighbors
        pixCenter = m_imvec[index];
        for(i = 0; i < m_NBSIZE[index]; i++) {

                indexNgbh = index + m_indOff[i];
                tOri = m_dist[indexNgbh];
                t = std::abs(pixCenter - m_imvec[indexNgbh]) + tSrc;
                if(tOri > t) {
                    m_dist[indexNgbh] = t;
                    m_labels[indexNgbh] = labSrc;

                    hnTmp = m_hpNodes[indexNgbh];
                    hnTmp.SetKeyValue(t);
                    m_heap->DecreaseKey(&m_hpNodes[indexNgbh], hnTmp);
                }

        }

        k++;

    }

//    std::cout << "all = " << k << std::endl;

}
template<typename SrcImageType, typename LabImageType, typename DistImageType>
void FastGrowCut<SrcImageType, LabImageType, DistImageType>
::FindROI() {

    typename LabImageType::IndexType roiStart;
    typename LabImageType::IndexType roiEnd;
    typename LabImageType::IndexType start;
    typename LabImageType::SizeType size;
    typename LabImageType::IndexType lstart;
    typename LabImageType::SizeType lsize;

    typename SrcImageType::IndexType istart;
    typename SrcImageType::SizeType isize;


    if(!m_bSegInitialized) {

    size = m_seedImg->GetLargestPossibleRegion().GetSize();
    start = m_seedImg->GetLargestPossibleRegion().GetIndex();


    roiStart[0] = 0; roiStart[1] = 0; roiStart[2] = 0;
    roiEnd[0] = 0; roiEnd[1] = 0; roiEnd[2] = 0;

    unsigned int ndims = m_seedImg->GetImageDimension();

    bool foundLabel = false;
     itk::ImageRegionIteratorWithIndex< LabImageType > label(m_seedImg, m_seedImg->GetBufferedRegion() );
    for(label.GoToBegin(); !label.IsAtEnd(); ++label) {
        if(label.Get() != 0) {
            typename LabImageType::IndexType idx = label.GetIndex();
            for (unsigned i = 0; i < ndims; i++)  {
              if(!foundLabel)  {
                roiStart[i] = idx[i];
                roiEnd[i] = idx[i];
                }
              else
                {
                if(idx[i] <= roiStart[i])
                  {
                  roiStart[i] = idx[i];
                  }
                if(idx[i] >= roiEnd[i])
                  {
                  roiEnd[i] = idx[i];
                  }
                }
              }
          foundLabel = true;
          }
    }

    int radius = 17;

    for (unsigned i = 0; i < ndims; i++) {
      int diff = static_cast< int > (roiStart[i] - radius);
      if (diff >= start[i])  {
        roiStart[i] -= radius;
        }
      else  {
        roiStart[i] = start[i];
        }
      roiEnd[i] = (static_cast<unsigned int>(roiEnd[i] + radius) < size[i]) ? (roiEnd[i] + radius) : size[i]-1;

      }




    std::cout << "ROI size = [";
    for (unsigned n = 0; n < ndims; n++) {
      istart[n] = roiStart[n];
      isize[n] = roiEnd[n]-roiStart[n];

//      std::cout << " istart " << istart[n] << " isize " << isize[n] << " " << std::endl;
      std::cout << isize[n] << " ";

      lstart[n] = istart[n];
      lsize[n] = isize[n];

      }
    std::cout << "]" << std::endl;

    std::vector<long> vecROI(6,0);
    vecROI[0] = isize[0]; vecROI[1] = isize[1];vecROI[2] = isize[2];
    vecROI[3] = istart[0]; vecROI[4] = istart[1];vecROI[5] = istart[2];

    FGC::WriteVectorIntoFile<long>(m_fnROI.c_str(), vecROI);

//    istart[0] = 32; istart[1] = 149; istart[2] = 0;
//    isize[0] = 502; isize[1] = 336; isize[3] = 43;

//    lstart[0] = 32; lstart[1] = 149; lstart[2] = 0;
//    lsize[0] = 502; lsize[1] = 336; lsize[3] = 43;


}
    else {
        std::vector<long> vecROI;
        FGC::LoadVectorIntoFile<long>(m_fnROI.c_str(), vecROI, 6);
        isize[0] = vecROI[0]; isize[1] = vecROI[1];isize[2] = vecROI[2];
        istart[0] = vecROI[3]; istart[1] = vecROI[4]; istart[2] = vecROI[5];
        lsize = isize;
        lstart = istart;

    }
    typename SrcImageType::RegionType iRegion;
    iRegion.SetSize( isize );
    iRegion.SetIndex( istart );

    typedef itk::RegionOfInterestImageFilter< SrcImageType, SrcImageType > iFilterType;
    typename iFilterType::Pointer fInput = iFilterType::New();
    fInput->SetRegionOfInterest( iRegion );

    fInput->SetInput( m_srcImg);
    fInput->Update();
    m_srcImgROI = SrcImageType::New();
    m_srcImgROI = fInput->GetOutput();

//    typename LabImageType::RegionType oRegion;
    m_outRegion.SetSize(lsize);
    m_outRegion.SetIndex(lstart);

    typedef itk::RegionOfInterestImageFilter< LabImageType, LabImageType > oFilterType;
    typename oFilterType::Pointer fOutput = oFilterType::New();
    fOutput->SetRegionOfInterest( m_outRegion );

    fOutput->SetInput( m_seedImg);
    fOutput->Update();
   m_seedImgROI = LabImageType::New();
   m_seedImgROI = fOutput->GetOutput();
}

} // end FGC
