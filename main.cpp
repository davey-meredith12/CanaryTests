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


int main(){
    return RUN_ALL_TESTS();
}