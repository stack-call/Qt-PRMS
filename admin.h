#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include "EditRefMessBox.h"
#include <QFile>
#include <QDataStream>
#include "user.h"
#include "AddRefMessBox.h"
#include "ModifyRefMessBox.h"
class admin:public user
{
    Q_OBJECT
public:
    admin();

public slots:
    //打开指定文件
    virtual void openRefMess();
    //实现保存文献信息功能
    virtual void saveRefMess();
    //增加文献信息界面盒子
    virtual void AddRefBox();
    //实现删除文献信息功能
    virtual void delRefFun();
    //实现查找文献信息功能,任意一部分的任意部分内容，不必管是哪一部分，全部搜索比较
    virtual void findRefMess();
    //实现修改文献信息功能
    //virtual void changeRefMess(int row);
    virtual void changeRefBox();
//两个flush函数起到显示文献的作用
    //更新表格中罗列的文献信息
    virtual void flushTable();
    //更新列表中显示的文献信息
    virtual void flushListWidget(int row);

    virtual void ExitMess();
public:
    //创建主窗口中的文献信息面板
    virtual QGroupBox * createRefMess();
    //创建主窗口中的功能面板
    virtual QGroupBox * createMenu();
private:
    //主窗口中的表格控件
    QTableWidget * TableWidget;
    //主窗口中的列表控件
    QListWidget *ListWidget;
    //主窗口中的添加、删除、保存、退出按钮和查找文本框控件
    QPushButton * AddRefBtn;
    QPushButton * DelRefBtn;
    QLineEdit * FindRefEdit;
    QPushButton * SaveBtn;
    QPushButton * ExitBtn;


    QPushButton * OpenBtn;
    QPushButton * ModifyBtn;
    //弹出的添加文献信息窗口
    AddRefMessBox * addmessBox;
    ModifyRefMessBox * changemessBox;
};

#endif // ADMIN_H
