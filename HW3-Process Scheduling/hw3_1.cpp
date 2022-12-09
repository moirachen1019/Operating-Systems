#include <iostream>
#include <algorithm>

using namespace std;

struct job{
    int job_no;
    int AT, BT, RBT;   //AT: Arrival Time, BT: Burst Time, RBT: Remain Burst Time
    int CT, TAT, WT;  //CT: Completion Time, TAT: Turn Around Time, WT: Waiting Time
};

bool compare(class job a, class job b){
    if(a.RBT != b.RBT)
        return a.RBT < b.RBT;
    else
        return a.AT < b.AT; //相同remain time，先來的先做
}

bool original(class job a, class job b){
    return a.job_no < b.job_no;
}

int main()
{
    int n;
    job job_arr[20];
    
    cin>>n;
    for (int i = 0; i < n; i++){
        job_arr[i].job_no = i;
        cin>>job_arr[i].AT;
    }
    for (int i = 0; i < n; i++){
        cin>>job_arr[i].BT;
        job_arr[i].RBT = job_arr[i].BT;
    }

    int flag = 0, time = 0; // flag:從第幾個開始做
    while (flag != n){
     sort(job_arr, job_arr+n, compare); //根據remain burst time排
        int is_empty = 1;
        for (int i = flag; i < n; i++){
            if (job_arr[i].AT <= time){ //找到最小已經在排的人
                is_empty = 0;
                time++;
                job_arr[i].RBT--;
                if (job_arr[i].RBT == 0){
                    job_arr[i].CT = time;
                    flag++;
                }
                break;
            }
        }
        if(is_empty){
            time++;
        }
    }
    sort(job_arr+0, job_arr+n, original);
    for (int i = 0; i < n; i++){
        job_arr[i].TAT = job_arr[i].CT - job_arr[i].AT;
        job_arr[i].WT = job_arr[i].TAT - job_arr[i].BT;
        cout<<job_arr[i].WT<<" "<<job_arr[i].TAT<<"\n";
    }
    int total_wait = 0;
    int total_turnaround = 0;
    for (int i = 0; i < n; i++){
        total_wait += job_arr[i].WT;
        total_turnaround += job_arr[i].TAT;
    }
    cout<<total_wait<<"\n"<<total_turnaround<<"\n";
    return 0;
}