#include<bits/stdc++.h>
using namespace std;

#include "song.h"

class Artist{
    private:
        string name;
        string database;
        map<string, Song> mySongs;
    public:
        Artist(string s){
            name = s;
            database = "data/artists/";
            database += s;
            database += ".txt";

            ifstream file(database);
            if(file.is_open()){
                Song s;
                //get no of records
                ifstream cf(database, ios::binary);
                cf.seekg(0, ios::end);
                int size = cf.tellg();
                cf.close();

                //store available songs in a map
                for(int i=0; i<size; i++){
                    file.read((char*)&s, sizeof(s));
                    if(s.name!="")
                    mySongs[s.name] = s;
                }
                file.close();
            }else{
                cout<<"Error loading database...\n";
            }
        }
    
        void add_song();
        void delete_song();
        void view_all();
        void delete_all();
};

void Artist::add_song(){
    Song s;
    cout<<"Enter song's name: ";
    getline(cin, s.name);
    cout<<"Enter album's name: ";
    getline(cin, s.album);
    cout<<"Enter song duration: ";
    getline(cin, s.duration);
    s.artist = name;

    mySongs[s.name] = s;

    ofstream f(database, ios::app);
    f.write((char *)&s, sizeof(s));
    f.close();
}

void Artist::delete_song(){
    string del;
    cout<<"Enter song's name: ";
    getline(cin, del);

    if(mySongs.find(del)!=mySongs.end()){
        mySongs.erase(mySongs.find(del));

        ofstream f(database);
        map<string, Song>::iterator it;
        for(it=mySongs.begin(); it!=mySongs.end(); it++){
            f.write((char *)&it->second, sizeof(it->second));
        }
        f.close();

        cout<<"Song deleted\n";
    }
    else{
        cout<<"Song not found\n";
    }
}

void Artist::view_all(){
    if(mySongs.empty()){
        cout<<"No songs to show\n";
    }
    else{
        map<string, Song>::iterator it;
        for(it=mySongs.begin(); it!=mySongs.end(); it++){
            list_song(it->second);
        }
    }
}

void Artist::delete_all(){
    mySongs.clear();
    ofstream f(database);
    f.close();
}