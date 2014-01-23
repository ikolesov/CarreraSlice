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

// FastGrowCutSegmenter Logic includes
#include <vtkSlicerFastGrowCutSegmenterLogic.h>

// FastGrowCutSegmenter includes
#include "qSlicerFastGrowCutSegmenterModule.h"
#include "qSlicerFastGrowCutSegmenterModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerFastGrowCutSegmenterModule, qSlicerFastGrowCutSegmenterModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerFastGrowCutSegmenterModulePrivate
{
public:
  qSlicerFastGrowCutSegmenterModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerFastGrowCutSegmenterModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerFastGrowCutSegmenterModulePrivate
::qSlicerFastGrowCutSegmenterModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerFastGrowCutSegmenterModule methods

//-----------------------------------------------------------------------------
qSlicerFastGrowCutSegmenterModule
::qSlicerFastGrowCutSegmenterModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerFastGrowCutSegmenterModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerFastGrowCutSegmenterModule::~qSlicerFastGrowCutSegmenterModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerFastGrowCutSegmenterModule::helpText()const
{
  return "This is a loadable module bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerFastGrowCutSegmenterModule::acknowledgementText()const
{
  return "This work was was partially funded by NIH grant 3P41RR013218-12S1";
}

//-----------------------------------------------------------------------------
QStringList qSlicerFastGrowCutSegmenterModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Jean-Christophe Fillion-Robin (Kitware)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerFastGrowCutSegmenterModule::icon()const
{
  return QIcon(":/Icons/FastGrowCutSegmenter.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerFastGrowCutSegmenterModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerFastGrowCutSegmenterModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerFastGrowCutSegmenterModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerFastGrowCutSegmenterModule
::createWidgetRepresentation()
{
  return new qSlicerFastGrowCutSegmenterModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerFastGrowCutSegmenterModule::createLogic()
{
  return vtkSlicerFastGrowCutSegmenterLogic::New();
}
