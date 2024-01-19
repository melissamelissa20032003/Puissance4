
#ifndef PUISSANCE4_H
#define PUISSANCE4_H
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

#define NUL 0
#define VORDI 1000
#define VHUMAIN -1000

class Puissance4 {
  int T[6][7];
  int Col[7];
  int hmax; // niveau de deffeculte
public:
  Puissance4(int a);
  void affichage();
  void Partie();
  void jouer(int j, int joueur);
  void dejouer(int j);
  bool coupGagnant(int joueur, int &bestMove);
  int JeuHumain(int &bestMove, int niveau);
  int JeuOrdi(int &bestMove, int niveau);
  int evaluation(int joueur, int j);
  bool pleine(int &colonne);
  bool pleine();
  int countConsecutive(int joueur, int row, int col, int rowIncrement,
                       int colIncrement);
  bool checkWin(int joueur);
  int direction4(int joueur, int col, int line);
  int direction3(int joueur, int col, int line);
  int direction2(int joueur, int col, int line);
  int direction1(int joueur, int col, int line);
  // int getHumanMove();
  // int jouerH();
};

#endif