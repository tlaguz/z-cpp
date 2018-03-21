#include <iostream>
#include "zespolona.hpp"

int main2();

int main(){
  Zespolona<float> c1(1.0f,0.0f),c2({0.0f,1.0f}); // 2 róƶne konstruktory => bazujące
  Zespolona<double> c3, c4(2.0,3.0);              // na typach T i std::initializer_list<T>

  std::cout<<"c1 = "<<c1<<" ";
  std::cout<<"c2 = "<<c2<<std::endl;
  std::cout<<"c1+c2= "<<c1+c2<<" "<<std::endl;
  std::cout<<"c1-c2= "<<c1-c2<<" "<<std::endl;
  std::cout<<"c3 = "<<c3<<" ";
  std::cout<<"c4 = "<<c4<<std::endl;
  std::cout<<"c3*c4= "<<c3*c4<<" "<<std::endl;
  std::cout<<"c3/c4= "<<c3/c4<<" "<<std::endl;

  //Zespolona<int> c5; // odkomentowanie tej linii powoduje błąd kompilacji

  return main2();
}


#include <iostream>
#include "wykonywacz.hpp"

double f_di(double d1, int i1);
double f_3i(int i1, int i2, int i3);
double f_2d3i(double d1, double d2, int i1, int i2, int i3);

int main2(){
    std::cout << "Zadanie 2: " << std::endl;

  double a = 1.0, b = 2.0;
  int i = 1, j = 2, k = 3;

  Wykonywacz<double,int>                jeden(&f_di,a,i);
  Wykonywacz<int,int,int>                 dwa(&f_3i,i,j,k);
  Wykonywacz<double,double,int,int,int>  trzy(&f_2d3i,a,b,i,j,k);

/*
 * Jeƶeli ktoś juƶ potrafi warto korzystać ze znacznie bardziej
 * bezpiecznego szablonu std::function. Ale o nim na innych zajęciach.
 */
  return 0;
}


double f_di(double d1, int i1){
  return d1 + i1;
}

double f_3i(int i1, int i2, int i3){
  return i1 + i2 + i3;
}

double f_2d3i(double d1, double d2, int i1, int i2, int i3){
  return d1 + d2 + i1 + i2 + i3;
}
