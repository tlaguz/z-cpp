#ifndef UJ1_CZLOWIEK_HPP
#define UJ1_CZLOWIEK_HPP

#include <string>
#include <ostream>

class czlowiek {
    private:
        std::string _imie;
        std::string _nazwisko;
        unsigned int _wiek;
        float _umiejetnosc_gry_na_ukulele;
    public:
        czlowiek(
                std::string imie,
                std::string nazwisko,
                unsigned int wiek,
                float umiejetnosc_gry_na_ukulele) {
            _imie = imie;
            _nazwisko = nazwisko;
            _wiek = wiek;
            _umiejetnosc_gry_na_ukulele = umiejetnosc_gry_na_ukulele;
        }

        friend std::ostream & operator<< (std::ostream &stream, const czlowiek &s) {
            return stream << "Nazwisko, Imie: " << s._nazwisko << ", " << s._imie << std::endl
                          << "Wiek, Umiejetnosc gry na ukulele: " << s._wiek << ", " << s._umiejetnosc_gry_na_ukulele;

        }

        const std::string &get_imie() const {
            return _imie;
        }

        const std::string &get_nazwisko() const {
            return _nazwisko;
        }

        unsigned int get_wiek() const {
            return _wiek;
        }

        float get_umiejetnosc_gry_na_ukulele() const {
            return _umiejetnosc_gry_na_ukulele;
        }
};

//zakladam ze imie i nazwisko jednoznacznie identyfikuja osoby

//źródło: http://thispointer.com/using-unordered_set-with-custom-hasher-and-comparision-function/
//uwagi patrz komentarz w pliku wektor.hpp
struct czlowiek_comparator {
    public:
        bool operator()(const czlowiek & c1, const czlowiek & c2) const {
            return (c1.get_nazwisko() == c2.get_nazwisko() && c1.get_imie() == c2.get_imie());
        }
};


struct czlowiek_hasher {
    size_t operator() (const czlowiek &c) const {
        auto n_i = c.get_nazwisko() + "!-" + c.get_imie();
        return std::hash<std::string>()(n_i);
    }
};

#endif //UJ1_CZLOWIEK_HPP
