#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "kolor.h"
#include "fab_kol.h"

class MojaPolityka
{
    public:
         Kolor handleUnknownColor(const std::string &nazwa)
         { return Kolor(); }
};

template<unsigned char r, unsigned char g, unsigned char b>
class CustomUnknownColorPolicy
{
    public:
        Kolor handleUnknownColor(const std::string &nazwa)
        { return Kolor(r, g, b); }
};

FabrykaKolorow<> fabryka;
FabrykaKolorow<MojaPolityka> moja_fabryka;
FabrykaKolorow<CustomUnknownColorPolicy<255, 255, 255>> defaultWhiteColorFactory;

int main()
{
    cout << "Default policy:" << endl;

    try {
        cout << "zielony - " << fabryka.zwrocKolor("zielony") << '\n';
        cout << "green - " << fabryka.zwrocKolor("green") << '\n';
    } catch(...) {
        cout << "Zlapano wyjatek.\n";
    }

    cout << "MojaPolityka:" << endl;

    cout << "zielony - " << moja_fabryka.zwrocKolor("zielony") << '\n';
    cout << "green - " << moja_fabryka.zwrocKolor("green") << '\n';

    cout << "CustomPolicy - white:" << endl;

    cout << "zielony - " << defaultWhiteColorFactory.zwrocKolor("zielony") << '\n';
    cout << "green - " << defaultWhiteColorFactory.zwrocKolor("green") << '\n';

    return 0;
}