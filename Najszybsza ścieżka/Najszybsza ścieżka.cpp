// Najszybsza ścieżka.cpp : 

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string> 

struct daneuzytkownika {
    int liczbakolumn, liczbawierszy;
};


struct krawedz {
    int dest, weight;
};


class Wezel {
public:
    std::vector<krawedz> listasasiadow;
    bool sprawdzone = false;
    int liczba;

    Wezel()
    {

    }
 
};
bool kolejkapusta(std::vector<Wezel> Q)
{
    for (int i = 0; i < Q.size(); i++)
    {
        if (Q[i].sprawdzone != true) //jezeli wezel nie jest sprawdzony, to kolejka nie jest pusta
        {
            return false;
       }
    }
    return true;
}
int zdejmijmin(std::vector<Wezel> &Q, std::vector<int> odleglosci)
{
    int najblizszywezel, najblizszaodleglosc = INT_MAX;


    for (int i = 0; i < Q.size(); i++)
    {
        if (Q[i].sprawdzone != true && najblizszaodleglosc > odleglosci[i]) //jezeli wezel nie jest sprawdzony, to kolejka nie jest pusta
        {
            najblizszywezel = i;
            najblizszaodleglosc = odleglosci[i];
          
        }
    }

    Q[najblizszywezel].sprawdzone = true;

    return najblizszywezel;
}
std::vector<int> najkrotszasciezka (std::vector<Wezel> Q)
{
    std::vector<int> odleglosci(Q.size()), poprzednik(Q.size());
    for (int i = 0; i < Q.size(); i++)
    {
        odleglosci[i] = INT_MAX; //najwieksza liczba
        poprzednik[i] = NULL; //poprzedni wierzcholek/wezel
    }
    odleglosci[0] = 0;

    while (kolejkapusta(Q) == false)
    {
        int wk = zdejmijmin(Q, odleglosci);
        for (int i = 0; i < Q[wk].listasasiadow.size(); i++)
        {
            if (odleglosci[Q[wk].listasasiadow[i].dest] > odleglosci[wk] + Q[wk].listasasiadow[i].weight) //odleglosc, z ktorego prowadzi krawedz jest wieksza niz docelowego
            {
                odleglosci[Q[wk].listasasiadow[i].dest] = odleglosci[wk] + Q[wk].listasasiadow[i].weight;
                poprzednik[Q[wk].listasasiadow[i].dest] = wk;
            }
        }
    }
    return poprzednik;
    
}
std::vector<Wezel> zrobgraf(std::vector <std::vector<int>> tablica_dwuwymiarowa, daneuzytkownika dane)
{
    std::vector<Wezel> Q(dane.liczbakolumn * dane.liczbawierszy + 2);

    Q[0] = Wezel();
    Q[dane.liczbakolumn * dane.liczbawierszy + 2 - 1] = Wezel();

    for (int i = 0; i < dane.liczbawierszy; i++)
    {
       
        for (int j = 0; j < dane.liczbakolumn; j++)
        {
            Wezel nowywezel = Wezel();
            nowywezel.liczba = tablica_dwuwymiarowa[i][j];
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                nowywezel.listasasiadow.push_back(krawedz{
                   (i - 1) * dane.liczbakolumn + j - 1 + 1,
                   tablica_dwuwymiarowa[i - 1][j - 1]
                });
            }
            if (i - 1 >= 0 && j + 1 < dane.liczbakolumn)
            {
                nowywezel.listasasiadow.push_back(krawedz{
                   (i - 1) * dane.liczbakolumn + j + 1 + 1,
                   tablica_dwuwymiarowa[i - 1][j + 1]
                    });
            }
            if (j - 1 >= 0)
            {
                nowywezel.listasasiadow.push_back(krawedz{
                   (i) * dane.liczbakolumn + j - 1 + 1,
                   tablica_dwuwymiarowa[i][j - 1]
                    });
            }
            if (j + 1 < dane.liczbakolumn)
            {
                nowywezel.listasasiadow.push_back(krawedz{
                   (i) * dane.liczbakolumn + j + 1 + 1,
                   tablica_dwuwymiarowa[i][j + 1]
                    });
            }
            if (i + 1 < dane.liczbawierszy && j - 1 >= 0)
            {
                nowywezel.listasasiadow.push_back(krawedz{
                   (i + 1) * dane.liczbakolumn + j - 1 + 1,
                   tablica_dwuwymiarowa[i + 1][j - 1]
                    });
            }
            if (i + 1 < dane.liczbawierszy && j + 1 < dane.liczbakolumn)
            {
                nowywezel.listasasiadow.push_back(krawedz{
                   (i + 1) * dane.liczbakolumn + j + 1 + 1,
                   tablica_dwuwymiarowa[i + 1][j + 1]
                    });
            }
            Q[i * dane.liczbakolumn + j + 1] = nowywezel;
        }

        
        Q[0].listasasiadow.push_back(krawedz{
            (i) * dane.liczbakolumn + 1,
            tablica_dwuwymiarowa[i][0]
            });
        Q[(i)*dane.liczbakolumn + dane.liczbakolumn - 1 + 1].listasasiadow.push_back(krawedz{
            dane.liczbakolumn* dane.liczbawierszy + 2 - 1,
            0
            });
        
    }

    return Q;
}
void display(std::vector <std::vector<int>> tablicad)
{
    
    for (int i = 0; i < tablicad.size(); i++)
    {
       
        for (int j = 0; j < tablicad[i].size(); j++)
        {
            std::cout << tablicad[i][j] << "\t";
        }
        std::cout << "\n";

    }


}

daneuzytkownika pobierzdaneoduzytkownika()
{
    srand(time(NULL));
    int liczbawierszy, liczbakolumn;
    do {
        std::cout << "Stworze dla Ciebie tablice. Podaj wymiary, czyli liczbe wierszy:\n";
        std::cin >> liczbawierszy;
        if (liczbawierszy < 1)
        {
            std::cout << "Podaj liczbe calkowita wieksza od 0:\n";
        }
    } while (liczbawierszy < 1);

    do {
        std::cout << "Podaj liczbe kolumn:\n";
        std::cin >> liczbakolumn;
        if (liczbakolumn < 1)
        {
            std::cout << "Podaj liczbe calkowita wieksza od 0:\n";
        }
    } while (liczbakolumn < 1);

    return daneuzytkownika{
        liczbakolumn,
        liczbawierszy
    };
}

std::vector <std::vector<int>> utworztablice(int liczbawierszy, int liczbakolumn)
{
    std::vector <std::vector<int>> tablica_dwuwymiarowa(liczbawierszy); //tworzy tablice dwuwymiarowa
    for (int i = 0; i < liczbawierszy; i++)
    {
        tablica_dwuwymiarowa[i] = std::vector<int>(liczbakolumn);
        for (int j = 0; j < liczbakolumn; j++)
        {
            tablica_dwuwymiarowa[i][j] = 1 + (std::rand() % 9); //wypelnia tablice liczbami od 1 do 9
        }
    }

    return tablica_dwuwymiarowa;
}

void wyswietlsciezke(std::vector<int> sciezka, std::vector<Wezel> Q)
{
    std::string sciezkadowyswietlenia = "";
    int aktualnywezel = sciezka.size() - 1, suma = 0;
    do {
        sciezkadowyswietlenia = std::to_string(Q[sciezka[aktualnywezel]].liczba) + ", " + sciezkadowyswietlenia;
        suma += Q[sciezka[aktualnywezel]].liczba;
        aktualnywezel = sciezka[aktualnywezel];

    }     while (sciezka[aktualnywezel] != 0);
    std::cout << "\nNajkrotsza sciezka to: \n\n" << sciezkadowyswietlenia << "\nsuma pol rowna:\n" << suma << "\n\n";
}

int main()
{
   
       
    auto dane = pobierzdaneoduzytkownika();  
    auto tablica_dwuwymiarowa = utworztablice(dane.liczbawierszy, dane.liczbakolumn);
    std::cout << "Tak wyglada Twoja tablica:\n\n";
    display(tablica_dwuwymiarowa);

    auto Q = zrobgraf(tablica_dwuwymiarowa, dane);
    auto sciezka = najkrotszasciezka(Q);
    wyswietlsciezke(sciezka, Q);
    return 0;
}

