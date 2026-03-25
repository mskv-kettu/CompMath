#include <iostream>
using std::string;
#include <fstream>
#include <cmath>

int upwind_scheme(const int NX, const int NT, const double C, const double* U0, string output_name);


int main()
{
    const double PI = 3.14159265358979323846;
    const int NX = 41;
    const double T = 18;
    double h = 0.5;
    double L = h * (NX - 1);
    // Courant number
    double* C = new double[3] { 1.0, 0.6, 0.3};

    string output_name = "1.txt";
    double* U0 = new double[NX]; 
    for (int m = 0; m < NX; m++)
    {
        U0[m] = std::sin( 4*PI*(m*h)/L ); 
    }

    double tau = C[0] * h;
    int NT = T / tau;

    upwind_scheme(NX, NT, C[0], U0, output_name);

    delete U0;
    delete C;
	return 0;
}

int upwind_scheme(const int NX, const int NT, const double C, const double* U0, string output_name)
{
    double* y = new double[NX];
    for (int m = 1; m <= NX; m++) // Можно сразу сделать шаг по времени
    {
        y[m] = U0[m];
    }
    for (int n = 1; n <= NT; n++)
    {
        for (int m = NX-1; m >= 2; m--) 
        {
            y[m] = y[m-1] - C * (y[m] - y[m-1]);
        }
        y[0] = y[NX-1];
    }

    //std::ofstream outFile("1.txt");

//    if (outFile.is_open()) {
        for (int m = 0; m < NX; m++)
        {
            std::cout << m+1 << " " << y[m] << std::endl;
        }

//        outFile.close();
//        std::cout << "File is ok" << std::endl;
//    } else {
//        std::cout << "File problem" << std::endl;
//    }
    delete y;
    
    return 0;
}