#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>

#include "NODE.h"
#include "Linked_List.h"
#include "login.h"
#include "room.h"


using namespace std;
NODE* Booking(string username,Linked_List** LL);
void room_detailed();

int main(){

    //set up room
    Room room[] ={Room(1,2000,"standard"),Room(2,2000,"standard"),Room(3,2000,"standard"),
                 Room(4,3500,"family"),Room(5,3500,"family"),Room(6,3500,"family"),
                 Room(7,2700,"deluxe"),Room(8,2700,"deluxe"),Room(9,2700,"deluxe")} ;

    Linked_List* hotel_list = new list_in_hotel;
    ((list_in_hotel*)(hotel_list))->init_room_in_hotel(room);

    Linked_List* LL[3]  ; // 1 => standard, 2 => deluxe, 3 => family
    LL[0] = new queue ;
    LL[1] = new queue ;
    LL[2] = new queue ;

    //set up queue
    for(int i = 0 ; i < 3; i++ ){

        string file_name ;

        if(i==0) file_name = "NODE_in_Q_standard.csv" ;
        else if(i==1) file_name = "NODE_in_Q_deluxe.csv" ;
        else if(i==2) file_name = "NODE_in_Q_family.csv" ;
        
        ifstream myFile(file_name); //open file r
        
        if(!myFile.is_open())cout << "can not open the file!."<<endl ;

        else{
        
            string line,user,person,room,n_night ;
            stringstream ss;

            while (getline (myFile, line)) {
                stringstream ss(line);
                getline(ss,user,',');
                getline(ss,person,',');
                getline(ss,room,',');
                getline(ss,n_night,',');

                NODE* customer = new NODE(user,stoi(person),room,stoi(n_night));
                LL[i]->insert_node(customer) ;
            }
        }
        myFile.close();
    }

    //login or register
    string usernames = "" ;
    int input ;
    cout<<"==============================================="<<endl;
    cout<<"||      -------------------------------      ||"<<endl;
    cout<<"||   ~~ | WELCOME TO OUR HOTEL SYSTEM | ~~   ||"<<endl;
    cout<<"||      -------------------------------      ||"<<endl;
    do{ 
        
        //cout << "1. for login.\n2. for register\ninput : ";
        cout<<"==============================================="<<endl;
        cout<<"||  >> 1. LOGIN:    (Enter '1' to Login)     ||"<<endl;
        cout<<"||  >> 2. REGISTER: (Enter '2' to Register)  ||"<<endl;
        cout<<"==============================================="<<endl;
        cout<<"Please Enter your Selection(0 to exit): ";
        string line ;
        cin >> noskipws;
        cin >> line ;
        if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "** Invalid input! **"<<endl;
            continue ;
        }
        else input = line[0] - '0' ;

        if(input == 1) usernames = login();
        else if(input == 2) Register();
        else if(input == 0)break;
        else {
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "** Invalid input! **"<<endl;
            }
    }while(input!=1);

    // user in hotel
    if(hotel_list->check_username(usernames)){

        int input ;
        cout<<"==========================================================="<<endl;
        cout<<"||                     ~ USER MENU ~                     ||"<<endl;
        cout<<"==========================================================="<<endl;
        do{
            cout<<"-----------------------------------------------------------"<<endl;
            cout<<"||  >> 1. CALL SERVICE:   (Enter '1' to Call Service)    ||"<<endl;
            cout<<"||  >> 2. CHECK OUT:      (Enter '2' to Check Out)       ||"<<endl;
            cout<<"||  >> 0. EXIT:           (Enter '0' to EXIT Program)    ||"<<endl;
            cout<<"-----------------------------------------------------------"<<endl;
            cout<<"Please Enter your Selection: ";
            string line ;
            cin >> noskipws;
            cin >> line ;
            if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
                cin.clear();
                cin.ignore(10000,'\n');
                cout << "** Invalid input! **"<<endl;
                continue ;
            }
            else input = line[0] - '0' ;

            if(input == 1) ((list_in_hotel*)(hotel_list))->call_service(usernames);
            else if(input == 2) ((list_in_hotel*)(hotel_list))->check_out(usernames,room);
            else if(input==0)break;
            else {
                cin.clear();
                cin.ignore(10000,'\n');
                cout << "** Invalid input! **"<<endl;
                }
            }while(input!=2);
    }
    // user in Q

    else if(LL[0]->check_username(usernames)||LL[1]->check_username(usernames)||LL[2]->check_username(usernames)){
        int Q ;
        bool check=false ;
        if(LL[0]->check_username(usernames)){
            Q = ((queue*)(LL[0]))->check_queue(usernames) ;
            
            if(Q==0){
                check=false ;
                for(int i=0;i<3;i++){
                    if(room[i].show_available()) check = true;
                }
            }
            if(Q >= 0&&!check){
                //cout <<"===================\nQueue before you : "<< Q <<"\n==================="<<endl ;
                if (Q!=0)cout<<">>>>>>>>>>>> You are NOT the first of the queue! <<<<<<<<<<<<"<<endl;
                else cout<<"Room is not available!!"<<endl;
                cout<<"============================================================="<<endl;
                cout<<">>>>>>>>>>>>>>>>> Queue Until Your Turn : "<<Q<<" <<<<<<<<<<<<<<<<<"<<endl;
                cout<<"============================================================="<<endl;
                do{
                    cout<<"-------------------------------------------------------------"<<endl;
                    cout<<"||   >> 1. CANCEL QUEUE:  (Enter '1' to Cancel Your Queue) ||"<<endl;
                    cout<<"||   >> 0. EXIT:          (Enter '0' to Exit Program)      ||"<<endl;
                    cout<<"-------------------------------------------------------------"<<endl;
                    cout<<"Please Enter your Selection: ";
                    string line ;
                    cin >> noskipws;
                    cin >> line ;
                    if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
                        cin.clear();
                        cin.ignore(10000,'\n');
                        cout << "** Invalid input! **"<<endl;
                        continue ;
                    }
                    else input = line[0] - '0' ;

                    if(input == 0) break;
                    else if(input == 1)  ((queue*)(LL[0]))->cancel_queue(usernames) ;
                    else {
                        cin.clear();
                        cin.ignore(10000,'\n');
                        cout << "** Invalid input! **"<<endl;
                    }
                }while(input!=1) ;
            }
            else if(check){
                    cout<<">>>>>>>>>>>>>> You are the first of the queue! <<<<<<<<<<<<<<"<<endl;
                    do{
                    
                    cout<<"-------------------------------------------------------------"<<endl;
                    cout<<"||   >> 1. CHECK IN:      (Enter '1' to Check In)          ||"<<endl;
                    cout<<"||   >> 2. CANCEL QUEUE:  (Enter '2' to Cancel Your Queue) ||"<<endl;
                    cout<<"||   >> 3. EXIT:          (Enter '0' to Exit Program)      ||"<<endl;
                    cout<<"-------------------------------------------------------------"<<endl;
                    cout<<"Please Enter your Selection: ";
                    
                    string line ;
                    cin >> noskipws;
                    cin >> line ;
                    if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
                        cin.clear();
                        cin.ignore(10000,'\n');
                        cout << "** Invalid input! **"<<endl;
                        continue ;
                    }
                    else input = line[0] - '0' ;

                    if(input == 0) break;
                    else if(input == 1) { ((queue*)(LL[0]))->check_in(usernames,room,hotel_list) ;break;}
                    else if(input == 2) { ((queue*)(LL[0]))->cancel_queue(usernames) ;break;}
                    else {
                        cin.clear();
                        cin.ignore(10000,'\n');
                        cout << "** Invalid input! **"<<endl;
                        }
                    }while(1);
                }
        }
        else if(LL[1]->check_username(usernames)){
            Q = ((queue*)(LL[1]))->check_queue(usernames) ;
            if(LL[1]->check_username(usernames)){
                int Q = ((queue*)(LL[1]))->check_queue(usernames) ;
                if(Q==0){
                    check=false ;
                    for(int i=6;i<9;i++){
                        if(room[i].show_available()) check = true;
                    }
                }
                if(Q >= 0&&!check){
                    //cout <<"===================\nQueue before you : "<< Q <<"\n==================="<<endl ;
                    if (Q!=0)cout<<">>>>>>>>>>>> You are NOT the first of the queue! <<<<<<<<<<<<"<<endl;
                    else cout<<"Room is not available!!"<<endl;
                    cout<<"============================================================="<<endl;
                    cout<<">>>>>>>>>>>>>>>>> Queue Until Your Turn : "<<Q<<" <<<<<<<<<<<<<<<<<"<<endl;
                    cout<<"============================================================="<<endl;
                    do{
                        //cout <<"\n1. for cancel queue.\n0. for exit."<<endl;
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"||   >> 1. CANCEL QUEUE:  (Enter '1' to Cancel Your Queue) ||"<<endl;
                        cout<<"||   >> 0. EXIT:          (Enter '0' to Exit Program)      ||"<<endl;
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"Please Enter your Selection: ";
                        string line ;
                        cin >> noskipws;
                        cin >> line ;
                        if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
                            cin.clear();
                            cin.ignore(10000,'\n');
                            cout << "** Invalid input! **"<<endl;
                            continue ;
                        }
                        else input = line[0] - '0' ;

                        if(input == 0) break;
                        else if(input == 1)  ((queue*)(LL[1]))->cancel_queue(usernames) ;
                        else {
                            cin.clear();
                            cin.ignore(10000,'\n');
                            cout << "** Invalid input! **"<<endl;
                            }
                    }while(input!=1);
                }
                else if(check){
                    cout<<">>>>>>>>>>>>>> You are the first of the queue! <<<<<<<<<<<<<<"<<endl;
                    do{
                        //cout << "Now is your queue!.\n1. for check in.\n2. for cancel queue.\n0. for exit"<<endl;
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"||   >> 1. CHECK IN:      (Enter '1' to Check In)          ||"<<endl;
                        cout<<"||   >> 2. CANCEL QUEUE:  (Enter '2' to Cancel Your Queue) ||"<<endl;
                        cout<<"||   >> 3. EXIT:          (Enter '0' to Exit Program)      ||"<<endl;
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"Please Enter your Selection: ";
                        string line ;
                        cin >> noskipws;
                        cin >> line ;
                        if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
                            cin.clear();
                            cin.ignore(10000,'\n');
                            cout << "** Invalid input! **"<<endl;
                            continue ;
                        }
                        else input = line[0] - '0' ;
                        
                        if(input == 0) break;
                        else if(input == 1) { ((queue*)(LL[1]))->check_in(usernames,room,hotel_list) ;break;}
                        else if(input == 2) { ((queue*)(LL[1]))->cancel_queue(usernames) ;break;}
                        else {
                            cin.clear();
                            cin.ignore(10000,'\n');
                            cout << "** Invalid input! **"<<endl;
                            }
                        }while(1);
                    }
            }

            }
        else if(LL[2]->check_username(usernames)){
            Q = ((queue*)(LL[2]))->check_queue(usernames) ;

            if(LL[2]->check_username(usernames)){
                int Q = ((queue*)(LL[2]))->check_queue(usernames) ;
                if(Q==0){
                    check=false ;
                    for(int i=3;i<6;i++){
                        if(room[i].show_available()) check = true;
                    }
                }
                if(Q >= 0&&!check){
                    if (Q!=0) cout<<">>>>>>>>>>>> You are NOT the first of the queue! <<<<<<<<<<<<"<<endl;
                    else cout<<"Room is not available!!"<<endl;
                    //cout <<"=================================\nQueue before you : "<< Q <<"\n==================="<<endl ;
                    cout<<"============================================================="<<endl;
                    cout<<">>>>>>>>>>>>>>>>> Queue Until Your Turn : "<<Q<<" <<<<<<<<<<<<<<<<<"<<endl;
                    cout<<"============================================================="<<endl;
                    do{
                        //cout <<"Queue before you : "<< Q <<endl ;
                        //cout <<"\n1. for cancel queue.\n0. for exit."<<endl;
                        
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"||   >> 1. CANCEL QUEUE:  (Enter '1' to Cancel Your Queue) ||"<<endl;
                        cout<<"||   >> 0. EXIT:          (Enter '0' to Exit Program)      ||"<<endl;
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"Please Enter your Selection: ";
                        string line ;
                        cin >> noskipws;
                        cin >> line ;
                        if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
                            cin.clear();
                            cin.ignore(10000,'\n');
                            cout << "** Invalid input! **"<<endl;
                            continue ;
                        }
                        else input = line[0] - '0' ;

                        if(input == 0) break;
                        else if(input == 1) ((queue*)(LL[2]))->cancel_queue(usernames) ;
                        else {
                            cin.clear();
                            cin.ignore(10000,'\n');
                            cout << "** Invalid input! **"<<endl;
                            }
                    }while(input!=1);
                }
                else if(check){
                    do{
                        //cout << "Now is your queue!.\n1. for check in.\n2. for cancel queue.\n0. for exit"<<endl;
                        cout<<">>>>>>>>>>>>>> You are the first of the queue! <<<<<<<<<<<<<<"<<endl;
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"||   >> 1. CHECK IN:      (Enter '1' to Check In)          ||"<<endl;
                        cout<<"||   >> 2. CANCEL QUEUE:  (Enter '2' to Cancel Your Queue) ||"<<endl;
                        cout<<"||   >> 0. EXIT:          (Enter '0' to Exit Program)      ||"<<endl;
                        cout<<"-------------------------------------------------------------"<<endl;
                        cout<<"Please Enter your Selection: ";
                        string line ;
                        cin >> noskipws;
                        cin >> line ;
                        if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
                            cin.clear();
                            cin.ignore(10000,'\n');
                            cout << "** Invalid input! **"<<endl;
                            continue ;
                        }
                        else input = line[0] - '0' ;

                        if(input == 0) break;
                        else if(input == 1) {((queue*)(LL[2]))->check_in(usernames,room,hotel_list) ;break;}
                        else if(input == 2)  {((queue*)(LL[2]))->cancel_queue(usernames) ;break;}
                        else {
                                cin.clear();
                                cin.ignore(10000,'\n');
                                cout << "** Invalid input! **"<<endl;
                            }
                        }while(1);
                    }
                }
            }

    }
    else if(usernames!=""){
        int input ;
        cout<<"==========================================================="<<endl;
        cout<<"||                     ~ USER MENU ~                     ||"<<endl;
        cout<<"==========================================================="<<endl;
        do{
            cout<<"-----------------------------------------------------------"<<endl;
            cout<<"||  >> 1. BOOKING:        (Enter '1' to Book Room)       ||"<<endl;
            cout<<"||  >> 2. CHECK DETAIL:   (Enter '2' to Check Detail)    ||"<<endl;
            cout<<"||  >> 0. EXIT:          (Enter '0' to Exit Program)     ||"<<endl;
            cout<<"-----------------------------------------------------------"<<endl;
            cout<<"Please Enter your Selection: ";
            string line ;
            cin >> noskipws;
            cin >> line ;
            if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
                cin.clear();
                cin.ignore(10000,'\n');
                cout << "** Invalid input! **"<<endl;
                continue ;
            }
            else input = line[0] - '0' ;
            if(input == 1){
                NODE *a = Booking(usernames,LL);
                if(a->show_roomtype()=="standard")LL[0]->insert_node(a);
                else if(a->show_roomtype()=="deluxe")LL[1]->insert_node(a);
                else if(a->show_roomtype()=="family")LL[2]->insert_node(a);
            }
            else if(input == 2) room_detailed();
            else if(input == 0)break;
            else {
                cin.clear();
                cin.ignore(10000,'\n');
                cout << "** Invalid input! **"<<endl;
                }
            }while(input!=1);    
    }



    // delete all Link list
    for(int i=0; i<3 ; i++)delete LL[i] ;
    delete hotel_list;
       
    return 0;
}


    

NODE* Booking(string username,Linked_List** LL)
{  
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //ใช้ sleep
    system("clear");
    cin.clear();
    cin.ignore(10000,'\n');
    cout<<endl<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"====== BOOKING MENU ======="<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<">>>>>> Type of room <<<<<<"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"1.Standard Room (1)"<<endl;
    cout<<" - Room Capacity : 1-2"<<endl;
    cout<<" - Price/Night : 2000 Baht"<<endl;
    cout<<" - Queue : " << ((queue*)(LL[0]))->check_queue(username) <<endl;
    cout<<"---------------------------"<<endl;
    cout<<"2.Family Room (2)"<<endl;
    cout<<" - Room Capacity : 2-5"<<endl;
    cout<<" - Price/Night : 3500 Baht"<<endl;
    cout<<" - Queue : "<< ((queue*)(LL[2]))->check_queue(username)<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"3.Deluxe Room (3)"<<endl;
    cout<<" - Room Capacity : 1-2"<<endl;
    cout<<" - Price/Night : 2700 Baht"<<endl;
    cout<<" - Queue : "<<((queue*)(LL[1]))->check_queue(username)<<endl;
    cout<<"---------------------------"<<endl;
    bool check_type = false;
    bool check_number = false;
    int n=0,type=0,night=0;
    string room;
    while(!check_number)
    {   
        cout<<"Please enter number of people(1-5 people): ";
        string line ;
        cin >> noskipws;
        cin >> line ;
        if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "** Invalid input!**"<<endl;
            continue ;
        }
        else n = line[0] - '0' ;

        if(n>0 && n<=5) 
        {
            check_number = true;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        else {cout<<"** Invalid input! **"<<endl;cin.clear();cin.ignore(100,'\n');}

    }
    while(!check_type)
    {
        cout<<"---------------------------"<<endl;
        cout<<"Select type of room you want to book in (1-3): ";
        string line ;
        cin >> noskipws;
        cin >> line ;
        if((!isdigit(line[1])&&line[1]!='\0')||isdigit(line[1])){
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "** Invalid input! **"<<endl;
            continue ;
        }
        else type = line[0] - '0' ;
        
        if(type == 1){
            room = "standard";
            if(n>2)
            {
                cout<<">>> Too many people for a standard room! <<<"<<endl<<"Please choose again! "<<endl;
                continue;
            }
            check_type = true;
        }
        else if(type == 2)
        {
            room = "family";
            if(n<2)
            {
                cout<<">>> Minimum occupancy not met for a family room! <<<"<<endl<<"Please choose again!"<<endl;
                continue;
            }
            check_type = true;
        }
        else if(type == 3)
        {
            room = "deluxe";
            if(n>2)
            {
                cout<<">>> Too many people for a deluxe room! <<<"<<endl<<"Please choose again!"<<endl;
                continue;
            }
            check_type = true;
        }
        else{
            cout<<"** Invalid Input Please Select Again! **"<<endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
    }
    cout<<"---------------------------"<<endl;
    cin.clear();
    cin.ignore(10000,'\n');
    int loop = 1 ;
    while(loop){

        cout<<"Please enter the number of nights you plan to stay: ";
    
        string line ;
        bool flag = true;
        cin >> noskipws;
        cin >> line ;
        for(int i = 0 ; i < line.length();i++){
            if(!isdigit(line[i]))flag = false ;
        }
        if(!flag) {cout<<"** Invalid input!! **"<<endl;cin.clear();cin.ignore(100,'\n') ;continue;}
        else night= atoi(line.c_str()) ;
        
        if(night<=0){
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"** Invalid Input Please Select Again! **"<<endl;
        }else loop = 0 ;
    }
    
    
    NODE* t = new NODE(username,n,room,night);
    cout<<endl<<"-------------------------------------------------------------------------"<<endl;
    cout<<">> You have been added to the queue. Please wait until it's your turn. <<"<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
    return t;
} 

void room_detailed(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    //sleep(1500);
    system("clear");
    cout<<"             ===================="<<endl;
    cout<<"             |  ROOM'S DETAILS  |"<<endl;
    cout<<"             ===================="<<endl<<endl;
    cout<<"             --1) STANDARD TYPE--             "<<endl;
    cout<<"The Standard rooms - where comfort meets simplicity"<<endl;
    cout<<"             PRICE/NIGHT   : 2000 bath"<<endl;
    cout<<"             ROOM CAPACITY : 1-2"<<endl;
    cout<<"             FURNITURE     : 1 Kettle"<<endl;
    cout<<"                           : 1 Small Refrigerator"<<endl;
    cout<<"                           : 1 King size bed"<<endl;
    cout<<"                           : 1 Toiletry set"<<endl;
    cout<<"                           : 1 Lamp"<<endl;
    cout<<"                           : 1 Sleeper"<<endl;
    cout<<"                           : 1 Towel"<<endl;
    cout<<"                           : 1 hairdryer"<<endl<<endl;
    cout<<"             -- 2) FAMILY TYPE --             "<<endl;
    cout<<"The Family room - Where bonds strengthen and memories flourish"<<endl;
    cout<<"             PRICE/NIGHT   : 3500 bath"<<endl;
    cout<<"             ROOM CAPACITY : 2-5"<<endl;
    cout<<"             FURNITURE     : 1 Kettle"<<endl;
    cout<<"                           : 1 Large Refrigerator"<<endl;
    cout<<"                           : 3 King size bed"<<endl;
    cout<<"                           : 3 Toiletry set"<<endl;
    cout<<"                           : 2 Lamp"<<endl;
    cout<<"                           : 3 Sleeper"<<endl<<endl;
    cout<<"                           : 1 Table"<<endl;
    cout<<"                           : 1 Chair"<<endl;
    cout<<"                           : 3 Towel"<<endl;
    cout<<"                           : 1 hairdryer"<<endl<<endl;
    cout<<"             -- 3) DELUXE TYPE --             "<<endl;
    cout<<"The Deluxe room - Indulge in luxury's embrace"<<endl;
    cout<<"             PRICE/NIGHT   : 2700 bath"<<endl;
    cout<<"             ROOM CAPACITY : 1-2"<<endl;
    cout<<"             FURNITURE     : 1 Kettle"<<endl;
    cout<<"                           : 1 Large Refrigerator"<<endl;
    cout<<"                           : 2 King size bed"<<endl;
    cout<<"                           : 2 Toiletry set"<<endl;
    cout<<"                           : 2 Lamp"<<endl;
    cout<<"                           : 2 Sleeper"<<endl<<endl;
    cout<<"                           : 1 Table"<<endl;
    cout<<"                           : 1 Chair"<<endl<<endl;
    cout<<"                           : 2 Bathrobe"<<endl;
    cout<<"                           : 1 Towel"<<endl;
    cout<<"                           : 1 Bathtub"<<endl;
    cout<<"                           : 1 hairdryer"<<endl;
    cout<<"                           : Balcony"<<endl<<endl;
    cout<<"---------------------------------------------"<<endl<<endl;
    cout<<"            ======================"<<endl;
    cout<<"            | ADDITIONAL SERVICES |"<<endl;
    cout<<"            ======================"<<endl<<endl;
    cout<<"            FOOD/DISH      : 120 bath"<<endl;
    cout<<"            LAUNDRY/ITEM   : 50  bath"<<endl;
    cout<<"            SHUTTLE/RIDE   : 100 bath"<<endl;
    cout<<"            EXTRA BED/BED  : 250 bath"<<endl;
    cout<<"---------------------------------------------"<<endl<<endl;
    cout<<"            ======================"<<endl;
    cout<<"            |     COMMON AREA    |"<<endl;
    cout<<"            ======================"<<endl<<endl;
    cout<<"            SWIMMING POOL  : FREE"<<endl;
    cout<<"            FITNESS        : FREE"<<endl;
    cout<<"---------------------------------------------"<<endl<<endl;
    cout<<"            ======================"<<endl;
    cout<<"            |      AMENITIES     |"<<endl;
    cout<<"            ======================"<<endl<<endl;
    cout<<"            STORE          : 7-11"<<endl;
    cout<<"                           : Starbucks"<<endl;
    cout<<"                           : KFC"<<endl;
    cout<<"                           : Souvenirs shop"<<endl;
    cout<<"                           : ATM"<<endl<<endl;
    cout<<"============================================="<<endl;
    cout<<"|      Where comfort meets hospitality      |"<<endl;
    cout<<"|    and memories find their perfect stay   |"<<endl;
    cout<<"|          - until we meet again -          |"<<endl;
    cout<<"============================================="<<endl;
    cin.clear();
    cin.ignore(10000,'\n');
}

