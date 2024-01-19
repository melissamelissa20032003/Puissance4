
#include "puissance4.h"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

// melissa
Puissance4::Puissance4(int a) {
  hmax = a;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      T[i][j] = 0;
       Col[j] = -1;
    }
  }

}


void Puissance4::jouer(int j, int joueur) {
  // Check if the column j is not full
  if(Col[j]<5){
  // Find the next available empty slot in column j
  int i = Col[j] + 1;

  // Place the player's token in that slot
  T[i][j] = joueur;

  // Update Col array to reflect the new position of the last played token in
  // column j
  Col[j] = i;
}
}








void Puissance4::affichage() {

  std::cout << "     0        1        2        3        4        5        6" << std::endl;
  
  for (int i = 5; i >= 0; --i) {
    std::cout << "|";
    for (int j = 0; j < 7; ++j) {
         if(T[i][j]==0 )
            std::cout<<"   "<<" . "<<" | ";
          if(T[i][j]==-1)   {std::cout<<"   "<<" X "<<" | ";}
          if(T[i][j]==1)   {std::cout<<"   "<<" O "<<" | ";}
    
         }
    std::cout << "  Ligne " <<"   " <<i<<"        " << std::endl;
  }
  std::cout << "----------------------------------------------------------------------" << std::endl;
}






// make void
void Puissance4::dejouer(int j) {
 
  // Récupérer la ligne du dernier pion dans la colonne j
  int i = Col[j];

  // Retirer le pion en réinitialisant la case à 0
  T[i][j] = 0;

  Col[j]--;
}
bool Puissance4::pleine(int &colonne) {
  // Check if the specified column is full
  return Col[colonne] >= 5; // Assuming 0-based indexing for rows
}

bool Puissance4::pleine() {
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 7; ++j) {
      if (T[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

bool Puissance4::checkWin(int joueur) {
  // Check horizontal
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
        
      if (T[i][j] == joueur && T[i][j + 1] == joueur && T[i][j + 2] == joueur &&
          T[i][j + 3] == joueur) {
           
        return true;
      }
    }
  }

  // Check vertical
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 7; j++) {
      if (T[i][j] == joueur && T[i + 1][j] == joueur && T[i + 2][j] == joueur &&
          T[i + 3][j] == joueur) {
             
        return true;
      }
    }
  }

  // Check diagonal (top-left to bottom-right)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      if (T[i][j] == joueur && T[i + 1][j + 1] == joueur &&
          T[i + 2][j + 2] == joueur && T[i + 3][j + 3] == joueur) {
               
        return true;
      }
    }
  }

  // Check diagonal (top-right to bottom-left)
  for (int i = 0; i < 3; i++) {
    for (int j = 3; j < 7; j++) {
      if (T[i][j] == joueur && T[i + 1][j - 1] == joueur &&
          T[i + 2][j - 2] == joueur && T[i + 3][j - 3] == joueur) {
             
        return true;
      }
    }
  }

  return false; // No winning combination found
}

bool Puissance4::coupGagnant(int joueur, int &bestMove) {
  for (int i = 0; i < 7; i++) {
    if(!pleine(i)){
     
      jouer(i,joueur);//i num colomn 
      if (checkWin(joueur)) {
        bestMove = i;
        //std::cout<<"maby the best move is  " ;
        dejouer(i);
        return true;
      }
      dejouer(i);
    }
   
  }

  return false;
}

int Puissance4::direction1(int joueur, int col, int line) {
  int result = 5;
  int i = line;
  for (int j = col + 1, count = 0; j < 7 && T[i][j] != (-joueur) && count < 3;

       j++, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  for (int j = col - 1, count = 0; j >= 0 && T[i][j] != (-joueur) && count < 3;
       j--, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  return result;
}

// vertical
int Puissance4::direction2(int joueur, int col, int line) {
  int result = 5;
  int j = col;
  for (int i = line + 1, count = 0; i < 6 && count < 3; i++, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
  }
  for (int i = line - 1, count = 0; i >= 0 && T[i][j] != (-joueur) && count < 3;
       i--, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  return result;
}

// diagonale1 "/"
int Puissance4::direction3(int joueur, int col, int line) {
  int result = 5;
  for (int i = line + 1, j = col + 1, count = 0;
       i < 6 && j < 7 && T[i][j] != (-joueur) && count < 3; i++, j++, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  for (int i = line - 1, j = col - 1, count = 0;
       i >= 0 && j >= 0 && T[i][j] != (-joueur) && count < 3;
       i--, j--, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  return result;
}

// diagonale2 "\"
int Puissance4::direction4(int joueur, int col, int line) {
  int result = 5;
  for (int i = line + 1, j = col - 1, count = 0;
       i < 6 && j >= 0 && T[i][j] != (-joueur) && count < 3;
       i++, j--, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  for (int i = line - 1, j = col + 1, count = 0;
       i >= 0 && j < 7 && T[i][j] != (-joueur) && count < 3;
       i--, j++, count++) {
    if (T[i][j] == 0) {
      result += 1;
    }
    if (T[i][j] == joueur) {
      result += 5;
    }
  }
  return result;
}

int Puissance4::evaluation(int joueur, int j) {
  int i = Col[j] + 1;
  int eval1 = direction1(joueur, j, i);
  int eval2 = direction2(joueur, j, i);
  int eval3 = direction3(joueur, j, i);
  int eval4 = direction4(joueur, j, i);
  if (eval1 >= 20 || eval2 >= 20 || eval3 >= 20 || eval4 >= 20)
    return (joueur)*1000;
  else
    return (eval1 + eval2 + eval3 + eval4);
}












int Puissance4::JeuOrdi(int &bestMove, int niveau) {
  int joueur = 1;
  int S;
  int val;
  int arg;
  int res ;

  // If the board is filled, it's a draw
  if (pleine()) {
    return NUL; // Return NUL
  }

  // If the computer has a winning move, return VORDI
  if (coupGagnant(joueur, bestMove)) {
    //std::cout<<"  do coupe ganant ";
    return VORDI;
  }
 // std::cout << " hi if the livel is max ";
  // If the maximum depth is reached, evaluate the state of the game
  if (niveau == hmax) {
     S = 0;
    for (int j = 0; j < 7; j++) {
      if (!pleine(j)) {
        jouer(j, joueur);
        S =S+ evaluation(joueur, j);
        dejouer(j);
      }
    }
   
    return S;
  }
  // std::cout<<" ida niveau machi max ";
  val = VHUMAIN; // VHUMAIN
  
  // For each column where it is possible to play
  for (int j = 0; j < 7; j++) {
    if (!pleine(j)) {
      jouer(j, joueur);

res = JeuHumain(arg, niveau + 1);

      dejouer(j);

      if (res > val) {
        val = res;
        bestMove = j;
      }
    }
  }

 
  return val;
 
}

int Puissance4::JeuHumain(int &bestMove, int niveau) {

  int arg, S;
  int joueur = -1;

  if (pleine()) {

    return (NUL);
  }

  // c'est le coup est ganant
  if (coupGagnant(joueur,bestMove )) {
    return VHUMAIN;
  }

  if (niveau == hmax) {
    S = 0;
    for (int j = 0; j < 7; j++) {
      if (!pleine(j)) // jouer dans la colomn j
      {
        jouer(j, joueur);
        S = S + evaluation(joueur, j);
        ///* Remettre la colonne j dans son ´etat initial */
        dejouer(j);
      }
    }
    return S;// au final S=val
  }
  int val = VORDI;

  /* Sinon pour chaque colonne j o`u il est possible de jouer,... */
  for (int j = 0; j < 7; j++) {
    if (!pleine(j)) {
      jouer(j, joueur);

      /* ´evaluer les r´eponses possibles de l’adversaire si l’ordinateur joue
      dans la colonne j. */
      int res;
      res = JeuOrdi(arg, niveau + 1);

      dejouer(j);
      /* Stocker dans ‘‘sval’’ la valeur maximale ‘‘res’’, correspondant au
      coup de l’ordinateur le plus favorable pour lui */
      if (res < val) {
        val = res;
        bestMove = j;
      }
    }
  }

  return val;
}

