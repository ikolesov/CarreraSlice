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

// KSlice Logic includes
#include <vtkSlicerKSliceLogic.h>

// KSlice includes
#include "qSlicerCarreraSliceModule.h"
#include "qSlicerCarreraSliceModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerCarreraSliceModule, qSlicerCarreraSliceModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerCarreraSliceModulePrivate
{
public:
  qSlicerCarreraSliceModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerKSliceModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerCarreraSliceModulePrivate
::qSlicerCarreraSliceModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerCarreraSliceModule methods

//-----------------------------------------------------------------------------
qSlicerCarreraSliceModule
::qSlicerCarreraSliceModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerCarreraSliceModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerCarreraSliceModule::~qSlicerCarreraSliceModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerCarreraSliceModule::helpText()const
{
  return "This is a loadable module bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerCarreraSliceModule::acknowledgementText()const
{
  return "This work was was partially funded by NIH grant 3P41RR013218-12S1";
}

//-----------------------------------------------------------------------------
QStringList qSlicerCarreraSliceModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Ivan Kolesov, Peter Karasev (Georgia Tech)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerCarreraSliceModule::icon()const
{
  return QIcon(":/Icons/KSlice.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerCarreraSliceModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerCarreraSliceModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerCarreraSliceModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerCarreraSliceModule
::createWidgetRepresentation()
{
  return new qSlicerCarreraSliceModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerCarreraSliceModule::createLogic()
{
  return vtkSlicerKSliceLogic::New();
}
