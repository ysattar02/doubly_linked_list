#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <string>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
class Tester;//this is your tester class, you add your test functions in this class
class Floor{
    friend class Grader;
    friend class Tester;
    friend class Elevator;
public:
    Floor(int floor, string passenger = ""){
        // note: floors can be negative, i.e. undergraound floors
        m_floorNum = floor;
        m_passenger = passenger;
        m_next=nullptr;
        m_previous=nullptr;
    }
    ~Floor(){}
private:
    int m_floorNum;
    string m_passenger;
    Floor* m_next;
    Floor* m_previous;
};
class Elevator{
    friend class Tester;
    friend class Grader;
public:
    Elevator();
    ~Elevator();
    Elevator(const Elevator & rhs);
    const Elevator & operator=(const Elevator & rhs);
    bool insertAtHead(int floor, string passenger="");// inserting at the head of linked list
    bool insertAtTail(int floor, string passenger="");// inserting at the tail of linked list
    bool move(int origin, int destination);// elevator moves from origin to destination
    bool enter(int floor, string passenger);// passenger enters
    string exit(int floor, string passenger);// passenger exists
    bool removeFloor(int floor);//removes a node from the linked list
    bool insertFloor(int floor);//inserts node in the middle of linked list
    bool checkFloor(int floor);// check whether floor exists
    void dump();// for debugging purposes
    void clear();// deallocating the memory and reinitializes everything

private:
    Floor* m_ground;// this is the head of the linked list
    Floor* m_top;// this is the tail of the linked list

    /******************************************
    * Private function declarations go here! *
    ******************************************/
    Floor* traverse(int floor); //returns null if floor out of range
    //otherwise will return node matching floor index or neighboring node
    bool in_range(int floor);
    void insert_in_front(int floor, Floor* temp, string passenger);
    void insert_behind(int floor, Floor* temp, string passenger);
    void deep_copy(const Elevator&);
};
#endif