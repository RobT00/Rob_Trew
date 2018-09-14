#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main ()
{
   // local variable declaration:
   srand(time(NULL));
   int a = rand() % 3;

   // check the boolean condition
   if ( a < 1 )
   {
       // if condition is true then print the following
       cout << "Goodbye Cruel World!" << endl;
   }
   else if ( a == 1 )
   {
       cout << "It's in the hands of the Gods..." << endl;
   }
   else
   {
       // if condition is false then print the following
       cout << "Hello World!" << endl;
   }
   cout << "value of a is : " << a << endl;

   return 0;
}
