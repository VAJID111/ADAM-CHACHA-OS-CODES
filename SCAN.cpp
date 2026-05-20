#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int n, head, disk_size;

    cout << "Enter number of requests: ";
    cin >> n;

    vector<int> rq(n);

    cout << "Enter request queue: ";
    for(int i=0; i<n; i++) {
        cin >> rq[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter disk size: ";
    cin >> disk_size;

    sort(rq.begin(), rq.end());

    int total = 0;
    int pos;

    for(int i=0; i<n; i++) {
        if(rq[i] > head) {
            pos = i;
            break;
        }
    }

    // Move right
    for(int i=pos; i<n; i++) {
        total += abs(head - rq[i]);
        head = rq[i];
    }

    // Move to disk end
    total += abs(head - (disk_size - 1));
    head = disk_size - 1;

    // Reverse direction
    for(int i=pos-1; i>=0; i--) {
        total += abs(head - rq[i]);
        head = rq[i];
    }

    cout << "Total Head Movement: " << total;

    return 0;
}