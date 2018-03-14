#ifndef ZAJECIA3_WYKONYWACZ_HPP
#define ZAJECIA3_WYKONYWACZ_HPP


template<class... Ts>
class Wykonywacz {
    private:
    public:
        explicit Wykonywacz(double (*fn)(Ts...), Ts... toExec) {
            std::cout << fn(toExec...) << std::endl;
        }
};


#endif //ZAJECIA3_WYKONYWACZ_HPP
