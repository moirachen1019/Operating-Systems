#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct job{
    int AT, BT, RBT;   //AT: Arrival Time, BT: Burst Time, RBT: Remain Burst Time
    int CT, TAT, WT;  //CT: Completion Time, TAT: Turn Around Time, WT: Waiting Time
};

int main(){
    int n, TQ;
    vector<job> job_vector;
    map<int,int> record_AT;
    queue<int> seq;
    cin>>n;
    for(int i = 0; i < n; i++){
        job temp;
        cin>>temp.AT;
        job_vector.push_back(temp);
        record_AT.insert(make_pair(temp.AT, i));
    }
    for(int i = 0; i < n; i++){
        cin>>job_vector[i].BT;
        job_vector[i].RBT = job_vector[i].BT;
    }
    cin>>TQ;

    int flag = 0, time = 0, old_time = 0, push_again = 0, head = -1;
    while (flag != n){
        for(int i = old_time; i <= time; i++){
            map<int,int>::iterator it = record_AT.find(i);
            if(it != record_AT.end()){ //該時間有人進來
                seq.push(it->second); //放進queue
            }
        }
        if(push_again){
            seq.push(head);
            push_again = 0;
        }
        old_time = time + 1;
        if(!seq.empty()){
            head = seq.front();
            if(job_vector[head].RBT <= TQ){
                time += job_vector[head].RBT;
                job_vector[head].RBT = 0;
                job_vector[head].CT = time;
                seq.pop();
                flag++;
            }
            else{
                time += TQ;
                job_vector[head].RBT -= TQ;
                seq.pop();
                push_again = 1;
            }
        }
        else{
            time++;
        }
    }
    
    for (int i = 0; i < n; i++){
        job_vector[i].TAT = job_vector[i].CT - job_vector[i].AT;
        job_vector[i].WT = job_vector[i].TAT - job_vector[i].BT;
        cout<<job_vector[i].WT<<" "<<job_vector[i].TAT<<"\n";
    }
    int total_wait = 0;
    int total_turnaround = 0;
    for (int i = 0; i < n; i++){
        total_wait += job_vector[i].WT;
        total_turnaround += job_vector[i].TAT;
    }
    cout<<total_wait<<"\n"<<total_turnaround<<"\n";
    return 0;
}