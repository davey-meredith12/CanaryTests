#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::vector;

struct TestInfo{
    string testName;
    void (*testFunction)();
};

vector<TestInfo> tests;
bool currentTestPassed = true;

struct TestRegistration{
    TestRegistration(string name, void (*test)()){
        tests.push_back({name, test});
    }
};

void reportFailure(string file, int line, string message = ""){
    cout << "Test failed at " << file << ":" << line << endl;
    cout << message << endl;
}

#define MAKE_NAME(a, b) a ## b

#define STRINGIFY(x) #x

#define TEST(name) \
    void name(); \
    TestRegistration MAKE_NAME(registration, name)(STRINGIFY(name), name); \
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

int RUN_ALL_TESTS(){
    bool allTestsPassed = true;
    int testsPassed = 0;
    int testsFailed = 0;

    for(auto test: tests) {
        currentTestPassed = true;
        test.testFunction();
        if(currentTestPassed){
            cout << test.testName << ": Test Passed" << endl;
            testsPassed++;
        }
        else{
            cout << test.testName << ": Test Failed" << endl;
            allTestsPassed = false;
            testsFailed++;
        }
    }
    cout << testsPassed + testsFailed << " tests ran." << endl;
    cout << testsPassed << " tests passed." << endl;
    cout << testsFailed << " tests failed." << endl;
    return allTestsPassed ? 0 : 1;
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
    return RUN_ALL_TESTS();
}