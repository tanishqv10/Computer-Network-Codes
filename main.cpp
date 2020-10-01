#include <iostream>
#include <stdio.h>
using namespace std;

struct node{
    int distance[20];
    int from[20];
}route[10];


int main()
{
    int dm[20][20], num, i, j, k;
    cout<<"Enter the number of nodes: "<<endl;
    cin>>num;
    cout<<"Enter the distance matrix values: "<<endl;
    for(i=0;i<num;i++)
    {
        for(j=0;j<num;j++)
        {
            cin>>dm[i][j];
            //set distance from i to i equal to 20
            dm[i][i]=0;
            route[i].distance[j]=dm[i][j];
            route[i].from[j]=j;
        }
    }
    
    int flag;
    
    do{
        flag=0;
        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
               for(k=0;k<num;k++)
               {
                   if((route[i].distance[j])>(route[i].distance[k]+route[k].distance[j]))
                   {
                       //to calculate distance of one route to another
                       route[i].distance[j]=route[i].distance[k]+route[k].distance[j];
                       route[i].from[j]=k;   //set the path travelled by node
                       flag=1;    //set flag to 1
                   }
               }
            }
        }
    }while(flag);
    
    for(i=0;i<num;i++)
    {
        cout<<"Router information for router: "<<i+1<<endl;
        cout<<"Dest\tNext Hop\tDistance"<<endl;
        for(j=0;j<num;j++)
        {
            cout<<j+1<<"\t"<<"\t"<<route[i].from[j]+1<<"\t"<<"\t"<<route[i].distance[j]<<endl;
        }
    }
    return 0;
}
