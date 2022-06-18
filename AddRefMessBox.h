#ifndef ADDREFMESSBOX_H
#define ADDREFMESSBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Reference.h"
#include <QFile>
#include <QDataStream>
#include "EditRefMessBox.h"
#include <QMessageBox>

class AddRefMessBox:public EditRefMessBox
{
Q_OBJECT
public:
    AddRefMessBox();
public slots:
    //将新文献的信息写入到文件中
    virtual void saveRefMess();
public:
    //发出 closeBox 信号
    virtual void emitCloseBox();
};

#endif // ADDREFMESSBOX_H
