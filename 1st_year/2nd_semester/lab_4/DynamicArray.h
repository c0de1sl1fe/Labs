#pragma once
#include "Data.h"
#include <ctype.h>
class DynamicArray
{
private:
    unsigned _size;
    unsigned _capacity;
    unsigned _growth;
    Data** _array;
public:
    DynamicArray();
    DynamicArray(const DynamicArray& a);
    void Create();
    int GetSize() const;
    void SortArray(int(*elemCmp)(Data*, Data*));
    unsigned FindSurname(char* str, unsigned begin);
    void PrintDynamicArray() const;
    void AddtoEnd(Data* a);
    void AddBefore(Data* a, unsigned index);
    void ReadBinFile(const char* path);
    void WriteBinFile(const char* path);
    Data* GetElement(unsigned index) const;
    Data* GetElementS(unsigned index);
    void ClearArray();
    void DeleteElement(unsigned index);
    ~DynamicArray();
};