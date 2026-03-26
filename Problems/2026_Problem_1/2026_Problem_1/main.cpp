#include <iostream>
using std::string;
#include <fstream>
#include <cmath>
#include <string>

int upwind_scheme(const int NX, double h, const double T, const double CFL, const double* U0, double dt_out_results, string outdir);


int main()
{
    // Начальные данные
    const double PI = 3.14159265358979323846;
    const int NX = 41;
    const double T = 18;
    const double h = 0.5;
    double L = h * (NX - 1);
    double dt_out_results = 5;
    double* CFL = new double[3] { 1.0, 0.6, 0.3}; // Courant number
    string outdir = "upwind_data/";

    
    int NX_new = NX;
    double h_new = h;

    for (int i = 0; i < 3; i++) // Цикл по CFL
    {
        h_new = h;
        NX_new = NX;
        for (int j = 0; j < 3; j++) // 3 разных сетки
        {
            // Начальные условия
            double* U0 = new double[NX_new]; 
            for (int m = 0; m < NX_new; m++)
            {
                U0[m] = std::sin( 4*PI*(m*h_new)/L ); 
            }
            U0[0] = U0[ NX_new-1 ];


            std::cout << "\nCFL=" << std::to_string(CFL[i]) << " h=" << h << "\n";
            upwind_scheme(NX_new, h_new, T, CFL[i], U0, dt_out_results, outdir);
            
            
            delete[] U0;
            h_new /= 2;
            NX_new = (NX_new) * 2 - 1;

        }
    }
    


    delete[] CFL;
	return 0;
}

int upwind_scheme(const int NX, double h, const double T, const double CFL, const double* U0, double dt_out_results,  string outdir)
{
    double time_next_output = 0;
    double* y = new double[NX];
    double tau = CFL * h;

    std::ofstream outFile;

    for (int m = 0; m < NX; m++)
    {
        y[m] = U0[m];
    }

    double t = 0;
    for (t = 0; t < T; t+=tau)
    {


        if (t >= time_next_output)
        {
            
            outFile.open(outdir + std::to_string(CFL) + "_" + std::to_string(h) + "_" + std::to_string(t) + ".txt");
            if (outFile.is_open()) {
                for (int m = 0; m < NX; m++)
                {
                    outFile << h*(m) << " " << y[m] << std::endl;
                }

                outFile.close();
                std::cout << T << " " << std::endl;
                } else {
                    std::cout << "File problem" << std::endl;
            }
            time_next_output += dt_out_results;
        }

        for (int m = NX-1; m >= 1; m--) 
        {
            y[m] = y[m] - CFL * (y[m] - y[m-1]);
        }
        y[0] = y[NX-1];

    }

    outFile.open(outdir + std::to_string(CFL) + "_" + std::to_string(h) + "_" + std::to_string(t) + ".txt");
    if (outFile.is_open()) {
        for (int m = 0; m < NX; m++)
        {
            outFile << h*(m) << " " << y[m] << std::endl;
        }

        outFile.close();
        std::cout << "File is ok" << std::endl;
        } else {
            std::cout << "File problem" << std::endl;
    }
    

    
    delete[] y;
    
    return 0;
}