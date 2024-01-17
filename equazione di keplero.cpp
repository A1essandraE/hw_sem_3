#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>

#define f(E) E - e * sin(E) - M
#define g(E) e * sin(E) + M

double fixed_point_iteration_method(double M, double e, double EPSILON = 1e-6) {
    double E0, E1, i = 1;  //нулевая и первая итерации
    E0 = M;  
    do {
        E1 = g(E0);
        i += 1;
        if (i > 40) {
            std::cout << "error" << std::endl;
        }
        E0 = E1;
    } while (fabs(f(E1)) > EPSILON);
    std::cout << "solution: " << E1 << std::endl;
    return 0;
}

double bisection_method(double M, double e, double EPSILON = 1e-6) {
    int a, b;
    a = -4;
    b = 10;
    double error = b - a;
    double c = a;
    while (fabs(error) >= EPSILON) {
        c = (a + b) / 2;
        if (f(c) == 0.0) {
            break;
        }
        else if (f(c) * f(a) < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }
    std::cout << "solution: " << c << std::endl;
    return c;
}

double golden_section_method(double M, double e, double EPSILON = 1e-6) {
    double a, b, c;
    double X = (sqrt(5) + 1.) / 2.;
    a = -10;
    b = 5;

    std::cout << "solution: "  << std::endl;
    return 0;
}

double newtons_method(double M, double e, double EPSILON = 1e-6) {
    double E = M; 
    for (int i = 0; i < 40; i++) {
        double f = E - e * sin(E) - M;  
        double der_f = 1 + e * cos(E);  //прозводная уравнения Кеплера
        E = E - (f / der_f) * 1.0;
        if (abs(f) < EPSILON) {
            break;
        }
    }
//  std::cout << "solution: " << E << std::endl;
    return abs(E);
}

int main() {
    double PI = 3.14159;
    double r_p = 2.06655e+8;//радиус-вектор до перицентра
    double r_a = 2.49232e+8; //радиус-вектор до апоцентра
    double mu = 0.642;  //масса планеты (Марса)
    double a = (r_a + r_p) * 1.0 / 2;   //большая полуось орбиты
    double e = ((r_a - r_p) * 1.0) / (r_a + r_p);   //эксцентриситет орбиты
    std::cout << "semi-major axis: " << a << std::endl;
    std::cout << "eccentricity: " << e << std::endl;

    //по 3-му закону Кеплера
    double T_earth = 365.2563, a_earth = 149598261;    //сидерический период обращения и большая полуось Земли
    double T = T_earth * sqrt(pow(a, 3) / pow(a_earth, 3));     //сидерический период обращения Марса
    std::cout << "sidereal orbital period: " << T << std::endl;

    double n = 2 * PI / T;   //среднее угловое движение
    double tau = 0, M, E, Phi;   //время прохождения перицентра, средняя, эксцентрическая и истинная аномалии

    std::ofstream valuesFile("anomalyValues.txt");
    valuesFile << "t, days\t" << "M, rad\t" << "E, rad\t" << "Phi, rad\t" << std::endl;
    for (int t = 0; t < T; t++) {
        M = n * (t - tau);
        E = newtons_method(M, e);
        Phi = 2 * atan((sqrt((1 + e) / (1 - e))) * tan(E / 2));   //тк область определения -PI < Phi < PI
        if (Phi < 0) {
            Phi += 2 * PI;
        }
        valuesFile << t << "\t" << M << "\t" << E << "\t" << Phi << std::endl;
    }
    //значения для углов = 360 градусов
    double t_2pi = T;
    double M_2pi = n * t_2pi;
    double E_2pi = newtons_method(M_2pi, e);
    double Phi_2pi = 2 * atan((sqrt((1 + e) / (1 - e))) * tan(E_2pi / 2));
    if (Phi_2pi < 0) {
        Phi_2pi += 2 * PI;
    }
    valuesFile  << t_2pi << "\t" << M_2pi << "\t" << E_2pi << "\t" << Phi_2pi << std::endl;
    valuesFile.close();
    return 0;
}