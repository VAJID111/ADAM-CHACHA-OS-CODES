#include<iostream>
#include<algorithm>
using namespace std;

struct process_start {
    int pid, StartTime, AT, BT, CT, TAT, WT, RT;
} ps[10];

bool compare(process_start a, process_start b){
    return a.AT < b.AT;
}

int main(){
    int n = 3;

    cout<<"Enter process id(pid), Arrival Time(AT) and Burst Time(BT)\n";

    for(int i=0;i<n;i++){
        cin>>ps[i].pid>>ps[i].AT>>ps[i].BT;
    }

    sort(ps, ps+n, compare);

    for(int i=0;i<n;i++){
        if(i==0){
            ps[i].StartTime = ps[i].AT;
        }
        else{
            ps[i].StartTime = max(ps[i-1].CT, ps[i].AT);
        }

        ps[i].CT = ps[i].StartTime + ps[i].BT;
        ps[i].TAT = ps[i].CT - ps[i].AT;
        ps[i].WT = ps[i].TAT - ps[i].BT;
        ps[i].RT = ps[i].WT; // FCFS → RT = WT
    }

    cout<<"\nPid\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for(int i=0;i<n;i++){
        cout<<ps[i].pid<<"\t"
            <<ps[i].AT<<"\t"
            <<ps[i].BT<<"\t"
            <<ps[i].CT<<"\t"
            <<ps[i].TAT<<"\t"
            <<ps[i].WT<<"\t"
            <<ps[i].RT<<"\n";
    }

    return 0;
}
