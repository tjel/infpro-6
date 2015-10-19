# include <iostream>
#include <math.h>

using namespace std;

int main( ) 
{ 
    double rad; 
    
    do {
    cout<<"Enter the radius: "; 
    cin>>rad;
    } while (rad<=0);
    
    cout<<"Area of the circle is "<<M_PI*rad*rad<<endl;

    return 0;
}  
