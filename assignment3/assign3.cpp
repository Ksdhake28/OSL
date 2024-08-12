#include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct Process
{
    int id;
    int AT, BT, CT, TAT, WT, RT;
};

bool cmp(Process a, Process b)
{
    return a.AT < b.AT;
}

vector<Process> Processes;
int qt;

void RR(int n)
{
    sort(Processes.begin(), Processes.end(), cmp);

    int time = 0;
    vector<Process> temp;
    queue<Process> q;

    while (!q.empty() || !Processes.empty())
    {

        while (!Processes.empty() && Processes.front().AT <= time)
        {
            q.push(Processes.front());
            Processes.erase(Processes.begin());
        }

        if (!q.empty())
        {

            Process p = q.front();
            q.pop();

            int executionT = min(qt, p.RT);
            time += executionT;
            p.RT -= executionT;

            cout << "P" << p.id << "| ";

            if (p.RT > 0)
            {
                while (!Processes.empty() && Processes.front().AT <= time)
                {
                    q.push(Processes.front());
                    Processes.erase(Processes.begin());
                }
                q.push(p);
            }
            else
            {
                p.CT = time;
                temp.push_back(p);
            }
        }
        else
        {
            time++;
        }
    }
    Processes = temp;


    // TAT WT

    cout << endl
         << endl;

    for (int i = 0; i < Processes.size(); i++)
    {
        Processes[i].TAT = Processes[i].CT - Processes[i].AT;
        Processes[i].WT = Processes[i].TAT - Processes[i].BT;
    }

    cout << "P"
         << "\t"
         << "AT"
         << "\t"
         << "BT"
         << "\t"
         << "CT"
         << "\t"
         << "TAT"
         << "\t"
         << "WT" << endl;

    for (auto it : Processes)
    {
        cout << it.id << "\t" << it.AT << "\t" << it.BT << "\t" << it.CT << "\t" << it.TAT << "\t" << it.WT << endl;
    }

    float TAT = 0;
    float WT = 0;
    for (auto i : Processes)
    {
        TAT += i.CT - i.AT;
        WT += i.CT - i.AT - i.BT;
    }

    printf("AVG TAT is %.2f \n",TAT / n);
    printf("AVG WT is %.2f \n",WT / n);
 

}
void SJF()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
     Process processes[n];      
                                                            
    int time=0;

    for(int i=0;i<n;i++)
    {
        processes[i].id=i+1;
        printf("Enter Arrival time for the process P%d: ", i+1);
        scanf("%d",&processes[i].AT);
        printf("Enter Burst time for the process: P%d: ", i+1);
        scanf("%d",&processes[i].BT);
        processes[i].RT=processes[i].BT; 
    }

  printf("Gantt Chart:\n|");


    int completed=0;
    while(completed<n)
    {
        int shortest=-1;
        for(int i=0;i<n;i++)
        {
            if(processes[i].AT<=time && processes[i].RT > 0)
            {
                if(shortest==-1 || processes[i].RT < processes[shortest].RT)
                {
                    shortest=i;
                }
            }
        }


        if(shortest==-1)
        {
            time++;
            continue;
        }

        processes[shortest].RT--;
        time++;

        if(processes[shortest].RT==0)
        {
            completed++;
            processes[shortest].CT=time;
        }
        // printf("%-5d | P%d",time,processes[shortest].id);
        printf(" P%d |", processes[shortest].id);
      
    }


    printf("\n\nat\tbt\tct\ttat\twt\n");
    
    float TAT=0;
    float WT=0;
    for (int i = 0; i < n; i++)
    {
      
        processes[i].TAT=processes[i].CT - processes[i].AT;
        processes[i].WT=processes[i].TAT- processes[i].BT;
        

         printf("%d\t%d\t%d\t%d\t%d\n", processes[i].AT, processes[i].BT, processes[i].CT, processes[i].TAT,processes[i].WT);
        
        TAT +=  processes[i].TAT;
        WT +=  processes[i].WT;
    }

    printf("\nThe average Turnaround time is %.2f\n",TAT/n);
    printf("\nThe average Waiting time is %.2f\n",WT/n);



}
int main()
{

    int choice;

    cout<<"1) RR "<<endl;
    cout<<"2) SJF "<<endl;

    cout<<"Enter choice :"<<endl;
    cin>>choice;

    if(choice==1)
    {

    int n;
    cout << "Enter no. of processes: " << endl;
    cin >> n;
    cout << "Enter Time quantum: " << endl;
    cin >> qt;

    for (int i = 0; i < n; i++)
    {
        Process P;
        int at, bt;
        P.id = i + 1;
        cout << "Arival Time : ";
        cin >> at;
        P.AT = at;
        cout << "Burst Time : ";
        cin >> bt;
        P.BT = bt;
        cout << endl;
        P.RT = P.BT;

        Processes.push_back(P);
    }

    RR(n);
    }
    else if(choice==2)
    {
        SJF();
    }
    else
    {
        cout<<"Enter valid choice"<<endl;
    }
}