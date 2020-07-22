#include<iostream>
using std::cout;
using std::endl;
template <typename T>
class MyVector
{
public :
  MyVector():mCapacity(1), pData(new T[1]), mSize(0){}
  MyVector(size_t capacity):mCapacity(capacity), pData(new T[capacity]), mSize(0){}
  ~MyVector() { delete []pData; }

  size_t size()     const { return  mSize; }
  bool   empty()    const { return (mSize == 0); }
  size_t capacity() const { return  mCapacity; }

  T& operator[](size_t i) { return pData[i]; }
  T& at(size_t i)         { if (i < size()) return pData[i]; else { throw std::out_of_range("Index Out Of Bounds !"); } }

  void push_back(T data)
  {
    if (capacity() == size())
    {
      T* pTemp = new T[capacity() * 2];
      for(size_t i = 0; i < size(); ++i) { pTemp[i] = pData[i];}
      delete []pData;
      pData = pTemp;
    }
    pData[mSize++] = data;
  }

  void pop_back() { if (!empty()) mSize = mSize -1; }

// Nested inner Iterator class
private :
  class Iterator
  {
    public:
      Iterator() : ptr(nullptr){}
      Iterator(T* p) : ptr(p){}

      T operator*()                            { return *ptr; }
      bool operator==(const Iterator& rhs) const { return (ptr == rhs.ptr); }
      bool operator!=(const Iterator& rhs) const { return !(*this == rhs);  }
      Iterator& operator++()                     { ++ptr;  return *this; }
      Iterator  operator++(int)                  { Iterator old(*this); ++*this; return old; }

    private:
      T* ptr;
  };

public :
  // Public Terface for container class of nested/inner class Iterator
  Iterator begin() { return Iterator(pData); }
  Iterator end()   { return Iterator(pData + size()); }

  // display my vector
  void printMyVector() { cout<<"\n\n"; for(auto p = begin(); p != end(); ++p) cout <<" " << *p;}

private:
  size_t mCapacity;
  T*   pData;
  size_t mSize;
};

int main()
{
 // MyVector<int> vec(5);
 // vec.push_back(0); vec.push_back(1); vec.push_back(2); vec.push_back(3);

  MyVector<char> vec(5);
   vec.push_back('a'); vec.push_back('b'); vec.push_back('c'); vec.push_back('d');

   cout << "\n\nSize : " << vec.size();
   vec.printMyVector();

   vec.pop_back();
   cout << "\n\nSize : " << vec.size();
   vec.printMyVector();

   cout << "\n\n";
   cout << "Current Vector size is : " << vec.size() << '\n';

   try
   {  cout << "\nAt index 4 (should be out of bounds) : " << vec.at(4); cout << "\n"; }
   catch(std::exception &e) // if you don't catch exception, it will call terminate
   {  cout<< '\n' << e.what() << '\n'; }

   cout << "\nAt index 1 : " << vec.at(1);  cout << "\n";
   cout << "\nAt subscript 2 : " << vec[2]; cout << "\n";


return 0;
};
