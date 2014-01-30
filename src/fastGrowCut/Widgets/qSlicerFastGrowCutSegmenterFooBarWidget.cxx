/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// FooBar Widgets includes
#include "qSlicerFastGrowCutSegmenterFooBarWidget.h"
#include "ui_qSlicerFastGrowCutSegmenterFooBarWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_FastGrowCutSegmenter
class qSlicerFastGrowCutSegmenterFooBarWidgetPrivate
  : public Ui_qSlicerFastGrowCutSegmenterFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerFastGrowCutSegmenterFooBarWidget);
protected:
  qSlicerFastGrowCutSegmenterFooBarWidget* const q_ptr;

public:
  qSlicerFastGrowCutSegmenterFooBarWidgetPrivate(
    qSlicerFastGrowCutSegmenterFooBarWidget& object);
  virtual void setupUi(qSlicerFastGrowCutSegmenterFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerFastGrowCutSegmenterFooBarWidgetPrivate
::qSlicerFastGrowCutSegmenterFooBarWidgetPrivate(
  qSlicerFastGrowCutSegmenterFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerFastGrowCutSegmenterFooBarWidgetPrivate
::setupUi(qSlicerFastGrowCutSegmenterFooBarWidget* widget)
{
  this->Ui_qSlicerFastGrowCutSegmenterFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerFastGrowCutSegmenterFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerFastGrowCutSegmenterFooBarWidget
::qSlicerFastGrowCutSegmenterFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerFastGrowCutSegmenterFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerFastGrowCutSegmenterFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerFastGrowCutSegmenterFooBarWidget
::~qSlicerFastGrowCutSegmenterFooBarWidget()
{
}
