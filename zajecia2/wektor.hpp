#ifndef UJ1_WEKTOR_HPP
#define UJ1_WEKTOR_HPP

#include <cstdlib>
#include <functional>

class wektor {
    private:
        int _x, _y;
    public:
        wektor(int x, int y) {
            _x = x;
            _y = y;
        }

        int get_x() const { return _x; }

        int get_y() const { return _y; }
};

//źródło: http://thispointer.com/using-unordered_set-with-custom-hasher-and-comparision-function/
//zmodyfikowałem comparator, w źródle pisali że ma być tak: w1 == w2 => hash(w1) == hash(w2)
//ale gdy tak jest to unordered_set źle obsługuje duplikaty hashy, czemu tak pisali?
//algorytm hashy może mieć kolizje i co wtedy?
struct wektor_comparator {
    public:
        bool operator()(const wektor & w1, const wektor & w2) const {
            return (w1.get_x() == w2.get_x() && w1.get_y() == w2.get_y());
        }
};


struct wektor_hasher {
    size_t operator() (const wektor &w) const {
        return std::hash<int>()(w.get_x());
    }
};

#endif //UJ1_WEKTOR_HPP
