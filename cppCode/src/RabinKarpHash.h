//
// Created by Naga Satya Karthik on 11/10/17.
//

#ifndef CPPCODE_RABINKARPHASH_H
#define CPPCODE_RABINKARPHASH_H

#include "iostream"
using namespace std;

class RabinKarpHash {
public:
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
            res = res*4 + intval;
        }
        return res;
    }
};


#endif //CPPCODE_RABINKARPHASH_H
