#include <iostream>
#include <fstream>

using namespace std;

bool figyelo(int**& lepesek, int*& celallapot, int vege, int feladat)
{
    int akt1 = 200, akt2 = 210;
    int minertek = 21474836;
    bool figyelo2 = true;
    for (int i = 0; i <= vege; ++i)
    {
        figyelo2 = true;
        for (int j = 0; j < 9; ++j)
        {
            if (lepesek[i][j] != celallapot[j])
            {
                figyelo2 = false;
            }
        }
        if (figyelo2 == true)
        {
            akt1 = i;
        }
        if (lepesek[i][10] < minertek)
        {
            if (lepesek[i][9] == 0) {
                akt2 = i;
                minertek = lepesek[i][10];
            }
        }
    }
    if (akt1 == akt2) {
        if (feladat == 1)
        {
            cout << "Koltseg: " << lepesek[akt1][13] << " ";
        }
        if (feladat == 0)
        {
            int akt = akt1;
            while (akt != 0)
            {
                int u = 0;
                for (int j = 0; j < 9; ++j)
                {
                    cout << lepesek[akt][j] << " ";
                    u++;
                    if (u == 3)
                    {
                        cout << endl;
                        u = 0;
                    }

                }
                akt = lepesek[akt][14];
                cout << endl;
            }
            int u = 0;
            for (int j = 0; j < 9; ++j)
            {
                cout << lepesek[0][j] << " ";
                u++;
                if (u == 3)
                {
                    cout << endl;
                    u = 0;
                }

            }
        }
        return false;
    }
    else {
        return true;
    }
}
int ertek(int**& lepesek, int vege, int heurisztika)
{
    int a[2][9] = {
       {0,0,0,1,1,1,2,2,2} ,
       {0,1,2,0,1,2,0,1,2}
    };
    int x = 0;
    int ossz = 0;
    if (heurisztika == 2) {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (lepesek[vege][x] != 0)
                {

                    int n = a[0][lepesek[vege][11]] - i;
                    int m = a[1][lepesek[vege][12]] - j;
                    if (n < 0)
                        n *= -1;
                    if (m < 0)
                        m *= -1;
                    ossz = ossz + n + m;
                }
                x++;
            }
        }
        ossz += lepesek[vege][13];
    }
    if (heurisztika == 1)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (a[0][lepesek[vege][x]] != i || a[1][lepesek[vege][x]] != j)
                {
                    ossz++;
                }
                x++;
            }
        }
        ossz += lepesek[vege][13];
    }
    return ossz;


}
void beolvas(int**& lepesek, const char* be, int& heurisztika) {
    int n = 3, x = 0;
    ifstream f(be);
    for (int i = 0; i < n; ++i)
    {

        for (int j = 0; j < n; ++j)
        {
            f >> lepesek[0][x];
            cout << lepesek[0][x] << " ";
            if (lepesek[0][x] == 0)
            {
                lepesek[0][11] = i;
                lepesek[0][12] = j;
            }
            x++;
        }
    }
    lepesek[0][10] = ertek(lepesek, 0, heurisztika);
    lepesek[0][9] = 1;
    lepesek[0][13] = 0;
    lepesek[0][14] = 0;
    cout << endl;
}
bool letezik(int**& lepesek, int*& uj, int vege)
{
    bool figy = true;
    for (int i = 0; i <= vege; ++i)
    {
        figy = true;
        for (int j = 0; j < 9; ++j)
        {
            if (lepesek[i][j] != uj[j])
                figy = false;
        }
        if (figy == true)
            return true;
    }
    return false;
}
void ujlepesek(int**& lepesek, int& aktualis, int& vege, int& heurisztika)
{
    int n = lepesek[aktualis][11];
    int m = lepesek[aktualis][12];
    int koltseg = lepesek[aktualis][13] + 1;
    int puzzle[3][3];
    int x = 0;
    int* uj;
    uj = new int[10];
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            puzzle[i][j] = lepesek[aktualis][x];
            x++;
        }
    }
    if (n > 0)
    {
        int s = puzzle[n][m];
        puzzle[n][m] = puzzle[n - 1][m];
        puzzle[n - 1][m] = s;
        x = 0;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                uj[x] = puzzle[i][j];
                x++;

            }
        }
        if (letezik(lepesek, uj, vege) == false)
        {
            vege++;
            for (int i = 0; i < 9; ++i)
            {
                lepesek[vege][i] = uj[i];
            }
            lepesek[vege][9] = 0;
            lepesek[vege][11] = n - 1;
            lepesek[vege][12] = m;
            lepesek[vege][13] = koltseg;
            lepesek[vege][10] = ertek(lepesek, vege, heurisztika);
            lepesek[vege][14] = aktualis;
        }
    }
    x = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            puzzle[i][j] = lepesek[aktualis][x];
            x++;
        }
    }
    if (n < 2)
    {

        int s = puzzle[n][m];
        puzzle[n][m] = puzzle[n + 1][m];
        puzzle[n + 1][m] = s;
        x = 0;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                uj[x] = puzzle[i][j];
                x++;

            }
        }

        if (letezik(lepesek, uj, vege) == false)
        {
            vege++;
            for (int i = 0; i < 9; ++i)
            {
                lepesek[vege][i] = uj[i];
            }
            lepesek[vege][9] = 0;
            lepesek[vege][11] = n + 1;
            lepesek[vege][12] = m;
            lepesek[vege][13] = koltseg;
            lepesek[vege][10] = ertek(lepesek, vege, heurisztika);
            lepesek[vege][14] = aktualis;
        }
    }
    x = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            puzzle[i][j] = lepesek[aktualis][x];
            x++;
        }
    }
    if (m < 2)
    {
        int s = puzzle[n][m];
        puzzle[n][m] = puzzle[n][m + 1];
        puzzle[n][m + 1] = s;
        x = 0;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                uj[x] = puzzle[i][j];
                x++;
            }
        }
        if (letezik(lepesek, uj, vege) == false)
        {
            vege++;
            for (int i = 0; i < 9; ++i)
            {
                lepesek[vege][i] = uj[i];
            }
            lepesek[vege][9] = 0;
            lepesek[vege][11] = n;
            lepesek[vege][12] = m + 1;
            lepesek[vege][13] = koltseg;
            lepesek[vege][10] = ertek(lepesek, vege, heurisztika);
            lepesek[vege][14] = aktualis;
        }
    }
    x = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            puzzle[i][j] = lepesek[aktualis][x];
            x++;
        }
    }
    if (m > 0)
    {
        int s = puzzle[n][m];
        puzzle[n][m] = puzzle[n][m - 1];
        puzzle[n][m - 1] = s;
        x = 0;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                uj[x] = puzzle[i][j];
                x++;
            }
        }
        if (letezik(lepesek, uj, vege) == false)
        {
            vege++;
            for (int i = 0; i < 9; ++i)
            {
                lepesek[vege][i] = uj[i];
            }
            lepesek[vege][9] = 0;
            lepesek[vege][11] = n;
            lepesek[vege][12] = m - 1;
            lepesek[vege][13] = koltseg;
            lepesek[vege][10] = ertek(lepesek, vege, heurisztika);
            lepesek[vege][14] = aktualis;
        }
    }
}

void megoldas(int**& lepesek, int*& celallapot, int& aktualis, int& vege, int& feladat, int& heurisztika)
{
    int lep = 0;
    while (figyelo(lepesek, celallapot, vege, feladat) == true)
    {
        lep++;
        ujlepesek(lepesek, aktualis, vege, heurisztika);
        lepesek[aktualis][9] = 1;
        int minertek = 2147483627;
        bool figyelo2 = false;
        for (int i = 0; i <= vege; ++i)
        {
            if (lepesek[i][9] == 0)
            {
                if (lepesek[i][10] < minertek)
                {
                    aktualis = i;
                    figyelo2 = true;
                    minertek = lepesek[i][10];
                }
            }
        }
        if (figyelo2 == false)
        {
            break;
        }
    }

    if (feladat == 2)
    {
        cout << "Meglatogatott csomopontok: " << lep;
    }
    //cout<<lep;
}


int** lepesek;
int* celallapot;
int aktualis = 0, vege = 0, feladat = 0, heurisztika = 1;
int main(int argc, char *argv[])
{
    if (argc != 4) {
        cout << "Not enough arguments!" << endl;
        return 0;
    }
    string option1 = argv[3], option2 = argv[4];
    if (option1._Equal("-solseq")) {
        feladat = 0;
    }
    if (option1._Equal("-pcost")) {
        feladat = 1;
    }
    if (option1._Equal("-nvisited")) {
        feladat = 2;
    }
    if (option2[3] == '1') {
        heurisztika = 1;
    }
    if (option2[3] == '2') {
        heurisztika = 2;
    }
    lepesek = new int* [3000];
    for (int i = 0; i < 3000; i++)
    {
        lepesek[i] = new int[14];
    }
    beolvas(lepesek, argv[2], heurisztika);
    celallapot = new int[10];
    for (int i = 0; i < 9; ++i)
    {
        celallapot[i] = i;
    }
    cout << endl;
    megoldas(lepesek, celallapot, aktualis, vege, feladat, heurisztika);
    for (int i = 0; i < 3000; i++) {
        delete lepesek[i];
    }
    delete& lepesek;
    delete& celallapot;
}
