#include "canaryTests.cpp"
#include <stdexcept>

TEST(Fail, ThrowFailsNoCrash){
    throw std::runtime_error("Correctly handled if failed test");
}

TEST(Fail, ExpectThrowWrongType){
    EXPECT_THROW(throw std::runtime_error("Test exception"), std::logic_error);
}

TEST(Fail, ExpectThrowNoThrow){
    EXPECT_THROW({int i = 5;}, std::exception);
}

TEST(Fail, ExpectAnyThrowNoThrow){
    EXPECT_ANY_THROW({int i = 5;});
}

TEST(Pass, ExpectThrowCorrectType){
    EXPECT_THROW(throw std::runtime_error("Test exception"), std::runtime_error);
}

TEST(Pass, ExpectAnyThrow){
    EXPECT_ANY_THROW(throw std::runtime_error("error"));
}

int main(){
    return RUN_ALL_TESTS();
}