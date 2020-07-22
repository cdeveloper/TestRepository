#include <iostream>
using namespace std;

typedef struct Result { int sum; int startIndex; int endIndex;} Result;
Result result;

Result maxSumSubArray(int* a , int nsize)
{
  if (nsize > 0)
  {
    int startIndex, endIndex;
    startIndex = endIndex = 0;

    int max_so_far = a[0];
    int max_ending_here = a[0];

    for (int i = 1; i < nsize; ++i)
    {
      max_ending_here = max_ending_here + a[i];

      if (a[i] > max_ending_here) // current is greater than running_total(prev_running + current)
      {
        startIndex = i;           // current element is start of new sum
        max_ending_here = a[i];
      }

      if (max_ending_here > max_so_far) // running_total is greater than the global_max at this index
      {
        endIndex = i;                   // so current index is the endInex of max sub array
        max_so_far = max_ending_here;
      }
    }

    result.sum = max_so_far;
    result.startIndex = startIndex;
    result.endIndex = endIndex;
  }

  return result;
}


int main()
{
  // int inputArray[] = { -3, 2, 3, -2, -1} ;
  int inputArray[] = { -3, -5, -2, -1} ;
  // int inputArray[] = { } ;
  // int inputArray[] = { 1 } ;
  // int inputArray[] = { -1 } ;
  // int inputArray[] = { 1, 2, 3 } ;
  int nSize = sizeof(inputArray)/sizeof(inputArray[0]);
  Result result = maxSumSubArray(inputArray, nSize);
  cout <<"\nResult : \n";
  cout << "\nMax Sum     = " << result.sum;
  cout << "\nStart Index = " << result.startIndex;
  cout << "\nEnd Index   = " << result.endIndex;
  cout <<"\n\nElements    = ";
  for(int i = result.startIndex; i < result.endIndex + 1; ++i )
  {
   cout <<inputArray[i] << " ";
  }

cout <<'\n';
return 0;
}
