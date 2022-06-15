#include <iostream>
#include <QMessageBox>
#include <QDebug>
#include <cstring>

#include "RefFile.h"
#include "tinyXML/tinyxml.h"



list<Reference>* RefFile::bookList = nullptr;
string RefFile::fileName = "database.xml";

RefFile::RefFile()
{

}

list<Reference>* RefFile::formatReadFile()
{
    try
    {
        // 创建一个XML的文档对象。
        TiXmlDocument *xmlDocument = new TiXmlDocument;
        // 解析
/*
        if(!xmlDocument->LoadFile(szFileName.c_str()))
        {
            qDebug()<<"加载XML文件失败";
            const char *errorStr = xmlDocument->ErrorDesc();
            if(strcmp(errorStr, "Failed to open file"))
            {
                QMessageBox::warning(NULL, QMessageBox::tr("警告"),QMessageBox::tr("打开XML文件失败!请检查文件格式是否为文献XML文件"),QMessageBox::Yes);
            }
            else if(strcmp(errorStr, "Error document empty."))
            {
                list<Reference> *BOOKLIST = new list<Reference>;
                return BOOKLIST;
            }
            qDebug()<<errorStr; //打印失败原因；
        }
*/

        if(!xmlDocument->LoadFile(fileName.c_str()))
        {
            qDebug()<<"加载XML文件失败";
            const char *errorStr = xmlDocument->ErrorDesc();
            qDebug()<<errorStr; //打印失败原因；

            QMessageBox::warning(NULL, QMessageBox::tr("警告 "),QMessageBox::tr("不是文献XML格式文件"),QMessageBox::Yes);

            list<Reference> *bookList = new list<Reference>;
            //bool a = bookList->empty();
            //qDebug()<<a;
            return bookList;


        }

        // 获得根元素
        TiXmlElement *rootElement = xmlDocument->RootElement();

        // 输出根元素名称
        qDebug() << rootElement->Value();
        // 获得第一个节点。
        //TiXmlElement *firstElement = rootElement->FirstChildElement();
        // 获得第一个Person的name节点和age节点和ID属性。
        //TiXmlElement *nameElement = firstElement->FirstChildElement();
       // TiXmlElement *priceElement = nameElement->NextSiblingElement();
       // TiXmlAttribute *IDAttribute = firstElement->FirstAttribute();
        //TiXmlElement *priceElement = rootElement->NextSiblingElement();
        //TiXmlAttribute *dsAttribute = pricetElement->FirstAttribute();
        list<Reference> *bookList = new list<Reference>;
        Reference* temp = new Reference;
       for(TiXmlElement* p_node=rootElement->FirstChildElement();p_node;p_node=p_node->NextSiblingElement())
       {

            /*for(TiXmlElement* c_node=p_node->FirstChildElement();c_node;c_node=c_node->NextSiblingElement())
            {
                cout<<c_node->FirstAttribute()->Value()<<endl;

            }*/
            TiXmlElement* c_node=p_node->FirstChildElement();
            cout<<c_node->FirstAttribute()->Value()<<endl;
            temp->setDOI(c_node->FirstAttribute()->Value());

            c_node=c_node->NextSiblingElement();
            cout<<c_node->FirstAttribute()->Value()<<endl;
            temp->setAuthor(c_node->FirstAttribute()->Value());

            c_node=c_node->NextSiblingElement();
            cout<<c_node->FirstAttribute()->Value()<<endl;
            temp->setTitle(c_node->FirstAttribute()->Value());

            c_node=c_node->NextSiblingElement();
            cout<<c_node->FirstAttribute()->Value()<<endl;
            temp->setJournal(c_node->FirstAttribute()->Value());

            c_node=c_node->NextSiblingElement();
            cout<<c_node->FirstAttribute()->Value()<<endl;
            temp->setDate(c_node->FirstAttribute()->Value());

            c_node=c_node->NextSiblingElement();
            cout<<c_node->FirstAttribute()->Value()<<endl;
            temp->setType(c_node->FirstAttribute()->Value());
            bookList->push_back(*temp);
       }
       delete temp;
       qDebug()<<bookList->size();
       return bookList;
        // 输出
        //std::cout << firstElement->FirstChild()->Value() << std::endl;
        //std::cout << priceElement->FirstChild()->Value() << std::endl;
        //std::cout << IDAttribute->Value() << std::endl;
       // std::cout << dsAttribute->Value() << std::endl;

    }
    catch (...)
    {
        return nullptr;
    }
}

void RefFile::build_one_book(TiXmlElement* parent, Reference* target)
{
        string temp;
        temp=target->getDOI();
        TiXmlElement * element = new TiXmlElement("Info");
        element->SetAttribute("DOI",temp.c_str());
        parent->LinkEndChild(element);

        temp=target->getAuthor();
        element = new TiXmlElement("Info");
        element->SetAttribute("Author",temp.c_str());
        parent->LinkEndChild(element);

        temp=target->getTitle();
        element = new TiXmlElement("Info");
        element->SetAttribute("Title",temp.c_str());
        parent->LinkEndChild(element);

        temp=target->getJournal();
        element = new TiXmlElement("Info");
        element->SetAttribute("Journal",temp.c_str());
        parent->LinkEndChild(element);

        temp=target->getDate();
        element = new TiXmlElement("Info");
        element->SetAttribute("Date",temp.c_str());
        parent->LinkEndChild(element);

        temp=target->getType();
        element = new TiXmlElement("Info");
        element->SetAttribute("Type",temp.c_str());
        parent->LinkEndChild(element);
}

bool RefFile::formatStoreFile(list<Reference>* boolList)
{
    TiXmlDocument doc;
    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    TiXmlElement * element = new TiXmlElement( "Reference" );

    Reference temp;

    for(auto it = bookList->begin(); it != bookList->end(); it++)
    {
        TiXmlElement * book = new TiXmlElement( "book" );
        temp.setDOI(it->getDOI());
        temp.setAuthor(it->getAuthor());
        temp.setTitle(it->getTitle());
        temp.setJournal(it->getJournal());
        temp.setDate(it->getDate());
        temp.setType(it->getType());
        element->LinkEndChild(book);
        build_one_book(book, &temp);
    }
    /*
    TiXmlElement * book2 = new TiXmlElement( "book2" );
    Reference ref1;
    ref1.setDOI("DOI1");
    ref1.setAuthor("Author1");
    ref1.setTitle("Title1");
    ref1.setJournal("Journal1");
    ref1.setDate("Date1");
    ref1.setType("Type1");
    element->LinkEndChild(book2);
    build_one_book(book2, &ref1);
*/
    doc.LinkEndChild( decl );
    doc.LinkEndChild( element );
    doc.SaveFile( fileName.c_str() );
    return true;
}
