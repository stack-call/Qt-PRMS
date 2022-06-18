#include <QMessageBox>
#include <list>
#include <QDebug>
#include <iostream>
#include <QString>
#include <QFileDialog>
#include <vector>
#include "admin.h"
#include "AddRefMessBox.h"
#include "Reference.h"
#include "RefFile.h"
#include "Config.h"

admin::admin()
{
    //setWindowIcon(QIcon(":/logo.ico"));
    setWindowTitle("个人文献管理系统");
    this->resize(1220,600);
    QHBoxLayout *HBoxLayout = new QHBoxLayout(this);

    QGroupBox *Left_Table_Box = createRefMess();
    QGroupBox *Right_Table_Box = createMenu();

    HBoxLayout->addWidget(Left_Table_Box,4);
    HBoxLayout->addWidget(Right_Table_Box,2);
}
QGroupBox * admin::createRefMess(){
    QGroupBox * box = new QGroupBox("文献信息");
    TableWidget = new QTableWidget;
    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    TableWidget->setColumnCount(6);
    TableWidget->setHorizontalHeaderLabels(QStringList() <<"DOI"<< "作者"<<"标题"<<"刊物"<<"日期"<<"类型");
    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    flushTable();//不能调用虚函数
    QHBoxLayout * AutoHBoxLayout = new QHBoxLayout;
    AutoHBoxLayout->addWidget(TableWidget);
    box->setLayout(AutoHBoxLayout);

    //当用户点击某个单元格时，更新列表中显示的文献信息
    connect(TableWidget,&QTableWidget::cellClicked,this,&admin::flushListWidget);
    //当用户更改某个单元格内的内容时，调用 changeRefMess() 方法处理

    //将用户更改某个单元格内的内容时，同时还要更新表格中显示的文献信息
    //connect(TableWidget,&QTableWidget::cellChanged,this,&admin::flushListWidget);
    return box;
}

QGroupBox * admin::createMenu(){
    QGroupBox * box = new QGroupBox("详细信息");
    QVBoxLayout *VBoxLayout = new QVBoxLayout;

    ListWidget = new QListWidget;


    QGridLayout * Buts = new QGridLayout;
    AddRefBtn = new QPushButton("添加");
    DelRefBtn = new QPushButton("删除");
    SaveBtn = new QPushButton("保存");
    ExitBtn = new QPushButton("退出");
    ModifyBtn = new QPushButton("编辑");
    OpenBtn = new QPushButton("打开");
    FindRefEdit = new QLineEdit;
    FindRefEdit->setPlaceholderText("输入任意信息查找...");
    FindRefEdit->setClearButtonEnabled(true);
    FindRefEdit->setStyleSheet("QLineEdit{padding:3,3,3,3;}");
    Buts->addWidget(FindRefEdit,0,0,1,2);
    Buts->addWidget(OpenBtn,1,0);
    Buts->addWidget(AddRefBtn,2,1);
    Buts->addWidget(DelRefBtn,1,1);

    Buts->addWidget(SaveBtn,2,0);
    Buts->addWidget(ExitBtn,3,1);
    Buts->addWidget(ModifyBtn,3,0);

    VBoxLayout->addWidget(ListWidget,4);
    VBoxLayout->addLayout(Buts,2);

    box->setLayout(VBoxLayout);
    //点击添加按钮，执行 addRefBox() 方法
    connect(AddRefBtn,&QPushButton::clicked,this,&admin::AddRefBox);
    //点击删除按钮，执行 delRefFun() 方法
    connect(DelRefBtn,&QPushButton::clicked,this,&admin::delRefFun);
    //当向输入框内输入信息后，执行 findRefMess() 方法
    connect(FindRefEdit,&QLineEdit::returnPressed,this,&admin::findRefMess);
    //点击退出按钮，关闭主窗口
    connect(ExitBtn,&QPushButton::clicked,this,&admin::ExitMess);
    //点击保存按钮，执行 saveRefMess() 方法
    connect(SaveBtn,&QPushButton::clicked,this,&admin::saveRefMess);
    //打开文件方法openRefMess()
    connect(OpenBtn, &QPushButton::clicked, this, &admin::openRefMess);
    //用户点击编辑后弹出提升，一个是通过单元格修改，一个是通过修改界面修改
    connect(ModifyBtn, &QPushButton::clicked, this, &admin::changeRefBox);
    return box;
}

void admin::flushListWidget(int row){//这个地方有点迷惑
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

void admin::delRefFun()
{
    QList<QTableWidgetItem*>items = TableWidget->selectedItems();
    //判断用户是否在表格中选中了某个文献信息，只有选中之后，才能执行删除操作
    if(items.count() > 0){
        QMessageBox::StandardButton result=QMessageBox::question(this, "删除","确定要删除文献DOI为【"+items.at(0)->text()+"】的文献吗？");
        if(result == QMessageBox::Yes)
        {
            for (auto it = BOOKLIST->begin(); it !=BOOKLIST->end(); ++it)
            {
                //qDebug()<<items.at(0)->text();
                if(QString::fromStdString(it->getDOI()) == items.at(0)->text())
                {
                    BOOKLIST->erase(it);
                    break;
                }
            }


            flushTable();
            ListWidget->clear();
        }
    }else{
        QMessageBox::warning(this,"提示","请选择要删除的文献");
    }
}

void admin::flushTable(){
    //更新表格内容前，要断开与 cellChanged 信号关联的所有槽，否则会导致程序闪退
    //disconnect(TableWidget,&QTableWidget::cellChanged,0,0);

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

   // connect(TableWidget,&QTableWidget::cellChanged,this,&admin::flushListWidget);
}

void admin::findRefMess()
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
        for(qint32 i=0;i<count;i++)
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

/*
void admin::changeRefMess(int row)
{
    QString Doiname = TableWidget->item(row,0)->text();
    int i = 0;
    for(auto it = BOOKLIST->begin(); it != BOOKLIST->end(); ++it)
    {
        if(i == row)
        {
            /*
            for(int j=0;j < TableWidget->columnCount();j++)
            {
                it->setDOI(TableWidget->item(row,j)->text().toStdString());
            }
            if(TableWidget->item(row,5)->text().toStdString() != "Review" && TableWidget->item(row,5)->text().toStdString() != "Article")
            {
                QMessageBox::information(this,"信息","文献格式错误["+TableWidget->item(row,5)->text()+"]");
            }
            it->setDOI(TableWidget->item(row,0)->text().toStdString());
            it->setAuthor(TableWidget->item(row,1)->text().toStdString());
            it->setTitle(TableWidget->item(row,2)->text().toStdString());
            it->setJournal(TableWidget->item(row,3)->text().toStdString());
            it->setDate(TableWidget->item(row,4)->text().toStdString());
            it->setType(TableWidget->item(row,5)->text().toStdString());
            break;
        }
        i++;
    }
    qDebug()<<Doiname;
    return;
}*/
void admin::saveRefMess()
{
    RefFile file;
    if(!file.formatStoreFile(BOOKLIST))
    {
        QMessageBox::warning(this,"警告","保存失败");
        return;
    }

    QMessageBox::information(this,"消息","保存成功");
    return;
}

void admin::openRefMess()
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
void admin::AddRefBox()
{
    addmessBox = new AddRefMessBox;
    //当添加文献信息窗口关闭时，更新表格，同时清空列表中显示的文献信息
    QObject::connect(addmessBox,&AddRefMessBox::closeBox,this,&admin::flushTable);
    QObject::connect(addmessBox,&AddRefMessBox::closeBox,ListWidget,&QListWidget::clear);
    addmessBox->exec();
    return;
}
void admin::changeRefBox()
{
    vector<string>* arraytemp = new vector<string>;
    QList<QTableWidgetItem*>items = TableWidget->selectedItems();
    qint32 a = items.count();
      if(items.count() > 0 )
      {
            for(int i=0;i < 6;i++)//或者写成6?
            {

                arraytemp->push_back(items.at(i)->text().toStdString());
            }

            changemessBox = new ModifyRefMessBox(arraytemp);
            //qDebug()<<11;
            QObject::connect(changemessBox,&ModifyRefMessBox::closeBox,this,&admin::flushTable);
            QObject::connect(changemessBox,&ModifyRefMessBox::closeBox,ListWidget,&QListWidget::clear);
            changemessBox->exec();
      }
      else
      {
            QMessageBox::information(this,"信息","请选择要修改的文献");
      }


    return;
}
void admin::ExitMess()
{
    QMessageBox::StandardButton result=QMessageBox::question(this, "退出","是否保存并退出");
    if(result == QMessageBox::Yes)
    {
        RefFile file;
        file.formatStoreFile(BOOKLIST);
        this->close();
    }
}
