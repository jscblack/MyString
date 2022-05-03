#include "MyString.h"
#include "MyStringstream.h"
iMyStringstream &iMyStringstream::operator>>(MyString &str)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    while (pos < s.length() && s[pos] != ' ' && s[pos] != '\n' && s[pos] != '\r')
        str += s[pos++];
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(char &ch)
{
    ch = s[pos];
    pos++;
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(char *str)
{
    MyString tmp;
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    while (pos < s.length() && s[pos] != ' ' && s[pos] != '\n' && s[pos] != '\r')
        str += s[pos++];
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    strcpy(str, tmp.c_str());
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(int &n)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    // check negative or positive

    bool negative = false;
    if (s[pos] == '-')
    {
        negative = true;
        pos++;
    }
    n = 0;
    while (pos < s.size() && isdigit(s[pos]))
    {
        n = n * 10 + s[pos] - '0';
        pos++;
    }
    if (negative)
        n = -n;
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(long long &n)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    // check negative or positive
    bool negative = false;
    if (s[pos] == '-')
    {
        negative = true;
        pos++;
    }
    n = 0;
    while (pos < s.size() && isdigit(s[pos]))
    {
        n = n * 10 + s[pos] - '0';
        pos++;
    }
    if (negative)
        n = -n;
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(unsigned &n)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    n = 0;
    while (pos < s.size() && isdigit(s[pos]))
    {
        n = n * 10 + s[pos] - '0';
        pos++;
    }
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(unsigned long &n)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    n = 0;
    while (pos < s.size() && isdigit(s[pos]))
    {
        n = n * 10 + s[pos] - '0';
        pos++;
    }
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(unsigned long long &n)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    n = 0;
    while (pos < s.size() && isdigit(s[pos]))
    {
        n = n * 10 + s[pos] - '0';
        pos++;
    }
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(float &n)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    // check negative or positive
    bool negative = false;
    if (s[pos] == '-')
    {
        negative = true;
        pos++;
    }
    n = 0;
    while (pos < s.size() && isdigit(s[pos]))
    {
        n = n * 10 + s[pos] - '0';
        pos++;
    }
    if (s[pos] == '.')
    {
        pos++;
        float m = 0.1;
        while (pos < s.size() && isdigit(s[pos]))
        {
            n += (s[pos] - '0') * m;
            m *= 0.1;
            pos++;
        }
    }
    if (negative)
        n = -n;
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(double &n)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    // check negative or positive
    bool negative = false;
    if (s[pos] == '-')
    {
        negative = true;
        pos++;
    }
    n = 0;
    while (pos < s.size() && isdigit(s[pos]))
    {
        n = n * 10 + s[pos] - '0';
        pos++;
    }
    if (s[pos] == '.')
    {
        pos++;
        float m = 0.1;
        while (pos < s.size() && isdigit(s[pos]))
        {
            n += (s[pos] - '0') * m;
            m *= 0.1;
            pos++;
        }
    }
    if (negative)
        n = -n;
    return *this;
}
iMyStringstream &iMyStringstream::operator>>(long double &n)
{
    while (pos < s.length() && (s[pos] == ' ' || s[pos] == '\n' || s[pos] == '\r'))
        pos++;
    // check negative or positive
    bool negative = false;
    if (s[pos] == '-')
    {
        negative = true;
        pos++;
    }
    n = 0;
    while (pos < s.size() && isdigit(s[pos]))
    {
        n = n * 10 + s[pos] - '0';
        pos++;
    }
    if (s[pos] == '.')
    {
        pos++;
        float m = 0.1;
        while (pos < s.size() && isdigit(s[pos]))
        {
            n += (s[pos] - '0') * m;
            m *= 0.1;
            pos++;
        }
    }
    if (negative)
        n = -n;
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const MyString &str)
{
    s += str;
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const char *str)
{
    s += str;
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const char &ch)
{
    s += ch;
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const int &n)
{
    s += MyString::to_string(n);
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const long long &n)
{
    s += MyString::to_string(n);
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const unsigned &n)
{
    s += MyString::to_string(n);
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const unsigned long &n)
{
    s += MyString::to_string(n);
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const unsigned long long &n)
{
    s += MyString::to_string(n);
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const float &n)
{
    s += MyString::to_string(n);
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const double &n)
{
    s += MyString::to_string(n);
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(const long double &n)
{
    s += MyString::to_string(n);
    return *this;
}
oMyStringstream &oMyStringstream::operator<<(oMyStringstream &(*op)(oMyStringstream &))
{
    return op(*this);
}
MyString oMyStringstream::str()
{
    return s;
}
oMyStringstream &oMyStringstream::endl(oMyStringstream &s)
{
    s << "\n";
    return s;
}