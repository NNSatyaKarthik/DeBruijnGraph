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
        RabinKarpHash sut;

        RabinKarpHashTest() {
            sut;
        }
    };
}

TEST_F(RabinKarpHashTest, hashValueOfATGC) {
    ASSERT_EQ(sut.rabinkarpHash("ATGC"), 27);
}
