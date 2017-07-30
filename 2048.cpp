#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void printMat(int mat[][4]);
bool empty(int mat[][4], int row, int col);
bool full(int mat[][4]);
bool random2(int mat[][4]);
int same(int mat[][4], int row, int col, char direction);
bool move(int mat[][4], char direction);
int moveALT(int mat[][4], char direction);
int moveALT2(int mat[][4], char direction); //DA FINIRE
int maxCifre(int mat[][4]);
bool lostGame(int mat[][4]);
void bot();
void game();
int moveAndCheck(char direction);

int main()
{
   game();
   return 0;
}

int moveAndCheck(int mat[][4], char direction)
{
   // 1 mosso
   // 0 non mosso
   // -1 perso
   bool movable;
   bool lost = false;
   movable = move(mat,direction);
   if (!movable)
   {
      cout << "Cannot move in that direction" << endl;
      if (full(mat))
         lost = lostGame(mat);
      else
         lost = false;
      if (lost)
         return -1;
      else
         return 0;
   }
   else
   {
      lost = random2(mat);
      if (lost)
         return -1;
      else
         return 1;
   }
}

void game()
{
   int mat[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
   int i,j,k,moved,h;
   char a;
   cout << "main" << endl;
   for (h=0; h<2; h++)
   {
      random2(mat);
   }
   do
   {
      printMat(mat);
      //cout << "controllo 2,3 con quella sopra" << endl;
      //cout << same(mat,1,2,'u') << endl;
      cout << "Press q to quit" << endl;
      system("stty raw"); 
      cin.get(a);
      system("stty cooked"); 
      cout << endl;
      if (a == 'w' || a == '8')
      {
         moved = moveAndCheck(mat,'u');
      }
      else if (a == 'a' || a == '4')
      {
         moved = moveAndCheck(mat,'l');
      }
      else if (a == 's' || a == '5' || a == '2')
      {
         moved = moveAndCheck(mat,'d');
      }
      else if (a == 'd' || a == '6')
      {
         moved = moveAndCheck(mat,'r');
      }
      else 
         cout << "Unknown direction" << endl;
   }while (a != 'q' && moved !=-1);
   if (moved == -1)
      cout << "YOU LOSE" << endl;
   return;
}

bool lostGame(int mat[][4])
{
   int i,j;
   for (i=0;i<4;i++)
   {
      for (j=0;j<4;j++)
      {
         if (same(mat,i,j,'u') == 1)
            return false;
         if (same(mat,i,j,'d') == 1)
            return false;
         if (same(mat,i,j,'l') == 1)
            return false;
         if (same(mat,i,j,'r') == 1)
            return false;
      }
   }
   return true;
}

void printMat(int mat[][4])
{
   // se il numero ha più di una cifra
   int i,j;
   int max = maxCifre(mat);
   if (max == 1)
   {
      cout << "._._._._." << endl;
      for (i=0; i<4; i++)
      {
         for (j=0; j<4; j++)
         {
            if (mat[i][j] == 0)
               cout << "| ";
            else
               cout << "|" << mat[i][j];
         }
         cout << "|" << endl;
      }
      cout << "'-'-'-'-'" << endl;
   }
   if (max == 2)
   {
      cout << ".__.__.__.__." << endl;
      for (i=0; i<4; i++)
      {
         for (j=0; j<4; j++)
         {
            if (mat[i][j] == 0)
               cout << "|  ";
            else if (mat[i][j] < 10)
               cout << "| " << mat[i][j];
            else
               cout << "|" << mat[i][j];
            
         }
         cout << "|" << endl;
      }
      cout << "'--'--'--'--'" << endl;
   }
   if (max == 3)
   {
      cout << ".___.___.___.___." << endl;
      for (i=0; i<4; i++)
      {
         for (j=0; j<4; j++)
         {
            if (mat[i][j] == 0)
               cout << "|   ";
            else if (mat[i][j] < 10)
               cout << "|  " << mat[i][j];
            else if (mat[i][j] < 100)
               cout << "| " << mat[i][j];
            else
               cout << "|" << mat[i][j];
            
         }
         cout << "|" << endl;
      }
      cout << "'---'---'---'---'" << endl;
   }
   if (max == 4)
   {
      cout << ".____.____.____.____." << endl;
      for (i=0; i<4; i++)
      {
         for (j=0; j<4; j++)
         {
            if (mat[i][j] == 0)
               cout << "|    ";
            else if (mat[i][j] < 10)
               cout << "|   " << mat[i][j];
            else if (mat[i][j] < 100)
               cout << "|  " << mat[i][j];
            else if (mat[i][j] < 1000)
               cout << "| " << mat[i][j];
            else
               cout << "|" << mat[i][j];
            
         }
         cout << "|" << endl;
      }
      cout << "'----'----'----'----'" << endl;
   }
   return;
}

int maxCifre(int mat[][4])
{
   int max = 0; //tanto non sono negativi
   int i,j;
   for (i=0;i<4;i++)
   {
      for (j=0;j<4;j++)
      {
         if (mat[i][j] > max)
            max = mat[i][j];
      }
   }
   if (max < 10)
      return 1;
   if (max < 100)
      return 2;
   if (max < 1000)
      return 3;
   if (max < 10000)
      return 4;
   if (max < 100000)
      return 5;
   return 0;
}

bool empty(int mat[][4], int row, int col)
{
   return mat[row][col] == 0;
}

bool full(int mat[][4])
{
   int i,j;
   for (i=0;i<4;i++)
   {
      for (j=0;j<4;j++)
      {
         if (empty(mat,i,j))
            return false;
      }
   }
   return true;
}

bool random2(int mat[][4])
{
   bool done = false;
   srand(time(NULL));
   int row;
   int col;
   int i = 0;
   do
   {
      if (full(mat))
      {
         cout << "GAME OVER" << endl;
         return true;
      }
      col = rand() % 4;
      row = rand() % 4;
      if (empty(mat,row,col))
      {
         mat[row][col] = 2;
         done = true;
      }
   }while (!done);
   return false;
}


int same(int mat[][4], int row, int col, char direction)
{
   // direction
   // u = up
   // d = down
   // l = left
   // r = right
   int i,j;
   i = row;
   j = col;
   if (empty(mat,row,col))
      return -1;
   if (direction == 'u')
   {
      //cout << "up" << endl;
      if (row == 0)
         return -1;
      i--;
   }
   else if (direction == 'd')
   {
      //cout << "down" << endl;
      if (row == 3)
         return -1;
      i++;
   }
   else if (direction == 'l')
   {
      //cout << "left" << endl;
      if (col == 0)
         return -1;
      j--;
   }
   else if (direction == 'r')
   {
      //cout << "right" << endl;
      if (col == 3)
         return -1;
      j++;
   }
   else
   {
      cout << "Error, that direction does not exist" << endl;
      return -1;
   }
   return mat[row][col] == mat[i][j];
}

bool move(int mat[][4], char direction)
{
   //SPINGO
   //SOMMO
   //SPINGO
   int row,col;
   int counter;
   bool spinto = true;
   if (direction == 'u')
   {
      //cout << "up" << endl;
      row = 1;
      // SPINGO
      counter = 0;
      while (spinto == true)
      {
         spinto = false;
         for (row=1; row<4; row++)
         {
            for (col=0; col<4; col++)
            {
               if (!empty(mat,row,col) && empty(mat,row-1,col))
               {
                  mat[row-1][col]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
         if (spinto == true)
            counter++;
      }
      //SOMMO
      for (row=1; row<4; row++)
      {
         for (col=0; col<4; col++)
         {
            if (same(mat,row,col,direction) == 1)
            {
               mat[row-1][col]+=mat[row][col];
               mat[row][col] = 0;
               counter++;
            }
         }
      }
      //RISPINGO
      spinto = true;
      while (spinto == true)
      {
         spinto = false;
         for (row=1; row<4; row++)
         {
            for (col=0; col<4; col++)
            {
               if (!empty(mat,row,col) && empty(mat,row-1,col))
               {
                  mat[row-1][col]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
         if (spinto == true)
            counter++;
      }
      if (counter == 0)
         return false;
      else
         return true;
   }
   else if (direction == 'd')
   {
      //cout << "down" << endl;
      row = 2;
      col = 0;
      // SPINGO
      counter = 0;
      while (spinto == true)
      {
         spinto = false;
         for (row=2; row>=0; row--)
         {
            for (col=0; col<4; col++)
            {
               if (!empty(mat,row,col) && empty(mat,row+1,col))
               {
                  mat[row+1][col]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
         if (spinto == true)
            counter++;
      }
      //SOMMO
      for (row=2; row>=0; row--)
      {
         for (col=0; col<4; col++)
         {
            if (same(mat,row,col,direction) == 1)
            {
               mat[row+1][col]+=mat[row][col];
               mat[row][col] = 0;
               counter++;
            }
         }
      }
      //RISPINGO
      spinto = true;
      while (spinto == true)
      {
         spinto = false;
         for (row=2; row>=0; row--)
         {
            for (col=0; col<4; col++)
            {
               if (!empty(mat,row,col) && empty(mat,row+1,col))
               {
                  mat[row+1][col]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
         if (spinto == true)
            counter++;
      }
      if (counter == 0)
         return false;
      else
         return true;
   }
   else if (direction == 'l')
   {
      //cout << "left" << endl;
      row = 0;
      col = 1;
      // SPINGO
      counter = 0;
      while (spinto == true)
      {
         spinto = false;
         for (col=1; col<4; col++)
         {
            for (row=0; row<4; row++)
            {
               if (!empty(mat,row,col) && empty(mat,row,col-1))
               {
                  mat[row][col-1]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
         if (spinto == true)
            counter++;
      }
      //SOMMO
      for (col=1; col<4; col++)
      {
         for (row=0; row<4; row++)
         {
            if (same(mat,row,col,direction) == 1)
            {
               mat[row][col-1]+=mat[row][col];
               mat[row][col] = 0;
               counter++;
            }
         }
      }
      //RISPINGO
      spinto = true;
      while (spinto == true)
      {
         spinto = false;
         for (col=1; col<4; col++)
         {
            for (row=0; row<4; row++)
            {
               if (!empty(mat,row,col) && empty(mat,row,col-1))
               {
                  mat[row][col-1]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
         if (spinto == true)
            counter++;
      }
      if (counter == 0)
         return false;
      else
         return true;
   }
   else if (direction == 'r')
   {
      //cout << "right" << endl;
      row = 0;
      col = 2;
      // SPINGO
      counter = 0;
      while (spinto == true)
      {
         spinto = false;
         for (col=2; col>=0; col--)
         {
            for (row=0; row<4; row++)
            {
               if (!empty(mat,row,col) && empty(mat,row,col+1))
               {
                  mat[row][col+1]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
         if (spinto == true)
            counter++;
      }
      //SOMMO
      for (col=2; col>=0; col--)
      {
         for (row=0; row<4; row++)
         {
            if (same(mat,row,col,direction) == 1)
            {
               mat[row][col+1]+=mat[row][col];
               mat[row][col] = 0;
               counter++;
            }
         }
      }
      //RISPINGO
      spinto = true;
      while (spinto == true)
      {
         spinto = false;
         for (col=2; col>=0; col--)
         {
            for (row=0; row<4; row++)
            {
               if (!empty(mat,row,col) && empty(mat,row,col+1))
               {
                  mat[row][col+1]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
         if (spinto == true)
            counter++;
      }
      if (counter == 0)
         return false;
      else
         return true;
   }
   else
   {
      cout << "Error, that direction does not exist" << endl;
      return false;
   }
}

int moveALT(int mat[][4], char direction)
{
   //SPINGO
   //SOMMO
   //SPINGO
   int row,col;
   bool spinto = true;
   if (direction == 'u')
   {
      //cout << "up" << endl;
      row = 1;
      // SPINGO
      while (spinto == true)
      {
         spinto = false;
         for (row=1; row<4; row++)
         {
            for (col=0; col<4; col++)
            {
               if (!empty(mat,row,col) && empty(mat,row-1,col))
               {
                  mat[row-1][col]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
      }
      //SOMMO
      for (row=1; row<4; row++)
      {
         for (col=0; col<4; col++)
         {
            if (same(mat,row,col,direction) == 1)
            {
               mat[row-1][col]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      //RISPINGO
      while (spinto == true)
      {
         spinto = false;
         for (row=1; row<4; row++)
         {
            for (col=0; col<4; col++)
            {
               if (!empty(mat,row,col) && empty(mat,row-1,col))
               {
                  mat[row-1][col]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
      }
   }
   else if (direction == 'd')
   {
      //cout << "down" << endl;
      row = 2;
      col = 0;
      // SPINGO
      while (spinto == true)
      {
         spinto = false;
         for (row=2; row>=0; row--)
         {
            for (col=0; col<4; col++)
            {
               if (!empty(mat,row,col) && empty(mat,row+1,col))
               {
                  mat[row+1][col]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
      }
      //SOMMO
      for (row=2; row>=0; row--)
      {
         for (col=0; col<4; col++)
         {
            if (same(mat,row,col,direction) == 1)
            {
               mat[row+1][col]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      //RISPINGO
      while (spinto == true)
      {
         spinto = false;
         for (row=2; row>=0; row--)
         {
            for (col=0; col<4; col++)
            {
               if (!empty(mat,row,col) && empty(mat,row+1,col))
               {
                  mat[row+1][col]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
      }
   }
   else if (direction == 'l')
   {
      //cout << "left" << endl;
      row = 0;
      col = 1;
            // SPINGO
      while (spinto == true)
      {
         spinto = false;
         for (col=1; col<4; col++)
         {
            for (row=0; row<4; row++)
            {
               if (!empty(mat,row,col) && empty(mat,row,col-1))
               {
                  mat[row][col-1]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
      }
      //SOMMO
      for (col=1; col<4; col++)
      {
         for (row=0; row<4; row++)
         {
            if (same(mat,row,col,direction) == 1)
            {
               mat[row][col-1]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      //RISPINGO
      while (spinto == true)
      {
         spinto = false;
         for (col=1; col<4; col++)
         {
            for (row=0; row<4; row++)
            {
               if (!empty(mat,row,col) && empty(mat,row,col-1))
               {
                  mat[row][col-1]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
      }
      
   }
   else if (direction == 'r')
   {
      //cout << "right" << endl;
      row = 0;
      col = 2;
            // SPINGO
      while (spinto == true)
      {
         spinto = false;
         for (col=2; col>=0; col--)
         {
            for (row=0; row<4; row++)
            {
               if (!empty(mat,row,col) && empty(mat,row,col+1))
               {
                  mat[row][col+1]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
      }
      //SOMMO
      for (col=2; col>=0; col--)
      {
         for (row=0; row<4; row++)
         {
            if (same(mat,row,col,direction) == 1)
            {
               mat[row][col+1]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      //RISPINGO
      while (spinto == true)
      {
         spinto = false;
         for (col=2; col>=0; col--)
         {
            for (row=0; row<4; row++)
            {
               if (!empty(mat,row,col) && empty(mat,row,col+1))
               {
                  mat[row][col+1]+=mat[row][col];
                  mat[row][col] = 0;
                  spinto = true;
               }
            }
         }
      }
   }
   else
   {
      cout << "Error, that direction does not exist" << endl;
      return -1;
   }
}

int moveALT2(int mat[][4], char direction) //DA FINIRE
{
   int row,col;
   if (direction == 'u')
   {
      for (col = 0; col<4; col++)
      {
         if (!empty(mat,row,col))
         {
            if (same(mat,row,col,direction) || empty(mat,row-1,col)) // se sopra è vuoto oppure è uguale sommo e azzero
            {
               mat[row-1][col]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      row = 2;
      for (col = 0; col<4; col++)
      {
         if (!empty(mat,row,col))
         {
            if (same(mat,row,col,direction) || empty(mat,row-1,col)) // se sopra è vuoto oppure è uguale sommo e azzero
            {
               mat[row-1][col]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      row = 1;
      for (col = 0; col<4; col++)
      {
         if (!empty(mat,row,col))
         {
            if (same(mat,row,col,direction) || empty(mat,row-1,col)) // se sopra è vuoto oppure è uguale sommo e azzero
            {
               mat[row-1][col]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      row = 3;
      for (col = 0; col<4; col++)
      {
         if (!empty(mat,row,col))
         {
            if (same(mat,row,col,direction) || empty(mat,row-1,col)) // se sopra è vuoto oppure è uguale sommo e azzero
            {
               mat[row-1][col]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      row = 2;
      for (col = 0; col<4; col++)
      {
         if (!empty(mat,row,col))
         {
            if (same(mat,row,col,direction) || empty(mat,row-1,col)) // se sopra è vuoto oppure è uguale sommo e azzero
            {
               mat[row-1][col]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
      row = 1;
      for (col = 0; col<4; col++)
      {
         if (!empty(mat,row,col))
         {
            if (same(mat,row,col,direction) || empty(mat,row-1,col)) // se sopra è vuoto oppure è uguale sommo e azzero
            {
               mat[row-1][col]+=mat[row][col];
               mat[row][col] = 0;
            }
         }
      }
   }
   else if (direction == 'd')
   {
      //cout << "down" << endl;
      row = 2;
      col = 0;
   }
   else if (direction == 'l')
   {
      //cout << "left" << endl;
      row = 0;
      col = 1;
   }
   else if (direction == 'r')
   {
      //cout << "right" << endl;
      row = 0;
      col = 2;
   }
   else
   {
      cout << "Error, that direction does not exist" << endl;
      return -1;
   }
}

void bot()
{
   int mat[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
   int i,j,k;
   int moveL,moveD,moveR,moveU;
   cout << "main" << endl;
   bool lost = false;
   for (int h=0; h<2; h++)
   {
      cout << ""; // per qualche motivo se non lo metto fa un ciclo solo
      random2(mat);
   }
   printMat(mat);
   do
   {
      cout << "giro" << endl;
      moveD = moveAndCheck(mat,'d');
      cout << "down"<< endl;
      printMat(mat);   
      moveL = moveAndCheck(mat,'l');
      cout << "left" << endl;
      printMat(mat);
      if (moveL == 0 && moveD == 0)
      {
         moveR = moveAndCheck(mat,'r');
         cout << "right"<< endl;
         printMat(mat); 
         moveL = moveAndCheck(mat,'l');
         cout << "left" << endl;
         printMat(mat); 
         if (moveR == 0 && moveL == 0)
         {
            moveU = moveAndCheck(mat,'u');
            cout << "up"<< endl;
            printMat(mat); 
            moveD = moveAndCheck(mat,'d');
            cout << "down" << endl;
            printMat(mat); 
         }
      }
   }while (!(moveR == -1 || moveL == -1 || moveD == -1 || moveU == -1));
   cout << "YOU LOSE" << endl;
   return;
}
