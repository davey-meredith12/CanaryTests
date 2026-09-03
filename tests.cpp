#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::vector;

vector<void(*)()> tests;
bool currentTestPassed = true;

struct TestRegistration{
    TestRegistration(void (*test)()){
        tests.push_back(test);
    }
};

void reportFailure(string file, int line, string message = ""){
    cout << "Test failed at " << file << ":" << line << endl;
    cout << message << endl;
}

#define MAKE_NAME(a, b) a ## b

#define TEST(name) \
    void name(); \
    TestRegistration MAKE_NAME(registration, name)(name); \
    void name()

#define EXPECT_TRUE(condition) \
    do{ \
        if (!(condition)){ \
                reportFailure(__FILE__, __LINE__); \
                currentTestPassed = false; \
        }  \
    } while (false);
    

#define EXPECT_EQ(a, b) \
    do{ \
        auto stored_a = a; \
        auto stored_b = b; \
        if (stored_a != stored_b){ \
        ostringstream message; \
        message << "Expected: " << stored_a << endl; \
        message << "Actual: " << stored_b << endl; \
        reportFailure(__FILE__, __LINE__, message.str()); \
        currentTestPassed = false; \
        } \
    } while (false);

#define RUN_ALL_TESTS() \
    for(auto test: tests) { \
        currentTestPassed = true; \
        test(); \
        if (currentTestPassed){ \
            cout << "Test Passed" << endl; \
        } \
        else { \
            cout << "Test Failed" << endl; \
        } \
    }

TEST(FailTest){
    EXPECT_TRUE(false);
}

TEST(PassTest){
    EXPECT_TRUE(true);
}

TEST(FailCompareTest){
    EXPECT_EQ(1, 2);
}

TEST(PassCompareTest){
    EXPECT_EQ(1, 1);
}


int main(){
    RUN_ALL_TESTS();
}