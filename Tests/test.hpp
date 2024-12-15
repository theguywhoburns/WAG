#include <WAG/util.hpp>
#include <functional>
#include <vector>

namespace WAG::Testing {

class TestCase {
public:
  TestCase(const std::string &name) : name_(name) {}

  void AddTest(const std::string &testName, std::function<void()> testFunc) {
    tests_.push_back({testName, testFunc});
  }

  void RunTests() {
    for (const auto &test : tests_) {
      try {
        test.second(); // Execute the test function
        Log<Util::Logger::Info>(name_, "::", test.first, ": Passed");
        if (!errors_.empty()) {
          Log<Util::Logger::Error>(name_, "::", test.first, ": Failed: ");
          for (const auto &error : errors_)
            Log<Util::Logger::Error>(error);
        } else
          passedTests_++;
      } catch (const std::exception &e) {
        Log<Util::Logger::Error>(name_, "::", test.first, ": Failed - ",
                                 e.what());
        failedTests_++;
      }
    }
  }

  int GetPassedTests() const { return passedTests_; }
  int GetFailedTests() const { return failedTests_; }

private:
  std::string name_;
  std::vector<std::pair<std::string, std::function<void()>>> tests_;
  std::vector<std::string> errors_;
  int passedTests_ = 0;
  int failedTests_ = 0;
};

// Example Macros (Simplified for brevity)
#define TEST(TestCaseName, TestName)                                           \
  void Test_##TestCaseName##_##TestName(TestCase &test);                       \
  static void                                                                  \
      __attribute__((constructor)) Register_##TestCaseName##_##TestName() {    \
    GetTestCase(#TestCaseName)                                                 \
        .AddTest(#TestName, Test_##TestCaseName##_##TestName);                 \
  }                                                                            \
  void Test_##TestCaseName##_##TestName()

// More macros like ASSERT_TRUE, ASSERT_EQ, etc. will be needed.

// Function to get or create a TestCase instance
TestCase &GetTestCase(const std::string &name);

#define ASSERT_COND_(expr, msg, ...)                                           \
  if (!expr) {                                                                 \
    throw std::runtime_error(#expr " - " msg #__VA_ARGS__);                    \
  }
#define LOCATION __FILE__ ":" __FUNCTION__ ":" __LINE__
#define FAILED_AT(what) #what "failed at " LOCATION

#define ASSERT_TRUE(expr) ASSERT_COND_(expr, FAILED_AT(ASSERT_TRUE))
#define ASSERT_FALSE(expr) ASSERT_COND_(expr, FAILED_AT(ASSERT_FALSE))
#define ASSERT_EQ(a, b) ASSERT_COND_(a == b, FAILED_AT(ASSERT_EQ))
#define ASSERT_NEQ(a, b) ASSERT_COND_(a != b, FAILED_AT(ASSERT_NEQ))
#define ASSERT_GT(a, b) ASSERT_COND_(a > b, FAILED_AT(ASSERT_GT))
#define ASSERT_GTE(a, b) ASSERT_COND_(a >= b, FAILED_AT(ASSERT_GTE))
#define ASSERT_LT(a, b) ASSERT_COND_(a < b, FAILED_AT(ASSERT_LT))
#define ASSERT_LTE(a, b) ASSERT_COND_(a <= b, FAILED_AT(ASSERT_LTE))
#define ASSERT_COND(expr) ASSERT_COND_(expr, FAILED_AT(ASSERT_COND))

#define EXPECT_COND_(expr, msg, ...)                                           \
  if (!(expr)) {                                                               \
    test.errors_.emplace_back(std::string(#expr) + " - " + msg #__VA_ARGS__);  \
  }

#define EXPECT_TRUE(expr) EXPECT_COND_(expr, FAILED_AT(EXPECT_TRUE))
#define EXPECT_FALSE(expr) EXPECT_COND_(expr, FAILED_AT(EXPECT_FALSE))
#define EXPECT_EQ(a, b) EXPECT_COND_(a == b, FAILED_AT(EXPECT_EQ))
#define EXPECT_NEQ(a, b) EXPECT_COND_(a != b, FAILED_AT(EXPECT_NEQ))
#define EXPECT_GT(a, b) EXPECT_COND_(a > b, FAILED_AT(EXPECT_GT))
#define EXPECT_GTE(a, b) EXPECT_COND_(a >= b, FAILED_AT(EXPECT_GTE))
#define EXPECT_LT(a, b) EXPECT_COND_(a < b, FAILED_AT(EXPECT_LT))
#define EXPECT_LTE(a, b) EXPECT_COND_(a <= b, FAILED_AT(EXPECT_LTE))
#define EXPECT_COND(expr) EXPECT_COND_(expr, FAILED_AT(EXPECT_COND))

} // namespace WAG::Testing
