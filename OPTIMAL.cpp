#include <iostream>
using namespace std;

int main() {

    int nf, np;

    cout << "Enter number of frames: ";
    cin >> nf;

    cout << "Enter number of pages: ";
    cin >> np;

    int pages[np];
    int frames[nf];

    cout << "Enter page reference string: ";

    for(int i = 0; i < np; i++) {
        cin >> pages[i];
    }

    for(int i = 0; i < nf; i++) {
        frames[i] = -1;
    }

    int hit = 0, fault = 0;

    for(int i = 0; i < np; i++) {

        int flag = 0;

        // Check for hit
        for(int j = 0; j < nf; j++) {

            if(frames[j] == pages[i]) {
                hit++;
                flag = 1;
                break;
            }
        }

        // Page fault
        if(flag == 0) {

            int pos = -1;
            int farthest = i + 1;

            // Find optimal page to replace
            for(int j = 0; j < nf; j++) {

                int k;

                for(k = i + 1; k < np; k++) {

                    if(frames[j] == pages[k]) {

                        if(k > farthest) {
                            farthest = k;
                            pos = j;
                        }

                        break;
                    }
                }

                // Page not found in future
                if(k == np) {
                    pos = j;
                    break;
                }
            }

            // Empty frame handling
            if(pos == -1) {
                pos = 0;
            }

            frames[pos] = pages[i];
            fault++;
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