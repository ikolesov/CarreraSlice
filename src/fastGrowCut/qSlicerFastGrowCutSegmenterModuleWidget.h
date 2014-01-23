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

#ifndef __qSlicerFastGrowCutSegmenterModuleWidget_h
#define __qSlicerFastGrowCutSegmenterModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerFastGrowCutSegmenterModuleExport.h"

class qSlicerFastGrowCutSegmenterModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_FASTGROWCUTSEGMENTER_EXPORT qSlicerFastGrowCutSegmenterModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerFastGrowCutSegmenterModuleWidget(QWidget *parent=0);
  virtual ~qSlicerFastGrowCutSegmenterModuleWidget();

public slots:


protected:
  QScopedPointer<qSlicerFastGrowCutSegmenterModuleWidgetPrivate> d_ptr;
  
  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerFastGrowCutSegmenterModuleWidget);
  Q_DISABLE_COPY(qSlicerFastGrowCutSegmenterModuleWidget);
};

#endif
