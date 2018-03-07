#include <iostream>
#include <unordered_set>

#include "wektor.hpp"
#include "czlowiek.hpp"
#include "multifunc.hpp"

using namespace std;

int main() {
    cout << "Wersja kompilatora: " <<  __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << endl;

    //-------------------------------- 1

    wektor w1(1, 2);
    wektor w2(1, 4);
    wektor w3(2, 2);
    wektor w4(3, 1);

    unordered_set<wektor, wektor_hasher, wektor_comparator> uset;

    uset.insert({w1, w2, w3, w4});

    for(wektor w : uset) {
        cout << "wektor x: " << w.get_x() << " y: " << w.get_y() << endl;
    }

    //--------------------------------- 2

    czlowiek c1("Jan", "Nowak", 30, 0.7);
    czlowiek c2("Jan", "Kowalski", 34, 0.0);
    czlowiek c3("Zdzisław", "Nowak", 24, 6.66);
    czlowiek c4("John", "Doe", 50, 4.0);

    unordered_set<czlowiek, czlowiek_hasher, czlowiek_comparator> czlowieki;
    czlowieki.insert({c1, c2, c3, c4});

    for(czlowiek c : czlowieki) {
        cout << c << endl;
    }

    //--------------------------------- 3

    functor1 f1;
    functor2 f2;
    multifunc<std::string,functor1,functor2> MF(f1, f2);
    cout << MF() << endl;
    MF.update();
    cout << MF() << endl;

    return 0;
}