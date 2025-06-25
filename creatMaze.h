#include <iostream>
#include <time.h>
#include <thread>
#include <chrono>
#include <bits/stdc++.h> // provides all stl functions

const int size = 80;
const int delay = 0; // delay for visuals

int lineWidth = 10;
int pos = 0;
int start = 0;
int goal = size*size - 1;
int rot;
int pathindex;
int emptywallcnt;

bool vis[size*size];
int walls[size*size][2]; // 0 - for wall , 1 - for no wall
int path[size*size] = {0};
int mazewalls[size*size][5];
int emptywalls[4] = {0}; // 1 - empty , 0 - otherwise

int nextocur(int cur){
        int opcnt = 0;
        int opt[4];

        if( (( cur + 1 ) % size) && !vis[cur+1] ){ opt[opcnt] = 1; opcnt++; }
        if( ( cur > size ) && !vis[cur-size] ){ opt[opcnt] = -size; opcnt++; }
        if( ( cur + size ) < ( size*size ) && !vis[cur+size] ){ opt[opcnt] = size; opcnt++; }
        if( ( cur % size ) && !vis[cur-1] ){ opt[opcnt] = -1; opcnt++; }

        if( !opcnt ) return 0;
        return opt[rand() % opcnt];
}

void connect( int pos1 , int pos2 ){
        if( pos2 == ( pos1 + 1 ) ) walls[pos2][0] = 1;
        else if( pos2 == ( pos1 + size ) ) walls[pos2][1] = 1;
        else if( pos1 == ( pos2 + 1 ) ) walls[pos1][0] = 1;
        else walls[pos1][1] = 1;
}

void dfs(int cur){
        vis[cur] = 1;
        int nextcur = cur + nextocur(cur);
        while( nextcur != cur ){
                std::this_thread::sleep_for(std::chrono::nanoseconds(delay)); // delay for making visuals clear
                connect(cur,nextcur);
                cur = nextcur;
                dfs(cur);
                nextcur = cur + nextocur(cur);
        }
}

void createMaze(){
        pos = 0;
        for( int i = 0 ; i < size*size ; i++ ) vis[i] = 0;
        // random dfs to make Maze
        dfs(pos);
}