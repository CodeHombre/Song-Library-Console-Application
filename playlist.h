#include<bits/stdc++.h>
using namespace std;

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"

class Playlist{
    public:
        string name;
        string creator;
        map<string, Song> songs;
};

#endif
