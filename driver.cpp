#include "elevator.h"
class Tester{
public:
    /******************************************
    * Test function declarations go here! *
    ******************************************/
};
int main(){
    Elevator anElev;
    //Creating an elevator with 10 floors
    for (int i = 1; i <= 10; i++)
        anElev.insertAtTail(i);
    cout << "\nCarrying Alice from 6th floor to 10th floor:\n";
    cout << "\tAlice enters the elevator:\n";
    anElev.enter(6,"Alice");
    anElev.dump();
    cout << "\n\tMoving to 10th floor:\n";
    anElev.move(6,10);
    anElev.dump();
    anElev.exit(10,"Alice");
    cout << "\n\tRemoving the 2nd floor:\n";
    anElev.removeFloor(2);
    anElev.dump();
    return 0;
}