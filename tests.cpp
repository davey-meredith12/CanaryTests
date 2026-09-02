#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;



void reportFailure(string file, int line, string message = ""){
    cout << "Test failed at " << file << ":" << line << endl;
    cout << message << endl;
}

#define EXPECT_TRUE(condition) \
    do{ \
        if (!(condition)){ \
                reportFailure(__FILE__, __LINE__); \
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
        } \
    } while (false);
    

    int main(){
        EXPECT_TRUE(true);
        EXPECT_TRUE(false);
        EXPECT_EQ(10, 10);
        EXPECT_EQ(10, 3);

    }