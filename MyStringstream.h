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
