#include<iostream>
#include<string>
#include<fstream>
using namespace std;


char M[100][4];
char IR[4];
char R[4];
int  IC;
int  C;
int  SI;

ifstream fin("input.txt");
ofstream fout("output.txt", ios::app);


void INIT();
void LOAD();
void STARTEXECUTION();
void EUP();
void MOS();
void READ();
void WRITE();
void TERMINATE();
void display();


void INIT(){
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 4; j++)
            M[i][j] = '*';

    for(int i = 0; i < 4; i++){
        R[i]  = '*';
        IR[i] = '*';
    }
    C  = 0;
    SI = 0;
    IC = 0;
}


void LOAD(){
    int m = 0;
    string card;

    while(getline(fin, card)){

        if(card.substr(0,4) == "$AMJ"){
            INIT();
            m = 0;
            cout << ">> Job Started: " << card << endl;
        }
        else if(card.substr(0,4) == "$DTA"){
            cout << ">> Data section found. Starting Execution...\n";
            STARTEXECUTION();
        }
        else if(card.substr(0,4) == "$END"){
            cout << ">> Job Stream Ended.\n";
            break;
        }
        else{

            int c = 0;
            for(int i = 0; i < (int)card.length(); i++){
                M[m][c++] = card[i];
                if(c == 4){
                    m++;
                    c = 0;
                }
            }
        }
    }
}


void STARTEXECUTION(){
    IC = 0;
    cout << "\n========================================\n";
    cout << "       EXECUTION PHASE STARTED          \n";
    cout << "========================================\n";
    EUP();
}


void EUP(){
    while(IC >= 0 && IC < 100){


        for(int i = 0; i < 4; i++)
            IR[i] = M[IC][i];
        IC++;

if(IR[0] == '*'){
    cout << "  EMPTY memory reached. Stopping.\n";
    return;
}

        cout << "\n[IC=" << IC << "] IR: "
             << IR[0] << IR[1] << IR[2] << IR[3] << endl;




        if(IR[0]=='L' && IR[1]=='R'){
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            for(int i = 0; i < 4; i++)
                R[i] = M[loc][i];

            cout << "  LR: R <- M[" << loc << "] = ";
            for(int i = 0; i < 4; i++) cout << R[i];
            cout << endl;
        }


        else if(IR[0]=='S' && IR[1]=='R'){
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            for(int i = 0; i < 4; i++)
                M[loc][i] = R[i];

            cout << "  SR: M[" << loc << "] <- R = ";
            for(int i = 0; i < 4; i++) cout << M[loc][i];
            cout << endl;
        }


        else if(IR[0]=='C' && IR[1]=='R'){
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            C = 1;
            for(int i = 0; i < 4; i++){
                if(R[i] != M[loc][i]){
                    C = 0;
                    break;
                }
            }
            cout << "  CR: R vs M[" << loc << "] => C = " << C << endl;
        }


        else if(IR[0]=='B' && IR[1]=='T'){
            int loc = (IR[2]-'0')*10 + (IR[3]-'0');
            if(C == 1){
                IC = loc;
                cout << "  BT: C=1, Branch taken -> IC = " << IC << endl;
            } else {
                cout << "  BT: C=0, Branch NOT taken.\n";
            }
        }

        else if(IR[0]=='G' && IR[1]=='D'){
            SI = 1;
            cout << "  GD: Reading data into memory...\n";
            MOS();
        }


        else if(IR[0]=='P' && IR[1]=='D'){
            SI = 2;
            cout << "  PD: Printing data from memory...\n";
            MOS();
        }

        else if(IR[0]=='H'){
            SI = 3;
            cout << "  H: HALT instruction encountered.\n";
            MOS();
            return;   // exit EUP
        }


        else{
            cout << "  ERROR: Unknown instruction -> "
                 << IR[0] << IR[1] << IR[2] << IR[3] << endl;
        }
    }
}

void MOS(){
    switch(SI){
        case 1: READ();      break;
        case 2: WRITE();     break;
        case 3: TERMINATE(); break;
    }
}


void READ(){
    string line;
    int loc = (IR[2]-'0')*10 + (IR[3]-'0');

    if(getline(fin, line)){
        int k = 0;
        for(int i = 0; i < (int)line.length(); i++){
            M[loc][k++] = line[i];
            if(k == 4){
                loc++;
                k = 0;
            }
        }
        cout << "  READ: Data loaded -> \"" << line << "\" at M["
             << ((IR[2]-'0')*10 + (IR[3]-'0')) << "]\n";
    } else {
        cout << "  READ: No more data cards!\n";
    }
}


void WRITE(){
    int loc = (IR[2]-'0')*10 + (IR[3]-'0');
    int startLoc = loc;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 4; j++)
            fout << M[loc][j];
        loc++;
    }
    fout << endl;

    cout << "  WRITE: 10 words from M[" << startLoc
         << "] written to output.txt\n";
}

void TERMINATE(){
    cout << "\n----------------------------------------\n";
    cout << "         JOB TERMINATED                  \n";
    cout << "----------------------------------------\n";
    display();
}


void display(){
    cout << "\n===== MEMORY MAP (non-empty words) =====\n";
    for(int i = 0; i < 100; i++){
        bool empty = true;
        for(int j = 0; j < 4; j++)
            if(M[i][j] != '*') { empty = false; break; }
        if(!empty){
            cout << "M[" << (i<10?"0":"") << i << "] = ";
            for(int j = 0; j < 4; j++)
                cout << M[i][j];
            cout << endl;
        }
    }

    cout << "\n===== REGISTERS =====\n";
    cout << "R  = "; for(int i=0;i<4;i++) cout<<R[i];  cout<<endl;
    cout << "IR = "; for(int i=0;i<4;i++) cout<<IR[i]; cout<<endl;
    cout << "IC = " << IC  << endl;
    cout << "C  = " << C   << endl;
    cout << "SI = " << SI  << endl;
}
int main(){
    if(!fin.is_open()){
        cout << "ERROR: input.txt not found!\n";
        return 1;
    }
    LOAD();
    return 0;
}

/*	Input.txt:
$AMJ
GD50
LR50
SR60
CR60
BT06
PD50
H
$DTA
HELLO
$END*/
