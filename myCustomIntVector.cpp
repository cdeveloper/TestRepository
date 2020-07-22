#include<iostream>
using std::cout;
using std::endl;

class MyIntVector
{
public :
  MyIntVector():mCapacity(1), pData(new int[1]), mSize(0){}
  MyIntVector(size_t capacity):mCapacity(capacity), pData(new int[capacity]), mSize(0){}
  ~MyIntVector() { delete []pData; }

  size_t size()     const { return  mSize; }
  bool   empty()    const { return (mSize == 0); }
  size_t capacity() const { return  mCapacity; }

  int& operator[](size_t i) { return pData[i]; }
  int& at(size_t i)         { if (i < size()) return pData[i]; else { throw std::out_of_range("Index Out Of Bounds !"); } }

  void push_back(int data)
  {
    if (capacity() == size())
    {
      int* pTemp = new int[capacity() * 2];
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
      Iterator(int* p) : ptr(p){}

      int operator*()                            { return *ptr; }
      bool operator==(const Iterator& rhs) const { return (ptr == rhs.ptr); }
      bool operator!=(const Iterator& rhs) const { return !(*this == rhs);  }
      Iterator& operator++()                     { ++ptr;  return *this; }
      Iterator  operator++(int)                  { Iterator old(*this); ++*this; return old; }

    private:
      int* ptr;
  };

public :
  // Public interface for container class of nested/inner class Iterator
  Iterator begin() { return Iterator(pData); }
  Iterator end()   { return Iterator(pData + size()); }

  // display my vector
  void printMyVector() { cout<<"\n\n"; for(auto p = begin(); p != end(); ++p) cout <<" " << *p;}

private:
  size_t mCapacity;
  int*   pData;
  size_t mSize;
};

int main()
{
 MyIntVector vec(5);
   vec.push_back(0); vec.push_back(1); vec.push_back(2); vec.push_back(3);
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


#if 0
class MyVector
{
public:

  MyVector() : mCapacity(1), mpArray(new int[1]), mSize(0) {}
  MyVector(int capacity) : mCapacity(capacity), mpArray(new int[capacity]), mSize(0){}
  ~MyVector() { delete []mpArray; }

  unsigned int  size()     const { return mSize; } // declaring this const, as it is used to get Iterator in begin() which is const function
  bool          empty()    const { return (size() == 0); }
  unsigned int  capacity() const { return mCapacity; }

  void push_back(int data);
  void pop_back();

  // to retrieve vector elements
  int& operator[](unsigned int i);
  int& at(unsigned int i);

  // to display the vector contents
  // going to display using iterators so we need iterator with begin(), end(), oper*(), oper==(), oper!=() and oper++()
  void printMyVector();

  class Iterator
  {
  public :
    explicit Iterator(): ptr(nullptr){};
    explicit Iterator(int* p) : ptr(p){}; // this is called in begin() and end(), conversion ctor

    // DeReference operator, oper*() -> returns the value of pointed type
    int operator*() const { return *ptr; }
    // PreIncrement, return reference
    Iterator& operator++(){ ++ptr; return *this; }
    // PostIncrement , return by value (old value ) - important return by value
    Iterator operator++(int) { Iterator old(*this); ++*this; return old; }
    // Equality operator!=()
    bool operator==(const Iterator& rhs) const { return ptr == rhs.ptr; }
    // InEquality operator!=()
    bool operator!=(const Iterator& rhs) const { return !(ptr == rhs.ptr); }
  private:
    int* ptr;
  };

// interfaces to get iterators in container class. For using iterators in the parent container
public :
  // begin() and end() would be in container class of Iterator - Important
  Iterator begin() const { return Iterator(mpArray); }
  Iterator end()   const { return Iterator(mpArray + size()); } // const mf can call only const mf, so we can use size() here as its const mf

private:
  int*         mpArray;
  unsigned int mCapacity; // capacity
  unsigned int mSize;     // size
};

// adds element at the back
void MyVector::push_back(int data)
{
  if (capacity() == size())
  {
    // allocate new memory for container with double the capacity
    int* pTemp = new int[capacity() * 2];
    // copy old container to new container (we are using array here)
    for(unsigned i = 0; i < capacity(); ++i)
    {
      pTemp[i] = mpArray[i];
    }
    // delete previous array
    delete []mpArray;
    // set the new capacity
    mCapacity = capacity() * 2;
    // set the container to new array (vector)
    mpArray = pTemp;

  } // end_if capacity == mSize

  // insert element
  mpArray[mSize++] = data;
}

// removes last element
void MyVector::pop_back()
{
  if (!empty())
  {
    mSize = mSize - 1;
  };
}

// bound check retrieval
int& MyVector::at(unsigned int i)
{
  if (i < size())
  {
    return mpArray[i];
  }
  else   // as return type is reference, there is no reference possible in else
    {    // so throw std::out_of_range() exception - note you need msg - you need msg, can not just throw type
      throw std::out_of_range("Index Out Of Bounds"); //
         // return -1;  as return type is reference, there is no reference possible in else
    }
}
// subscript operator retrieval
int& MyVector::operator[](unsigned int i)
{
  return *(mpArray+i);
}

void MyVector::printMyVector()
{
  cout << '\n' << '\n';
  //typedef MyVector::Iterator ptr;
  // here we need iterators begin() and end() to use range based for loop
  //for (MyVector::Iterator ptr = begin(); ptr != end(); ++ptr)
  using Iter_t = MyVector::Iterator;
  for (auto /*Iter_t*/ ptr = begin(); ptr != end(); ++ptr)
  cout << *ptr << " ";
}

int main()
{
   MyVector vec(5);
   vec.push_back(0); vec.push_back(1); vec.push_back(2); vec.push_back(3);
   cout << "\n\nSize : " << vec.size();
   vec.printMyVector();

   vec.pop_back();
   cout << "\n\nSize : " << vec.size();
   vec.printMyVector();

   cout << "\n\n";
   cout << "Current Vector size is : " << vec.size() << '\n';

   try {
      cout << "\nAt index 4 (should be out of bounds) : " << vec.at(4); cout << "\n";
   } catch(std::exception &e) { cout<< '\n' << e.what() << '\n'; } // if you don't catch exception, it will call terminate

   cout << "\nAt index 1 : " << vec.at(1); cout << "\n";
   cout << "\nAt subscript 2 : " << vec[2];    cout << "\n";


  return 0;
}
#endif
