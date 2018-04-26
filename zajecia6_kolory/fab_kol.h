#include <string>

using std::string;

class ExceptionUnknownColorPolicy{
    protected:
        Kolor handleUnknownColor(string s) {
            throw "Nieznany kolor";
        }
};

template<typename UnknownColorPolicy = ExceptionUnknownColorPolicy>
class FabrykaKolorow : private UnknownColorPolicy
{
    public:
        Kolor zwrocKolor(string s) {
            if(s == "zielony") {
                return Kolor(0, 255, 0);
            }
            return this->handleUnknownColor(s);
        }
};
