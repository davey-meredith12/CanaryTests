#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::vector;

struct TestInfo{
    string testSuite;
    string testName;
    void (*testFunction)();
};

vector<TestInfo> tests;
bool currentTestPassed = true;

struct TestRegistration{
    TestRegistration(string suite, string name, void (*test)()){
        tests.push_back({suite, name, test});
    }
};

void reportFailure(string file, int line, string message = ""){
    cout << "   Test failed at " << file << ":" << line << endl;
    cout << message;
}

#define MAKE_NAME(a, b) a ## b

#define STRINGIFY(x) #x

#define TEST(suite, name) \
    void name(); \
    TestRegistration MAKE_NAME(registration, name)(STRINGIFY(suite), STRINGIFY(name), name); \
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
        message << "   Expected: " << stored_a << endl; \
        message << "   Actual: " << stored_b << endl; \
        reportFailure(__FILE__, __LINE__, message.str()); \
        currentTestPassed = false; \
        } \
    } while (false);

int RUN_ALL_TESTS(){
    bool allTestsPassed = true;
    int testsPassed = 0;
    int testsFailed = 0;
    string currentSuite = "";

    for(auto test: tests) {

        if(test.testSuite != currentSuite){
            currentSuite = test.testSuite;
            cout << endl;
            cout << "============== " << currentSuite << " ==============" << endl;
            cout << endl;
        }

        currentTestPassed = true;
        cout << "\033[32m[ RUN       ] " << test.testSuite << "." << test.testName << "\033[0m" << endl;
        test.testFunction();
        if(currentTestPassed){
            cout << "\033[32m[        OK ] " << test.testSuite << "." << test.testName << "\033[0m" << endl;
            testsPassed++;
        }
        else{
            cout << "\033[31m[      FAIL ] " << test.testSuite << "." << test.testName << "\033[0m" << endl;
            allTestsPassed = false;
            testsFailed++;
        }
    }
    cout << endl;
    cout << testsPassed + testsFailed << " tests ran." << endl;
    cout << testsPassed << " tests passed." << endl;
    cout << testsFailed << " tests failed." << endl;
    return allTestsPassed ? 0 : 1;
}