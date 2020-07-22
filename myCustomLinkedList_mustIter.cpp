#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream; // error: ‘ostream’ does not name a type

struct Node
{
  Node(int data) : mData(data), mpPrev(nullptr), mpNext(nullptr){}
  int   mData;
  Node* mpPrev;
  Node* mpNext;
};

class Iterator
{
  public :
    Iterator(Node* pNode) : mpNode(pNode) {}

    int operator*() { return mpNode->mData; }
    bool operator==(const Iterator& rhs) const { return (mpNode == rhs.mpNode); }
    bool operator!=(const Iterator& rhs) const { return !(*this == rhs);  }
    // pre increment
    Iterator& operator++()
    {
      if (mpNode)    // calling ++ on nullptr will cause crash or UB
      {
        mpNode = mpNode->mpNext;
        return *this;
      }
    }

  private :
    Node* mpNode;
};

class LinkedList
{
  public:
    LinkedList()  : mSize(0), mpHead(nullptr), mpTail(nullptr) {}
    ~LinkedList()
      { int count = 0;
        while(!empty())
        {
            pop_back();
            cout << "\n deleted node number : " << ++count;
        }

      }

    bool size()  const { return mSize; }
    bool empty() const { return (size() == 0); }

    // push_front
    void push_front(int data)
    {
      Node *node = new Node(data);
      if (empty())
      {
        mpHead = mpTail = node;
      }
      else
      {
        node->mpNext = mpHead;
        node->mpPrev = nullptr;
        mpHead->mpPrev = node;
        mpHead = node;
      }
      mSize = mSize + 1;
    }
    // pop_back
    void pop_back()
    {
       if (!empty())
       {
         Node *pCurrentTail = mpTail;

         if (mpHead == pCurrentTail) // there is only one element, so need to update head also
         {
            mpHead = nullptr;
         }
         else                       // there are more than one element i.e. ( mpTail->mpPrev) exists, so update tail
         {
            mpTail = pCurrentTail->mpPrev;        // new last node
            mpTail->mpNext = nullptr;              // important, new last node next should be nullptr
         }

         delete pCurrentTail;
         pCurrentTail = nullptr;
         mSize = mSize - 1;
       }
    } // pop_back

    // Iterators
    Iterator begin() const { return Iterator(mpHead);  }
    Iterator end() const   { return Iterator(nullptr); }

    // displayList
    void displayList()
    { cout <<"\n\n";
      for (auto const& ele : *this)
      {
        cout << " " << ele;
      }
    }

  private:
    size_t mSize;
    Node*  mpHead;
    Node*  mpTail;
};




#include <forward_list>
std::forward_list<int> stdLL = { 1, 2, 3 };


int main()
{
#if 1
  cout << "\n\n";
  LinkedList ll;
  ll.push_front(3);  ll.push_front(2);  ll.push_front(1);
  ll.displayList();
#endif

  #if 0
//  for(const auto& ele : stdLL) { cout << "  " << ele << " ";}
auto it = stdLL.begin();
  for( ; it != stdLL.end(); ++it) { cout << "\n address :  " <<  " and Value  " << *it << " ";}

  cout << " and now : " << *++it;
  cout << "\n lets see what happens : \n";
#endif


  return 0;
}
