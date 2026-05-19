#include<iostream>
using namespace std;

int nf,np,pagesize,LA,page_num,offset,frame_num,PA;

int main(){
    cout<<"Enter no. of frames: ";
    cin>>nf;
    cout<<"Enter no. of pages: ";
    cin>>np;
    cout<<"Enter pagesize: ";
    cin>>pagesize;
    cout<<"Enter Logical Address: ";
    cin>>LA;
    int pagetable[np];
    cout<<"Pagetable array: "<<endl;
    for(int i=0;i<np;i++){
        cout<<"Page "<<i<<" -> Frame : ";
        cin>>pagetable[i];
    };

    page_num=LA/pagesize;
    offset=LA%pagesize;
    frame_num=pagetable[page_num];

    PA=(frame_num*pagesize)+offset;

    cout<<"Logical address: "<<LA<<endl;
    cout<<"Page number: "<<page_num<<endl;
    cout<<"offset: "<<offset<<endl;
    cout<<"frame number: "<<frame_num<<endl;
    cout<<"Physical address: "<<PA<<endl;
    return 0;
}
