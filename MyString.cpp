/*
 * @Author       : Gehrychiang
 * @LastEditTime : 2022-05-03 12:16:49
 * @Website      : www.yilantingfeng.site
 * @E-mail       : gehrychiang@aliyun.com
 */
#include "MyString.h"
MyString::MyString()
{
    capacity = 64;
    str = new char[capacity];
    str[0] = '\0';
    len = 0;
}
MyString::MyString(const char *s, size_t pos, size_t n)
{
    len = strlen(s);
    __limit(pos, n, len);
    capacity = 1;
    while (capacity <= len + 1)
        capacity <<= 1;
    str = new char[capacity];
    strcpy(str, s + pos);
    str[n] = '\0';
}
MyString::MyString(size_t n, char c)
{
    len = n;
    capacity = 1;
    while (capacity <= len + 1)
        capacity <<= 1;
    str = new char[capacity];
    for (size_t i = 0; i < n; i++)
        str[i] = c;
    str[n] = '\0';
}
MyString::MyString(const MyString &s)
{
    len = s.len;
    capacity = s.capacity;
    str = new char[capacity];
    strcpy(str, s.str);
}
MyString::~MyString()
{
    if (str)
        delete[] str;
}
void MyString::operator=(const MyString &s)
{
    if (this == &s)
        return;
    if (str)
        delete[] str;
    len = s.len;
    capacity = s.capacity;
    str = new char[capacity];
    strcpy(str, s.str);
}
void MyString::operator=(const char *s)
{
    if (str)
        delete[] str;
    len = strlen(s);
    capacity = 1;
    while (capacity <= len + 1)
        capacity <<= 1;
    str = new char[capacity];
    strcpy(str, s);
}
void MyString::operator=(char c)
{
    if (str)
        delete[] str;
    len = 1;
    capacity = 1;
    while (capacity <= len + 1)
        capacity <<= 1;
    str = new char[capacity];
    str[0] = c;
    str[1] = '\0';
}

MyString &MyString::assign(const MyString &s, size_t pos, size_t n)
{
    if (this == &s)
        return *this;
    if (str)
        delete[] str;
    len = s.len;
    __limit(pos, n, len);
    capacity = 1;
    while (capacity <= n + 1)
        capacity <<= 1;
    str = new char[capacity];
    strncpy(str, s.str + pos, n);
    str[n] = '\0';
    return *this;
}
MyString &MyString::assign(const char *s, size_t pos, size_t n)
{
    if (str)
        delete[] str;
    len = strlen(s);
    __limit(pos, n, len);
    capacity = 1;
    while (capacity <= n + 1)
        capacity <<= 1;
    str = new char[capacity];
    strncpy(str, s + pos, n);
    str[n] = '\0';
    return *this;
}
MyString &MyString::assign(size_t n, char c)
{
    if (str)
        delete[] str;
    len = n;
    capacity = 1;
    while (capacity <= n + 1)
        capacity <<= 1;
    str = new char[capacity];
    for (size_t i = 0; i < n; i++)
        str[i] = c;
    str[n] = '\0';
    return *this;
}
size_t MyString::length() const { return len; }
size_t MyString::size() const { return len; }
char &MyString::operator[](size_t pos) { return str[pos]; }
char &MyString::at(size_t pos) { return str[pos]; }
const char *MyString::c_str() const { return (const char *)str; }
MyString &MyString::append(const MyString &s, size_t pos, size_t n)
{
    __limit(pos, n, s.len);
    while (capacity <= len + n + 1)
        capacity <<= 1;

    char *tmp = new char[len];
    strcpy(tmp, str);
    delete[] str;
    str = new char[capacity];
    strcpy(str, tmp);
    strncpy(str + len, s.str + pos, n);
    str[len + n] = '\0';
    len += n;
    delete[] tmp;
    return *this;
}
MyString &MyString::append(const char *s, size_t pos, size_t n)
{
    __limit(pos, n, strlen(s));
    while (capacity <= len + n + 1)
        capacity <<= 1;
    char *tmp = new char[len];
    strcpy(tmp, str);
    delete[] str;
    str = new char[capacity];
    strcpy(str, tmp);
    strncpy(str + len, s + pos, n);
    str[len + n] = '\0';
    len += n;
    delete[] tmp;
    return *this;
}
MyString &MyString::append(size_t n, char c)
{
    while (capacity <= len + n + 1)
        capacity <<= 1;
    char *tmp = new char[capacity];
    strcpy(tmp, str);
    for (size_t i = len; i < len + n; i++)
        tmp[i] = c;
    tmp[len + n] = '\0';
    if (str)
        delete[] str;
    str = tmp;
    len += n;
    return *this;
}
MyString &MyString::operator+=(const MyString &s) { return append(s); }
MyString &MyString::operator+=(const char *s) { return append(s); }
MyString &MyString::operator+=(char c) { return append(1, c); }
MyString MyString::operator+(const MyString &s) const
{
    MyString tmp(*this);
    return tmp.append(s);
}
MyString MyString::operator+(const char *s) const
{
    MyString tmp(*this);
    return tmp.append(s);
}
MyString MyString::operator+(char c) const
{
    MyString tmp(*this);
    return tmp.append(1, c);
}

bool MyString::operator==(const MyString &s) const
{
    if (len != s.len)
        return false;
    return strcmp(str, s.str) == 0;
}
bool MyString::operator==(const char *s) const
{
    if (len != strlen(s))
        return false;
    return strcmp(str, s) == 0;
}
bool MyString::operator!=(const MyString &s) const
{
    if (len != s.len)
        return true;
    return strcmp(str, s.str) != 0;
}
bool MyString::operator!=(const char *s) const
{
    if (len != strlen(s))
        return true;
    return strcmp(str, s) != 0;
}
bool MyString::operator<(const MyString &s) const
{
    return strcmp(str, s.str) < 0;
}
bool MyString::operator<(const char *s) const { return strcmp(str, s) < 0; }
bool MyString::operator>(const MyString &s) const
{
    return strcmp(str, s.str) > 0;
}
bool MyString::operator>(const char *s) const { return strcmp(str, s) > 0; }
bool MyString::operator<=(const MyString &s) const
{
    return strcmp(str, s.str) <= 0;
}
bool MyString::operator<=(const char *s) const { return strcmp(str, s) <= 0; }
bool MyString::operator>=(const MyString &s) const
{
    return strcmp(str, s.str) >= 0;
}
bool MyString::operator>=(const char *s) const { return strcmp(str, s) >= 0; }

MyString MyString::substr(size_t pos, size_t n) const
{
    __limit(pos, n, len);
    MyString s(n, '\0');
    strncpy(s.str, str + pos, n);
    s.len = n;
    return s;
}

MyString &MyString::swap(MyString &s)
{
    char *tmp = str;
    str = s.str;
    s.str = tmp;
    size_t tmp2 = len;
    len = s.len;
    s.len = tmp2;
    size_t tmp3 = capacity;
    capacity = s.capacity;
    s.capacity = tmp3;
    return *this;
}

int MyString::compare(const MyString &s) const 
{
    int res = strcmp(str, s.str); 
    if(res < 0)
        return -1;
    else if(res > 0)
        return 1;
    else
        return 0;
 }
int MyString::compare(const char *s) const
{
    int res = strcmp(str, s); 
    if(res < 0)
        return -1;
    else if(res > 0)
        return 1;
    else
        return 0;
}
int MyString::compare(size_t pos, size_t n, const MyString &s, size_t pos2, size_t n2) const
{
    __limit(pos, n, len);
    __limit(pos2, n2, s.len);
    int ret;
    ret = strncmp(str + pos, s.str + pos2, std::min(n, n2));
    if (ret == 0)
        ret = __compare(n, n2);
    if(ret < 0)
        return -1;
    else if(ret > 0)
        return 1;
    else
        return 0;
}
int MyString::compare(size_t pos, size_t n, const char *s, size_t pos2, size_t n2) const
{
    __limit(pos, n, len);
    __limit(pos2, n2, strlen(s));
    int ret;
    ret = strncmp(str + pos, s + pos2, std::min(n, n2));
    if (ret == 0)
        ret = __compare(n, n2);
    if(ret < 0)
        return -1;
    else if(ret > 0)
        return 1;
    else
        return 0;
}

MyString &MyString::replace(size_t pos, size_t n, const MyString &s, size_t pos2, size_t n2)
{
    __limit(pos, n, len);
    __limit(pos2, n2, s.len);
    while (capacity <= len + n2 - n + 1)
        capacity <<= 1;
    char *tmp = new char[capacity];
    strcpy(tmp, str);
    delete[] str;
    str = new char[capacity];
    strncpy(str, tmp, pos);
    strncpy(str + pos, s.str + pos2, n2);
    strncpy(str + pos + n2, tmp + pos + n, len - pos - n);
    str[len + n2 - n] = '\0';
    len += n2 - n;
    delete[] tmp;
    return *this;
}
MyString &MyString::replace(size_t pos, size_t n, const char *s, size_t pos2, size_t n2)
{
    __limit(pos, n, len);
    __limit(pos2, n2, strlen(s));
    while (capacity <= len + n2 - n + 1)
        capacity <<= 1;
    char *tmp = new char[capacity];
    strcpy(tmp, str);
    delete[] str;
    str = new char[capacity];
    strncpy(str, tmp, pos);
    strncpy(str + pos, s + pos2, n2);
    strncpy(str + pos + n2, tmp + pos + n, len - pos - n);
    str[len + n2 - n] = '\0';
    len += n2 - n;
    delete[] tmp;
    return *this;
}
MyString &MyString::replace(size_t pos, size_t n, size_t n2, char c)
{
    __limit(pos, n, len);
    while (capacity <= len + n2 - n + 1)
        capacity <<= 1;
    char *tmp = new char[capacity];
    strcpy(tmp, str);
    delete[] str;
    str = new char[capacity];
    strncpy(str, tmp, pos);
    for (size_t i = 0; i < n2; i++)
        str[pos + i] = c;
    strncpy(str + pos + n2, tmp + pos + n, len - pos - n);
    str[len + n2 - n] = '\0';
    len += n2 - n;
    delete[] tmp;
    return *this;
}

MyString &MyString::erase(size_t pos, size_t n)
{
    return replace(pos, n, "", 0, 0);
}

void MyString::clear()
{
    delete[] str;
    capacity = 64;
    str = new char[capacity];
    str[0] = '\0';
    len = 0;
}

MyString &MyString::insert(size_t pos, const MyString &s, size_t pos2, size_t n2)
{
    return replace(pos, 0, s, pos2, n2);
}
MyString &MyString::insert(size_t pos, const char *s, size_t pos2, size_t n2)
{
    return replace(pos, 0, s, pos2, n2);
}
MyString &MyString::insert(size_t pos, size_t n, char c)
{
    return replace(pos, 0, n, c);
}

size_t MyString::find(const MyString &s, size_t pos) const
{
    __limit(pos, len);
    char *i = strstr(str + pos, s.str);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::find(const char *s, size_t pos) const
{
    __limit(pos, len);
    char *i = strstr(str + pos, s);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::find(char c, size_t pos) const
{
    __limit(pos, len);
    char *i = strchr(str + pos, c);
    if (i == NULL)
        return npos;
    return i - str;
}

size_t MyString::rfind(const MyString &s, size_t pos) const
{
    __limit(pos, len);
    char *i = strrstr(str + pos, s.str);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::rfind(const char *s, size_t pos) const
{
    __limit(pos, len);
    char *i = strrstr(str + pos, s);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::rfind(char c, size_t pos) const
{
    __limit(pos, len);
    char *i = strrchr(str + pos, c);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::find_first_of(char c, size_t pos) const
{
    __limit(pos, len);
    char *i = strchr(str + pos, c);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::find_first_of(const MyString &s, size_t pos) const
{
    __limit(pos, len);
    char *i = strpbrk(str + pos, s.str);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::find_first_of(const char *s, size_t pos) const
{
    __limit(pos, len);
    char *i = strpbrk(str + pos, s);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::find_last_of(char c, size_t pos) const
{
    __limit(pos, len);
    char *i = strrchr(str + pos, c);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::find_last_of(const MyString &s, size_t pos) const
{
    __limit(pos, len);
    char *i = strrpbrk(str + pos, s.str);
    if (i == NULL)
        return npos;
    return i - str;
}
size_t MyString::find_last_of(const char *s, size_t pos) const
{
    __limit(pos, len);
    char *i = strrpbrk(str + pos, s);
    if (i == NULL)
        return npos;
    return i - str;
}

size_t MyString::find_first_not_of(char c, size_t pos) const
{
    __limit(pos, len);
    size_t i = strspn(str + pos, &c);
    i += pos;
    if (i == len)
        return npos;
    return i;
}
size_t MyString::find_first_not_of(const MyString &s, size_t pos) const
{
    __limit(pos, len);
    size_t i = strspn(str + pos, s.str);
    i += pos;
    if (i == len)
        return npos;
    return i;
}
size_t MyString::find_first_not_of(const char *s, size_t pos) const
{
    __limit(pos, len);
    size_t i = strspn(str + pos, s);
    i += pos;
    if (i == len)
        return npos;
    return i;
}
size_t MyString::find_last_not_of(char c, size_t pos) const
{
    __limit(pos, len);
    size_t i = strcspn(str + pos, &c);
    i += pos;
    if (i == len)
        return npos;
    return i;
}
size_t MyString::find_last_not_of(const MyString &s, size_t pos) const
{
    __limit(pos, len);
    size_t i = strrspn(str + pos, s.str);
    i += pos;
    if (i == len)
        return npos;
    return i;
}
size_t MyString::find_last_not_of(const char *s, size_t pos) const
{
    __limit(pos, len);
    size_t i = strrspn(str + pos, s);
    i += pos;
    if (i == len)
        return npos;
    return i;
}
MyString::iterator MyString::begin()
{
    return iterator(str);
}
MyString::iterator MyString::end()
{
    return iterator(str + len);
}
MyString::const_iterator MyString::cbegin() const
{
    return const_iterator(str);
}
MyString::const_iterator MyString::cend() const
{
    return const_iterator(str + len);
}
MyString MyString::to_string(int n)
{
    char buf[64];
    sprintf(buf, "%d", n);
    MyString s(buf);
    return s;
}
MyString MyString::to_string(long long n)
{
    char buf[64];
    sprintf(buf, "%lld", n);
    MyString s(buf);
    return s;
}
MyString MyString::to_string(unsigned n)
{
    char buf[64];
    sprintf(buf, "%u", n);
    MyString s(buf);
    return s;
}
MyString MyString::to_string(unsigned long n)
{
    char buf[64];
    sprintf(buf, "%lu", n);
    MyString s(buf);
    return s;
}
MyString MyString::to_string(unsigned long long n)
{
    char buf[64];
    sprintf(buf, "%llu", n);
    MyString s(buf);
    return s;
}
MyString MyString::to_string(float n)
{
    char buf[64];
    sprintf(buf, "%g", n);
    MyString s(buf);
    return s;
}
MyString MyString::to_string(double n)
{
    char buf[64];
    sprintf(buf, "%g", n);
    MyString s(buf);
    return s;
}
MyString MyString::to_string(long double n)
{
    char buf[64];
    sprintf(buf, "%Lg", n);
    MyString s(buf);
    return s;
}