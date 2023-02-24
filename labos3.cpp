#include <iostream>

using namespace std;

/*zadatak sa laboratorijske vjezbe na kolegiju diskretna matematika:
Zadani su prirodni brojevi 𝑛, 𝑎, 𝑏, 𝑐 ∈ 𝐍. Neka je graf 𝐺 jednostavni težinski graf s 𝑛 vrhova koji su
indeksirani brojevima od 1 do 𝑛 te neka su bridovi grafa i njihove težine određeni na sljedeći način. Za
vrhove 𝑖, 𝑗 ∈ {1, … , n}, 𝑖 < 𝑗, kažemo da su susjedni vrhovi grafa 𝐺 ako i samo ako je floor((a*i-b*j)/c)
različito od nule i u tom slučaju taj broj uzimamo kao težinu brida između vrhova 𝑖 i 𝑗. Vaš zadatak je odrediti
je li zadani graf povezan i, ako jest povezan, pronađite minimalno razapinjuće stablo grafa 𝐺 te ispišite
Prüferov kôd tog stabla.
*/

// funkcija koja rekurzivnim DFS algoritmom provjerava povezanost grafa
void povezanost(int *Mat, bool *polje, int k, int n) {
    if (polje[k]) return;
    polje[k] = true;
    for (int i = 0; i < n; i++) {
        if (*(Mat + n * k + i)) {
            povezanost(Mat, polje, i, n);
        }
    }
}

// rekurzivna funkcija koja pohlepnim algoritmom trazi najmanje razapinjuce stablo
void razap_stablo(int *Mat_tez, int *Mat_st, bool *polje, int k, int n) {
    if (k == n) {
        return;
    }

    int minvrh1 = 0, minvrh2 = 0;
    // trazenje povezanog vrha najmanje tezine koji jos nije obiden
    for (int i = 0; i < n; i++) {
        if (polje[i]) {
            for (int j = 0; j < n; j++) {
                if ((*(Mat_tez + n * i + j) != 0) && (polje[j] == false)) {
                    if (minvrh1 == minvrh2 || *(Mat_tez + n * i + j) < *(Mat_tez + n * minvrh1 + minvrh2)) {
                        minvrh1 = i;
                        minvrh2 = j;
                    }
                }
            }
        }
    }
    polje[minvrh2] = true;
    *(Mat_st + n * minvrh1 + minvrh2) = *(Mat_tez + n * minvrh1 + minvrh2);
    *(Mat_st + n * minvrh2 + minvrh1) = *(Mat_tez + n * minvrh1 + minvrh2);
    razap_stablo(Mat_tez, Mat_st, polje, k + 1, n);
    return;
}

int main(void) {
    int n, a, b, c, tezina, minvrh1 = 0, minvrh2 = 0, mintezina;
    bool povezan = true;

    cout << "Unesite prirodan broj n: ";
    cin >> n;
    cout << "Unesite prirodan broj a: ";
    cin >> a;
    cout << "Unesite prirodan broj b: ";
    cin >> b;
    cout << "Unesite prirodan broj c: ";
    cin >> c;

    int Mat_tez[n][n];  // matrica tezina
    int Mat_st[n][n];   // matrica koja ce predstavljati stablo
    bool polje[n] = {0};    // polje koje ce nam sluziti za provjeru povezanosti matrice

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Mat_tez[i][j] = 0;
            Mat_st[i][j] = 0;
        }
    }

    // popunjavanje matrica i pronalazenje minimalnog vrha
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            tezina = abs((a * (i+1) - b * (j+1))/c);
            if (tezina != 0) {
                Mat_tez[i][j] = tezina;
                Mat_tez[j][i] = Mat_tez[i][j];
                if (Mat_tez[minvrh1][minvrh2] == 0 || tezina < Mat_tez[minvrh1][minvrh2]) {
                    minvrh1 = i;
                    minvrh2 = j;
                    mintezina = tezina;
            }
            }
        }
    }

    povezanost(Mat_tez[0], polje, 0, n);
    
    for (int i = 0; i < n; i++) {
        if (polje[i] == false) {
            povezan = false;
        }
        polje[i] = false;
    }

    if (!povezan) cout << "Graf g nije povezan graf";
    else {
        cout << "Graf g je povezan graf" << endl;

        polje[minvrh1] = true;
        polje[minvrh2] = true;

        Mat_st[minvrh1][minvrh2] = mintezina;
        Mat_st[minvrh2][minvrh1] = mintezina;

        razap_stablo(Mat_tez[0], Mat_st[0], polje, 2, n);

        // pronalazenje Prüferovog kôda tako sto trazimo najmanje listove, zapisujemo ih u polje i micemo iz matrice
        int broj, list, prufer[n-2];
        for (int z = 0; z < n - 2; z++) {
            for (int i = 0; i < n; i++) {
                broj = 0;
                for (int j = 0; j < n; j++) {
                    if (Mat_st[i][j] != 0) {
                        broj++;
                    }
                }
                if (broj == 1) {
                    list = i;
                    break;
                }
            }
            for (int i = 0; i < n; i++) {
                if (Mat_st[list][i] != 0) {
                    prufer[z] = i + 1;
                    Mat_st[list][i] = 0;
                    Mat_st[i][list] = 0;
                    break;
                }
            }
        }
        
        cout << "Pruferov kod minimalnog razapinjuceg stabla: (";
        for (int i = 0; i < n-3; i++) {
            cout << prufer[i] << ",";
        }
        cout << prufer[n-3] << ")" << endl;

    }
    return 0;
}