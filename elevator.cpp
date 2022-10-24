#include "elevator.h"
Elevator::Elevator()
:m_ground(nullptr), m_top(nullptr)
{
    //done
}
Elevator::~Elevator(){
    //done
    clear();
}
void Elevator::clear(){
    //done
    Floor* temp; //create temp pointer
    while (m_ground != nullptr){
        temp = m_ground; //set temp to ground
        m_ground = m_ground->m_next; //move ground forward
        temp->m_next = nullptr;  //sets next to null
        temp->m_previous = nullptr;  //sets next to null
        delete temp;
    }
    temp = nullptr;
    m_top = nullptr;
}

bool Elevator::insertAtHead(int floor, string passenger){
    //done
    if (m_ground == nullptr){ //push-front operation
        m_ground = m_top = new Floor(floor, passenger);
        return true;
    }
    else if (m_ground->m_floorNum > floor){
        m_ground->m_previous =  new Floor(floor, passenger); //setting new node
        m_ground->m_previous->m_next = m_ground; //reassigning the forwards link to the ground
        m_ground = m_ground->m_previous; //moving the head to previous node
        return true;
    }
    return false; //if both cases fail return false
}

bool Elevator::insertAtTail(int floor, string passenger){
    //done
    //this function is the inverse of the head, switch top and ground and prev and next
    if (m_top == nullptr){ //push-front operation
        m_top = m_ground = new Floor(floor, passenger);
        return true;
    }
    else if (m_top->m_floorNum < floor){
        m_top->m_next =  new Floor(floor, passenger); //setting new node
        m_top->m_next->m_previous = m_top;
        m_top = m_top->m_next;
        return true;
    }
    return false; //if both cases fail return false
}
//40, 171, 185
bool Elevator::removeFloor(int floor){
    //done
    Floor* temp = traverse(floor);
    //checking case if floor to remove is the ground or the tail
    if (temp == nullptr){
        throw out_of_range("Not in Range");
    }
    if (temp->m_floorNum != floor){
        return false;
    }

    if (temp == m_ground){ //if floor to remove is ground
        m_ground = m_ground->m_next;
        temp->m_next = nullptr;
        if (m_ground != nullptr) {
            m_ground->m_previous = nullptr;
        }
        else{
            m_top = nullptr;
        }
    }
    else if (temp == m_top) { //if floor to remove is top
        m_top = m_top->m_previous;
        temp->m_previous = nullptr;
        if (m_top != nullptr) {
            m_top->m_next = nullptr;
        }
    }
    else{ //if floor to remove is in middle
        temp->m_previous->m_next = temp->m_next;
        temp->m_next->m_previous = temp->m_previous;
        temp->m_previous = nullptr;
        temp->m_next = nullptr;
    }

    //clearing out temp
    delete temp;
    temp = nullptr;
    return true;
}

bool Elevator::insertFloor(int floor){
    //done
//    if (m_ground == nullptr){
//        return insertAtHead(floor);
//    }
//    if (m_top->m_floorNum < floor){
//        return insertAtTail(floor);
//    }
    Floor* temp = traverse(floor); //setting temp node to target floor using floor
    //checking case if floor to remove is the ground or the tail
    if (temp == nullptr){
        throw out_of_range("Not in Range"); //throw to exit function w error code
    }
    if (temp->m_floorNum == floor){
        return false; //if floor already in list
    }
    if (temp->m_floorNum < floor){ //case if there is a floor before and not sure about after
        insert_behind(floor, temp, "");
    }
    else{
        insert_in_front(floor, temp, "");
    }
    temp = nullptr;
    return true;
}

bool Elevator::checkFloor(int floor){
    //done
    Floor* temp = traverse(floor);
    if (temp == nullptr){
        throw out_of_range("Not in Range");
    }
    //checking case if floor to remove is the ground or the tail
    return temp->m_floorNum == floor; //bool return statement
}

bool Elevator::move(int origin, int destination){
    //done
    Floor* temp_1 = traverse(origin);
    Floor* temp_2 = traverse(destination);
    if (temp_1 == nullptr || temp_2 == nullptr){
        throw out_of_range("Error: Out of Range");
    }
    if (temp_1->m_floorNum != origin || temp_2->m_floorNum != destination){
        return false;
    }
    if (!temp_2->m_passenger.empty()){ //in the case that the destination floor is already occupied
        cout << "Floor is Occupied!" << endl;
        return false;
    }
    temp_2->m_passenger = temp_1->m_passenger; //moves string val
    temp_1->m_passenger.clear(); //empties string
    //ask prof what to do in the already occupied case
    return true;
}

string Elevator::exit(int floor, string passenger){
    //done
    Floor *temp = traverse(floor);
    if (temp == nullptr || temp->m_floorNum != floor) { //if floor doesnt exist
        return "";
    }
    if (temp->m_passenger == passenger){
        temp->m_passenger = "";
    }
    return passenger;
}

bool Elevator::enter(int floor, string passenger){
    //done
    Floor *temp = traverse(floor);
    if (temp == nullptr || temp->m_floorNum != floor) { //if floor doesnt exist
        return false;
    }
    if (temp->m_passenger.empty()){
        temp->m_passenger = passenger;
        return true;
    }
    return false;
}

Elevator::Elevator(const Elevator& rhs)
        :m_ground(nullptr), m_top(nullptr)
{
    //done
    deep_copy(rhs);
}

const Elevator & Elevator::operator=(const Elevator& rhs){
    //done
    if (this != &rhs){ //this points to invoking object, is a pointer
        //&rhs = address of rhs
        clear();
        deep_copy(rhs);
    }
    return *this;
}

void Elevator::dump(){
    if (m_top != nullptr){
        Floor *temp = m_top;
        cout << "Top Floor " ;
        while(temp->m_previous != nullptr){
            cout << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
            temp = temp->m_previous;
        }
        cout << "Ground Floor " << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
    }
}

Floor* Elevator::traverse(int floor) { //avoid traversing through list in diferent cases
    //done
    if (!in_range(floor)){
        return nullptr;
    }
    Floor *temp = nullptr;
    if (floor - m_ground->m_floorNum < m_top->m_floorNum - floor){
        //if true, floor is closer to ground than top floor
        temp = m_ground;
        while (temp->m_floorNum < floor){
            temp = temp->m_next;
        }
    }
    else {
        temp = m_top;
        while (temp->m_floorNum > floor) {
            temp = temp->m_previous;
        }
    }
    return temp;
}

bool Elevator::in_range(int floor) {
    //done
    if (m_ground == nullptr || floor < m_ground->m_floorNum || floor > m_top->m_floorNum){
        return false;
    }
    return true;
}

void Elevator::insert_in_front(int floor, Floor *temp, string passenger) {
    if (temp == m_ground){ //new floor is the new lowest floor case
        m_ground->m_previous = new Floor(floor, passenger);
        m_ground->m_previous->m_next = m_ground; //connecting link again
        m_ground = m_ground->m_previous;
    }
    else{ //case if new floor is in middle of two existing floors
        Floor* p = new Floor(floor, passenger);
        p->m_previous = temp->m_previous; //four pointers to link, two on each side
        temp->m_previous = p;
        p->m_next = temp;
        p->m_previous->m_next = p;
        p = nullptr;
    }
}

void Elevator::insert_behind(int floor, Floor *temp, string passenger) {
    if (temp == m_top){ //new floor is the new highest floor case
        m_top->m_next = new Floor(floor, passenger);
        m_top->m_next->m_previous = m_top; //connecting link again
        m_top = m_top->m_next;
    }
    else{ //case if new floor is in middle ot two existing floors
        Floor* p = new Floor(floor, passenger);
        p->m_next = temp->m_next; //four pointers to link
        temp->m_next = p;
        p->m_previous = temp;
        p->m_next->m_previous = p;
        p = nullptr;
    }
}

void Elevator::deep_copy(const Elevator& src){
    if (src.m_ground == nullptr){
        return;
    }
    this->m_ground = new Floor(src.m_ground->m_floorNum, src.m_ground->m_passenger);
    Floor *temp = src.m_ground->m_next;
    this -> m_top = this->m_ground;
    while (temp != nullptr){
        this->m_top->m_next = new Floor(temp->m_floorNum, temp->m_passenger);
        this->m_top->m_next->m_previous = this->m_top;
        this->m_top = this->m_top->m_next;
        temp = temp->m_next;
    }

}