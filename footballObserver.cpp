#include <iostream>
#include <unordered_set>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::ostream; // error: ‘ostream’ does not name a type
using std::string;
using std::unordered_set;

class Subject; // fwd declare Subject first.
// Important Observer needs to be defined first with subject forward declared as we call concrete obs in Subject's notify
class Observer
{
   public :
      // class Subject; // fwd declare so can only use pointer or reference otherwise incomplete type
         Observer() = default;
         virtual ~Observer(){}; // must define or undefined reference error so empty body
         virtual void event(Subject* changedSubject) = 0;
         virtual string name() = 0;
};

class Subject
{
   public :
         Subject() = default;
         virtual ~Subject(){};
         virtual string name() = 0;

         // add obs
         void addObserver(Observer *pObsvr)
         {
            if (Observers.find(pObsvr) == Observers.end())
            {
               Observers.insert(pObsvr);
            }
         }
         // detach obs
         void removeObserver(Observer *pObsvr)
         {
               Observers.erase(Observers.find(pObsvr));
         }
         // notify obs pure virtual
         virtual void notifyEventToObservers()
         {
            for (auto const& obs : Observers)
            {
               obs->event(this);
            }
         }
         // display Observers
         void listObservers()
         {
            cout << "\n\nSubject : " << name();
            cout <<"\nAnd it's Observers -> { ";
            for(auto const& obs : Observers)
            {
               cout << obs->name() << " ";
            }
            cout<<"}\n";
         }
   private :
         unordered_set<Observer*> Observers;
};

class BallSubject : public Subject
{
   public :
      BallSubject(string name) : mSubjName(name) {}
      ~BallSubject() {}

      virtual string name() override { return mSubjName; }
      string mSubjName;
};


class BallObserver : public Observer
{
   public :
      BallObserver(string name) : mObsName(name) {};
      virtual ~BallObserver() {};

      void event(Subject* changedSubject) override
      {
         cout << "\n" << "Subject : " << changedSubject->name() << " changed it's position, notified to Observer : "  << mObsName;
      }

      virtual string name() override { return mObsName; }
      string mObsName;
};

int main()
{
#if 1
  cout << "\n\n";
#endif
BallSubject football("football");
BallObserver messi("Messi");
BallObserver ronaldo("Ronaldo");

football.addObserver(&messi);
football.addObserver(&ronaldo);
football.listObservers();
// football changed it's position
football.notifyEventToObservers();

football.removeObserver(&messi);
football.listObservers();
// football changed it's position
football.notifyEventToObservers();

cout << "\n";
return 0;
}
