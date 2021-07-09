#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <string.h>
using namespace std;
class customer{
    private:
    string cid;
	int operation_time,arrival_time,priority;
    public:
	customer (string cid,int operation_time,int arrival_time,int priority)
    {
    	this->cid=cid;
		this->operation_time=operation_time;
		this->arrival_time=arrival_time;
		this->priority=priority;
	}


	string getCid () {return cid ;}
	int getOperationTime () {return operation_time;}
	int getArrivalTime () {return arrival_time;}
	int getPriority () {return priority;}
};
struct process
{
	string pid;
	int btime;// Busrt Time
	int atime;// Arrival Time
	int priority;
    int ctime=0;// Complete Time
    int wtime=0;// Waiting Time
    int ta;// Turnaround Time
    int stime;//Start Time
};
// Shortest Remaning Time First 

void SRTF (vector <customer> list)
{

    int n=list.size();
    
    float avg_turnaround_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
   
    process a[n];
    int is_completed[n];
    memset(is_completed,0,sizeof(is_completed));
	int burst_remaining[n];
	for (int j=0;j<n;j++)
	{
		a[j].pid=list[j].getCid ();
		a[j].atime=list[j].getArrivalTime();
		a[j].btime=list[j].getOperationTime();
		burst_remaining[j] = a[j].btime;
	}
	
	
	
    int current_time = 0;
    int completed = 0;
    int previous = 0;

    while(completed != n) {
        int index = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(a[i].atime <= current_time && is_completed[i] == 0) {
                if(burst_remaining[i] < mn) {
                    mn = burst_remaining[i];
                    index = i;
                    
                }
                if(burst_remaining[i] == mn) {
                    if(a[i].atime < a[index].atime) {
                        mn = burst_remaining[i];
                        index = i;
                        
                    }
                }
            }
        }
		
        if(index != -1) {
            if(burst_remaining[index] == a[index].btime) {
                a[index].stime = current_time;
               
            }
            burst_remaining[index] -= 1;
            current_time++;
            previous = current_time;
            
            if(burst_remaining[index] == 0) {
                a[index].ctime = current_time;
                a[index].ta = a[index].ctime - a[index].atime;
                a[index].wtime = a[index].ta- a[index].btime;
                

                total_turnaround_time += a[index].ta;
                total_waiting_time += a[index].wtime;
               

                is_completed[index] = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }  
       
    }


    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    
    

    cout<<left<<setw(20)<<"Customer ID"<<setw(20)<<"Arrival Time"<<setw(20)<<"Operation Time"<<setw(20)<<"Completion Time"<<setw(25)<<"TurnAround Time"<<setw(20)<<"Waiting Time"<<endl<<endl;


    for(int i = 0; i < n; i++) {
        cout<<left<<setw(20)<<"C"+a[i].pid<<setw(20)<<a[i].atime<<setw(20)<<a[i].btime<<setw(20)<<a[i].ctime<<setw(25)<<a[i].ta<<setw(20)<<a[i].wtime<<endl<<endl;
    }
     cout<<endl<<endl<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;

}
// Shortest Job First
bool SJFBurstTimeSort(process a,process b){
    return a.btime < b.btime; 
}
bool SJFArrivalTimeSort(process a,process b){
    return a.atime < b.atime; 
}
void SJF (vector <customer> list)
{
	process a[1000];
	int n=list.size();
	
	for (int j=0;j<n;j++)
	{
		a[j].pid=list[j].getCid ();
		a[j].atime=list[j].getArrivalTime();
		a[j].btime=list[j].getOperationTime();
	}
	 sort(a,a+n,SJFBurstTimeSort);
    sort(a,a+n,SJFArrivalTimeSort);
	
	 int ttime=0,i;
    int j,tArray[n];
    for(i=0;i<n;i++){
        j=i;
        while(a[j].atime<=ttime&&j!=n){
            j++;
        }
        sort(a+i,a+j,SJFBurstTimeSort);
        tArray[i]=ttime;
        ttime+=a[i].btime;
    }
    tArray[i] = ttime;
    float averageWaitingTime=0;
    float averageResponseTime=0;
    float averageTAT=0;

    cout<<left<<setw(20)<<"Customer ID"<<setw(20)<<"Arrival Time"<<setw(20)<<"Operation Time"<<setw(20)<<"Completion Time"<<setw(25)<<"TurnAround Time"<<setw(20)<<"Waiting Time"<<endl<<endl;

    int index=1;

    while (index<=n){
		for (int i=0;i<n;i++)
		{
		if (a[i].pid==to_string(index)){
		int turnaround=0,waiting=0;
				if((tArray[i]-a[i].atime)<0)
		{
			waiting=0;
		}
		else
		{
			waiting=tArray[i]-a[i].atime;
		}
		turnaround=waiting+a[i].btime;


        cout <<left<<setw(20)<<"C"+a[i].pid <<setw(20)<<a[i].atime <<setw(20)<< a[i].btime<<setw(20)<<tArray[i+1]<<setw(25)<<turnaround<<setw(20)<<waiting<<endl<<endl;
	

        averageTAT+=turnaround;
        averageWaitingTime+=waiting;


    }
    }
    index++;
	}

 
    cout<<endl<<endl<<"Average Waiting Time: "<<(float)averageWaitingTime/(float)n<<endl;
    cout<<"Average TurnAround Time: "<<(float)averageTAT/(float)n<<endl;
	
}
// Priority Scheduling
bool compare(process a,process b)
{
 return a.atime<b.atime;


}

bool compare2(process a,process b)
{
 return a.priority<b.priority;


}
// Priority Scheduling
void PriorityScheduling (vector<customer>list)
{
	int n=list.size();
	process pro[n];
	for (int m=0;m<n;m++)
	{
		pro[m].pid=list[m].getCid ();
		pro[m].atime=list[m].getArrivalTime();
		pro[m].btime=list[m].getOperationTime();
		pro[m].priority=list[m].getPriority();
	}
	
	sort(pro,pro+n,compare);
	int i,j;

 pro[0].ctime=pro[0].btime+pro[0].atime;
 pro[0].ta=pro[0].ctime-pro[0].atime;
 pro[0].wtime=pro[0].ta-pro[0].btime;
 i=1;

 while(i<n-1)
 {

  for(j=i;j<n;j++)
  {
   if(pro[j].atime>pro[i-1].ctime)
   break;
  }
  sort(pro+i,pro+i+(j-i),compare2);
  pro[i].ctime=pro[i-1].ctime+pro[i].btime;
  pro[i].ta=pro[i].ctime-pro[i].atime;
  pro[i].wtime=pro[i].ta-pro[i].btime;
  i++;
  }
  pro[i].ctime=pro[i-1].ctime+pro[i].btime;
  pro[i].ta=pro[i].ctime-pro[i].atime;
  pro[i].wtime=pro[i].ta-pro[i].btime;
int index=1;
cout<<left<<setw(20)<<"Customer ID"<<setw(15)<<"Priority"<<setw(20)<<"Arrival Time"<<setw(20)<<"Operation Time"<<setw(20)<<"Completion Time"<<setw(25)<<"TurnAround Time"<<setw(20)<<"Waiting Time"<<endl<<endl;
float averageWaitingTime=0;
float averageTAT=0;
while (index<=n)
{
	 for(i=0;i<n;i++)
 {
  if (pro[i].pid==to_string(index))
  {
  	  cout<<left<<setw(20)<<pro[i].pid<<setw(15)<<pro[i].priority<<setw(20)<<pro[i].atime<<setw(20)<<pro[i].btime<<setw(20)<<pro[i].ctime<<setw(25)<<pro[i].ta<<setw(20)<<pro[i].wtime<<endl<<endl;
	averageWaitingTime+=pro[i].wtime;
	averageTAT+=pro[i].ta;
  }

 }
 index++;
}
 cout<<endl<<endl<<"Average Waiting Time: "<<averageWaitingTime/(float)n<<endl;
cout<<"Average TurnAround Time: "<<averageTAT/(float)n<<endl;
 
 
 
}
int menu ()
{

		int opt;
		cout<<endl<<"Please the following operations"<<endl;
		cout<<"1) Add customer into queue"<<endl;
		cout<<"2) View customer's queue"<<endl;
		cout<<"3) Terminate the system"	<<endl;
		cout<<"\nYour operation: ";
		cin>>opt;
				
		if (opt!=1&&opt!=2&&opt!=3)
		{
			cout<<"Invalid input...."<<endl;
		}
		if (opt==3)
		{
			cout<<"Terminating the program"<<endl;
		}

			return opt;
}
int main ()
{
	
	int num_cus=1;
		
		vector <customer> customerList;
		
		int opt;
		do
		{
			cout<<"Welcom to the Customer Queue Management System"<<endl;
			opt=menu();
			system ("CLS");
			if (opt==1)
			{
				int type=0,estOperationTime,arrivaltime,membership;// estOperationTime=bursttime,membership=priority
				cout<<"\nPlease fill in the following required information"<<endl;
				cout<<"<<< Type of banking services required to be performed>>>"<<endl;
				do{
				cout<<"1) Transaction Services"<<endl;
				cout<<"2) Consultation"<<endl;
				cout<<"3) Debit & Credit Cards Related Services"<<endl;
				cout<<"4) Insurance"<<endl;
				cout<<"5) Wealth Management"<<endl;
				cout<<"6) Account Openning & Closing Services"<<endl;
				cout<<"7) Loan & Financing Services"<<endl;
				cout<<"8) Account Security Issue"<<endl;
				cout<<"\nYour Choice: ";
				cin>>type;
				}
				while (type!=1&&type!=2&&type!=3&&type!=4&&type!=5&&type!=6&&type!=7&&type!=8);
				system ("CLS");
				cout<<"\nPlease enter your estimated operation time for this service (*integer)"<<endl;
				cout<<"Estimated operation time: ";
				cin>>estOperationTime;
				cout<<"\nPlease enter your arrival time(*integer)"<<endl;
				cout<<"Arrival time: ";
				cin>>arrivaltime;
				system ("CLS");
				do{
				cout<<"\nPlease select the category of your membership"<<endl;
				cout<<"1) Diamond"<<endl;
				cout<<"2) Platinum"<<endl;
				cout<<"3) Gold"<<endl;
				cout<<"4) Silver"<<endl;
				cout<<"5) Copper"<<endl;
				cout<<"6) Basic"<<endl;
				cout<<"\nYour membership: ";
				cin>>membership;
				if (membership!=1&&membership!=2&&membership!=3&&membership!=4&&membership!=5&&membership!=6)
				{
					cout<<"Invalid input"<<endl;
				}
				}
				while (membership!=1&&membership!=2&&membership!=3&&membership!=4&&membership!=5&&membership!=6);
				string cid;//Customer's ID
				cid="C"+to_string(num_cus);
				customer *temp=new customer (to_string(num_cus),estOperationTime,arrivaltime,membership);
				customerList.push_back(*temp);
				num_cus++;
				cout<<"Your ID is "+cid<<endl;
				cout<<"You have successfully added a customer"<<endl;
				system ("PAUSE");
				system ("CLS");
			}
			else if (opt==2)
			{
				int typeprocess;
				do{
				cout<<"\nPlease select the type of process scheduling algorithm to view the queue of customers"<<endl;
				cout<<"1) Shortest Job First (SJF)"<<endl;
				cout<<"2) Shortest Remaining Time First (SRTF)"<<endl;
				cout<<"3) Priority"<<endl;
				cout<<"4) Return to the previous page"<<endl;
				cout<<"\nYour Choice: ";
				cin>>typeprocess;
				system ("CLS");
				switch (typeprocess)
				{
					case 1: 
							if (customerList.size()==0)
							{
								cout<<"There is no customer added yet"<<endl;
							}
							else
							{
								SJF(customerList);
							}
							
							break;
					case 2: 
							if (customerList.size()==0)
							{
								cout<<"There is no customer added yet"<<endl;
							}
							else
							{
								SRTF(customerList);
							}
							
						
							break;
					case 3: 
								if (customerList.size()==0)
							{
								cout<<"There is no customer added yet"<<endl;
							}
							else
							{
								PriorityScheduling (customerList);
							}
								
							
							break;
					case 4: cout<<"Returning to the previouse screen"<<endl;
							break;
					default: cout<<"Invalid Input...."<<endl;
							break;
				}
				system ("PAUSE");
				system ("CLS");
				}
				while (typeprocess!=4);


			}
		}
		while (opt!=3);

	}
	

