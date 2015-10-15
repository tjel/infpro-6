# include <iostream>

using namespace std;

int main( ) 
{ 
    float PI = 3.1415926;                // variables can be initialized during declaration 
    double rad; 
    
    do {
    cout<<"Enter the radius:\n"; 
    cin>>rad;
    } while (rad<=0);
    
    cout<<"Area of the circle is "<<PI*rad*rad<<endl;

    return 0;
}  
