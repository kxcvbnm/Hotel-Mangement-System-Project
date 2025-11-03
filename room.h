#include <iostream> 
using namespace std;
#ifndef Room_H
#define Room_H

class Room{
    private :
        int room_id,price ;
        string room_type ;
        bool available ;
    public :
        Room(int,int ,const string );
        int show_price();
        int show_room();
        string show_room_type();
        bool show_available() ;
        void set_available(bool) ;
};

#endif
