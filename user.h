#include<bits/stdc++.h>
#include<cstdio>
using namespace std;

#include "song.h"
#include "playlist.h"

class User{
    private:
        string name;
        string database;
        string playlist_names;
        map<string, Playlist> myPlaylists;
    public:
        User(string s){
            name = s;
            database = "data/users/";
            database += name;
            database += "/";
            playlist_names = database+"playlists.txt";

            ifstream f(playlist_names);
            if(f.is_open()){
                while(!f.eof()){
                    string p;
                    getline(f, p);
                    if(p!=""){
                        //add playlist to the map
                        myPlaylists[p].name = p;
                        myPlaylists[p].creator = name;

                        string pldir = database+p+".txt";

                        ifstream cf(pldir, ios::binary);
                        cf.seekg(0, ios::end);
                        int size = cf.tellg();
                        cf.close();

                        ifstream plfile(pldir);
                        Song s;
                        for(int i=0; i<size; i++){
                            plfile.read((char *)&s, sizeof(s));
                            if(s.name!="")
                                //add songs to individual playlists in the map
                                myPlaylists[p].songs[s.name] = s;
                        }
                        plfile.close();
                    }
                }
                f.close();
            }
            else{
                f.close();
                ofstream f(playlist_names);
                f.close();
            }
        }
        
        void find_songs(map<string, Song>);
        void play_songs(map<string, Song>);
        void create_playlist();
        void view_playlists();
        void delete_playlist();
        void edit_playlist(map<string, Song>);
};

void User::find_songs(map<string, Song> SONGS){
    cout<<"Search: ";
    string s;
    getline(cin, s);
    for(map<string, Song>::iterator it=SONGS.begin(); it!=SONGS.end(); it++){
        if(it->first.find(s)!=string::npos)
            list_song(it->second);
    }
}

void User::play_songs(map<string, Song> SONGS){
    cout<<"Enter song name: ";
    string s;
    getline(cin, s);
    if(SONGS.find(s)!=SONGS.end()){
        play_song(SONGS[s]);
    }
}

void User::create_playlist(){
    cout<<"Enter playlist name: ";
    string p;
    getline(cin, p);

    myPlaylists[p].name = p;
    myPlaylists[p].creator = name;
    
    ofstream f(playlist_names, ios::app);
    f<<p<<'\n';
    f.close();

    string pldir = database + p + ".txt";
    ofstream plfile(pldir);
    plfile.close();

    cout<<"Playlist created! You can now add songs\n";
}

void User::view_playlists(){
    for(map<string, Playlist>::iterator it=myPlaylists.begin(); it!=myPlaylists.end(); it++){
        // cout<<"PLAYLIST: "<<it->second.name<<" | CREATED BY: "<<it->second.creator<<'\n';
        show_playlist(it->second);
    }
    if(myPlaylists.empty()){
        cout<<"No playlists to show\n";
    }
}

void User::delete_playlist(){
    string p;
    cout<<"Which playlist you wish to delete: ";
    getline(cin, p);

    if(myPlaylists.find(p)!=myPlaylists.end()){
        myPlaylists.erase(myPlaylists.find(p));

        string pldir = database + p + ".txt";
        int del = remove(pldir.c_str());

        string playlist_names = database + "playlists.txt";
        ofstream f(playlist_names);
        for(map<string, Playlist>::iterator it=myPlaylists.begin(); it!=myPlaylists.end(); it++)
            f<<it->first<<'\n';

        cout<<"Playlist deleted\n";
    }
    else{
        cout<<"Playlist not found\n";
    }
}

int get_edit_opt(){
    int opt;
    do{
        cin>>opt;
        if(cin.fail()){
            cout<<"Please enter value in right format\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else if(opt!=1 && opt!=2){
            cout<<"Please select a valid option\n";
        }
    }while(opt!=1 && opt!= 2);

    string dummy;
    getline(cin, dummy);
    return opt;
}

void User::edit_playlist(map<string, Song> SONGS){
    cout<<"Which playlist do you wish to edit: ";
    string p;
    getline(cin, p);

    if(myPlaylists.find(p)!=myPlaylists.end()){
        cout<<"Press 1 to ADD songs and 2 to DELETE songs\n";
        int opt = get_edit_opt();
        if(opt==1){
            //adding songs
            cout<<"Enter song name: ";
            string s;
            getline(cin, s);
            if(SONGS.find(s)!=SONGS.end()){
                myPlaylists[p].songs[s] = (SONGS[s]);

                string pldir = database + p + ".txt";
                ofstream plfile(pldir, ios::app);
                plfile.write((char*)&SONGS[s], sizeof(SONGS[s]));
                plfile.close();

                cout<<"Song Added\n";
            }
            else{
                cout<<"Song not found\n";
            }
        }
        else if(opt==2){
            //deleting songs
            cout<<"Enter song name: ";
            string s;
            getline(cin, s);
            if(SONGS.find(s)!=SONGS.end()){
                if(myPlaylists[p].songs.find(s) != myPlaylists[p].songs.end()){
                    myPlaylists[p].songs.erase(s);

                    string pldir = database + p + ".txt";
                    ofstream plfile(pldir);
                    for(map<string, Song>::iterator it=myPlaylists[p].songs.begin(); it!=myPlaylists[p].songs.end(); it++){
                        plfile.write((char*)&it->second, sizeof(it->second));
                    }
                    plfile.close();
                }
                cout<<"Song Deleted\n";
            }
            else{
                cout<<"Song not found\n";
            }
        }
    }
    else{
        cout<<"Playlist not found\n";
    }
}










