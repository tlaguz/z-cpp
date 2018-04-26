#include <ostream>

using std::ostream;

class Kolor
{
    public:
        Kolor() : Kolor(0,0,0){}

        Kolor(unsigned char r, unsigned char g, unsigned char b) {
            red = r;
            green = g;
            blue = b;
        }

        unsigned char red;
        unsigned char green;
        unsigned char blue;

        friend ostream & operator<< (ostream &wyjscie, const Kolor &k) {
            return wyjscie << "(" << (int)k.red << ", " << (int)k.green << ", " << (int)k.blue << ")";
        }
};