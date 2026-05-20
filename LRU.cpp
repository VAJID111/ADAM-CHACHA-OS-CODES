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
    int recent[nf];

    cout << "Enter page reference string: ";

    for(int i = 0; i < np; i++) {
        cin >> pages[i];
    }

    for(int i = 0; i < nf; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    int hit = 0, fault = 0;
    int time = 0;

    for(int i = 0; i < np; i++) {

        int flag = 0;

        // Check for page hit
        for(int j = 0; j < nf; j++) {

            if(frames[j] == pages[i]) {

                hit++;
                time++;
                recent[j] = time;
                flag = 1;
                break;
            }
        }

        // Page fault
        if(flag == 0) {

            int pos = 0;

            // Find least recently used page
            for(int j = 1; j < nf; j++) {

                if(recent[j] < recent[pos]) {
                    pos = j;
                }
            }

            time++;
            frames[pos] = pages[i];
            recent[pos] = time;
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