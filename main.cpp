#include<bits/stdc++.h>
using namespace std;

#include "song.h"
#include "collection.h"

string start();
string init_user(string);
void display_menu();
int get_selection();

int main(){
    string fname = start();
    Collection myCollection(fname);

    display_menu();

    int selection=0;
    do{
        selection=get_selection();
        switch(selection){
            case 1:
                myCollection.add_song();
                break;
            case 2:
                myCollection.delete_song();
                break;
            case 3:
                myCollection.play_song();
                break;
            case 4:
                myCollection.show_all();
                break;
            case 5:
                myCollection.delete_all();
                break;
        }
        if(selection!=6){
            display_menu();
        }
    }while(selection!=6);

    return 0;
}

string init_user(string user){
    string fname = "data/";
    fname += user;
    fname += ".txt";
    // cout<<fname<<endl;
    ifstream f(fname);

    if(!f.is_open()){
        f.close();
        cout<<"Seems like you don't have an account\n";
        cout<<"Creating Account...\n";
        ofstream f(fname);
        cout<<"Account Created!\nYou can now add songs\n";
        f.close();

    }
    else{
        cout<<"Hey "<<user<<", Welcome!\n";
        f.close();
    }

    return fname;
}

string start(){
    cout<<"Welcome to Vibezz\n";
    cout<<"Please enter your name: ";
    string user;
    getline(cin, user);
    return init_user(user);
}

void display_menu(){
    cout<<"--------------------------\n";
    cout<<"MENU\n";
    cout<<"\t1. Add a song\n";
    cout<<"\t2. Delete a song\n";
    cout<<"\t3. Play a song\n";
    cout<<"\t4. Show all songs\n";
    cout<<"\t5. Delete all songs\n";
    cout<<"\t6. Close Application\n";
    cout<<"Enter an option: ";
}


int get_selection(){
    int s=0;
    cin>>s;
    while(cin.fail() || s<1 || s>6){
        if(cin.fail()){
            cout<<"Invalid Choice\n";
        }
        else{
            cout<<"Selection unavailable\n"; 
        }
        display_menu();  
        cin.clear();
        cin.ignore(1000, '\n');
        cin>>s;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return s;
}