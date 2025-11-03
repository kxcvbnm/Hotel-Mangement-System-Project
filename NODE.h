using namespace std;
#ifndef NODE_H
#define NODE_H

class NODE{
    private :
        NODE* next ;
        std::string username , room_type ;
        int n_person ;
        int room_id ;
        int night;
        int food,laundry,shuttle,extrabed ;
    public :
        NODE(std::string a, int b,std::string c,int d);
        NODE(std::string a,std::string b,int c,int d,int e,int f, int g, int h, int i);
        //show_node(std::string);
        void show_node(); //สร้างไว้ check constuctor list_in_hotel เฉยๆ
        ~NODE();
        NODE* move_next();
        string show_username();
        int show_nperson();
        int show_room_id();
        string show_roomtype();
        int show_night();
        int show_food();
        int show_laundry();
        int show_shuttle();
        int show_extrabed();
        void insert(NODE*& );
        void set_next_NULL();
        void set_room_id(int);
        void set_food(int);
        void set_laundry(int);
        void set_shuttle(int);
        void set_extrabed(int);

};

#endif