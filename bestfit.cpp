#include <iostream>
using namespace std;

int main() {

    int nb, np;

    cout << "Enter number of processes: ";
    cin >> np;

    cout << "Enter number of memory blocks: ";
    cin >> nb;

    int b[nb], p[np];

    cout << "Enter sizes of memory blocks:\n";

    for(int i = 0; i < nb; i++) {
        cout << "Block " << i << ": ";
        cin >> b[i];
    }

    cout << "Enter sizes of processes:\n";

    for(int i = 0; i < np; i++) {
        cout << "Process " << i << ": ";
        cin >> p[i];
    }

    int bn[np], bf[nb], frag[np];

    for(int i = 0; i < np; i++) {
        bn[i] = -1;
        frag[i] = -1;
    }

    for(int i = 0; i < nb; i++) {
        bf[i] = 0;
    }

    for(int i = 0; i < np; i++) {

        int best = -1;

        for(int j = 0; j < nb; j++) {

            if(bf[j] == 0 && b[j] >= p[i]) {

                if(best == -1 || b[j] < b[best]) {
                    best = j;
                }
            }
        }

        if(best != -1) {
            bn[i] = best;
            bf[best] = 1;
            frag[i] = b[best] - p[i];
        }
    }

    cout << "\nProcess\tSize\tBlock\tBlockSize\tFragment\n";

    for(int i = 0; i < np; i++) {

        cout << "P" << i << "\t" << p[i] << "\t";

        if(bn[i] != -1) {

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