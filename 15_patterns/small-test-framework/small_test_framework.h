#pragma once

#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <unordered_set>
#include <vector>

class AbstractTest {
   public:
    AbstractTest() = default;
    AbstractTest(const AbstractTest&) = delete;
    AbstractTest& operator=(const AbstractTest&) = delete;
    AbstractTest(AbstractTest&&) = delete;
    AbstractTest& operator=(AbstractTest&&) = delete;
    virtual void SetUp() = 0;
    virtual void TearDown() = 0;
    virtual void Run() = 0;
    virtual ~AbstractTest() = default;
};

class TestRegistry final {
   public:
    TestRegistry(const TestRegistry&) = delete;
    TestRegistry& operator=(const TestRegistry&) = delete;
    TestRegistry(TestRegistry&&) = delete;
    TestRegistry& operator=(TestRegistry&&) = delete;
    ~TestRegistry() = default;

    static TestRegistry& Instance() {
        static TestRegistry registry;
        return registry;
    }

    template <class TestClass>
    void RegisterClass(const std::string& class_name) {
        if (tests_.contains(class_name) || types_.contains(typeid(TestClass))) {
            throw std::runtime_error("Test already registered");
        }
        tests_.emplace(class_name, [] { return std::make_unique<TestClass>(); });
        types_.insert(typeid(TestClass));
    }

    std::unique_ptr<AbstractTest> CreateTest(const std::string& class_name) {
        if (!tests_.contains(class_name)) {
            throw std::out_of_range("Test not registered");
        }
        return tests_[class_name]();
    }

    void RunTest(const std::string& test_name) {
        const auto test = CreateTest(test_name);
        test->SetUp();
        try {
            test->Run();
            test->TearDown();
        } catch (...) {
            test->TearDown();
            throw;
        }
    }

    template <class Predicate>
    std::vector<std::string> ShowTests(Predicate callback) const {
        std::vector<std::string> result;
        result.reserve(tests_.size());
        for (const auto& [name, value] : tests_) {
            if (callback(name)) {
                result.push_back(name);
            }
        }
        return result;
    }

    std::vector<std::string> ShowAllTests() const {
        return ShowTests([](const std::string&) { return true; });
    }

    template <class Predicate>
    void RunTests(Predicate callback) {
        for (const auto& test : ShowTests(callback)) {
            RunTest(test);
        }
    }

    void Clear() {
        tests_.clear();
        types_.clear();
    }

   private:
    std::map<std::string, std::function<std::unique_ptr<AbstractTest>()>> tests_;
    std::unordered_set<std::type_index> types_;
    TestRegistry() = default;
};

class FullMatch {
   public:
    explicit FullMatch(const char* str) : str_{str} {
    }

    bool operator()(const std::string& other_str) const {
        return str_ == other_str;
    }

   private:
    std::string str_;
};

class Substr {
   public:
    explicit Substr(const char* str) : str_{str} {
    }

    bool operator()(const std::string& other_str) const {
        return other_str.contains(str_);
    }

   private:
    std::string str_;
};
