#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::vector;

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

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

#define CONCAT(a, b) a ## b

#define MAKE_NAME(a, b) CONCAT(a, b)

#define STRINGIFY(x) #x

#define TEST(suite, name) \
    void MAKE_NAME(suite, name)(); \
    TestRegistration MAKE_NAME(MAKE_NAME(registration, suite), name)(STRINGIFY(suite), STRINGIFY(name), MAKE_NAME(suite, name)); \
    void MAKE_NAME(suite, name)()

#define EXPECT_TRUE(condition) \
    do{ \
        if (!(condition)){ \
                reportFailure(__FILE__, __LINE__); \
                currentTestPassed = false; \
        }  \
    } while (false);

#define EXPECT_FALSE(condition) \
    do{ \
        if (condition){ \
                reportFailure(__FILE__, __LINE__); \
                currentTestPassed = false; \
        }  \
    } while (false);

#define EXPECT_NEAR(val1, val2, abs_error) \
    do{ \
        auto stored_val1 = val1; \
        auto stored_val2 = val2; \
        auto diff = stored_val1 - stored_val2; \
        if(diff < 0){ \
            diff = diff * -1; \
        } \
        if (diff > abs_error){ \
            reportFailure(__FILE__, __LINE__); \
            currentTestPassed = false; \
        } \
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
        cout << GREEN << "[ RUN       ] " << test.testSuite << "." << test.testName << RESET << endl;
        test.testFunction();
        if(currentTestPassed){
            cout << GREEN << "[        OK ] " << test.testSuite << "." << test.testName << RESET << endl;
            testsPassed++;
        }
        else{
            cout << RED << "[      FAIL ] " << test.testSuite << "." << test.testName << RESET << endl;
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