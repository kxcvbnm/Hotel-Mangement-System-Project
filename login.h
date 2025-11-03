#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <cstdlib>
bool user_exist(std::string);
bool check_name(std::string);

using namespace std ;

string login(){

    cin.clear();
    cin.ignore(50,'\n');
    vector<string> data;  //vector
    string line,username,password;
    stringstream ss;
    int attempt = 0;

    ifstream myFile("username.csv"); //open file r

    if(!myFile.is_open()) cout << "Can't open file." ;
    
    while (getline (myFile, line)) {
        stringstream ss(line);
        getline(ss,username,',');
        getline(ss,password,',');
        
        data.push_back(username);
        data.push_back(password);
    }

    while(attempt < 3){
    cout<<"---------------------------"<<endl;
    cout<<"|        ~ LOGIN ~        |"<<endl;
    cout<<"---------------------------"<<endl;
    cout << "Username: ";
    getline(cin,username);

    cout << "Password: ";
    cin >> password;
    cout<<"---------------------------"<<endl;

    for(int i = 0 ;i < data.size();i += 2){ 
        if(username == data[i] && password == data[i+1]){
            cout <<endl<< ">> Login Successful! <<" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //ใช้ sleep
            system("clear");
            cin.clear();
            cin.ignore(10000,'\n');
            return username;
            
        }          
    }
    
    cout << "** Incorrect username or password. Please try again! **" << endl;
    attempt++;
    cin.clear();
    cin.ignore();
    }
    cout << "** Too many login attempt. Please try again later! **" << endl;
    exit(0);
    /*
    
    ทำหน้าล็อกอินรับอินพุต แล้วนำไปเช็คกับค่าใน csv file 
    โดย data[เลขคู่] จะเป็น username data[เลขคี่] จะเป็น password
    วิธีการเข้าถึงคือ data[0] data[1] เป็นต้น
    
    ไกด์ไลน์ใช้ for loop เช็ค user ก็อาจจะ i เพิ่มทีละสอง แล้วก็ input == data[i] มั้ย เป็นต้น (ถ้า userก็ i เริม่ที่ 0 เพราะ username เริ่ม 0)
    
    */
}

void Register() {

    cin.clear();
    cin.ignore(50,'\n');
    string username, password;
    
    while(1){
        cout<<"----------------------------"<<endl;
        cout<<"|       REGISTRATION       |"<<endl;
        cout<<"----------------------------"<<endl;
        cout << "Enter new username: ";
        getline(cin,username);

        if(username.size() == 0){
            cout << "** Username shouldn't be empty! **" << endl;
            continue;
        }
        if (check_name(username) == true){
            cout << "** Invalid username. Please try again! **" << endl;
            continue;
        }
        if(user_exist(username)){
            cout << "** Username already exists. Please choose a new one! **" << endl;
            continue;
        }
        else break;
    }
    cout << "Enter password    : ";
    cin >> password;
    cout<<"----------------------------"<<endl;

    ofstream myFile("username.csv", ios::app); // open file for appending
    if(!myFile.is_open()) {
        cout << "** Can't open file for registration! **" << endl;
    } else {
        myFile << username << "," << password << endl;
        cout << ">> Registration Successfull! <<" << endl;
    }
    cin.clear();
    cin.ignore(10000,'\n');
}
bool user_exist(string username){
    
    string line, exist_username;
    
    ifstream myFile("username.csv");
    
    while(getline (myFile, line)){
        stringstream ss(line);
        getline(ss, exist_username, ',');
        if(username == exist_username){
            return true;
        }
    }
    return false;
}

bool check_name(string username) {
    
    int i;
    
    for(i=0;i<username.size();i++){
       char ch = username[i];
        if(ch == '/' || ch == '\\' || ch == ',' || ch == '.' || ch == '(' || ch == ')' || ch == '^' || ch == '*' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '&' || ch == '!' || ch == '#' || ch == '%' || ch == ':' || ch == ';' || ch == '?' || ch == '<' || ch == '>' || ch == ' '){
            return true;
        }
    }
    return false;
}

/*
int main(){
    Register();
    //login();
    return 0 ;
}
*/