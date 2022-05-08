#include <iostream>

#define _SELECT
//如果完成了选做内容，请将此宏_SELECT定义前的注释符号删除
// #include <cstring> 不使用!!!

#ifndef  _SELECT
#include <string>
#include <sstream>
#endif

using namespace std;
// 请将完成的所有代码粘贴在此处，包括类的声明和所有定义 ,并注释掉下面一行语句
// typedef string MyString;
//测试时请注释掉上面一行语句
/*
 * @Author       : Gehrychiang
 * @LastEditTime : 2022-05-01 11:45:18
 * @Website      : www.yilantingfeng.site
 * @E-mail       : gehrychiang@aliyun.com
 */
void *memcpy(void *dest,const void* src,size_t n)
{
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}
static size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}
static void strcpy(char *dest, const char *src)
{
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
}
static void strncpy(char *dest, const char *src, size_t n)
{
    while (n--)
        *dest++ = *src++;
    *dest = '\0';
}
class MyString
{
    char *str;
    size_t len;
    size_t capacity;
    // static zone
    static const size_t __pos = 0ULL; // default begin position
    static void __limit(size_t &pos, size_t len)
    {
        if (pos > len)
            pos = len;
    }
    static void __limit(size_t &pos, size_t &n, size_t len)
    {
        if (pos > len)
            pos = len;
        if (n == npos || n > len - pos)
            n = len - pos;
    }
    static int __compare(const size_t a, const size_t b)
    {
        return a - b;
    }
    //cstring self-implment
    static void strcat(char *dest, const char *src)
    {
        while (*dest)
            dest++;
        while (*src)
            *dest++ = *src++;
        *dest = '\0';
    }
    static int strcmp(const char *a, const char *b)
    {
        while (*a && *b && *a == *b)
        {
            a++;
            b++;
        }
        return *a - *b;

    }
    static int strncmp(const char *a, const char *b, size_t n)
    {
        while (*a && *b && *a == *b && n--)
        {
            a++;
            b++;
        }
        if(n)
            return *a - *b;
        else
            return 0;
    }
    static char *strchr(char *str, int c)
    {
        while (*str && *str != c)
            str++;
        return *str ? str : NULL;
    }
    static char *strchr(const char *str, int c)
    {
        while (*str && *str != c)
            str++;
        return *str ? (char *)str : NULL;
    }
    static char *strrchr(char *str, int c)
    {
        char *p = NULL;
        while (*str)
        {
            if (*str == c)
                p = str;
            str++;
        }
        return p;
    }
    static char *strstr(char *str,const char *sub)
    {
        //find substring
        size_t len = strlen(sub);
        while (*str)
        {
            if (!strncmp(str, sub, len))
                return str;
            str++;
        }
        return NULL;
    }
    static char *strpbrk(char *str,const char *set)
    {
        while (*str)
        {
            if (strchr(set, *str))
                return str;
            str++;
        }
        return NULL;
    }
    static size_t strspn(const char *str, const char *set)
    {
        size_t n = 0;
        while (*str)
        {
            if (!strchr(set, *str))
                return n;
            str++;
            n++;
        }
        return n;
    }
    static size_t strcspn(const char *str, const char *set)
    {
        size_t n = 0;
        while (*str)
        {
            if (strchr(set, *str))
                return n;
            str++;
            n++;
        }
        return n;
    }
    // originate from strstr
    static char *strrstr(char *s1, const char *s2) // find the last occurrence of s2 in s1 using STRSTR
    {
        char *_s1 = new char[strlen(s1) + 1];
        strcpy(_s1, s1);
        for (size_t i = 0, j = strlen(_s1) - 1; i < j; i++, j--)
        {
            _s1[i] = _s1[i] ^ _s1[j];
            _s1[j] = _s1[i] ^ _s1[j];
            _s1[i] = _s1[i] ^ _s1[j];
        }
        char *_s2 = new char[strlen(s2) + 1];
        strcpy(_s2, s2);
        for (size_t i = 0, j = strlen(_s2) - 1; i < j; i++, j--)
        {
            _s2[i] = _s2[i] ^ _s2[j];
            _s2[j] = _s2[i] ^ _s2[j];
            _s2[i] = _s2[i] ^ _s2[j];
        }

        char *pos = strstr(_s1, _s2);
        if (pos == NULL)
        {
            delete[] _s1;
            delete[] _s2;
            return NULL;
        }
        else
        {
            pos = s1 + strlen(_s1) - (pos - _s1) - strlen(_s2);
            delete[] _s1;
            delete[] _s2;
            return pos;
        }
    }
    // originate from strpbrk
    static char *strrpbrk(char *s1, const char *s2) // find the last occurrence of any character in s2 in s1 using STRPBRK
    {
        char *_s1 = new char[strlen(s1) + 1];
        strcpy(_s1, s1);
        for (size_t i = 0, j = strlen(_s1) - 1; i < j; i++, j--)
        {
            _s1[i] = _s1[i] ^ _s1[j];
            _s1[j] = _s1[i] ^ _s1[j];
            _s1[i] = _s1[i] ^ _s1[j];
        }
        char *pos = strpbrk(_s1, s2);
        if (pos == NULL)
        {
            delete[] _s1;
            return NULL;
        }
        else
        {
            pos = s1 + strlen(_s1) - (pos - _s1) - 1;
            delete[] _s1;
            return pos;
        }
    }
    // originate from strspn
    static size_t strrspn(const char *s1, const char *s2) // find the last occurrence of any character not in s2 in s1 using STRCHR
    {
        size_t len = strlen(s1);
        for (size_t i = len - 1; i >= 0; i--)
        {
            if (!strchr(s2, s1[i]))
                return i;
        }
        return len;
    }

public:
    static const size_t npos = -1; // default fail position
    MyString();
    MyString(const char *s, size_t pos = __pos, size_t n = npos);
    MyString(size_t n, char c);
    MyString(const MyString &s);
    ~MyString();

    void operator=(const MyString &s);
    void operator=(const char *s);
    void operator=(const char);

    MyString &assign(const MyString &s, size_t pos = __pos, size_t n = npos);
    MyString &assign(size_t n, char c);
    MyString &assign(const char *s, size_t pos = __pos, size_t n = npos);

    size_t length() const;
    size_t size() const;

    char &operator[](size_t i);
    char &at(size_t i);
    const char *c_str() const;
    MyString &append(const MyString &s, size_t pos = __pos, size_t n = npos);
    MyString &append(size_t n, char c);
    MyString &append(const char *s, size_t pos = __pos, size_t n = npos);
    MyString operator+(const MyString &s) const;
    MyString operator+(const char *s) const;
    MyString operator+(const char) const;

    MyString &operator+=(const MyString &s);
    MyString &operator+=(const char *s);
    MyString &operator+=(const char);

    bool operator==(const MyString &s) const;
    bool operator==(const char *s) const;
    bool operator!=(const MyString &s) const;
    bool operator!=(const char *s) const;
    bool operator<(const MyString &s) const;
    bool operator<(const char *s) const;
    bool operator>(const MyString &s) const;
    bool operator>(const char *s) const;
    bool operator<=(const MyString &s) const;
    bool operator<=(const char *s) const;
    bool operator>=(const MyString &s) const;
    bool operator>=(const char *s) const;

    int compare(const MyString &s) const;
    int compare(size_t pos, size_t n, const MyString &s, size_t pos2 = __pos, size_t n2 = npos) const;
    int compare(const char *s) const;
    int compare(size_t pos, size_t n, const char *s, size_t pos2 = __pos, size_t n2 = npos) const;

    MyString substr(size_t n = 0, size_t m = MyString::npos) const;

    MyString &swap(MyString &s);

    size_t find(char c, size_t pos = __pos) const;
    size_t find(const MyString &s, size_t pos = __pos) const;
    size_t find(const char *s, size_t pos = __pos) const;

    size_t rfind(char c, size_t pos = __pos) const;
    size_t rfind(const MyString &s, size_t pos = __pos) const;
    size_t rfind(const char *s, size_t pos = __pos) const;

    size_t find_first_of(char c, size_t pos = __pos) const;
    size_t find_first_of(const MyString &s, size_t pos = __pos) const;
    size_t find_first_of(const char *s, size_t pos = __pos) const;
    size_t find_last_of(char c, size_t pos = __pos) const;
    size_t find_last_of(const MyString &s, size_t pos = __pos) const;
    size_t find_last_of(const char *s, size_t pos = __pos) const;

    size_t find_first_not_of(char c, size_t pos = __pos) const;
    size_t find_first_not_of(const MyString &s, size_t pos = __pos) const;
    size_t find_first_not_of(const char *s, size_t pos = __pos) const;
    size_t find_last_not_of(char c, size_t pos = __pos) const;
    size_t find_last_not_of(const MyString &s, size_t pos = __pos) const;
    size_t find_last_not_of(const char *s, size_t pos = __pos) const;

    MyString &replace(size_t pos, size_t n, const MyString &s, size_t pos2 = __pos, size_t n2 = npos);
    MyString &replace(size_t pos, size_t n, const char *s, size_t pos2 = __pos, size_t n2 = npos);
    MyString &replace(size_t pos, size_t n, size_t n2, char c);

    MyString &erase(size_t pos = __pos, size_t n = npos);
    void clear();
    MyString &insert(size_t pos, const MyString &s, size_t pos2 = __pos, size_t n2 = npos);
    MyString &insert(size_t pos, const char *s, size_t pos2 = __pos, size_t n2 = npos);
    MyString &insert(size_t pos, size_t n, char c);

    typedef char *iterator;
    typedef const char *const_iterator;
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

    friend std::ostream &operator<<(std::ostream &os, const MyString &s)
    {
        os << s.str;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, MyString &s)
    {
        // init here
        if (s.str)
            delete[] s.str;
        s.capacity = 64;
        s.str = new char[s.capacity];
        s.str[0] = '\0';
        s.len = 0;

        while (is.peek() != EOF && is.peek() != '\n' && is.peek() != '\r' && is.peek() != ' ')
        {
            if (s.len + 1 >= s.capacity)
            {
                s.capacity *= 2;
                char *tmp = new char[s.capacity];
                memcpy(tmp, s.str, s.len);
                delete[] s.str;
                s.str = tmp;
            }
            s.str[s.len] = is.get();
            s.len++;
        }
        s.str[s.len] = '\0';
        return is;
    }
    static MyString to_string(int n);
    static MyString to_string(long long n);
    static MyString to_string(unsigned n);
    static MyString to_string(unsigned long n);
    static MyString to_string(unsigned long long n);
    static MyString to_string(float n);
    static MyString to_string(double n);
    static MyString to_string(long double n);
};


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

//将 MyString 对象作为流处理
// implement endl
class iMyStringstream
{
private:
    MyString s;
    size_t pos;

public:
    iMyStringstream(const MyString &str) : s(str), pos(0) {}
    iMyStringstream(const char *str) : s(str), pos(0) {}
    iMyStringstream(const iMyStringstream &str) : s(str.s), pos(str.pos) {}
    iMyStringstream &operator>>(MyString &str);
    iMyStringstream &operator>>(char &ch);
    iMyStringstream &operator>>(char *str);
    iMyStringstream &operator>>(int &n);
    iMyStringstream &operator>>(long long &n);
    iMyStringstream &operator>>(unsigned &n);
    iMyStringstream &operator>>(unsigned long &n);
    iMyStringstream &operator>>(unsigned long long &n);
    iMyStringstream &operator>>(float &n);
    iMyStringstream &operator>>(double &n);
    iMyStringstream &operator>>(long double &n);
};
class oMyStringstream
{
private:
    MyString s;

public:
    oMyStringstream() : s("") {}
    oMyStringstream(const MyString &str) : s(str) {}
    oMyStringstream &operator<<(const MyString &str);
    oMyStringstream &operator<<(const char *str);
    oMyStringstream &operator<<(const char &ch);
    oMyStringstream &operator<<(const int &n);
    oMyStringstream &operator<<(const long long &n);
    oMyStringstream &operator<<(const unsigned &n);
    oMyStringstream &operator<<(const unsigned long &n);
    oMyStringstream &operator<<(const unsigned long long &n);
    oMyStringstream &operator<<(const float &n);
    oMyStringstream &operator<<(const double &n);
    oMyStringstream &operator<<(const long double &n);
    oMyStringstream &operator<<(oMyStringstream &(*op)(oMyStringstream &));
    MyString str();
    static oMyStringstream &endl(oMyStringstream &s);
};

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


int main()
{
    {  //测试1
        MyString s1;  // si = ""
        MyString s2("Hello");  // s2 = "Hello"
        MyString s3(4, 'K');  // s3 = "KKKK"
        MyString s4("12345", 1, 3);  //s4 = "234"，即 "12345" 的从下标 1 开始，长度为 3 的子串

        cout<<s1<<s2<<s3<<s4 ;
    }

    {  //测试2
        {
            MyString s1,s2;
            s1 = "Hello";  // s1 = "Hello"
            s2 = 'K';  // s2 = "K”
            cout<<s1<<s2 ;
        }

        {
            MyString s1("12345"), s2,s3;
            s3.assign(s1);  // s3 = s1
            cout<<s3;
            s2.assign(s1, 1, 2);  // s2 = "23"，即 s1 的子串(1, 2)
            cout<<s2;
            s2.assign(4, 'K');  // s2 = "KKKK"
            cout<<s2;
            s2.assign("abcde", 2, 3);  // s2 = "cde"，即 "abcde" 的子串(2, 3)
            cout<<s2 ;
        }

    }

    {  //测试3

        MyString s1("12345"), s2;
        cout<<s1.length()<<s2.size() ;
    }

    {//测试4
        MyString s1("123"), s2("abc");
        s1.append(s2);  // s1 = "123abc"
        cout<<s1;
        s1.append(s2, 1, 2);  // s1 = "123abcbc"
        cout<<s1;
        s1.append(3, 'K');  // s1 = "123abcbcKKK"
        cout<<s1;
        s1.append("ABCDE", 2, 3);  // s1 = "123abcbcKKKCDE"，添加 "ABCDE" 的子串(2, 3)
        cout<<s1 ;
    }

    {   //测试5
        MyString s1("hello"), s2("hello, world");
        cout<<(s1>s2)<<(s1<s2)<<(s1>=s2)<<(s1<=s2)<<(s1==s2)<<(s1!=s2) ;
        int n = s1.compare(s2);
        cout<<n;
        n = s1.compare(1, 2, s2, 0, 3);  //比较s1的子串 (1,2) 和s2的子串 (0,3)
        cout<<n;
        n = s1.compare(0, 2, s2);  // 比较s1的子串 (0,2) 和 s2
        cout<<n;
        n = s1.compare("Hello");
        cout<<n;
        n = s1.compare(1, 2, "Hello");  //比较 s1 的子串(1,2)和"Hello”
        cout<<n;
        n = s1.compare(1, 2, "Hello", 1, 2);  //比较 s1 的子串(1,2)和 "Hello" 的子串(1,2)
        cout<<n ;
    }

    {   //测试6
        MyString s1 = "this is ok";
        MyString s2 = s1.substr(2, 4);  // s2 = "is i"
        cout<<s1<<s2;
        s2 = s1.substr(2);  // s2 = "is is ok"
        cout<<s2 ;
    }

    {   //测试7
        MyString s1("West"), s2("East");
        cout<<s1<<s2;
        s1.swap(s2);  // s1 = "East"，s2 = "West"
        cout<<s1<<s2 ;
    }

    {   //测试8
        MyString s1("Source Code");
        size_t n;

        if ((n = s1.find('u')) != MyString::npos) //查找 u 出现的位置
            cout << "1) " << n << "," << s1.substr(n)  ;
        //输出 l)2,urce Code
        if ((n = s1.find("Source", 3)) == MyString::npos)//从下标3开始查找"Source"，找不到
            cout << "2) " << "Not Found"  ;  //输出 2) Not Found
        if ((n = s1.find("Co")) != MyString::npos) //查找子串"Co"。能找到，返回"Co"的位置
            cout << "3) " << n << ", " << s1.substr(n)  ;
        // else
        //     cout<<"fuck here\n"<<s1<<"\n";
        //输出 3) 7, Code
        if ((n = s1.find_first_of("ceo")) != MyString::npos)//查找第一次出现或 'c'、'e'或'o'的位置
            cout << "4) " << n << ", " << s1.substr(n) ;
        //输出 4) l, ource Code
        if ((n = s1.find_last_of('e')) != MyString::npos)//查找最后一个 'e' 的位置
            cout << "5) " << n << ", " << s1.substr(n)  ;
        //输出 5) 10, e
        if ((n = s1.find_first_not_of("eou", 1)) != MyString::npos) //从下标1开始查找第一次出现非 'e'、'o' 或 'u' 字符的位置
        cout << "6) " << n << ", " << s1.substr(n) ;
        //输出 6) 3, rce Code
    }

    {   //测试9
        MyString s1("Real Steel");
        cout<<s1;
        s1.replace(1, 3, "123456", 2, 4);  //用 "123456" 的子串(2,4) 替换 s1 的子串(1,3)
        cout << s1  ;  //输出 R3456 Steel

        MyString s2("Harry Potter");
        cout<<s2;
        s2.replace(2, 3, 5, '0');  //用 5 个 '0' 替换子串(2,3)
        cout << s2  ;  //输出 HaOOOOO Potter

        size_t n = s2.find("00000");  //查找子串 "00000" 的位置，n=2
        cout<<n;   //输出2
        s2.replace(n, 5, "XXX");  //将子串(n,5)替换为"XXX"
        cout << s2  ;  //输出 HaXXX Potter
    }

    { //测试10
        MyString s1("Real Steel");
        cout<<s1;
        s1.erase(1, 3);  //删除子串(1, 3)，此后 s1 = "R Steel"
        cout<<s1;
        s1.erase(5);  //删除下标5及其后面的所有字符，此后 s1 = "R Ste"
        cout<<s1 ;
    }

    { //测试11
        MyString s1("Limitless"), s2("00");
        cout<<s1<<s2;
        s1.insert(2, "123");  //在下标 2 处插入字符串"123"，s1 = "Li123mitless"
        cout<<s1;
        s1.insert(3, s2);  //在下标 2 处插入 s2 , s1 = "Li10023mitless"
        cout<<s1;
        s1.insert(3, 5, 'X');  //在下标 3 处插入 5 个 'X'，s1 = "Li1XXXXX0023mitless"
        cout<<s1;
    }

    {   //测试12  选做部分
        #ifndef _SELECT
        //没有完成选作部分则使用string类和istringstream类测试
        string src("Avatar 123 5.2 Titanic K");
        istringstream istrStream(src); //建立src到istrStream的联系
        string s1, s2;
        int n;  double d;  char c;
        istrStream >> s1 >> n >> d >> s2 >> c; //把src的内容当做输入流进行读取

        ostringstream ostrStream;
        ostrStream << s1  << s2   << n   << d   << c ;
        cout << ostrStream.str()<<endl;

        #else

        //如果完成选作部分则使用MyString类和iMyStringstream类测试
        MyString src("Avatar 123 5.2 Titanic K");
        iMyStringstream istrStream(src); //建立src到istrStream的联系
        MyString s1, s2;
        int n;  double d;  char c;
        istrStream >> s1 >> n >> d >> s2 >> c; //把src的内容当做输入流进行读取
        oMyStringstream ostrStream;
        ostrStream << s1  << s2   << n   << d   << c ;
        cout << ostrStream.str()<<endl;
        #endif // _SELECT

    }

    return  0;
}
