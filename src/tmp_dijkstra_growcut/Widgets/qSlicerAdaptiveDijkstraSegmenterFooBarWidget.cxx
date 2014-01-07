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
#include "qSlicerAdaptiveDijkstraSegmenterFooBarWidget.h"
#include "ui_qSlicerAdaptiveDijkstraSegmenterFooBarWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_AdaptiveDijkstraSegmenter
class qSlicerAdaptiveDijkstraSegmenterFooBarWidgetPrivate
  : public Ui_qSlicerAdaptiveDijkstraSegmenterFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerAdaptiveDijkstraSegmenterFooBarWidget);
protected:
  qSlicerAdaptiveDijkstraSegmenterFooBarWidget* const q_ptr;

public:
  qSlicerAdaptiveDijkstraSegmenterFooBarWidgetPrivate(
    qSlicerAdaptiveDijkstraSegmenterFooBarWidget& object);
  virtual void setupUi(qSlicerAdaptiveDijkstraSegmenterFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerAdaptiveDijkstraSegmenterFooBarWidgetPrivate
::qSlicerAdaptiveDijkstraSegmenterFooBarWidgetPrivate(
  qSlicerAdaptiveDijkstraSegmenterFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerAdaptiveDijkstraSegmenterFooBarWidgetPrivate
::setupUi(qSlicerAdaptiveDijkstraSegmenterFooBarWidget* widget)
{
  this->Ui_qSlicerAdaptiveDijkstraSegmenterFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerAdaptiveDijkstraSegmenterFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerAdaptiveDijkstraSegmenterFooBarWidget
::qSlicerAdaptiveDijkstraSegmenterFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerAdaptiveDijkstraSegmenterFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerAdaptiveDijkstraSegmenterFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerAdaptiveDijkstraSegmenterFooBarWidget
::~qSlicerAdaptiveDijkstraSegmenterFooBarWidget()
{
}
