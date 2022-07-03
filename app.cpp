#include<bits/stdc++.h>
using namespace std;
#include<sys/stat.h>
#include<sys/types.h>

#include "display.h"

#include "song.h"

#include "user.h"
#include "artist.h"


map<string, Song> SONGS;

string ARTIST="", USER="";

void init_app();
void start();

string artist_start();
void artist_app(string name);

string user_start();
void user_app(string name);

int main(){
    start();
    if(ARTIST!=""){
        artist_app(ARTIST);
    }
    else if(USER!=""){
        user_app(USER);
    }
    
    return 0;
}

void start(){
    cout<<"WELCOME TO VIBEZZZ\n";
    cout<<"Press 1 if you are a User or 2 if you are an Artist\n";
    int person;
    do{
        cin>>person;
        if(cin.fail()){
            cout<<"Please enter value in right format\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(person!=1 && person !=2){
            cout<<"Please select a valid option\n";
        }
    }while(person!=1 && person != 2);

    if(person==1){
        USER = user_start();
    }
    else if(person==2){
        ARTIST = artist_start();
    }
}

string artist_start(){
    cout<<"Enter your name: ";
    string name;
    getline(cin,name); //dummy getline
    getline(cin,name);
    string artist_db = "data/artists/";
    artist_db += name;
    artist_db += ".txt";

    ifstream f(artist_db);

    if(f.is_open()){
        cout<<"Welcome Back "<<name<<'\n';
        f.close();
    }
    else{
        cout<<"You aren't a memeber. Creating account...\n";
        f.close();
        ofstream f(artist_db);
        f.close();
        ofstream file("data/artists/artists.txt", ios::app);
        file<<name<<'\n';
        file.close();
        cout<<"Account Created!\n";
        cout<<"Your username is "<<name<<'\n';
    }
    return name;
}

void artist_app(string artist_name){
    Artist artist(artist_name);

    int selection;
    while(1){
        artist_menu();
        cin>>selection;
        string dummy;
        getline(cin, dummy);
        switch (selection)
        {
            case 1:
                artist.add_song();
                break;
            case 2:
                artist.delete_song();
                break;
            case 3:
                artist.view_all();
                break;
            case 4:
                artist.delete_all();
                break;
            case 5:
                exit(0);
        }
    }
}

string user_start(){
    //Loading song database
    ifstream artists("data/artists/artists.txt");
    string a;
    string adata;
    do{
        adata = "data/artists/";
        getline(artists, a);      

        if(a!=""){
            adata += a;
            adata += ".txt";

            ifstream cf(adata, ios::binary);
            cf.seekg(0, ios::end);
            int size = cf.tellg();
            cf.close();

            ifstream afile(adata);
            Song s;
            for(int i=0; i<size; i++){
                afile.read((char *)&s, sizeof(s));
                if(s.name!="")
                    SONGS[s.name] = s;
            }
            afile.close();
        }
    }
    while(!artists.eof());

    artists.close();

    cout<<"Enter your name: ";
    string name;
    getline(cin,name); //dummy geline
    getline(cin,name);
    string user_db = "data/users/";
    user_db += name;

    //check if user dir exists else create
    struct stat buffer;
    if(stat(user_db.c_str(), &buffer)==0){
        cout<<"Welcome Back "<<name<<'\n';
    }
    else{
        cout<<"You aren't a memeber. Creating account...\n";
        if(mkdir(user_db.c_str(),0777)==-1){
            cout<<"Failed to create account. Try Again.\n";
        }
        else{
            cout<<"Account Created!\n";
            cout<<"Your username is "<<name<<'\n';
        }
    }

    return name;
}

void user_app(string user_name){
    User user(user_name);

    int selection;
    while(1){
        user_menu();
        cin>>selection;
        string dummy;
        getline(cin, dummy);
        switch (selection)
        {
            case 1:
                user.find_songs(SONGS);
                break;
            case 2:
                user.play_songs(SONGS);
                break;
            case 3:
                user.create_playlist();
                break;
            case 4:
                user.view_playlists();
                break;
            case 5:
                user.delete_playlist();
                break;
            case 6:
                user.edit_playlist(SONGS);
                break;
            case 7:
                exit(0);
        }

    }
}

