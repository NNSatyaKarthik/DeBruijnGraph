//
// Created by Naga Satya Karthik on 11/13/17.
//



#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/ConstructKMers.h"
#include "../src/BBHash.h"


#define GENOMEFA "/Users/nagasaty/0classes/bdb/DeBruijnGraph/datasets/genome.fa"
using testing::Eq;

namespace {
    class BBHashTest : public testing::Test {
    public:
        vector<long long> input_keys = {1,2,3,4,5,6,7,10,20,30,40,50};
        int k;
        ConstructKMers* sut;
        RabinKarpHash* rkhash;
        BBHashExt* bbHashExt;
        BBHashTest() {
            k = 15;
            sut = new ConstructKMers(k);
            rkhash = new RabinKarpHash(k);
            bbHashExt = new BBHashExt(input_keys);
        }

        virtual ~BBHashTest() {
            delete sut;
            delete rkhash;
        }
    };
}

TEST_F(BBHashTest, getMPHF) {
    // GIven an long long returns the index of the mphf
    //CHeck for unique ness.
    set<uint64_t> hashSet;
    u_int64_t idx;
    for(long long rkhash: input_keys){
        idx = bbHashExt->getMPHF(rkhash);
        printf("RKHash: %lli, Value(IDX): %llu\n", rkhash, idx);
    }
}

