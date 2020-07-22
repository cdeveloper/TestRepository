// sort array
#include <iostream>
using namespace std;

#define SIZE(a) (sizeof(a)/sizeof(a[0]));

#if 0
// #if 0 is hack for commenting code which has comments, multiple comments

// void sort( int (&a)[], int n) --> DOES NOT work in c++ as a[n] != a[]
Because It is an array without size. Incomplete type . ALSO
In C++ there is unlike as in C no concept of compatible types and the type T[] is unrelated to T[N].
You need to make the reference have a size and the size must equal the one of the array you pass.
C++ also bans references to arrays without bounds as function parameter types (perhaps for this reason).

please note [] has higher preference to & so , reference is (&a)[] and not &a[] otherwise it is array of references

What you can do
// 1) can create template to pass size

template<typename T, std::size_t S>
void my_func(T (&arr)[S]) {
   // do stuff
}

// 2) or pass with exact size
void sort(int (&a)[5], int 5)

----------------
Note on swapping :
  using temp like shown below or
  using any temp variable
  using xor
  a = a ^ b; b = a ^ b; a = a ^ b; // or one liner a ^= b ^= a ^= b;
  using arithmetic
  a = a + b - (b = a);

#endif

void sort(int *a, int n)
{
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n ; ++j)
  {
    if (a[j] < a[i])
    {
      int temp = a[i];
      a[i] = a[j];
      a[j] = temp;
    }

  }

}
int main()
{
  int a[] = {3, 4, 2, 1, 5};
  int n = SIZE(a);
  sort(a, n);

  for(auto const& ele : a)
  {
    cout << " " << ele ;
  }
  return 0;
}
