#include<iostream>
using namespace std;
 
int main(){
    int np,nr,flag=0,k=0;
    cout<<"Enter no. of processes: ";
    cin>>np;
    cout<<"Enter no. of resources: ";
    cin>>nr;
    int allocation[np][nr], max[np][nr], need[np][nr];
    int available[nr];
    int finish[np]={0};
    int safeseq[np];
    int i,j;
    cout<<"Enter allocation matrix: "<<endl;
    for(int i=0;i<np;i++){
        for(int j=0;j<nr;j++){
            cin>>allocation[i][j];
        }
    }
    cout<<"Enter max matrix: "<<endl;
    for(int i=0;i<np;i++){
        for(int j=0;j<nr;j++){
            cin>>max[i][j];
        }
    }
    cout<<"Enter available array: ";
    for(int i=0;i<nr;i++){
        cin>>available[i];
    }
    
    for(int i=0;i<np;i++){
        for(int j=0;j<nr;j++){
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }

    for(i=0;i<np;i++){
        flag=0;
        if(finish[i]==0){
            for(j=0;j<nr;j++){
                if(need[i][j]>available[j]){
                    flag=1;
                    break;
                }
                if(flag==0){
                    finish[i]=1;
                    safeseq[k]=i;
                    k++;
                    for(j=0;j<nr;j++){
                        available[j]+=allocation[i][j];
                    }
                    i=-1;
                }
            }
        }
    }
    cout<<"Need matrix: "<<endl;
    for(i=0;i<np;i++){
        for(j=0;j<nr;j++){
            cout<<need[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Available array: ";
    for(i=0;i<nr;i++){
        cout<<available[i]<<" ";
    }
    cout<<endl;

    cout<<"Safe sequence: ";
    if(finish[i]={1}){
        for(i=0;i<np;i++){
            cout<<safeseq[i]<<" ";
        }
    }else{
        for(i=0;i<np;i++){
            cout<<safeseq[i]<<" ";
        }
    }
    return 0;
}
