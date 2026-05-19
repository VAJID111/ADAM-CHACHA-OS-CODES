#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

char M[100][4];
char IR[4];
char R[4];
int IC;
bool C;
char buffer[40];
ifstream fin;
void INIT()
{
 for (int i = 0; i < 100; i++)
 for (int j = 0; j < 4; j++)
 M[i][j] = '*';
 for (int i = 0; i < 4; i++)
 {
 IR[i] = '*';
 R[i] = '*';
 }
 IC = 0;
 C = false;
}
void printMemory()
{
 cout << "\nMemory Content:\n";
 for (int i = 0; i < 50; i++)
 {
 cout << i << " : ";
 for (int j = 0; j < 4; j++)
 cout << M[i][j];
 cout << endl;
 }
}
void LOAD()
{
 int m = 0;
 while (fin.getline(buffer, 40))
 {
 if (strncmp(buffer, "$AMJ", 4) == 0)
 {
 INIT();
 m = 0;
 }
 else if (strncmp(buffer, "$DTA", 4) == 0)
 {
 continue;
 }
 else if (strncmp(buffer, "$END", 4) == 0)
 {
 printMemory();
 }
 else
 {
 int start = m;
 for (int i = 0; buffer[i] != '\0'; i++)
 {
 M[start][i % 4] = buffer[i];
 if ((i + 1) % 4 == 0)
 start++;
 }
 m += 10;
 }
 }
}
int main()
{
 fin.open("input.txt");
 if (!fin)
 {
 cout << "Error: File input.txt not found\n";
 return 0;
 }
 LOAD();
 fin.close();
 return 0;
}
