#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAP_SIZE 10
#define NUM_MAPS 5
#define NUM_OBSTACLES 15

struct mapa {
    char polje[MAP_SIZE][MAP_SIZE];
};
struct glavni_karakter {
    char ime_karaktera[50];
    int hp;
    int snaga;
    int klasa;
    int trenutna_mapa;
    int pozicija_x;
    int pozicija_y;
};
int main() {
    srand(time(NULL));
    struct glavni_karakter igrac;
    struct mapa mape[NUM_MAPS];
    printf("\n");
printf("\n");
printf("  ********************************************\n");
printf("      A   S   T   R   A   L   I   J   A      \n");
printf("  ********************************************\n");
printf("\n");
    int izbor;
    printf("1. Kreni u avanturu!\n");
    printf("2. EXIT\n");
    scanf("%d", &izbor);
    switch (izbor) {
        case 1: {
            printf("\nAstralija...zemlja puna zivota, dom raznovrsnih stvorenja, ljudi i prirode.\n");
            printf("Medjutim, sve se promijenilo kada je u svijet dosao Rokvel, cuvar tajanstvenih moci.\n");
            printf("Rokvel je zaludjen svojim ambicijama, poceo je proizvoditi eksperimente na Astraliju.\n");
            printf("Astralija je na rubu propasti, tvoj zadatak je da otkrijes istinu koja se krije iza Rokvelovih eksperimenata.\n");
            printf("I razbiti jezgro korupcije i osloboditi Astraliju!\n");
            pocetak(&igrac);
            izaberi_karaktera(&igrac);
            generiraj_mapu(&mape[0], &igrac);
            while (1) {
                ispisi_mapu(&mape[igrac.trenutna_mapa], &igrac);
                printf("HP: %d\n", igrac.hp);
                printf("Snaga: %d\n", igrac.snaga);
                char korak;
                printf("\nUnesite korak (W/A/S/D): ");
                scanf(" %c", &korak);
                int nova_pozicija_x = igrac.pozicija_x;
                int nova_pozicija_y = igrac.pozicija_y;
                switch (korak) {
                    case 'W':
                    case 'w':
                        nova_pozicija_x = igrac.pozicija_x - 1;
                        system("cls");
                        break;
                    case 'A':
                    case 'a':
                        nova_pozicija_y = igrac.pozicija_y - 1;
                        system("cls");
                        break;
                    case 'S':
                    case 's':
                        nova_pozicija_x = igrac.pozicija_x + 1;
                        system("cls");
                        break;
                    case 'D':
                    case 'd':
                        nova_pozicija_y = igrac.pozicija_y + 1;
                        system("cls");
                        break;
                    default:
                        printf("Neispravan unos.\n");
                        continue;
                }
                if (provjeri_korak(&mape[igrac.trenutna_mapa], nova_pozicija_x, nova_pozicija_y, &igrac)) {
                    if (mape[igrac.trenutna_mapa].polje[nova_pozicija_x][nova_pozicija_y] == '.') {
                        mape[igrac.trenutna_mapa].polje[nova_pozicija_x][nova_pozicija_y] = 'O';
                        ispisi_mapu(&mape[igrac.trenutna_mapa], &igrac);
                        mape[igrac.trenutna_mapa].polje[igrac.pozicija_x][igrac.pozicija_y] = '.';
                    } else {
                        mape[igrac.trenutna_mapa].polje[igrac.pozicija_x][igrac.pozicija_y] = 'O';
                    }
                    if (nova_pozicija_x >= 1 && nova_pozicija_x < MAP_SIZE - 1 &&
                        nova_pozicija_y >= 1 && nova_pozicija_y < MAP_SIZE - 1) {
                        igrac.pozicija_x = nova_pozicija_x;
                        igrac.pozicija_y = nova_pozicija_y;
                    }
                    if (mape[igrac.trenutna_mapa].polje[igrac.pozicija_x][igrac.pozicija_y] == 'W') {
                        promijeni_mapu(&igrac, mape);
                    }
                }
            }
            break;
        }
        case 2:
            printf("Hvala sto ste igrali!\n");
            break;
        default:
            printf("Neispravan izbor. Molimo odaberite ponovno.\n");
    }
    return 0;
}
void ispisi_mapu(struct mapa *m, struct glavni_karakter *igrac) {
 system("cls");
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i == igrac->pozicija_x && j == igrac->pozicija_y) {
                printf(" O ");
            } else if (m->polje[i][j] == 'W') {
                printf(" W ");
            } else if (m->polje[i][j] == '#') {
                printf(" # ");
            } else if (m->polje[i][j] == '.') {
                printf(" . ");
            }
        }
        printf("\n");
    }
}
void generiraj_mapu(struct mapa *m, struct glavni_karakter *igrac) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1) {
                m->polje[i][j] = '#';
            } else {
                m->polje[i][j] = '.';
            }
        }
    }
    int cilj_x, cilj_y;
    do {
        cilj_x = rand() % (MAP_SIZE - 2) + 1;
        cilj_y = rand() % (MAP_SIZE - 2) + 1;
    } while (m->polje[cilj_x][cilj_y] != '.');
    m->polje[cilj_x][cilj_y] = 'W';
    igrac->pozicija_x = rand() % (MAP_SIZE - 2) + 1;
    igrac->pozicija_y = rand() % (MAP_SIZE - 2) + 1;
    while (m->polje[igrac->pozicija_x][igrac->pozicija_y] != '.') {
        igrac->pozicija_x = rand() % (MAP_SIZE - 2) + 1;
        igrac->pozicija_y = rand() % (MAP_SIZE - 2) + 1;
    }
    m->polje[igrac->pozicija_x][igrac->pozicija_y] = 'O';
    postavi_prepreke(m, NUM_OBSTACLES);
}
void izaberi_karaktera(struct glavni_karakter *igrac) {
    int izbor;
    printf("\nIzaberite karaktera:\n");
    printf("1. Vitez\n");
    printf("2. Carobnjak\n");
    printf("3. Placenik\n");
    scanf("%d", &igrac->klasa);
    igrac->hp = igrac->klasa * 40;
    igrac->snaga = igrac->klasa * 5;
    igrac->trenutna_mapa = 0;
    igrac->pozicija_x = 0;
    igrac->pozicija_y = 0;
    printf("\nInformacije o odabranom karakteru:\n");
    printf("Ime: %s\n", igrac->ime_karaktera);
    printf("Klasa: %d\n", igrac->klasa);
    printf("HP: %d\n", igrac->hp);
    printf("Snaga: %d\n", igrac->snaga);
}
void promijeni_mapu(struct glavni_karakter *igrac, struct mapa *mape) {
    igrac->trenutna_mapa++;

    if (igrac->trenutna_mapa == NUM_MAPS) {
        printf("CESTITAMO! \nUnistili ste jezgro korupcije i oslobodili ASTRALIJU.\n");
        printf("Igru radio: Danis Pajic\n");
        exit(0);
    }
    generiraj_mapu(&mape[igrac->trenutna_mapa], igrac);
}
void pocetak(struct glavni_karakter *k) {
    printf("\nUnesite ime karaktera:");
    scanf("%s", k->ime_karaktera);
}
void postavi_prepreke(struct mapa *m, int broj_prepreka) {
    for (int i = 0; i < broj_prepreka; i++) {
        int x, y;
        do {
            x = rand() % (MAP_SIZE - 2) + 1;
            y = rand() % (MAP_SIZE - 2) + 1;
        } while (m->polje[x][y] != '.');
        m->polje[x][y] = '#';
    }
}
int provjeri_korak(struct mapa *m, int nova_pozicija_x, int nova_pozicija_y, struct glavni_karakter *igrac) {
    return (nova_pozicija_x >= 0 && nova_pozicija_x < MAP_SIZE &&
            nova_pozicija_y >= 0 && nova_pozicija_y < MAP_SIZE &&
            (nova_pozicija_x == igrac->pozicija_x && nova_pozicija_y == igrac->pozicija_y ||
            m->polje[nova_pozicija_x][nova_pozicija_y] != '#'));
}
