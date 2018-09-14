#include <iostream>
#include <iomanip> //for io manipulation//
using namespace std;

int main() {
    int i, j;
    /* print table heaer */
    cout << "Times | ";
    for (i=1;i<=10;i++)
     {
        cout << setw(5) << i;
     }
    cout << "\n";
    /* print a line of ----------- */
    for (i=1;i<=58;i++) cout << "-";
    cout << "\n";

    /* Now print rows 1 to 12 */
    for (j=1;j<=12;j++)
       {
       /* print table row */
       cout << setw(5) << j << " | ";//This is the left hand column
       for (i=1;i<=12;i++)
        {
            cout << setw(5) << i*j;
        }
        cout << "\n";
     }

    return 0;
}
