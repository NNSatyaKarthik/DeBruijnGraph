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


struct Component{
    u_int64_t heightIdx, vertexIdx, ComponentIdx;
    int height, size;

    Component(u_int64_t heightIdx, u_int64_t vertexIdx, u_int64_t ComponentIdx, int height, int size): heightIdx(heightIdx), vertexIdx(vertexIdx), ComponentIdx(ComponentIdx), height(height), size(size) {}
};

class GraphDS {
    u_int64_t N;
    int sigma, K;
    vector<vector<bool>> IN, OUT;
    vector<u_int64_t> parentPtrs;
    vector<Component> components;
    BBHashExt *bbHash;
    RabinKarpHash *rkHash;
    u_int64_t desired_sz, min_ht, max_ht, mid_ht;
    bool isNoParent(u_int64_t idx){
        return parentPtrs[idx] == (N+1);
    }
public:
    GraphDS(u_int64_t n, int sigma, int K, BBHashExt *bbHashExt, RabinKarpHash *rkHashExt): N(n), sigma(sigma), K(K) {
        bbHash = bbHashExt;
        rkHash = rkHashExt;
        // IN OUT assigned both to false
        IN.assign(n, vector<bool>((size_t)sigma, false));
        OUT.assign(n, vector<bool>((size_t)sigma, false));
        // parent pointers point to -1 is root node.
        parentPtrs.assign(n, n+1);
        desired_sz = (u_int64_t)ceil(K*log2(sigma));
        min_ht = desired_sz;
        max_ht = 3*desired_sz;
        mid_ht = 2*desired_sz;
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
        while(idx < N && !isNoParent(idx)){
            curr = (u_int64_t) parentPtrs[idx];
        }
        return curr;
    }

    int getDepth(u_int64_t idx){
        u_int64_t curr = idx;
        int res= 0;
        while(idx < N && !isNoParent(idx)){
            curr = (u_int64_t) parentPtrs[idx];
            res++;
        }
        return res;
    }



    int getHeight(u_int64_t componentIdx){
        if(componentIdx >= components.size()) return -1;
        return components[componentIdx].height;
    }

    int getSize(u_int64_t componentIdx){
        if(componentIdx >= components.size()) return -1;
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
        u_int64_t maxHeight = max_ht;
        vector<STATE > states(N, UNVISITED);
        for( u_int64_t i = 0 ; i < N ; i++){
            if(states[i]==UNVISITED){
                *height = 0;
                *size = 0 ;
                *heightIdx = N+1;
                dfs(i, N+1, maxHeight, height, size, heightIdx, states);
                temp = new Component(*heightIdx, i, (int)components.size(), *height, *size);
                components.push_back(*temp);
            }
        }
    }

    void dfs(u_int64_t root, u_int64_t parentPtr, u_int64_t maxHeight, int *height, int *size, u_int64_t *heightIdx, vector<STATE> &states){
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


    void updateParentPointers(u_int64_t idx){
        u_int64_t parent;
        if(isNoParent(idx)) return; // Current idx is the root and no change is needed.
        stack<u_int64_t> stack1;
        while(!isNoParent(idx)){ // if there is a parent of the current idx. swap the direction
            stack1.push(idx);
            if(isNoParent(idx)) break; // this conditino is always false as we are not changing the idx from while loop
            idx = (u_int64_t)parentPtrs[idx];
        }
        u_int64_t curr = idx;
        while(stack1.size() > 0){
            parentPtrs[curr] = stack1.top();
            curr = stack1.top();
            stack1.pop();
        }
        parentPtrs[curr] = N+1;
    }

//  hash(U) -> i hash(V)->j
//  b = firstChar(U), a = lastChar(V)
    void addDynamicEdge(u_int64_t i, u_int64_t j, int a, int b){ //u and v are the vertex id's
        OUT[i][a] = 1;
        IN[j][b]= 1;
        u_int64_t Ci = getRoot(i);
        u_int64_t Cj = getRoot(j);
        if(Ci != Cj) {

        }
    }
};


#endif //CPPCODE_GRAPHDS_H
