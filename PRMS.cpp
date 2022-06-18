#include <QMessageBox>
#include <QTextStream>
#include <QWidget>

#include "RefFile.h"
#include "admin.h"
#include "visitor.h"
#include "Config.h"
#include "PRMS.h"
#include "login.h"

PRMS::PRMS()
{
};

void PRMS::run()
{
    login *logindialog=new login;
    if(logindialog->exec()==QDialog::Accepted)
    {
        int a = login::loginstatus;//根据不同值从而进入不同界面
        QTextStream qout(stdout);

        RefFile xmlread;
       BOOKLIST = xmlread.formatReadFile();
        if(a == 1)
        {
            admin *adminwindow = new admin;

            adminwindow->show();
           return;
        }
        else if(a == -1)
        {
            visitor *visitorwindow = new visitor;

            visitorwindow->show();
           return;
        }
    }
    else
    {
       return;
    }
}
PRMS::~PRMS()
{
    delete BOOKLIST;
}
