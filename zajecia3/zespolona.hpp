#ifndef ZAJECIA3_ZESPOLONA_HPP
#define ZAJECIA3_ZESPOLONA_HPP

#include <tuple>
#include <iterator>
#include <cmath>

/*
 * Można użyć Static Assertion
 * Można zrobić klasę bazową, nieabstrakcyjną i ogólną,
 * a Zespoloną abstrakcyjną i specjalizować ją do konkretnych typów i dziedziczyć.
 * Wtedy nie bedzie problemu z przeciążaniem +-*\/
 * Patrz też: std::enable_if
 */

template<typename T>
class Zespolona {
    private:
        std::tuple<T,T> _dane;
        bool _hasRealValue() const {
            return std::get<0>(_dane) != 0;
        };
        bool _hasImaginaryValue() const {
            return std::get<1>(_dane) != 0;
        };
        void _init(T a, T b) {
            _dane = std::tuple<T,T>(a, b);
        }

    public:
        Zespolona() : Zespolona(0,0) {}

        Zespolona(T a, T b) {
            _init(a, b);
        }

        Zespolona(std::initializer_list<T> list) {
            switch(list.size()) {
                case 0: _init(0, 0); break;
                case 1: _init(*list.begin(), 0); break;
                case 2: _init(*list.begin(), *list.end()); break;
                default: throw std::invalid_argument("list");
            }
        }

        virtual ~Zespolona() = default;

        T GetReal() const {
            return std::get<0>(_dane);
        }

        T GetImaginary() const {
            return std::get<1>(_dane);
        }

        friend std::ostream & operator<< (std::ostream &stream, const Zespolona &z) {
            if(!z._hasRealValue() && !z._hasImaginaryValue()) {
                return stream << "0.0";
            }

            if(z._hasRealValue()) {
                stream << z.GetReal()
                       << (z._hasImaginaryValue() ? (z.GetImaginary() > 0 ? " + " : " - ") : "");
            }

            if(z._hasImaginaryValue()) {
                stream << abs(z.GetImaginary()) << "j";
            }

            return stream;
        }

        friend Zespolona operator+(const Zespolona& a, const Zespolona& b) {
            return Zespolona(a.GetReal() + b.GetReal(), a.GetImaginary() + b.GetImaginary());
        }

        friend Zespolona operator-(const Zespolona& a, const Zespolona& b) {
            return Zespolona(a.GetReal() - b.GetReal(), a.GetImaginary() - b.GetImaginary());
        }

        friend Zespolona operator*(const Zespolona& a, const Zespolona& b) {
            return Zespolona(a.GetReal() * b.GetReal() - a.GetImaginary() * b.GetImaginary(),
                             a.GetReal() * b.GetImaginary() + a.GetImaginary() * b.GetReal());
        }

        friend Zespolona operator/(const Zespolona& a, const Zespolona& b) {
            auto denominator = pow(b.GetReal(), 2)+pow(b.GetImaginary(), 2);
            return Zespolona((a.GetReal()*b.GetReal()+a.GetImaginary()*b.GetImaginary())/denominator,
                             (a.GetImaginary()*b.GetReal()-a.GetReal()*b.GetImaginary())/denominator);
        }
};

template<>
Zespolona<float>::~Zespolona() = default;

template<>
Zespolona<double>::~Zespolona() = default;

template<>
Zespolona<long double>::~Zespolona() = default;

template<>
class Zespolona<int> {
    public:
        virtual ~Zespolona() = 0;
};


#endif //ZAJECIA3_ZESPOLONA_HPP
