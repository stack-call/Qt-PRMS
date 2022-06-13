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
    login *logindialog=new login;
    if(logindialog->exec()==QDialog::Accepted)
    {
        int a = login::loginstatus;
        QTextStream qout(stdout);
        qout<<a;

        RefFile xmlread;
       BOOKLIST = xmlread.formatReadFile(DEFAULT_FILE_NAME);
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
};
