#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "NODE.h"

using namespace std ;

NODE::NODE(string a,int b,string c, int d){
    username = a;
    n_person = b;
    room_type = c;
    night = d;
    next = NULL;
    room_id = 0 ;
    food = 0;
    laundry=0;
    shuttle=0;
    extrabed = 0;
}
NODE::NODE(string a,string b,int c,int d,int e,int f, int g, int h, int i){
    username = a;
    room_type = b;
    n_person = c;
    room_id = d;
    night = e;
    food = f;
    laundry = g;
    shuttle = h;
    extrabed = i;
    next = NULL;
}


NODE::~NODE(){

    string file_name ;
    if(show_roomtype()=="standard") file_name = "NODE_in_Q_standard.csv" ;
    else if(show_roomtype()=="deluxe") file_name = "NODE_in_Q_deluxe.csv" ;
    else if(show_roomtype()=="family") file_name = "NODE_in_Q_family.csv" ;
    
    if(room_id==0){
        ofstream myFile(file_name,ios::app); //w
        // Send data to the stream
        myFile << username <<","<< n_person <<"," << room_type <<"," << night<<endl; 
        // Close the file
        myFile.close();
    }

    else if(room_id!=-1){
        ofstream myFile("NODE_in_hotel.csv",ios::app); //w
        // Send data to the stream username,room_type,n_person,room_id,night,food,laundry,shuttle,extrabed
        myFile << username <<"," << room_type <<"," << n_person <<"," << room_id <<","<<night<<","<<food<<","<<laundry<<","<<shuttle<<","<<extrabed<<endl; 
        // Close the file
        myFile.close();
    }

}

NODE* NODE::move_next(){
    return next;
}

string NODE:: show_username(){
    return username;
}

int NODE:: show_nperson(){
    return n_person;
}

int NODE:: show_room_id(){
    return room_id;
}

string NODE:: show_roomtype(){
    return room_type;
}

int NODE:: show_night(){
    return night;
}

int NODE:: show_food(){
    return food;
}

int NODE:: show_laundry(){
    return laundry;
}

int NODE:: show_shuttle(){
    return shuttle;
}

int NODE:: show_extrabed(){
    return extrabed;
}

void NODE::insert(NODE*& x){
     this -> next = x ;
}

void NODE::set_next_NULL(){
    this->next=NULL;
}

void NODE::set_room_id(int a){
    room_id=a;
}


void NODE::set_food(int Food){
    this->food = Food;
}
void NODE::set_laundry(int Laundry){
    this->laundry = Laundry;
}
void NODE::set_shuttle(int Shuttle){
    this->shuttle = Shuttle;
}
void NODE::set_extrabed(int Extrabed){
    this->extrabed = Extrabed;
}

void NODE::show_node(){
    cout<<"Name: "<<username<<endl;
    cout<<"Room type: "<<room_type<<endl;
    cout<<"Number of person: "<<n_person<<endl;
    cout<<"Room ID: "<<room_id<<endl;
    cout<<"Night: "<<night<<endl;
    cout<<"Food: "<<food<<endl;
    cout<<"Laundry: "<<laundry<<endl;
    cout<<"Shuttle: "<<shuttle<<endl;
    cout<<"Extra Bed: "<<extrabed<<endl;
    cout<<"==========================="<<endl;
}
