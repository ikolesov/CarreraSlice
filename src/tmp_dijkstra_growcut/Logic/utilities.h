#ifndef utilities_hxx_
#define utilities_hxx_

// std
#include <iostream>
#include <fstream>
#include <limits>

// itk
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkImportImageFilter.h"
#include "itkVTKImageToImageFilter.h"

#include <csignal>

#include "vtkImageData.h"

namespace FGC
{

	/*
	* createImage
	*/

	template<typename itkImageType>
	typename itkImageType::Pointer createImage(typename itkImageType::SizeType size, int iniValue) {

		typename itkImageType::Pointer img = itkImageType::New();
		typename itkImageType::SpacingType spacing;
		typename itkImageType::IndexType start;
		start.Fill(0);
		spacing.Fill(1);
		spacing[itkImageType::ImageDimension - 1] = 2;

		typename itkImageType::RegionType region;
		img->SetSpacing(spacing);
		region.SetSize(size);
		region.SetIndex(start);
		img->SetRegions(region);
		img->Allocate();
		img->FillBuffer(static_cast<typename itkImageType::PixelType>(iniValue));

		const typename itkImageType::SpacingType& sp = img->GetSpacing();
		std::cout << "Spacing = ";
		std::cout << sp[0] << ", " << sp[1] << std::endl;


		return img;

	}

/**
 * convert between vtk and itk
 */
template< typename itkImage_t >
typename itkImage_t::Pointer convertImgToITK(vtkImageData* convertSource)
{
  //typedef itk::ImageFileReader< itkImage_t > ImageReaderType;
  //typename ImageReaderType::Pointer reader = ImageReaderType::New();
  //reader->SetFileName(fileName);

  typename itkImage_t::Pointer image;

  //run the conversion here!
  typedef itk::VTKImageToImageFilter<itkImage_t> VTKImageToImageType;

  typename VTKImageToImageType::Pointer vtkImageToImageFilter = VTKImageToImageType::New();
  vtkImageToImageFilter->SetInput(convertSource);
  vtkImageToImageFilter->Update();

  //itkImage_t::Pointer image = itkImage_t::New();
  image->Graft(vtkImageToImageFilter->GetOutput());

  return image;
}





  /**
   * readImage
   */
  template< typename itkImage_t >
  typename itkImage_t::Pointer readImage(const char *fileName)
  {
    typedef itk::ImageFileReader< itkImage_t > ImageReaderType;
    typename ImageReaderType::Pointer reader = ImageReaderType::New();
    reader->SetFileName(fileName);

    typename itkImage_t::Pointer image;

    try
      {
        reader->Update();
        image = reader->GetOutput();
      }
    catch ( itk::ExceptionObject &err)
      {
        std::cerr<< "ExceptionObject caught !" << std::endl;
        std::cerr<< err << std::endl;
        raise(SIGABRT);
      }

    return image;
  }

  /**
   * writeImage
   */
  template< typename itkImage_t > void writeImage(typename itkImage_t::Pointer img, const char *fileName)
  {
    typedef itk::ImageFileWriter< itkImage_t > WriterType;

    typename WriterType::Pointer writer = WriterType::New();
    writer->SetFileName( fileName );
    writer->SetInput(img);
    writer->UseCompressionOn();

    try
      {
        writer->Update();
      }
    catch ( itk::ExceptionObject &err)
      {
        std::cout << "ExceptionObject caught !" << std::endl;
        std::cout << err << std::endl;
        raise(SIGABRT);
      }
  }

   template<typename VType>
    void WriteVectorIntoFile(const char* fnSave, const std::vector<VType>& vec) {

        try{
            std::ofstream outfile(fnSave);
            outfile.write((const char *)&vec[0], vec.size()*sizeof(VType));
        }
        catch ( itk::ExceptionObject &err)
          {
            std::cout << "Fail to write to file " << fnSave << std::endl;
            std::cout << err << std::endl;
            raise(SIGABRT);
          }
    }

    template<typename VType>
     void LoadVectorIntoFile(const char* fnLoad, std::vector<VType>& vec, const long VEC_SIZE) {

          try{
             std::ifstream infile(fnLoad);
              vec.resize(VEC_SIZE);
              infile.read((char *)&vec[0], vec.size()*sizeof(VType));
         }
         catch ( itk::ExceptionObject &err)
           {
             std::cout << "Fail to load file " << fnLoad << std::endl;
             std::cout << err << std::endl;
             raise(SIGABRT);
           }
     }
}// douher

#endif
