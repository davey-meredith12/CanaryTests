#include "tests.cpp"

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


int main(){
    return RUN_ALL_TESTS();
}