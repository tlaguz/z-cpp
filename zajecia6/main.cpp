#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <list>
using std::list;

#include <iterator>
using std::ostream_iterator;

// ----------------------------------------------------------------------------

template <typename WytycznaLamaniaWierszy>
class Dokument : private WytycznaLamaniaWierszy
{
        list<string> akapity;

        //bo akapity są private
        template <typename t> friend class Dokument;

    public:
        Dokument(){}

        template <typename WytycznaLamaniaWierszy2>
        Dokument(const Dokument<WytycznaLamaniaWierszy2> & d)
        {
            akapity = d.akapity;
        }

        template <typename WytycznaLamaniaWierszy2>
        Dokument & operator=(const Dokument<WytycznaLamaniaWierszy2> & d)
        {
            akapity = d.akapity;
            return *this;
        }

        void wstawAkapit(string tresc, int nr = -1);
        void usunAkapit(int nr);
        // akapity sÄ numerowane od 0

        void drukujNaEkran(int szerokosc = 79);
};


template <typename WLW>
void Dokument<WLW>::wstawAkapit(string tresc, int nr)
{
    if (nr == -1 || nr > static_cast<int>(akapity.size())) {
        // static_cast jest po to, aby kompilator nie wypisywaĹ ostrzeĹźeĹ
        akapity.push_back(tresc);
    } else {
        list<string>::iterator i = akapity.begin();
        while (--nr >= 0)
            ++i;
        akapity.insert(i, tresc);
    }
}

template <typename WLW>
void Dokument<WLW>::usunAkapit(int nr)
{
    if (nr < 0 || nr >= akapity.size())
        return;
    list<string>::iterator i = akapity.begin();
    while (--nr >= 0)
        ++i;
    akapity.erase(i);
}

template <typename WLW>
void Dokument<WLW>::drukujNaEkran(int szerokosc)
{
    ostream_iterator<string> output(cout, "\n");
    for (list<string>::iterator i = akapity.begin(); i != akapity.end(); ++i)
        this->zlam_akapit(*i, szerokosc, output);
}

// ----------------------------------------------------------------------------

class TrywialnyLamacz
{
    public:
        template <typename OIter>
        OIter zlam_akapit(const string &, int, OIter);
};

template <typename OIter>
OIter TrywialnyLamacz::zlam_akapit(const string & tresc,
                                   int szerokosc, OIter zlamane_linie)
{
    int poczatek = 0;
    int koniec = tresc.size() - 1;
    while (poczatek <= koniec) {
        if (poczatek + szerokosc > koniec) {
            *zlamane_linie = tresc.substr(poczatek, koniec - poczatek + 1);
            ++zlamane_linie;
            break;
        }
        int i = poczatek + szerokosc;
        while (i > poczatek && tresc[i] != ' ')
            --i;
        if (i > poczatek) {     // udaĹo siÄ znaleĹşÄ punkt zĹamania
            *zlamane_linie = tresc.substr(poczatek, i - poczatek);
            ++zlamane_linie;
            poczatek = i + 1;
        } else {        // nie ma spacji - zĹam w Ĺrodku dĹuuugiego sĹowa
            *zlamane_linie = tresc.substr(poczatek, szerokosc);
            ++zlamane_linie;
            poczatek = poczatek + szerokosc - 1;
        }
    }
    return zlamane_linie;
}

// ----------------------------------------------------------------------------

class NielamiacyLamacz
{
        public:
        template <typename OIter>
        OIter zlam_akapit(const string & tresc, int szerokosc, OIter zlamane_linie)
        {
            *zlamane_linie = tresc;
            return ++zlamane_linie;
        }
};

int main()
{
    Dokument<TrywialnyLamacz> dok;

    dok.wstawAkapit("Litwo! Ojczyzno moja! Ty jestes jak zdrowie.");
    dok.wstawAkapit("Ile cie trzeba cenic, ten tylko sie dowie,");
    dok.wstawAkapit("Kto cie stracil. Dzis pieknosc twa w calej ozdobie");
    dok.wstawAkapit("Widze i opisuje, bo tesknie po tobie.");

    dok.drukujNaEkran(19);

    Dokument<NielamiacyLamacz> dok2 = dok;
    dok2.drukujNaEkran(19);

    return 0;
}