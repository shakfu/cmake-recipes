///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2005, Mike Jackson
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////


#include "TestForm.h"
// #include <QtGui>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>


TestForm::TestForm(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    connect( addButton, SIGNAL(clicked()), this, SLOT(addClicked() ) );
    connect( pushButton, SIGNAL(clicked()), this, SLOT(doClicked() ) );

}

void TestForm::addClicked()
{
  theListBox->addItem(theListItem->text() );
  theListItem->setText("");
}

void TestForm::doClicked()
{
  theListBox->addItem(theListItem->text() );
  theListItem->setText("");
}

void TestForm::openFile() 
{
  
}
