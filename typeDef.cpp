#include <iostream>  // std::cout
#include <algorithm> // std::copy(iBegIter, iEndIter, outputBegIter)
#include <iterator>  // std::ostream_iterator

// Note - this is problematic, avoid in new code
// old C style typedef for array
// this is problematic while using this typedef as parameter in function
// use C++ style structure with operator[] overload for passing in function
// to enable pass by value or better use the new std::array<>
typedef int intArraySize3[3] ;
intArraySize3 a;

int main()
{

   a[0] = 0; a[1] = 1; a[2] = 2;
   size_t n = sizeof(a)/sizeof(a[0]);
   std::cout <<"\n\n";

   std::copy(std::begin(a), std::end(a),
            std::ostream_iterator<int>(std::cout, " "));

   typedef struct typeArraySize3 {
      int& operator[](int i) { return data[i]; }
      int data[3];
   } typeArraySize3;

   typeArraySize3 x;

   x[1] = 1;  std::cout << "\n\n x[1] = " << x[1];
   // ascii of char '2' is 50 , iostream NOT Safe due to this type of conversions
   // so better use new std::fmt library code for IO formatting
   x[2] = '2'; std::cout << "\n x[2] = " << x[2] << "\n\n";

   return 0;
}

/*

However, this is probably a very bad idea,
Because the resulting type is an array type,
But users of it won't see that it's an array type.

If used as a function argument,
it will be passed by reference, NOT by value,
and the sizeof for it will then be wrong.

A better solution would be ->
1) to use struct as wrapper around the array &
2) overload operator[] (-> for convenience of using subscript syntax)
i.e.  we can use xArray[0] instead of xArray.data[0].


typedef struct typeArraySize3 {
    int& operator[](int i) { return data[i]; }
    int data[3];
} typeArraySize3;

typeArraySize3 x;
x[2] = '2';
int i = x[2];

*/

/*
// 1)  typedef for function type , please note it is not function pointer
typedef void T();
T t;                 // -> evaluates to  void t();

// 2)  typedef equivalent of above
typedef void (U)();
U u;                 // -> evaluates to  void u();

// 3) modern style using  - for function type
using FuncType = void();
FuncType r;            // -> evaluates to  void r();

*/

// references
/*
https://stackoverflow.com/questions/4523497/typedef-fixed-length-array
https://stackoverflow.com/questions/50152242/how-to-pass-array-by-value-in-c
https://stackoverflow.com/questions/15359713/passing-array-by-value

https://stackoverflow.com/questions/4424579/stdvector-versus-stdarray-in-c
https://stackoverflow.com/questions/30263303/stdarray-vs-array-performance

https://stackoverflow.com/questions/3674200/what-does-a-typedef-with-parenthesis-like-typedef-int-fvoid-mean-is-it-a
https://stackoverflow.com/questions/750178/is-it-a-good-idea-to-typedef-pointers/43312230#43312230


*/
