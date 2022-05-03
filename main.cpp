/*
 * @Author       : Gehrychiang
 * @LastEditTime : 2022-05-03 09:55:21
 * @Website      : www.yilantingfeng.site
 * @E-mail       : gehrychiang@aliyun.com
 */
#include "MyString.h"
#include <iostream>
using namespace std;
void test1()
{
    // MyString s1();
    // empty parentheses interpreted as a function declaration
    // note: remove parentheses to default-initialize a variable
    MyString s1;
    cout << s1 << endl;
    MyString s2("hello");
    cout << s2 << endl;
    MyString s3(4, 'K');
    cout << s3 << endl;
    MyString s4("12345", 1, 3);
    cout << s4 << endl;
}
void test2()
{
    MyString s1, s2;
    s1 = "Hello";
    s2 = 'K';
    cout << s1 << endl;
    cout << s2 << endl;
}
void test2_2()
{
    MyString s1("12345"), s2, s3;
    s3.assign(s1); // s3 = s1
    cout << s3 << endl;
    s2.assign(s1, 1, 2); // s2 = "23"，即 s1 的子串(1, 2)
    cout << s2 << endl;
    s2.assign(4, 'K'); // s2 = "KKKK"
    cout << s2 << endl;
    s2.assign("abcde", 2, 3); // s2 = "cde"，即 "abcde" 的子串(2, 3)
    cout << s2 << endl;
}
void test3()
{
    MyString s1("12345");
    cout << s1.size() << endl;
    cout << s1.length() << endl;
}
void test4()
{
    MyString s1("123"), s2("abc");
    s1.append(s2); // s1 = "123abc"
    cout << s1 << endl;
    s1.append(s2, 1, 2); // s1 = "123abcbc"
    cout << s1 << endl;
    s1.append(3, 'K'); // s1 = "123abcbcKKK"
    cout << s1 << endl;
    s1.append("ABCDE", 2, 3); // s1 = "123abcbcKKKCDE"，添加 "ABCDE" 的子串(2, 3)
    cout << s1 << endl;
}
void test5()
{
    MyString s1("hello"), s2("hello, world");
    int n = s1.compare(s2);
    cout << n << endl;
    n = s1.compare(1, 2, s2, 0, 3); //比较s1的子串 (1,2) 和s2的子串 (0,3)
    cout << n << endl;
    n = s1.compare(0, 2, s2); // 比较s1的子串 (0,2) 和 s2
    cout << n << endl;
    n = s1.compare("Hello");
    cout << n << endl;
    n = s1.compare(1, 2, "Hello"); //比较 s1 的子串(1,2)和"Hello”
    cout << n << endl;
    n = s1.compare(1, 2, "Hello", 1, 2); //比较 s1 的子串(1,2)和 "Hello" 的子串(1,2)
    cout << n << endl;
}
void test6()
{
    MyString s1 = "this is ok";
    MyString s2 = s1.substr(2, 4); // s2 = "is i"
    cout << s2 << endl;
    s2 = s1.substr(2); // s2 = "is is ok"
    cout << s2 << endl;
}
void test7()
{
    MyString s1("West"), s2("East");
    s1.swap(s2); // s1 = "East"，s2 = "West"
    cout << s1 << " " << s2 << endl;
}
void test8()
{
    MyString s1("Source Code");
    int n;
    if ((n = s1.find('u')) != MyString::npos) //查找 u 出现的位置
        cout << "1) " << n << "," << s1.substr(n) << endl;
    //输出 l)2,urce Code
    if ((n = s1.find("Source", 3)) == MyString::npos) //从下标3开始查找"Source"，找不到
        cout << "2) "
             << "Not Found" << endl;           //输出 2) Not Found
    if ((n = s1.find("Co")) != MyString::npos) //查找子串"Co"。能找到，返回"Co"的位置
        cout << "3) " << n << ", " << s1.substr(n) << endl;
    //输出 3) 7, Code
    if ((n = s1.find_first_of("ceo")) != MyString::npos) //查找第一次出现或 'c'、'e'或'o'的位置
        cout << "4) " << n << ", " << s1.substr(n) << endl;
    //输出 4) l, ource Code
    if ((n = s1.find_last_of('e')) != MyString::npos) //查找最后一个 'e' 的位置
        cout << "5) " << n << ", " << s1.substr(n) << endl;
    //输出 5) 10, e
    if ((n = s1.find_first_not_of("eou", 1)) != MyString::npos)
        //从下标1开始查找第一次出现非 'e'、'o' 或 'u' 字符的位置
        cout << "6) " << n << ", " << s1.substr(n) << endl;
    //输出 6) 3, rce Code
}
void test9()
{
    MyString s1("Real Steel");
    s1.replace(1, 3, "123456", 2, 4); //用 "123456" 的子串(2,4) 替换 s1 的子串(1,3)
    cout << s1 << endl;               //输出 R3456 Steel
    MyString s2("Harry Potter");
    s2.replace(2, 3, 5, 'O'); //用 5 个 '0' 替换子串(2,3)
    cout << s2 << endl;       //输出 HaOOOOO Potter
    int n = s2.find("OOOOO"); //查找子串 "00000" 的位置，n=2
    s2.replace(n, 5, "XXX");  //将子串(n,5)替换为"XXX"
    cout << s2 << endl;       //输出 HaXXX Potter
}
void test10()
{
    MyString s1("Real Steel");
    s1.erase(1, 3); //删除子串(1, 3)，此后 s1 = "R Steel"
    cout << s1 << endl;
    s1.erase(5); //删除下标5及其后面的所有字符，此后 s1 = "R Ste"
    cout << s1 << endl;
}
void test11()
{
    MyString s1("Limitless"), s2("00");
    s1.insert(2, "123"); //在下标 2 处插入字符串"123"，s1 = "Li123mitless"
    cout << s1 << endl;
    s1.insert(3, s2); //在下标 2 处插入 s2 , s1 = "Li10023mitless"
    cout << s1 << endl;
    s1.insert(3, 5, 'X'); //在下标 3 处插入 5 个 'X'，s1 = "Li1XXXXX0023mitless"
    cout << s1 << endl;
}
int main()
{
    test8();
    return 0;
}