#ifndef ZAJECIA7_ASSERT_HPP
#define ZAJECIA7_ASSERT_HPP

#include <sstream>
#include <exception>
#include <utility>

class AssertionException : public std::exception {
    private:
        std::string _s;
    public:
        explicit AssertionException(std::string s) {
            _s = std::move(s);
        }

        const char *what() const noexcept override {
            return _s.c_str();
        }

};

double Abs(double d) {
    return (d >= 0.0) ? d : -d;
}

template<typename t>
void Assert(t expected, t given) {
    if(expected == given) return;

    std::stringstream ss;
    ss << "Expected: " << expected << " but was " << given;

    throw AssertionException(ss.str());
}

template<typename t>
void AssertLess(t arg1, t arg2) {
    if(arg1 < arg2) return;

    std::stringstream ss;
    ss << "Expected: " << arg1 << " to be smaller than " << arg2;

    throw AssertionException(ss.str());
}

#endif //ZAJECIA7_ASSERT_HPP
