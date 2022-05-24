#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

long double fun1(long double x);

long double fun2(long double x);

long double fun1_pochodna(long double x);

long double fun2_pochodna(long double x);

bool warunkiBisekcji(double (*f)(double), long double a, long double b);

bool warunkiZakonczenia(int n, long double e, long double f);

void metodaPicarda(long double (*f)(long double), long double x);

void metodaBisekcji(long double (*f)(long double), long double a, long double b);

void metodaNewtowna(long double (*f)(long double), long double (*f_pochodna)(long double), double x);

void metodaSiecznych(long double (*f)(long double), double x, double x1);

using namespace std;

int main()
{
    char opcja;
    while (true)
    {
        cout << "------\n";
        cout << "MENU" << endl;
        cout << "------\n";
        cout << "0. ZAKONCZ\n";
        cout << "1. Metoda Picarda\n";
        cout << "2. Metoda bisekcji\n";
        cout << "3. Metoda Newtona\n";
        cout << "4. Metoda siecznych\n";
        cout << "5. Wszystkie metody\n";
        cout << "Wybierz opcje (1-5):";
        cin >> opcja;
        switch (opcja)
        {
            case '0':
                exit(0);
            case '1':
                metodaPicarda(fun1, 0.0001);
                break;
            case '2':
                metodaBisekcji(fun2, 0.4, 0.6);
                break;
            case '3':
                metodaNewtowna(fun2, fun2_pochodna, 0.6);
                break;
            case '4':
                metodaSiecznych(fun2, 0.4, 0.5);
                break;
            case '5':
                metodaPicarda(fun1, 0.0001);
                metodaBisekcji(fun2, 0.4, 0.6);
                metodaNewtowna(fun2, fun2_pochodna, 0.6);
                metodaSiecznych(fun2, 0.4, 0.5);
                break;
            default:
                cout << "Nie ma takiej opcji!\n";
                system("PAUSE");
        }
    }
}

long double fun1(long double x)
{
    return sin(x / 4) * sin(x / 4) - x;
}

long double fun2(long double x)
{
    return tan(2 * x) - x - 1;
}

long double fun1_pochodna(long double x)
{
    return 0.5 * sin(x / 4) * cos(x / 4) - 1;
}

long double fun2_pochodna(long double x)
{
    return -1 + 2 / (cos(2 * x) * cos(2 * x));
}

bool warunkiZakonczenia(int n, long double e, long double f)
{
    constexpr int maxIloscIteracji{50};
    constexpr long double tolerancjaBledu{10e-50};
    constexpr long double tolerancjaReziduum{10e-50};
    return !(n >= maxIloscIteracji || e <= tolerancjaBledu || f <= tolerancjaReziduum);
}

void metodaPicarda(long double (*f)(long double), long double x)
{
    string napis{"Metoda Picarda - poczatek"};
    string kreskiPoczatek('-', napis.length());
    cout << kreskiPoczatek << endl << napis << endl << kreskiPoczatek << endl;

    long double estymatorBleduPierwiastka;
    int i{};

    do
    {
        long double y{f(x)};
        estymatorBleduPierwiastka = fabs(x - y);
        cout << scientific << setprecision(20);
        cout << "Esytmator bledu pierwiastka:" << estymatorBleduPierwiastka << endl;
        cout << "Aktualne przyblizenie pierwiastka:" << y << endl;
        x = y;
    } while (warunkiZakonczenia(++i, estymatorBleduPierwiastka, fabs(x)));

    napis = "Metoda Picarda - koniec";
    string kreskiKoniec('-', napis.length());
    cout << kreskiKoniec << endl << napis << endl << kreskiKoniec << endl;
}

void metodaBisekcji(long double (*f)(long double), long double a, long double b)
{
    string napis{"Metoda bisekcji - poczatek"};
    string kreskiPoczatek('-', napis.length());
    cout << kreskiPoczatek << endl << napis << endl << kreskiPoczatek << endl;

    int i{};
    long double m;
    long double estymatorBleduPierwiastka;

    if ((f(a) * f(b)) > 0)
    {
        return;
    }

    do
    {
        m = (a + b) * 0.5;
        estymatorBleduPierwiastka = (b - a) * 0.5;
        cout << scientific << setprecision(20);
        cout << "Esytmator bledu pierwiastka:" << estymatorBleduPierwiastka << endl;
        cout << "Aktualne przyblizenie pierwiastka:" << m << endl;
        if ((f(a) * f(m)) < 0)
        {
            b = m;
        }
        else
        {
            a = m;
        }
    } while (warunkiZakonczenia(++i, estymatorBleduPierwiastka, fabs(f(m))));

    napis = "Metoda bisekcji - koniec";
    string kreskiKoniec('-', napis.length());
    cout << kreskiKoniec << endl << napis << endl << kreskiKoniec << endl;
}

void metodaNewtowna(long double (*f)(long double), long double (*f_pochodna)(long double), double x)
{
    string napis{"Metoda Newtona - poczatek"};
    string kreskiPoczatek('-', napis.length());
    cout << kreskiPoczatek << endl << napis << endl << kreskiPoczatek << endl;

    long double estymatorBleduPierwiastka;
    long double x1, prevX, i{}, x0{x};

    do
    {
        x1 = x0 - f(x0) / f_pochodna(x0);
        if (fabs(x1 - x0) <= 10e-50 * fabs(x1))
            break;
        prevX = x0;
        x0 = x1;
        estymatorBleduPierwiastka = fabs(x1 - prevX);
        cout << scientific << setprecision(20);
        cout << "Esytmator bledu pierwiastka:" << estymatorBleduPierwiastka << endl;
        cout << "Aktualne przyblizenie pierwiastka:" << x1 << endl;
    } while ((i++) <= 50);

    napis = "Metoda Newstona - koniec";
    string kreskiKoniec('-', napis.length());
    cout << kreskiKoniec << endl << napis << endl << kreskiKoniec << endl;
}

void metodaSiecznych(long double (*f)(long double), double x, double x1)
{
    string napis{"Metoda siecznych - poczatek"};
    string kreskiPoczatek('-', napis.length());
    cout << kreskiPoczatek << endl << napis << endl << kreskiPoczatek << endl;

    long double estymatorBleduPierwiastka;
    int i{};
    long double x2;

    do
    {
        x2 = x1 - f(x1) / ((f(x1) - f(x)) / (x1 - x));
        estymatorBleduPierwiastka = fabs(x2 - x1);

        x = x1;
        x1 = x2;
        cout << "Esytmator bledu pierwiastka:" << estymatorBleduPierwiastka << endl;
        cout << "Aktualne przyblizenie pierwiastka:" << x << endl;
    } while (warunkiZakonczenia(++i, estymatorBleduPierwiastka, fabs(f(x2))));

    napis = "Metoda siecznych - koniec";
    string kreskiKoniec('-', napis.length());
    cout << kreskiKoniec << endl << napis << endl << kreskiKoniec << endl;
}
