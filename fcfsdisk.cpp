#include<iostream>
using namespace std;

int main(){
    int n,initial=50,seektime,THM=0;
    cout<<"Enter no. of tracks: ";
    cin>>n;
    int RQ[n];
    cout<<"Enter Request Queue: ";
    for(int i=0;i<n;i++){
        cin>>RQ[i];
    }
    for(int i=0;i<n;i++){
        THM=THM+abs(initial-RQ[i]);
        initial=RQ[i];
    }

    seektime=THM;
    cout<<"Total head movement: "<<THM<<endl;
    cout<<"Seek time: "<<seektime<<endl;
    return 0;
}
