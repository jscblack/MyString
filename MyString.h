/*
 * @Author       : Gehrychiang
 * @LastEditTime : 2022-05-02 10:06:12
 * @Website      : www.yilantingfeng.site
 * @E-mail       : gehrychiang@aliyun.com
 */
#include <cstring>
#include <iostream>
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

    MyString &assgin(const MyString &s, size_t pos = __pos, size_t n = npos);
    MyString &assgin(size_t n, char c);
    MyString &assgin(const char *s, size_t pos = __pos, size_t n = npos);

    size_t length() const;
    size_t size() const;

    char &operator[](size_t i);
    char &at(size_t i);

    MyString &append(const MyString &s, size_t pos = __pos, size_t n = npos);
    MyString &append(size_t n, char c);
    MyString &append(const char *s, size_t pos = __pos, size_t n = npos);
    MyString operator+(const MyString &s) const;
    MyString operator+(const char *s) const;
    MyString &operator+=(const MyString &s);
    MyString &operator+=(const char *s);

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

    size_t find_first_of(const MyString &s, size_t pos = __pos) const;
    size_t find_first_of(const char *s, size_t pos = __pos) const;
    size_t find_last_of(const MyString &s, size_t pos = __pos) const;
    size_t find_last_of(const char *s, size_t pos = __pos) const;

    size_t find_first_not_of(const MyString &s, size_t pos = __pos) const;
    size_t find_first_not_of(const char *s, size_t pos = __pos) const;
    size_t find_last_not_of(const MyString &s, size_t pos = __pos) const;
    size_t find_last_not_of(const char *s, size_t pos = __pos) const;

    MyString &replace(size_t pos, size_t n, const MyString &s, size_t pos2 = __pos, size_t n2 = npos);
    MyString &replace(size_t pos, size_t n, const char *s, size_t pos2 = __pos, size_t n2 = npos);
    MyString &replace(size_t pos, size_t n, char c, size_t n2);

    MyString &erase(size_t pos = __pos, size_t n = npos);

    MyString &insert(size_t pos, const MyString &s, size_t pos2 = __pos, size_t n2 = npos);
    MyString &insert(size_t pos, const char *s, size_t pos2 = __pos, size_t n2 = npos);
    MyString &insert(size_t pos, size_t n, size_t n2, char c);

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
        s.capacity = 32;
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
};