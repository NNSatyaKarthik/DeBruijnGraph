//
// Created by Naga Satya Karthik on 11/10/17.
//

#ifndef CPPCODE_RABINKARPHASH_H
#define CPPCODE_RABINKARPHASH_H

#include "iostream"
#include "math.h"
using namespace std;

class RabinKarpHash {
    int powk1;
    int k;
public:

    RabinKarpHash(int k) : k(k), powk1((int)pow(4, k-1)) {}

    int genToI(char c){
        switch(c){
            case 'A': return 0;
            case 'T': return 1;
            case 'G': return 2;
            case 'C': return 3;
            default: return -1;
        }
    }

    long long rabinkarpHash(string s){
        //ATGC - 0123 all elase -1
        long long res = 0 ;
        int intval;
        for(char c: s){
            intval = genToI(c);
            if(intval == -1) return -1;
            res = res*k + intval;
        }
        return res;
    }

    long long computeNextHash(long long initialHash, char c, int k){
        if(genToI(c) == -1) return -1;
        return initialHash%powk1 + genToI(c);
    }

    long long computePrevValue(long long initialHash, char c, int k){
        if(genToI(c)==-1) return -1;
        return genToI(c)*powk1 + initialHash/k;
    }
};


#endif //CPPCODE_RABINKARPHASH_H
