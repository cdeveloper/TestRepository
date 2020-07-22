#include <iostream>
#include <vector>
//#include <iterator>
using std::cout;
using std::cin;
using std::endl;
using std::ostream; // error: ‘ostream’ does not name a type

class Stack
{

public:
  Stack(){} // data meber vector is automatically default initialized to zero. vector of size zero

  // friend function to print stack
  friend ostream& operator<<(ostream& os, const Stack& stack);

  void push(int i)
  {
    // calls push_back of underlying container --> generally a deque. here we are using vector
    dataElements.push_back(i);
  }

  // pop() - Calling this function on an empty container causes undefined behavior.
  void pop()
  {
    if (!dataElements.empty())
    {
      // calls pop_back of underlying container --> generally a deque. here we are using vector
      dataElements.pop_back();
      // Note : As per standard If the container is not empty, the function never throws exceptions (no-throw guarantee).
      // Otherwise, it causes undefined behavior. we can put empty() check here just to avoid it.
    }
  }

   // top() - Calling this function on an empty container causes undefined behavior.
   int& top() // returns reference to the last element in the vector.
   {
    if (!dataElements.empty())
    {
      // calls "back" of underlying container
      return dataElements.back();
      // Note : As per standard If the container is not empty, the function never throws exceptions (no-throw guarantee).
      // Otherwise, it causes undefined behavior. we can put empty() check here just to avoid it.
    }
   }

   // for range based for loop , going to just provide underlying containers begin and end :) !

   // Important Note 1 : ->  error: passing 'const Stack' as 'this' argument discards qualifiers
   // error: passing xxx as 'this' argument of xxx discards qualifiers
   //  you're calling a non-const member function (begin() and end() ) on const object argument in printStack,
   // which is not allowed because non-const member functions make NO PROMISE not to modify
   // SO we are adding 'const' identifier to this functions to make them const functions

   // Important Note 2 : -> error: invalid conversion from 'const int*' to 'int*' [-fpermissive]
   // error: invalid conversion from 'const T*' to 'T*'
   // It is because std library stl's begin() and end() member functions of container returns 'const pointer' and 'not just pointer'
   // i.e. const T* and not T*
   // So we are changing the return type from int* to const int*

   // Very Important Note 3 : ->
   // STL containers begin() and end() returns Iterator , here we don't have iterator, but we can convert it to pointer as follows for range_based for
   // here is how to convert an iterator to a pointer,
   // first dereference the iterator, which will yield a reference (to int, in your case),
   // and then get the address of the value referenced. This gives:
   // std::vector<int>::iterator it_a = std::lower_bound(x.begin(), x.end(),temp1);
   // int& ref_a = *it_a;
   // int* ptr_a = &ref_a; or in one line -> int *a = &*std::lower_bound(x.begin(), x.end(),temp1);
   // here anyway we are not finding temp1, so x.begin() itself is the lower bound
   // hence ptr = &*(underlying_container.begin()) = &*dataElements.begin() !!!

  const int* begin() const { return &(*dataElements.begin());}
  const int* end() const { return &(*dataElements.end());}

private:
  // underlying container, adapted to use as stack
  std::vector<int> dataElements;

};

// free function to print stack
ostream& operator<<(ostream& os, const Stack& stack)
{
  // NOTE : -> error: 'begin' & 'end' was not declared in this scope as Stack is our custom made
  // Error for range based for loop, need to provide begin and end for this cusotm type to use this
  //  for(auto const& ele : stack)

  cout << "\nCurrent Stack is : "  ;
  for(auto const& ele : stack)
  {
     os << ele;
  }
  cout << "\n"  ;
  return os;
}

int main()
{
Stack st;

  cout << "\n\n";
  st.push(1);    st.push(2);     st.push(3);
  cout << st;

  cout << "\n\nCurrent data at Top : " << st.top();
  st.pop();
  cout << "\n\nAfter POPing top - " << st;


return 0;
}
