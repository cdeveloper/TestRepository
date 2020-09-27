// What does the explicit keyword mean in C++?
// See notes below after the program

#include <iostream>  // std::cout

class Foo
{
   public:
      // single parameter constructor, can be used as an implicit conversion
      Foo (int foo) : m_foo (foo)
      {
         std::cout <<"\n\n Single Parameter CTOR invoked - Implicitly! \n\n";
      }

      // public method accessor for private member
      int GetFoo () { return m_foo; }

   private:
      // private data member
      int m_foo;
};

// Here's a simple function that takes a Foo objectby value
void DoBar (Foo foo)
{
  int i = foo.GetFoo ();
}

// main how DoBar gets used which can create problem
int main ()
{
  DoBar (42); // int is implicitly converted to Foo object due to single argument ctor of Foo (to avoid this make that ctor EXPLICIT)

  return 0; // main return
}

#if 0
IMPORTANT NOTES :
-----------------
https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean?rq=1

'x'is being treated as an integer because the char data type is just a 1-byte integer.

In DoBar (42); ->The argument is not a Foo object, but an int.
However, there exists a constructor for Foo that takes an int
so this constructor can be used to convert the parameter to the correct type.

The compiler is allowed to do this once for "each" parameter. <=== This REMEMBER
The compiler is allowed to make one implicit conversion to resolve the parameters to a function.
What this means is that the compiler can use constructors callable with a single parameter
to convert from one type to another in order to get the right type for a parameter.
Prefixing the explicit keyword to the constructor prevents the compiler
from using that constructor for implicit conversions.
Adding it to the above class will create a compiler error at the function call DoBar (42).
It is now necessary to call for conversion explicitly with DoBar (Foo (42))

The reason you might want to do this is to avoid accidental construction that can hide bugs.
Contrived example:

    You have a MyString(int size) class with a constructor that constructs a string of the given size.
    You have a function print(const MyString&), and you call print(3)
    (when you actually intended to call print("3")).
    You expect it to print "3", but it prints an empty string of length 3 instead.
===================================================


1)
And it's worth noting that
the new generalized initialization rules of C++0x
will make String s = {0}; ill-formed,
rather than trying to call the other constructor with a null pointer, as String s = 0; would do.

2)
Even though this is an old question it seems worth pointing a few things out (or having someone set me straight).
By making the int form, or both ctors, 'explicit'
you would still have the same bug if you used String mystring('x')
when you meant String mystring("x") wouldn't you?
Also, from the comment above I see the improved behavior of String s = {0} over String s = 0
thanks to making the int form of the ctor 'explicit'.
But, other than knowing the precedence of the ctors how do you know the intent (i.e. how to spot the bug) of this String s{0} ?



3) MUST -->
------------
The problem with your example is that
it only works with "copy initialization" (using =)
but NOT with "direct initialization" (without using =):
the compiler will still call the String(int) constructor
without generating an error
if you write String mystring('x');, as @Arbalest pointed out.
The explicit keyword is meant for
preventing "implicit conversions" that happen in "direct initialization" and "function resolution".
Solution:
----------
a) A better solution to your example would be a simple overload of the constructor: String(char c);
b) another soln To avoid confusion with char argument delete the char constructor: String(char n) = delete;
But in pre C++11, in old compilers - previous method should be used.
i.e. And before = delete programmers would just have added a private overloaded function.
#endif // 0
