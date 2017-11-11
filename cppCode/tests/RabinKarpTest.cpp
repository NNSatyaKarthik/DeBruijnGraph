//
// Created by Naga Satya Karthik on 11/10/17.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/RabinKarpHash.h"

using testing::Eq;

namespace {
    class RabinKarpHashTest : public testing::Test {

    public:
        RabinKarpHash* sut;

        RabinKarpHashTest() {
            sut = new RabinKarpHash(4);
        }

        virtual ~RabinKarpHashTest() {
            delete sut;
        }
    };
}

TEST_F(RabinKarpHashTest, hashValueOfATGC) {
    ASSERT_EQ(sut->rabinkarpHash("ATGC"), 27);
    ASSERT_EQ(sut->rabinkarpHash("TGC"), 27);
    ASSERT_EQ(sut->rabinkarpHash("LFAJFLAJFF"), -1);
}

TEST_F(RabinKarpHashTest, charToIMapping){
    ASSERT_EQ(sut->genToI('A'), 0);
    ASSERT_EQ(sut->genToI('T'), 1);
    ASSERT_EQ(sut->genToI('G'), 2);
    ASSERT_EQ(sut->genToI('C'), 3);
    ASSERT_EQ(sut->genToI('a'), -1);
}
