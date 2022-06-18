#include <list>
//构建添加文献信息主界面
#include <QString>
#include <QDebug>
#include <iostream>
#include <QString>
#include "ModifyRefMessBox.h"
#include "Reference.h"
#include "Config.h"
#include "RefFile.h"
ModifyRefMessBox::ModifyRefMessBox(vector<string>* arrayptr)
{
    /*
     * QVBoxLayout 局部工具中放置 QFormLayout 和 QHBoxLayout
     * QFormLayout 中放置多个单行输入框
     * QHBoxLayout 中放置两个按钮
    */
    //setWindowIcon(QIcon(":/logo.ico"));
    setWindowFlags(Qt::Dialog);
    setWindowTitle("修改文献信息");
    QVBoxLayout * VBox = new QVBoxLayout;

    QFormLayout *FormLayout = new QFormLayout;

    DOI = new QLineEdit;
    Author = new QLineEdit;
    Title = new QLineEdit;
    Journal = new QLineEdit;
    Date = new QLineEdit;
    Type = new QLineEdit;

    DOI->setText(QString::fromStdString(arrayptr->at(0)));
    Author->setText(QString::fromStdString(arrayptr->at(1)));
    Title->setText(QString::fromStdString(arrayptr->at(2)));
    Journal->setText(QString::fromStdString(arrayptr->at(3)));
    Date->setText(QString::fromStdString(arrayptr->at(4)));
    Type->setText(QString::fromStdString(arrayptr->at(5)));

    ModifyDOI = QString::fromStdString(arrayptr->at(0));

    //qDebug()<< QString::fromStdString(arrayptr->at(0));

    //arrayptr->clear();
    //qDebug()<<12;
    FormLayout->addRow("DOI:",DOI);
    FormLayout->addRow("作者:",Author);
    FormLayout->addRow("标题:",Title);
    FormLayout->addRow("刊物:",Journal);
    FormLayout->addRow("年份:",Date);
    FormLayout->addRow("类型:",Type);

    FormLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);

    QHBoxLayout * HBox = new QHBoxLayout;
    submit = new QPushButton("提交");
    cancel = new QPushButton("取消");
    HBox->addWidget(submit);
    HBox->addWidget(cancel);

    VBox->addLayout(FormLayout,4);
    VBox->addLayout(HBox,1);
    this->setLayout(VBox);
    //点击提交按钮时，将新文献信息保存到文件中
    QObject::connect(submit,&QPushButton::clicked,this,&ModifyRefMessBox::saveRefMess);
    //点击取消按钮时，关闭添加文献信息窗口
    QObject::connect(cancel,&QPushButton::clicked,this,&ModifyRefMessBox::close);
}

//当用户添加提交按钮时，保存文献信息
void ModifyRefMessBox::saveRefMess(){
    //确保所有信息填写后，将信息写入到文件中，否则提示用户将信息填写完整
    if(this->DOI->text() !="" && this->Author->text()!="" && this->Title->text()!="" && this->Journal->text()!="" && this->Date->text()!="" && this->Type->text()!="")
    {

        for(auto it = BOOKLIST->begin();it!=BOOKLIST->end();++it)
        {
            if(this->DOI->text().toStdString() == it->getDOI() && this->DOI->text() != this->ModifyDOI)
            {
                QMessageBox::warning(this,"提示","文献DOI重复",QMessageBox::Ok);
                return;
            }
        }
        if(this->Type->text().toStdString() != "Article" && this->Type->text().toStdString() != "Review")
        {
            QMessageBox::warning(this,"提示","文献类型错误",QMessageBox::Ok);
            return;
        }
        for(auto it = BOOKLIST->begin(); it != BOOKLIST->end(); ++it)
        {
            if(ModifyDOI == QString::fromStdString(it->getDOI()))
            {
                it->setDOI(this->DOI->text().toStdString());
                it->setAuthor(this->Author->text().toStdString());
                it->setTitle(this->Title->text().toStdString());
                it->setJournal(this->Journal->text().toStdString());
                it->setDate(this->Date->text().toStdString());
                it->setType(this->Type->text().toStdString());
            }
        }


        this->close();
        emitCloseBox();
    }else{
        QMessageBox::warning(this,"提示","请将信息填写完整",QMessageBox::Ok);
    }

}

void ModifyRefMessBox::emitCloseBox(){
    emit closeBox();
}
