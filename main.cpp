#include "canaryTests.cpp"

TEST(ExpectTrue, FailTest){
    EXPECT_TRUE(false);
}

TEST(ExpectTrue, PassTest){
    EXPECT_TRUE(true);
}

TEST(ExpectEq, FailCompareTest){
    EXPECT_EQ(1, 2);
}

TEST(ExpectEq, PassCompareTest){
    EXPECT_EQ(1, 1);
}

TEST(ExpectFalse, FailTest){
    EXPECT_FALSE(true);
}

TEST(ExpectFalse, PassTest){
    EXPECT_FALSE(false);
}

TEST(ExpectNear, FailTest){
    EXPECT_NEAR(1, 1.2, .1);
}

TEST(ExpectNear, PassTest){
    EXPECT_NEAR(1, 1.2, .3);
}

TEST(NotEqual, FailTest){
    EXPECT_NE(1, 1);
}

TEST(NotEqual, PassTest){
    EXPECT_NE(1, 2);
}

TEST(LessThan, FailTest){
    EXPECT_LT(1, 0);
    EXPECT_LT(1, 1);
}

TEST(LessThan, PassTest){
    EXPECT_LT(1, 2);
}

TEST(LessThanOrEqual, FailTest){
    EXPECT_LE(1, 0);
}

TEST(LessThanOrEqual, PassTest){
    EXPECT_LE(1, 1)
    EXPECT_LE(1, 2);
}

TEST(GreaterThan, FailTest){
    EXPECT_GT(1, 2);
    EXPECT_GT(1, 1);
}

TEST(GreaterThan, PassTest){
    EXPECT_GT(1, 0);
}

TEST(GreaterThanOrEqual, FailTest){
    EXPECT_GE(1, 2);
}

TEST(GreaterThanOrEqual, PassTest){
    EXPECT_GE(1, 1);
    EXPECT_GE(1, 0);
}


int main(){
    return RUN_ALL_TESTS();
}