#ifndef COLLECTION_H
#define COLLECTION_H

#include<bits/stdc++.h>
using namespace std;

#include "song.h"

class Collection{
    private:
        string fname;
        map<string, Song> songs;
    public:
        Collection(string str){
            fname = str;
            songs.clear();
            ifstream file(fname);
            if(file.is_open()){
                Song s;
                //get no of records
                ifstream cf(fname, ios::binary);
                cf.seekg(0, ios::end);
                int size = cf.tellg();
                cf.close();

                //store available songs in a map
                for(int i=0; i<size; i++){
                    file.read((char*)&s, sizeof(s));
                    if(s.name!="")
                    songs[s.name] = s;
                }
                file.close();
            }else{
                cout<<"Error loading database...\n";
            }
        }
        void add_song();
        void delete_song();
        void play_song();
        void show_all();
        void delete_all();
};

void Collection::add_song(){
    Song s;
    cout<<"Enter song name: ";
    getline(cin, s.name);
    cout<<"Enter artist's name: ";
    getline(cin, s.artist);
    cout<<"Enter genre: ";
    getline(cin, s.genre);
    songs[s.name] = s;

    ofstream file(fname, ios::app);
    if(!file.is_open()){
        cout<<"Error loading database...\n";
    }
    else{
        file.write((char *)&s, sizeof(s) );
    }
    file.close();
    cout<<"Song Added!\n";
}

void Collection::delete_song(){
    string q;
    cout<<"Which song do you wish to delete: ";
    getline(cin, q);
    if(songs.find(q)!=songs.end()){
        songs.erase(songs.find(q));

        ofstream file(fname);
        if(!file.is_open()){
            cout<<"Error loading database...\n";
        }
        else{
            Song s;
            map<string, Song>::iterator it;
            for(it=songs.begin(); it!=songs.end(); it++){
                file.write((char *)&it->second, sizeof(it->second) );
            }
        }
        file.close();
        cout<<"Song Deleted\n";
    }
    else{
        cout<<"Song not found\n";
    }  
}

void Collection::play_song(){
    string q;
    cout<<"What would like to listen to: ";
    getline(cin, q);
    if(songs.find(q)!=songs.end()){
        cout<<"Name: "<<songs[q].name<<" Artist: "<<songs[q].artist<<" Genre: "<<songs[q].genre<<'\n';
    }
    else{
        cout<<"Song not found\n";
    }
}

void Collection::show_all(){
    map<string, Song>::iterator it;
    int i=1;
    if(songs.begin()==songs.end()) cout<<"No songs have been added\n";
    for(it=songs.begin(); it!=songs.end(); it++){
        Song temp = it->second;
        cout<<i<<":- "<<"Name: "<<temp.name<<" Artist: "<<temp.artist<<" Genre: "<<temp.genre<<'\n';
        i++;
    }
}

void Collection::delete_all(){
    songs.clear();
    ofstream file(fname);
    file.close();
    cout<<"All Songs Deleted\n";   
}

#endif