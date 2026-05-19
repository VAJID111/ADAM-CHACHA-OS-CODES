#include <iostream>
using namespace std;

int main() {
    int nb, np;
    cout << "Enter number of processes: ";
    cin >> np;
    cout << "Enter number of memory blocks: ";
    cin >> nb;

    int b[nb];
    cout << "Enter sizes of memory blocks:\n";
    for (int i = 0; i < nb; i++) {
        cout << "Block " << i << ": ";
        cin >> b[i];
    }

    int p[np];
    cout << "Enter sizes of processes:\n";
    for (int i = 0; i < np; i++) {
        cout << "Process " << i << ": ";
        cin >> p[i];
    }

    int bn[np], bf[nb], frag[np];

    for (int i = 0; i < np; i++)
        bn[i] = -1;

    for (int i = 0; i < nb; i++)
        bf[i] = 0;

    for (int i = 0; i < np; i++)
        frag[i] = -1;

    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= p[i]) {
                bn[i] = j;
                bf[j] = 1;
                frag[i] = b[j] - p[i];
                break; 
            }
        }
    }

    cout << "\nProcess\tSize\tBlock\tBlockSize\tFragment\n";
    for (int i = 0; i < np; i++) {
        cout << "P" << i << "\t" << p[i] << "\t";

        if (bn[i] != -1) {
            cout << bn[i] << "\t"
                 << b[bn[i]] << "\t\t"
                 << frag[i];
        } else {
            cout << "NA\tNA\t\tNA";
        }
        cout << endl;
    }

    return 0;
}
