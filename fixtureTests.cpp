#include "canaryTests.cpp"

struct FixtureTest : Test{
    int array[10];
    void SetUp() override {
        for(int i = 0; i < 10; i++){
            array[i] = i;
        }
    };
    void TearDown() override {
    };
};

TEST_F(FixtureTest, TestValues){
    for(int i = 0; i < 10; i++){
        ASSERT_EQ(array[i], i);
    }
}

TEST_F(FixtureTest, EditValues){
    for(int i = 0; i < 10; i++){
        array[i] = array[i] + 10;
    }
}

TEST_F(FixtureTest, ValuesUnchangedFromPrevious){
    for(int i = 0; i < 10; i++){
        ASSERT_EQ(array[i], i);
    }
}

int main(){
    return RUN_ALL_TESTS();
}