#include <iostream>
#include <fstream>
#include <string>
using namespace std;

char M[100][4];     // Memory (100 words, 4 characters each)
char IR[4];         // Instruction Register
char R[4];          // General Purpose Register
int IC;             // Instruction Counter
int SI;             // Service Interrupt
string buffer;      // Buffer to read file

void MOS();
void executeUserProgram();
void load();

int main()
{
    load();
    return 0;
}

void load()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int m = 0;

    while (getline(fin, buffer))
    {
        if (buffer.substr(0,4) == "$AMJ")
        {
            m = 0;   // Start loading from memory 0
        }
        else if (buffer.substr(0,4) == "$DTA")
        {
            executeUserProgram();
        }
        else if (buffer.substr(0,4) == "$END")
        {
            break;
        }
        else
        {
            // Store program card into memory
            for (int i = 0; i < buffer.length(); i++)
            {
                M[m][i % 4] = buffer[i];

                if (i % 4 == 3)
                    m++;
            }
            if (buffer.length() % 4 != 0)
                m++;
        }
    }

    fin.close();
    fout.close();
}

void executeUserProgram()
{
    IC = 0;

    while (true)
    {
        // Fetch
        for (int i = 0; i < 4; i++)
            IR[i] = M[IC][i];

        IC++;

        // Decode
        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'H')
        {
            SI = 3;
            MOS();
            break;
        }
    }
}

void MOS()
{
    int address = (IR[2] - '0') * 10 + (IR[3] - '0');

    if (SI == 1)   // READ
    {
        ifstream fin("input.txt");

        while (getline(fin, buffer))
        {
            if (buffer.substr(0,4) == "$DTA")
            {
                getline(fin, buffer);
                break;
            }
        }

        int k = 0;
        for (int i = 0; i < buffer.length(); i++)
        {
            M[address][k++] = buffer[i];

            if (k == 4)
            {
                address++;
                k = 0;
            }
        }

        fin.close();
    }
    else if (SI == 2)   // WRITE
    {
        ofstream fout("output.txt", ios::app);

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 4; j++)
                fout << M[address + i][j];
        }

        fout << endl;
        fout.close();
    }
    else if (SI == 3)   // TERMINATE
    {
        ofstream fout("output.txt", ios::app);
        fout << "\n\n";
        fout.close();
    }
}