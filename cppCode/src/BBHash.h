//
// Created by Naga Satya Karthik on 11/14/17.
//

#ifndef CPPCODE_BBHASH_H
#define CPPCODE_BBHASH_H

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
#include <bitset>

using namespace std;

#include "../lib/BBHash-master/BooPHF.h"
typedef boomphf::SingleHashFunctor<u_int64_t>  hasher_t;
typedef boomphf::mphf<  long long, hasher_t  > boophf_t;

class BBHashExt {
    boophf_t * bphf;
    int n;
    vector<long long> *rkeys; // reverse mapping.. index is the mphf lookup value..
    // element value is the rk hahs value
public:

    BBHashExt(vector<long long> values) {
        n = values.size();
        rkeys = new vector<long long>(n, 0);
        bphf = new boomphf::mphf<long long,hasher_t>(n,values,1);
        u_int64_t idx;
        for(long long value: values){
            idx = bphf->lookup(value);
            (*rkeys).at(idx) = value;
        }
    }

    long long getRabinHash(u_int64_t vertexId){
        if(vertexId >= (*rkeys).size()) return -1;
        return (*rkeys).at(vertexId);
    }

// Assuming that rabinKarpHash is always present
    u_int64_t getMPHF(long long rabinKarphHash){
        u_int64_t idx = bphf->lookup(rabinKarphHash);
        return idx;
    }
};
#endif //CPPCODE_BBHASH_H