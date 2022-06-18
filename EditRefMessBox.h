#ifndef EDITREFMESSBOX_H
#define EDITREFMESSBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Reference.h"
#include <QFile>
#include <QDataStream>

#include <QMessageBox>
//自定义添加或修改文献信息窗口
class EditRefMessBox : public QDialog
{
    Q_OBJECT

signals:
    //自定义信号，当添加文献信息完成后，更新主界面上的表格
    void closeBox();

public slots:
    //将新文献的信息写入到文件中
    virtual void saveRefMess()=0;
public:
    //发出 closeBox 信号
    virtual void emitCloseBox()=0;


    QLineEdit * DOI;
    QLineEdit * Author;
    QLineEdit * Title;
    QLineEdit * Journal;
    QLineEdit * Date;
    QLineEdit * Type;
    QPushButton * submit;
    QPushButton * cancel;
};

#endif // EDITREFMESSBOX_H
