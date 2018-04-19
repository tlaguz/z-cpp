#ifndef ZAJECIA3_WYKONYWACZ_HPP
#define ZAJECIA3_WYKONYWACZ_HPP

/*
 * Można użyć boost::any
 */

template<class... Ts>
class Wykonywacz {
    private:
    protected:
        std::tuple<Ts...> params;
    public:
        explicit Wykonywacz(auto func(Ts... args), Ts... toExec) {
            params = std::make_tuple(toExec...);
            std::cout << func(toExec...) << std::endl;
        }
};


#endif //ZAJECIA3_WYKONYWACZ_HPP
