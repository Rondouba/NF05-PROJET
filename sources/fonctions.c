#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "structures.c" // TEMP: Remove


Vol vols[255];
int nb_vols = 0;


void genererBillet(Passager *passager) {
  int continuer;
  float nb_rand;
  char billet[11];
  billet[11] = '\0';

  printf("Generation du billet en cours...\n");

  while (billet[0] == '\0' || continuer == 1) {
    continuer = 0;

    for (int i = 0; i < 13; i++) {
      nb_rand = (float)rand()/RAND_MAX * 10.0;
      billet[i] = (int)nb_rand + '0';
    }
    billet[10] = '\0';

    int i = 0, j;
    while (i < nb_vols && continuer == 0) {
      j = 0;
      while (j < vols[i].places_reservees && continuer == 0) {
        if (vols[i].passagers[j].billet == billet) {
          continuer = 1;
        }
        j++;
      }
      i++;
    }
  }

  printf("Generation du billet terminee.\n");
  printf("Recopiage en cours... \n");

  strcpy(billet, passager->billet);

  // for (int i = 0; i < 11; i++) {
  //   passager->billet[i] = billet[i];
  // }

  printf("Recopiage termine \n");
}

void saisirPassager(Passager *passager) {
  char reponse[10];

  printf("Enregistrement des informations sur les passagers.\n");

  printf("Entrez le nom de votre passager :\n");
  fgets(passager->nom, 64, stdin);
  printf("%s", passager->nom);

  printf("Entrez le prénom de votre passager :\n");
  scanf(" %s", passager->prenom);

  printf("Êtes vous prioritaire ? (oui ou non)\n");
  scanf(" %s", &reponse);

  if (strcmp(reponse, "oui") == 0) {
    passager->prioritaire = 0;
  } else {
    passager->prioritaire = 1;
  }

  printf("Indiquez votre date de naissance en format JJ/MM/AAAA : \n");
  fgets(passager->date_naissance, 11, stdin);
}

int ajouterPassager(Vol *vol) {
  Passager *passager;

  saisirPassager(passager);
  genererBillet(passager);
  // Les informations du passager sont montrés en une "jolie" phrase.
  printf("%s %s ne(e) le %s ", passager->nom, passager->prenom, passager->date_naissance);

  if (passager->prioritaire == 0){
    printf("est prioritaire.\n");
  }
  else {
    printf("n'est pas prioritaire.\n");
  }

  printf("Votre billet est le n°%s.\n", passager->billet);

  if (vol->places_libres > 0) {
    // TODO : fix it ; create function to copy
    // vol->passagers[vol->places_reservees] = passager;
    vol->places_libres -= 1;
    vol->places_reservees += 1;
    printf("[INFO]Ajout reussi du passager au vol\n");
    return 1;
  }

  return 0;
}

int main(void) {

  Passager *passager;
  saisirPassager(passager);

  return 0;
}
