#include "Reference.h"

string Reference::getDOI() const
{
    return DOI;
}

void Reference::setDOI(const string &value)
{
    DOI=value;
}

string Reference::getAuthor() const
{
    return Author;
}

void Reference::setAuthor(const string &value)
{
    Author=value;
}

string Reference::getTitle() const
{
    return Title;
}

void Reference::setTitle(const string &value)
{
    Title=value;
}

string Reference::getJournal() const
{
    return Journal;
}

void Reference::setJournal(const string &value)
{
    Journal=value;
}

string Reference::getDate() const
{
    return Date;
}

void Reference::setDate(const string &value)
{
    Date=value;
}

string Reference::getType() const
{
    return Type;
}

void Reference::setType(const string &value)
{
    Type=value;
}
