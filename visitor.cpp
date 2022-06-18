#include <QMessageBox>
#include <list>
#include "Reference.h"
#include <QDebug>
#include <iostream>
#include <QString>
#include <QFileDialog>

#include "visitor.h"
#include "Config.h"
#include "RefFile.h"
visitor::visitor()
{
    //setWindowIcon(QIcon(":/logo.ico"));
    setWindowTitle("文献管理系统");
    this->resize(1220,600);
    QHBoxLayout *HBoxLayout = new QHBoxLayout(this);

    QGroupBox *Left_Table_Box = createRefMess();
    QGroupBox *Right_Table_Box = createMenu();

    HBoxLayout->addWidget(Left_Table_Box,4);
    HBoxLayout->addWidget(Right_Table_Box,2);
}
QGroupBox * visitor::createRefMess(){
    QGroupBox * box = new QGroupBox("文献信息");
    TableWidget = new QTableWidget;
    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    TableWidget->setColumnCount(6);
    TableWidget->setHorizontalHeaderLabels(QStringList() <<"DOI"<< "Author"<<"Title"<<"Journal"<<"Date"<<"Type");
    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    flushTable();//不能调用虚函数
    QHBoxLayout * AutoHBoxLayout = new QHBoxLayout;
    AutoHBoxLayout->addWidget(TableWidget);
    box->setLayout(AutoHBoxLayout);

    //当用户点击某个单元格时，更新列表中显示的文献信息
    connect(TableWidget,&QTableWidget::cellClicked,this,&visitor::flushListWidget);
    //当用户更改某个单元格内的内容时，调用 changeRefMess() 方法处理
    connect(TableWidget,&QTableWidget::cellChanged,this,&visitor::changeRefMess);
    //将用户更改某个单元格内的内容时，同时还要更新表格中显示的文献信息
    connect(TableWidget,&QTableWidget::cellChanged,this,&visitor::flushListWidget);
    return box;
}

QGroupBox * visitor::createMenu(){
    QGroupBox * box = new QGroupBox("功能面板");
    QVBoxLayout *VBoxLayout = new QVBoxLayout;

    ListWidget = new QListWidget;


    QGridLayout * Buts = new QGridLayout;



    ExitBtn = new QPushButton("退出");

    OpenBtn = new QPushButton("打开");
    FindRefEdit = new QLineEdit;
    FindRefEdit->setPlaceholderText("输入任意信息查找...");
    FindRefEdit->setClearButtonEnabled(true);
    FindRefEdit->setStyleSheet("QLineEdit{padding:3,3,3,3;}");
    Buts->addWidget(FindRefEdit,0,0,1,2);
    Buts->addWidget(OpenBtn,1,0);

    Buts->addWidget(ExitBtn,1,1);

    VBoxLayout->addWidget(ListWidget,4);
    VBoxLayout->addLayout(Buts,2);

    box->setLayout(VBoxLayout);

    //当向输入框内输入信息后，执行 findStuMess() 方法
    connect(FindRefEdit,&QLineEdit::returnPressed,this,&visitor::findRefMess);
    //点击退出按钮，关闭主窗口
    connect(ExitBtn,&QPushButton::clicked,this,&visitor::close);
    //打开文件方法openRefMess()
    connect(OpenBtn, &QPushButton::clicked, this, &visitor::openRefMess);

    return box;
}

void visitor::flushListWidget(int row){//这个地方row初始值就是0，不传参就是0
    //当列表中有信息时，直接修改即可
    if(ListWidget->count() > 0){
        ListWidget->item(0)->setText("DOI：" + TableWidget->item(row,0)->text());
        ListWidget->item(1)->setText("作者：" + TableWidget->item(row,1)->text());
        ListWidget->item(2)->setText("标题：" + TableWidget->item(row,2)->text());
        ListWidget->item(3)->setText("刊物：" + TableWidget->item(row,3)->text());
        ListWidget->item(4)->setText("日期：" + TableWidget->item(row,4)->text());
        ListWidget->item(5)->setText("类型：" + TableWidget->item(row,5)->text());

    }else{
        ListWidget->addItem("DOI：" + TableWidget->item(row,0)->text());
        ListWidget->addItem("作者：" + TableWidget->item(row,1)->text());
        ListWidget->addItem("标题：" + TableWidget->item(row,2)->text());
        ListWidget->addItem("刊物：" + TableWidget->item(row,3)->text());
        ListWidget->addItem("日期：" + TableWidget->item(row,4)->text());
        ListWidget->addItem("类型：" + TableWidget->item(row,5)->text());

    }
    /*
    ListWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
    for (int i = 0; i < ListWidget->count(); i++)
    {
        ListWidget->item(i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }*/
}



void visitor::flushTable(){
    //更新表格内容前，要断开与 cellChanged 信号关联的所有槽，否则会导致程序闪退
    disconnect(TableWidget,&QTableWidget::cellChanged,0,0);

    QString doi,author,title,journal,date,type;
    TableWidget->setRowCount(0);
    for(auto it = BOOKLIST->begin(); it!=BOOKLIST->end(); ++it){
        TableWidget->setRowCount(TableWidget->rowCount()+1);
        doi = QString::fromStdString(it->getDOI());
        author = QString::fromStdString(it->getAuthor());
        title = QString::fromStdString(it->getTitle());
        journal = QString::fromStdString(it->getJournal());
        date = QString::fromStdString(it->getDate());
        type = QString::fromStdString(it->getType());
        TableWidget->setItem(TableWidget->rowCount()-1,0,new QTableWidgetItem(doi));
        TableWidget->setItem(TableWidget->rowCount()-1,1,new QTableWidgetItem(author));
        TableWidget->setItem(TableWidget->rowCount()-1,2,new QTableWidgetItem(title));
        TableWidget->setItem(TableWidget->rowCount()-1,3,new QTableWidgetItem(journal));
        TableWidget->setItem(TableWidget->rowCount()-1,4,new QTableWidgetItem(date));
        TableWidget->setItem(TableWidget->rowCount()-1,5,new QTableWidgetItem(type));

    }

    //完成更新表格的任务后，重新关联与 cellChanged 相关的槽。
    connect(TableWidget,&QTableWidget::cellChanged,this,&visitor::changeRefMess);
    connect(TableWidget,&QTableWidget::cellChanged,this,&visitor::flushListWidget);
}

void visitor::findRefMess()
{
    //list<Reference>* listemp;
    if(FindRefEdit->text().isEmpty())
    {
        flushTable();
        return;
    }
    flushTable();
    qint32 count = TableWidget->rowCount();
    bool findSuccess = false;
    if(count>0)
    {
        list<Reference>* templist = new list<Reference>;
        Reference* temp;
        temp = new Reference;
        for(qint32 i=0;i<count;i++)//搜索所有信息的所有部分，类似二维数组，两层循环
        {
            for(qint32 j=0;j<6;j++)
            {
                QString source = TableWidget->item(i,j)->text();
                if(source.contains(FindRefEdit->text(),Qt::CaseInsensitive))
                {

                    findSuccess = true;
                    //TableWidget->selectRow(i);


                     qint32 k = 0;
                    for(auto it=BOOKLIST->begin(); it != BOOKLIST->end(); ++it)
                    {

                        if(i == k)
                         {
                            temp->setDOI(it->getDOI());
                            temp->setAuthor(it->getAuthor());
                            temp->setTitle(it->getTitle());
                            temp->setJournal(it->getJournal());
                            temp->setDate(it->getDate());
                            temp->setType(it->getType());
                            break;
                        }
                        k++;
                    }

                    templist->push_back(*temp);
                    break;

                }

            }
        }
        delete temp;
        if(findSuccess == false)
        {
            QMessageBox::information(this,"查找失败","当前表格中没有信息["+FindRefEdit->text()+"]");
            return;
        }
        list<Reference>* a;
        a = templist;
        templist=BOOKLIST;
        BOOKLIST = a;

        flushTable();
        flushListWidget(0);

        a = templist;
        templist=BOOKLIST;
        BOOKLIST = a;
        templist->clear();
        delete templist;

        return;
    }

}




void visitor::openRefMess()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开文献文件"), "./", tr("文献存储文件 (*.xml)"));
    //qDebug()<<fileName;
    RefFile openfile;
    if(fileName.isEmpty())
    {
        return;
    }

    RefFile::fileName = fileName.toStdString();
    BOOKLIST = openfile.formatReadFile();
    flushTable();
    QMessageBox::information(this,"信息","打开文件成功");
    return;
}
