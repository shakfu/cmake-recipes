///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2005, Mike Jackson
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////


#include <QtGui/QDialog>

#include "ui_TestForm.h"

class TestForm : public QDialog, private Ui::TestForm
{

Q_OBJECT;

public:
  TestForm(QWidget *parent = 0);
 
  int _test;

private slots:
  
  void addClicked();
  void doClicked();
  void openFile() ;
  
};
  
