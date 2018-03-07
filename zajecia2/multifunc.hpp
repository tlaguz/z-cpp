#ifndef UJ1_MULTIFUNC_HPP
#define UJ1_MULTIFUNC_HPP

//Możliwe że nie do końca zrozumiałem polecenie.

#include <iomanip>

template<typename res, typename func1, typename func2>
class multifunc {
    protected:
        func1 _A;
        func2 _B;
    public:
        multifunc(func1 A, func2 B) {
            _A = A;
            _B = B;
        }

        void update() { // uaktualnienie A i B
            _A.update();
            _B.update();
        }

        res operator()() {
            std::cout << _A() << std::endl;
            std::cout << _B() << std::endl;
            return _A() + _B();
        }
};

class functor1 {
    private:
        std::string _internal_state = "empty f1";
    public:
        void update() {
            _internal_state = "updated f1";
        }

        std::string operator()() const {
            return _internal_state;
        }
};

class functor2 {
    private:
        std::string _internal_state = "empty f2";
    public:
        void update() {
            _internal_state = "updated f2";
        }

        std::string operator()() const {
            return _internal_state;
        }
};

#endif //UJ1_MULTIFUNC_HPP
