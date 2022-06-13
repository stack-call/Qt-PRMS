#ifndef REFERENCE_H
#define REFERENCE_H

#include <QString>
#include <string>
using namespace std;

class Reference
{
public:
    string getDOI() const;
    void setDOI(const string &value);

    string getAuthor() const;
    void setAuthor(const string &value);

    string getTitle() const;
    void setTitle(const string &value);

    string getJournal() const;
    void setJournal(const string &value);

    string getDate() const;
    void setDate(const string &value);

    string getType() const;
    void setType(const string &value);//可以用枚举

private:
    string DOI;
    string Author;
    string Title;
    string Journal;
    string Date;
    string Type;
};

#endif // REFERENCE_H
