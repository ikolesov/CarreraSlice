#ifndef FAST_MARCHING_H
#define FAST_MARCHING_H

#include <math.h>
#include <queue>
#include <set>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iterator>

#include "utilities.h"

#include "fibheap.h"

namespace FGC {

/***************************************************************************
* class HeapNode
***************************************************************************/
class HeapNode : public FibHeapNode {
    float   N;
    long IndexV;

public:
    HeapNode() : FibHeapNode() { N = 0; }
    virtual void operator =(FibHeapNode& RHS);
    virtual int  operator ==(FibHeapNode& RHS);
    virtual int  operator <(FibHeapNode& RHS);
    virtual void operator =(double NewKeyVal );
    virtual void Print();
    double GetKeyValue() { return N; }
    void SetKeyValue(double n) { N = n; }
    long int GetIndexValue() { return IndexV; }
    void SetIndexValue( long int v) { IndexV = v; }
};

const float  DIST_INF = std::numeric_limits<float>::max();
const float  DIST_EPSION = 1e-3;
unsigned char NNGBH = 26;



//typedef itk::Image<float , 3> DistImageType;
class FastGrowCut {
		public:
        FastGrowCut(vtkImageData* image, vtkImageData* seed);
         ~FastGrowCut();

        //void SetSourceImage(const typename SrcImageType::Pointer srcImg);
        //void SetSeedlImage(const typename LabImageType::Pointer seedImg);
        void SetWorkMode(bool bSegInitialized = false);
        void DoSegmentation();
        //typename LabImageType::Pointer GetLabeImage();
        typename DistImageType::Pointer GetDistImage();
        typename LabImageType::Pointer GetForegroundmage();

		private:
            void FindROI();
            void InitializationHP();
            void DijkstraBasedClassificationHP();
            void InitializationAHP();
            void DijkstraBasedClassificationAHP();

            //computation containers
            vtkImageData *m_srcImg;
            vtkImageData *m_seedImg;


            //cropped containers
            typename SrcImageType::Pointer m_srcImgROI;
            typename LabImageType::Pointer m_seedImgROI;

            //
            typename LabImageType::SizeType m_imSize;
            typename LabImageType::RegionType m_outRegion;



            typedef typename SrcImageType::IndexType IndexType;
            long m_DIMX, m_DIMY, m_DIMZ, m_DIMXY, m_DIMXYZ;
            long m_NDiff;

            std::vector<int> m_indOff;
            std::vector<typename SrcImageType::PixelType> m_imvec;

            FibHeap *m_heap;
            HeapNode *m_hpNodes;
            std::vector<unsigned char>  m_NBSIZE;
            std::vector<char> m_labels;
            std::vector<float> m_dist;

            std::vector<char> m_labelsPre;
            std::vector<float> m_distPre;
            bool m_bSegInitialized;

            //state variables
            long vecROI[6];
            double *img;
            short *seed;
            int *mdims;
            long dimz,dimy,dimx;
            //std::string m_fnROI;
            //std::string m_fnDistPre;
            //std::string m_fnLabPre;

	};

}

#include "AdaptiveDijkstraSegmenter.hxx"

#endif
