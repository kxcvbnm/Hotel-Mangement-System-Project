using namespace std;
#include"NODE.h"
#include "room.h"

#ifndef Linked_List_H
#define Linked_List_H

class Linked_List{
    protected :
        NODE * head ;
        int size ;
    public :
        bool check_username(string username);
        void show_all();
        virtual void insert_node(NODE* &q)=0;
        virtual ~Linked_List();
        
};


class queue:public Linked_List{
    private :
        NODE *tail ;
    public :
        queue() ;
        void insert_node(NODE* &q);
        void check_in(string username,Room room[],Linked_List*hotel);
        int check_queue(string username);
        void cancel_queue(string username);
        ~queue() ;
};


class list_in_hotel : public Linked_List{
    private :
        NODE *tail ;
    public :

        list_in_hotel();
        void insert_node(NODE* &q);
        void check_out(string username,Room room[]);
        void call_service(string username);
        bool check_username(string username);
        void init_room_in_hotel(Room room[]);
        ~list_in_hotel() ;
        

};


#endif