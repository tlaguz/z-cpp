#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iterator>
using std::iterator_traits;

#include <list>
using std::list;
#include <iterator>
using std::iterator_traits;
using std::forward_iterator_tag;
using std::random_access_iterator_tag;
using std::bidirectional_iterator_tag;

int main2();
int main3();
int main4();

template <typename Iter>
typename iterator_traits<Iter>::value_type najmniejszy(Iter a, Iter b)
{
    if (a == b)
        throw "Pusta sekwencja";

    Iter minimum = a;
    for(Iter i = a; i != b; i++) {
        if (*minimum > *b) minimum = b;
    }
    return *minimum;
}


int main()
{
    list<int> lista({-4, 12, -2, 5});
    cout << "List min: " << najmniejszy(lista.begin(), lista.end()) << endl;

    int t[4] = {-4, 12, -2, 5};
    cout << "Array min: " << najmniejszy(t, t + 4) << endl;

    return main2();
}

//------------------------------------------------------------------------------------

template <typename Iter>
int operacja_impl(Iter i, bidirectional_iterator_tag)
{
    cout << "Iterator dwukierunkowy.\n";
    return 3;
}

template <typename Iter>
int operacja_impl(Iter i, forward_iterator_tag)
{
    cout << "Iterator jednokierunkowy.\n";
    return 1;
}

template <typename Iter>
int operacja_impl(Iter i, random_access_iterator_tag)
{
    cout << "Iterator o swobodnym dostepie.\n";
    return 2;
}

template <typename Iter>
inline int operacja(Iter i)
{
    return operacja_impl(i, typename iterator_traits<Iter>::iterator_category());
}


int main2()
{
    cout << "main2: " << endl;
    list<int> l;
    operacja(l.begin());

    int t[3];
    operacja(t);

    return main3();
}



//---------------------------------------------------------------

template <typename Iter>
void sortuj_f(Iter b, Iter e, forward_iterator_tag) //prosty wybor
{
    Iter i, min;
    while (b != e) {
        i = min = b;
        while (++i != e) {
            if (*min > *i) min = i;
        }
        if (b != min)
            std::swap(*b, *min);
        ++b;
    }
}

template <typename Iter>
void sortuj_f(Iter b, Iter e, random_access_iterator_tag tag) //quicksort
{
    if (e - b <= 1) return;
    Iter left = b;
    Iter right = e - 1;
    typename iterator_traits<Iter>::value_type pivot = *(left + (right - left) / 2);
    while (1) {
        while (*left < pivot) ++left;
        while (*right > pivot) --right;
        if (left > right) break;
        std::swap(*left, *right);
        ++left;
        --right;
    }
    sortuj_f(b, right + 1, tag);
    sortuj_f(left, e, tag);
}


template <typename Iter>
inline void sortuj(Iter b, Iter e)
{
    return sortuj_f(b, e, typename iterator_traits<Iter>::iterator_category());
}
template <typename Iter>
void wypisz_na_cout(Iter b, Iter e)
{
    while (b != e) {
        cout << *b;
        ++b;
        if (b != e) cout << ' ';
    }
    cout << '\n';
}
int main3()
{
    static const int len = 20;
    int t[len];
    list<int> l;

    srand(time(0));
    for (int i = 0; i < len; ++i) {
        t[i] = 10 + rand() % 90;
        l.push_back(t[i]);
    }

    wypisz_na_cout(l.begin(), l.end());
    sortuj(l.begin(), l.end());
    wypisz_na_cout(l.begin(), l.end());
    sortuj(t, t + len);
    wypisz_na_cout(t, t + len);

    return main4();
}

//----------------------------------------------


template <typename T>
struct is_pointer_trait
{
    static const bool value = false;
};

template <typename T>
struct is_pointer_trait<T *>
{
    static const bool value = true;
};

int main4()
{
    cout << "int: " << is_pointer_trait<int>::value << endl
         << "int*: " << is_pointer_trait<int*>::value << endl;

    return 0;
}