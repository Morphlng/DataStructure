#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::ostream;
using std::string;

// Dynamic String
struct DString
{
    friend ostream &operator<<(ostream &, const DString &);
    friend bool operator==(const DString &, const DString &);
    friend bool operator<(const DString &, const DString &);
    friend bool operator>(const DString &, const DString &);

public:
    DString();
    DString(int);
    DString(const string &);
    DString SubString(int pos, int len);
    int IndexOf(const DString &);
    int Length();
    void Clear();

    char *ch; // ch[0]不用，这样可以保证位序一致
    int length;
};

DString::DString()
{
    ch = new char[1];
    length = 0;
}

DString::DString(int _length)
{
    length = _length;
    ch = new char[length + 1];
}

DString::DString(const string &s)
{
    length = s.length();
    ch = new char[length + 1];
    int i = 1;
    for (char c : s)
    {
        ch[i++] = c;
    }
}

int DString::Length()
{
    return length;
}

void DString::Clear()
{
    delete[] ch;
    length = 0;
}

DString DString::SubString(int pos, int len)
{
    if (pos + len - 1 > length)
        return DString();

    DString sub(len);
    for (int i = pos, j = 1; i < pos + len; i++, j++)
    {
        sub.ch[j] = ch[i];
    }

    return sub;
}

int DString::IndexOf(const DString &s)
{
    int i;
    for (i = 1; (i + s.length - 1) <= length; i++)
    {
        if (SubString(i, s.length) == s)
            return i;
    }

    return -1;
}

ostream &operator<<(ostream &out, const DString &S)
{
    for (int i = 1; i <= S.length; i++)
    {
        out << S.ch[i];
    }
    return out;
}

bool operator==(const DString &s1, const DString &s2)
{
    if (s1.length != s2.length)
        return false;

    for (int i = 1; i <= s1.length; i++)
        if (s1.ch[i] != s2.ch[i])
            return false;

    return true;
}

bool operator<(const DString &s1, const DString &s2)
{
    for (int i = 1; i <= s1.length && i <= s2.length; i++)
        return s1.ch[i] < s2.ch[i];

    return true;
}

bool operator>(const DString &s1, const DString &s2)
{
    for (int i = 1; i <= s1.length && i <= s2.length; i++)
        return s1.ch[i] > s2.ch[i];

    return false;
}