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

// Qt includes
#include <QtPlugin>

// AdaptiveDijkstraSegmenter Logic includes
#include <vtkSlicerAdaptiveDijkstraSegmenterLogic.h>

// AdaptiveDijkstraSegmenter includes
#include "qSlicerAdaptiveDijkstraSegmenterModule.h"
#include "qSlicerAdaptiveDijkstraSegmenterModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerAdaptiveDijkstraSegmenterModule, qSlicerAdaptiveDijkstraSegmenterModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerAdaptiveDijkstraSegmenterModulePrivate
{
public:
  qSlicerAdaptiveDijkstraSegmenterModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerAdaptiveDijkstraSegmenterModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerAdaptiveDijkstraSegmenterModulePrivate
::qSlicerAdaptiveDijkstraSegmenterModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerAdaptiveDijkstraSegmenterModule methods

//-----------------------------------------------------------------------------
qSlicerAdaptiveDijkstraSegmenterModule
::qSlicerAdaptiveDijkstraSegmenterModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerAdaptiveDijkstraSegmenterModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerAdaptiveDijkstraSegmenterModule::~qSlicerAdaptiveDijkstraSegmenterModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerAdaptiveDijkstraSegmenterModule::helpText()const
{
  return "This is a loadable module bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerAdaptiveDijkstraSegmenterModule::acknowledgementText()const
{
  return "This work was was partially funded by NIH grant 3P41RR013218-12S1";
}

//-----------------------------------------------------------------------------
QStringList qSlicerAdaptiveDijkstraSegmenterModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Jean-Christophe Fillion-Robin (Kitware)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerAdaptiveDijkstraSegmenterModule::icon()const
{
  return QIcon(":/Icons/AdaptiveDijkstraSegmenter.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerAdaptiveDijkstraSegmenterModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerAdaptiveDijkstraSegmenterModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerAdaptiveDijkstraSegmenterModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerAdaptiveDijkstraSegmenterModule
::createWidgetRepresentation()
{
  return new qSlicerAdaptiveDijkstraSegmenterModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerAdaptiveDijkstraSegmenterModule::createLogic()
{
  return vtkSlicerAdaptiveDijkstraSegmenterLogic::New();
}
