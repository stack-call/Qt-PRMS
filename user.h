#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QGroupBox>

//自定义主窗口
class user : public QWidget
{
    Q_OBJECT
public:
    //构建主窗口界面
public slots:
    //打开指定文件
    virtual void openRefMess()=0;
    //实现保存文献信息功能
    virtual void saveRefMess()=0;
    //增加文献信息界面盒子
    virtual void AddRefBox()=0;
    //实现删除文献信息功能
    virtual void delRefFun()=0;
    //实现查找文献信息功能,任意一部分的任意部分内容，不必管是哪一部分，全部搜索比较
    virtual void findRefMess()=0;
    //实现修改文献信息功能
    virtual void changeRefBox()=0;//预留接口可以修改为使用单独的Box修改
    //virtual void changeRefMess(int row)=0;
//两个flush函数起到显示文献的作用
    //更新表格中罗列的文献信息
    virtual void flushTable()=0;
    //更新列表中显示的文献信息
    virtual void flushListWidget(int row)=0;

    virtual void ExitMess()=0;
public:
    //创建主窗口中的文献信息面板
    virtual QGroupBox * createRefMess()=0;
    //创建主窗口中的功能面板
    virtual QGroupBox * createMenu()=0;

};

#endif // USER_H
