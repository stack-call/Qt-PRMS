#ifndef REFFILE_H
#define REFFILE_H

#include <string>
#include <fstream>
#include <list>
#include "tinyXML/tinyxml.h"
#include "Reference.h"

using namespace std;

class RefFile
{
public:
    RefFile();

    list<Reference>* formatReadFile(const string& szFileName);
    bool formatStoreFile(list<Reference>* bookList);
    static list<Reference>* bookList;
private:
    void build_one_book(TiXmlElement* parent, Reference* target);

};


#endif // REFFILE_H
