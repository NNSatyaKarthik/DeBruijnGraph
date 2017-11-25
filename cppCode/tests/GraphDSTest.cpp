//
// Created by Naga Satya Karthik on 11/10/17.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/RabinKarpHash.h"
#include "../src/ConstructKMers.h"
#include "../src/BBHash.h"
#include "../src/GraphDS.h"

using testing::Eq;

namespace {
    class GraphDSTest : public testing::Test {

    public:
        string data;
        int k;
        ConstructKMers* sut;
        RabinKarpHash* rkhash;
        BBHashExt* bbHashExt;
        GraphDS* gds;
        vector<long long> kmersHashValues;
        vector<string> kmers;
        GraphDSTest() {
            data = "AGCGCTGAAAGTTTCATGAACAT";
            k = 5;
            sut = new ConstructKMers(k-1);
            rkhash = new RabinKarpHash(k-1);
            kmers = sut->getKmersFromData(data);
            kmersHashValues = sut->getRKHashMaps(kmers);
            bbHashExt = new BBHashExt(kmersHashValues);
            gds = new GraphDS(kmersHashValues.size(), 4, k, bbHashExt, rkhash);
        }

        virtual ~GraphDSTest() {
            delete gds, sut, rkhash, bbHashExt;
        }
    };
}

TEST_F(GraphDSTest, getNeighbours) {
    for(int i = 0 ; i < kmers.size(); i++){
        printf("%s, %lld, %llu\n", kmers[i].c_str(), kmersHashValues[i], bbHashExt->getMPHF(kmersHashValues[i]));
    }
//    gds->printInOut(); //Prints all 0's and 1'st
    for(int id = 1; id < kmers.size(); id++){
        gds->addStaticEdge(bbHashExt->getMPHF(kmersHashValues[id-1]), bbHashExt->getMPHF(kmersHashValues[id]), rkhash->getLastCharI(kmersHashValues[id]), rkhash->getFirstCharI(kmersHashValues[id-1]));
    }
    gds->printInOut();

    //Test neighbours of 19th vertex id
    vector<u_int64_t> neighboursExpected = {6, 14, 9, 3};
    vector<u_int64_t> neighboursAct = gds->getNeighbours(19);
    //prints both the lists
    printf("Expected: ");
    for(u_int64_t nact: neighboursExpected)printf("%llu, ", nact);
    printf("\nActual: ");
    for(u_int64_t nact: neighboursAct)printf("%llu, ", nact);
    printf("\n");

    // checks all neighbours found whether present in expected list
    for(u_int64_t nact: neighboursAct){
        if(find(neighboursExpected.begin(), neighboursExpected.end(), nact) == neighboursExpected.end()){
            printf("%llu is not found in expected list\n", nact);
            EXPECT_TRUE(false);
        }
    }
    // checks all neighbours expected whether present in neighbours found list
    for(u_int64_t nexpt: neighboursExpected){
        if(find(neighboursAct.begin(), neighboursAct.end(), nexpt) == neighboursAct.end()){
            printf("%llu is not found in expected list\n", nexpt);
            EXPECT_TRUE(false);
        }
    }
}

