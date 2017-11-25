//
// Created by Naga Satya Karthik on 11/11/17.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/ConstructKMers.h"
#include "../src/RabinKarpHash.h"
#include "../lib/BBHash-master/BooPHF.h"
typedef boomphf::SingleHashFunctor<u_int64_t>  hasher_t;
typedef boomphf::mphf<  long long, hasher_t  > boophf_t;

#define GENOMEFA "/Users/nagasaty/0classes/bdb/DeBruijnGraph/datasets/genome.fa"

namespace {
    class ConstructKMersTest : public testing::Test {

    public:
        int k;
        ConstructKMers* sut;
        RabinKarpHash* rkhash;
        ConstructKMersTest() {
            k = 15;
            sut = new ConstructKMers(k);
            rkhash = new RabinKarpHash(k);
        }

        virtual ~ConstructKMersTest() {
            delete sut;
            delete rkhash;
        }
    };
}

TEST_F(ConstructKMersTest, DISABLED_Kmers) {
    vector<string> kmers = sut->getKMers(GENOMEFA);
    vector<long long> kmersHashValues = sut->getRKHashMaps(kmers);
    map<string, long long> map;
    set<long long> hashSet;
    for(int i = 0 ; i < kmersHashValues.size(); i++){
        if(map.find(kmers[i]) != map.end()){
            if(map[kmers[i]]!= kmersHashValues[i]){
                printf("Diff hash value found for the same key");
                ASSERT_FALSE(true);
            }
        }else{
            map.insert(make_pair(kmers[i], kmersHashValues[i]));
            if(hashSet.find(kmersHashValues[i]) != hashSet.end()){
                printf("Duplicate hash found. for : %lli, \n"
                               "There is one more key in the map with the same hash value.\n", kmersHashValues[i]);
                ASSERT_FALSE(true);
            }
            hashSet.insert(kmersHashValues[i]);
        }
    }
    printf("No duplicate hash values found");
    ASSERT_EQ(kmersHashValues.size(), kmers.size());
}

TEST_F(ConstructKMersTest, GetUniqueKmersTest){
    vector<string> kmers = {"abc", "eac", "aec", "abc"};
    vector<string> uniqKmers = sut->getUniqueKMers(kmers);
    ASSERT_EQ(uniqKmers.size(), 3);
    ASSERT_EQ(uniqKmers[0], "abc");
    ASSERT_EQ(uniqKmers[1], "aec");
    ASSERT_EQ(uniqKmers[2], "eac");
}

