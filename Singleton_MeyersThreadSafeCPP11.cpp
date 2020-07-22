// Meyer's singleton - thread safe since C++11, as
// static inside the function(here getInstance()), the initialization order is deterministic
// if one thread is initializing, other threads will wait on it and not try to initialize it
#include <iostream>
using namespace std;
class Singleton
{
public:
  // Note :
  // Meyer's singleton thread safe as per C++11.
    // local static variables are thread-safe beginning with C++11 (except when --fno-threadsafe-statics is used in GCC).
    // Plain old static member variables aren't thread safe pre C++11, and the undefined initialization order causes a nightmare situation. This is less of an issue with ints and floats, but if a singleton contains a class, like a string, you're in a really big trouble.
    // Note that technically there's a little functional difference between static member variables and local static variables. When you moved the static inside the Get() function, you made the initialization order deterministic. Local static variables are initialized the first time control passes through the declaration. This makes it safe to call one singleton from another singleton.
    // for better readbility and not needing to declare static member variable, we are using "local static variable" instead of "static member variable"

  // static method returning reference to the Only singleton object
  static Singleton& getInstance()
  {
    static Singleton instance;
    return instance;
  }

private:
  // private CTOR , defaulted  means user declared
  Singleton() = default;
  // private DTOR , defaulted  means user declared
  ~Singleton() = default;
  // private COPY CTOR, deleted meaning "user_declared" COPY Ctor - So NO MOVE Ctor is generated
  Singleton(const Singleton& other) = delete;
  // as we have disabled COPY Ctor, also means we should disable COPY ASSIGNMENT
  // private COPY ASSIGNMENT Operator, user_declared COPY ASSIGNMENT Operator - So NO MOVE ASSIGNMENT Operator is generated
  Singleton& operator=(const Singleton& rhs) = delete;
};

int main()
{

   for ( size_t i= 0; i <=3; ++i){
      Singleton* p = &Singleton::getInstance();
     cout << '\n instance' << p << '\n';
  }
  return 0;
}
