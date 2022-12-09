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
    queue<int> rr;
    queue<int> fcfs;
    
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

    int flag = 0, time = 0, old_time = 0, move_down = 0, head1 = -1, low_flag = 0;
    
    while (flag != n){
        for(int i = old_time; i <= time; i++){
            map<int,int>::iterator it = record_AT.find(i);
            if(it != record_AT.end() && low_flag){ //該時間有人進來且low queue正在跑
                rr.push(it->second); //放進queue
                fcfs.push(fcfs.front());
                fcfs.pop();
                low_flag = 0;
            }
            else if(it != record_AT.end()){ //該時間有人進來
                rr.push(it->second); //放進queue
            }
        }
        if(move_down){
            fcfs.push(head1);
            move_down = 0;
        }
        old_time = time + 1;
        if(!rr.empty()){ //high priority: rr
            head1 = rr.front();
            if(job_vector[head1].RBT <= TQ){
                time += job_vector[head1].RBT;
                job_vector[head1].RBT = 0;
                job_vector[head1].CT = time;
                rr.pop();
                flag++;
            }
            else{
                time += TQ;
                job_vector[head1].RBT -= TQ;
                rr.pop();
                move_down = 1;
            }
        }
        else{ //fcfs
            if(!fcfs.empty()){
                int head2 = fcfs.front();
                low_flag = 1;
                time++;
                job_vector[head2].RBT--;
                if(!job_vector[head2].RBT){
                    job_vector[head2].CT = time;
                    fcfs.pop();
                    flag++;
                    low_flag = 0;
                }
            }
            else{
                time++;
            }
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