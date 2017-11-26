//
// Created by Naga Satya Karthik on 11/11/17.
//

#ifndef CPPCODE_CONSTRUCTKMERS_H
#define CPPCODE_CONSTRUCTKMERS_H

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
#include "RabinKarpHash.h"
#include <bitset>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

class ConstructKMers {
    int k;
public:
    ConstructKMers(int k) : k(k) {}
    vector<string> getKMers(string filePath){
        vector<string> res;
        string line, kmer = "";
        ifstream myfile (filePath);
        if (myfile.is_open())
        {
            while(getline(myfile,line)){
                kmer += line;
                if(kmer.length() >= k){
                    for(int i  = 0 ; i < kmer.length()-k+1 ; i++){
                        res.push_back(kmer.substr(i, k));
                    }
                    kmer = kmer.substr(kmer.length()-k+1);
                }
            }
            myfile.close();
        }
        return res;
    }

    vector<string> getKmersFromData(string data){
        vector<string> res;
        for(int i = 0 ; i < data.length()-k+1; i++){
            res.push_back(data.substr(i, k));
        }
        return res;
    }

    vector<string> getUniqueKMers(vector<string> res){
        sort(res.begin(), res.end());
        int curr = 0;
        string currItem= res[0];
        for(int i = 0; i < res.size(); i++){
            if(res[i].compare(currItem)!=0){
                res[curr] = currItem;
                curr++;
                currItem = res[i];
            }
        }
        res[curr] = currItem;
        vector<string> returnItem;
        for(int i = 0 ; i< curr+1; i++){
            returnItem.push_back(res[i]);
        }
        return returnItem;
    }

    vector<long long> getRKHashMaps(vector<string> kmers){
        vector<long long> res;
        RabinKarpHash* rkhash = new RabinKarpHash(k);
        long long kmerhash = 0, prev = rkhash->rabinkarpHash(kmers[0]);
        res.push_back(prev);
        for(int i =  1 ; i < kmers.size(); i++){
            kmerhash = rkhash->computeNextHash(prev,kmers[i][k-1]);
            res.push_back(kmerhash);
            prev = kmerhash;
        }
        return res;
    }
};


#endif //CPPCODE_CONSTRUCTKMERS_H
