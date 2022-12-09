///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2005, Mike Jackson
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////



#include <QApplication>

#include "ui_TestForm.h"
#include "TestForm.h"
#include <iostream>


int main(int argc, char *argv[])
{
   // Q_INIT_RESOURCE(calculatorbuilder);
    std::cout << "Testing" << std::endl;
    QApplication app(argc, argv);
    
    TestForm *test = new TestForm;
    test->show();
    return app.exec();
    
    
}
