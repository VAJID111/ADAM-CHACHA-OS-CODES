#include <iostream>
using namespace std;

int main() {
    int nf, np;
    cout << "Enter number of frames: ";
    cin >> nf;
    cout << "Enter number of pages: ";
    cin >> np;
    int f[nf];
    int p[np];
    cout <<"Enter page reference string: ";
    for (int i = 0; i < np; i++) {
        cin >> p[i];
    }

    for (int i = 0; i < nf; i++) {
        f[i] = -1;
    }

    int hit = 0, fault = 0;
    int position = 0;

    for (int i = 0; i < np; i++) {
        int flag = 0;
        for (int j = 0; j < nf; j++) {
            if (f[j] == p[i]) {
                hit++;
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            f[position] = p[i];
            position++;
            fault++;
            if(position==nf){
                position=0;
            }
        }
    }

    cout << "Hits = " << hit << endl;
    cout << "Faults = " << fault << endl;

    float hit_ratio = (float)hit / np;
    float miss_ratio = (float)fault / np;

    cout << "Hit Ratio = " << hit_ratio << endl;
    cout << "Miss Ratio = " << miss_ratio << endl;

    return 0;
}
