#include "canaryTests.cpp"
#include <stdexcept>


TEST(HandlingException, ThrowFailsNoCrash){
    throw std::runtime_error("Correctly handled if failed test");
}

TEST(HandlingException, ExpectThrow){
    EXPECT_THROW(throw std::runtime_error("Test exception"), std::runtime_error);
}

TEST(HandlingException, ExpectAnyThrow){
    EXPECT_ANY_THROW(throw std::runtime_error("error"));
}

int main(){
    return RUN_ALL_TESTS();
}