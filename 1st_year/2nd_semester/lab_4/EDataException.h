#pragma once
class EDataException
{
protected:
    char _err[256];
public:
    EDataException(const char* err);
    virtual void Print();
    virtual ~EDataException();
};

class EInvalidIndex : public EDataException
{
protected:
    unsigned _max;
    unsigned _min;
    unsigned _index;
public:
    EInvalidIndex(unsigned _max, unsigned _min, unsigned _index);
    void Print();
    ~EInvalidIndex();
};

class EFileException : public EDataException
{
protected:
    char _details[128];
    char _path[128];
public:
    EFileException(const char* path, const char* details);
    void Print();
    ~EFileException();
};

class EOutofrangeException : public EDataException
{
protected:
    int _max;
    int _min;
    int _number;
public:
    EOutofrangeException(int index, int min = 2, int max = 5);
    void Print();
    ~EOutofrangeException();
};

class EisEmpty : public EDataException
{
protected:
    char _details[128];
public:
    EisEmpty(const char* details = "");
    void Print();
    ~EisEmpty();
};
