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

#ifndef __qSlicerFastGrowCutSegmenterFooBarWidget_h
#define __qSlicerFastGrowCutSegmenterFooBarWidget_h

// Qt includes
#include <QWidget>

// FooBar Widgets includes
#include "qSlicerFastGrowCutSegmenterModuleWidgetsExport.h"

class qSlicerFastGrowCutSegmenterFooBarWidgetPrivate;

/// \ingroup Slicer_QtModules_FastGrowCutSegmenter
class Q_SLICER_MODULE_FASTGROWCUTSEGMENTER_WIDGETS_EXPORT qSlicerFastGrowCutSegmenterFooBarWidget
  : public QWidget
{
  Q_OBJECT
public:
  typedef QWidget Superclass;
  qSlicerFastGrowCutSegmenterFooBarWidget(QWidget *parent=0);
  virtual ~qSlicerFastGrowCutSegmenterFooBarWidget();

protected slots:

protected:
  QScopedPointer<qSlicerFastGrowCutSegmenterFooBarWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerFastGrowCutSegmenterFooBarWidget);
  Q_DISABLE_COPY(qSlicerFastGrowCutSegmenterFooBarWidget);
};

#endif
