//
// Created by Naga Satya Karthik on 11/16/17.
//

#ifndef CPPCODE_GRAPHDS_H
#define CPPCODE_GRAPHDS_H

#include "iostream"
#include "map"
#include "vector"
#include "string"
#include "stack"
#include "queue"
#include "set"
#include "unistd.h"
#include "sstream"
#include "fstream"
#include "sys/wait.h"
#include "BBHash.h"
#include "RabinKarpHash.h"
#include <bitset>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<u_int64_t> vu64;

#define INF 1000000000
#define abs_val(a) (((a)>0)?(a):-(a))
#define min(a, b) (a < b)?a:b;
#define max(a, b) (a > b)?a:b;
#define FOR(x, b, e) for(int x = (b); x < ((int)e); ++x)

struct Component{
    u_int64_t heightIdx, vertexIdx, ComponentIdx;
    int height, size;

    Component(u_int64_t heightIdx, u_int64_t vertexIdx, u_int64_t ComponentIdx, int height, int size): heightIdx(heightIdx), vertexIdx(vertexIdx), ComponentIdx(ComponentIdx), height(height), size(size) {}
};

class GraphDS {
    u_int64_t N;
    int sigma, K;
    vector<vector<bool>> IN, OUT;
    vector<int> parentPtrs;
    vector<Component> components;
    BBHashExt *bbHash;
    RabinKarpHash *rkHash;
public:
    GraphDS(u_int64_t n, int sigma, int K, BBHashExt *bbHashExt, RabinKarpHash *rkHashExt): N(n), sigma(sigma), K(K) {
        bbHash = bbHashExt;
        rkHash = rkHashExt;
        // IN OUT assigned both to false
        IN.assign(n, vector<bool>(sigma, false));
        OUT.assign(n, vector<bool>(sigma, false));
        // parent pointers point to -1 is root node.
        parentPtrs.assign(n, -1);
    }

    vu64 getNeighbours(u_int64_t vertexId){
        vu64 res;
        long long rkHashVertexId = bbHash->getRabinHash(vertexId);
        for(int i = 0 ; i < sigma; i++){
            if(IN[vertexId][i])
                res.push_back(bbHash->getMPHF(rkHash->computePrevValue(rkHashVertexId, i)));
            if(OUT[vertexId][i])
                res.push_back(bbHash->getMPHF(rkHash->computeNextHash(rkHashVertexId, i)));
        }

        return res;
    }

    u_int64_t getRoot(u_int64_t idx){
        u_int64_t curr = idx;
        while(idx < N && parentPtrs[idx] != -1){
            curr = (u_int64_t) parentPtrs[idx];
        }
        return curr;
    }

    int getHeight(u_int64_t componentIdx){
        if(componentIdx < 0 || componentIdx >= components.size()) return -1;
        return components[componentIdx].height;
    }

    int getSize(u_int64_t componentIdx){
        if(componentIdx < 0 || componentIdx >= components.size()) return -1;
        return components[componentIdx].size;
    }

    vu64 getLeaves(u_int64_t rootVertexIdx){
        vu64 res;
        if(rootVertexIdx >= N) return res;
        queue<u_int64_t> q;
        u_int64_t vidx;
        q.push(rootVertexIdx);
        vu64 neighbours;
        while(q.size() > 0 ){
            vidx = q.front();
            neighbours = getNeighbours(vidx);
            neighbours = filter(neighbours, vidx);
            if(neighbours.size() > 0){
                for(u_int64_t neigbour: neighbours) q.push(neigbour);
            }else{
                res.push_back(vidx);
            }
        }
        return res;
    }

    vu64 filter(vu64 neighbours, u_int64_t parentPtr){
        vu64 res;
        for(u_int64_t neighbour : neighbours){
            if(parentPtrs[neighbour] == parentPtr){
                res.push_back(neighbour);
            }
        }
        return res;
    }

    enum STATE {VISITED, VISITING, UNVISITED};

//    Updates parent Pointers & Populates components vector with the
//    root of each Componenet.
    void buildForest(){
        Component *temp;
        int *height, *size;

        u_int64_t *heightIdx;
        int maxHeight = getMaxHeight();
        vector<STATE > states(N, UNVISITED);
        for( u_int64_t i = 0 ; i < N ; i++){
            if(states[i]==UNVISITED){
                *height = 0;
                *size = 0 ;
                *heightIdx = N+1;
                dfs(i, -1, maxHeight, height, size, heightIdx, states);
                temp = new Component(*heightIdx, i, (int)components.size(), *height, *size);
                components.push_back(*temp);
            }
        }
    }

    void dfs(u_int64_t root, int parentPtr, int maxHeight, int *height, int *size, u_int64_t *heightIdx, vector<STATE> &states){
        if(maxHeight <=  0){
            *height = 0 ;
            *size = 0;
            return;
        }
        u_int64_t *tempHeightIdx;
        int *tempHeight;
        states[root] = VISITING;
        vu64 neighbours = getNeighbours(root);
        for(u_int64_t neighbour : neighbours){
            if(states[neighbour] == UNVISITED){
                *tempHeight = 0;
                *tempHeightIdx = N+1;
                dfs(neighbour, root, maxHeight - 1, tempHeight, size, tempHeightIdx, states);
                if(*tempHeight > *height){
                    *height = *tempHeight;
                    *heightIdx = neighbour;
                }
            }
        }
        *size += 1;
        *height += 1;
        parentPtrs[root] = parentPtr;
        states[root] = VISITED;
    }

    int getMaxHeight(){
        return (int)ceil(3*K*log(sigma));
    }
};


#endif //CPPCODE_GRAPHDS_H
