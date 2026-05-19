#include<iostream>
using namespace std;
#define INT_MAX 100

int main(){
    int n,initial=50,seektime,THM=0;
    cout<<"Enter no. of tracks: ";
    cin>>n;
    int RQ[n];
    cout<<"Enter Request Queue: ";
    for(int i=0;i<n;i++){
        cin>>RQ[i];
    }

    int visited[n] = {0};
    for (int i = 0; i < n; i++) {
        int minDist = INT_MAX;
        int index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int dist = abs(initial - RQ[j]);
                if (dist < minDist) {
                    minDist = dist;
                    index = j;
                }
            }
        }

        THM += minDist;
        initial = RQ[index];
        visited[index] = 1;
    }

    seektime=THM;

    cout<<"Total head movement: "<<THM<<endl;
    cout<<"Seek time: "<<seektime<<endl;

    return 0;
}
