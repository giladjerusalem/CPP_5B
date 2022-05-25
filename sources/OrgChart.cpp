#include <string>
#include <iostream>
#include "OrgChart.hpp"

using namespace std;

namespace ariel{
OrgChart::OrgChart()
{}
OrgChart & OrgChart::add_root(string str)
{
    return *this;
}
OrgChart & OrgChart::add_sub(string f, string c)
{
    return *this;
}
OrgChart::iterator OrgChart::begin()
{
    return iterator(this);
}
OrgChart::iterator OrgChart::end()
{
    return iterator(this);
}
OrgChart::iterator OrgChart::begin_level_order()
{
    return iterator(this);
}
OrgChart::iterator OrgChart::begin_preorder()
{
    return iterator(this);
}
OrgChart::iterator OrgChart::begin_reverse_order()
{
    return iterator(this);
}
OrgChart::iterator OrgChart::end_level_order()
{
    return iterator(this);
}
OrgChart::iterator OrgChart::end_preorder()
{
    return iterator(this);
}
OrgChart::iterator OrgChart::reverse_order()
{
    return iterator(this);
}
OrgChart::iterator::iterator(OrgChart * cur)
{}

OrgChart::iterator & OrgChart::iterator::operator++()
{
    return *this;
}
OrgChart::iterator & OrgChart::iterator::operator++(int)
{
    return *this;
}
string OrgChart::iterator::operator*()
{
    return " ";
}
bool OrgChart::iterator::operator!=(OrgChart::iterator iterat)
{
    return false;
}
string * OrgChart::iterator::operator->()
{
    return (&(this->cur)->name);
}
std::ostream & operator<<(std::ostream & stream, OrgChart const & chart)
{
    return stream;
}
}