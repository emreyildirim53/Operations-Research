#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){	
	int totalNode;
	int *activityDuration,*tempActivityDuration;// Memory space has been reserved for activity time, backup of time (required for the longest route operation).
	int **activityConnect;// The memory was requested for the connection matrix. If there are links between activities, rows and columns will be filled in as 1 or 0.
	int connectCount;// Number of connected activities
	
	printf("  Enter the number of activities: ");scanf("%d",&totalNode);	
	activityDuration=(int*)malloc(sizeof(int*)*totalNode);
	tempActivityDuration=(int*)malloc(sizeof(int*)*totalNode);
	activityConnect=(int**)malloc(sizeof(int*)*totalNode);
	printf("\n");
	//We've taken the duration of the activity in the activityDuration matrix
	for(int i=0;i<totalNode;i++){
		printf("%3d. duration of activity: ",i+1);scanf("%d",&activityDuration[i]);
		tempActivityDuration[i]=activityDuration[i];	
	}
	int con;	
	printf("\n------------------------------------------------------------------\n");
	for(int i=0;i<totalNode;i++){		
		printf("\n%3d. the number of jobs that must end for the start of the activity: ",i+1); scanf("%d",&connectCount);
		activityConnect[i]=(int*)malloc(sizeof(int*)*totalNode);
			for(int j=0;j<connectCount;j++){ 
				printf("\tName of the %d. activity that depends on the %d. activity. ",j+1,i+1);scanf("%d",&con);			
				activityConnect[i][con-1]=1;// For upper triangle.
				activityConnect[con-1][i]=1;// For lower triangle.
		    }
	}
	/*
		* This code block was written to find the total distance.
		* The null values were set to 0.
		* The previously found values have been transferred to the lower rows.
		* Processed for linked nodes. (Values of 1)
		* Because the initial state included an exception, it was processed separately. (case i=0)
		* Each row and column represents an activity. Based on this;
		* If we collect the relevant activity links. The total path length is found.
		* exp: 1.(3days),2.(6days),3.(4days)    1->2 => 3+6=9 , 1->3 => 3+4=7 values are obtained. We need to get the big on the critical path.
		* Compared to the previous line. The smaller the value is taken.
		* Optimal if the previous row is small. The bottom line value is changed.
		* The latest column and the latest line give us the solution.
		* The last line of any column gives the optimal path of i.(column)activity.
	*/
	printf("\n\n");
	for(int i=0;i<totalNode;i++){
		printf("\n");
		for(int j=0;j<totalNode;j++){
			 if(activityConnect[i][j]!=1)activityConnect[i][j]=0;
			 if( i==0 && j==0)activityConnect[0][0]=activityDuration[0];
			 else if((j<i || activityConnect[i][j]==0 || i==j) && i!=0)activityConnect[i][j]=activityConnect[i-1][j];			 
			 else if(activityConnect[i][j]==1){
			 	if (i==0){
			 		activityConnect[i][j]=activityDuration[i]+tempActivityDuration[j];
				 	activityDuration[j]=activityConnect[i][j];
				}else if(activityDuration[i]+tempActivityDuration[j]>activityConnect[i-1][j]){			 
					 activityConnect[i][j]=activityDuration[i]+tempActivityDuration[j];
					 activityDuration[j]=activityConnect[i][j];
				}else{
					 activityConnect[i][j]=activityConnect[i-1][j];
					 activityDuration[j]=activityConnect[i-1][j];				
				}
			} 
			 printf(" %6d",activityConnect[i][j]);
		}
	}
	/*
		Backtracking is in progress. Operations are fed back from the lower right corner of the matrix towards the upper left corner.
	*/
	printf("\n\n\n");
	printf(" %3d",totalNode);
	for(int i=totalNode-1;i>=0;i--)
		for(int j=i-1;j>=0;j--){
			if(tempActivityDuration[i]==abs(activityConnect[totalNode-1][i]-activityConnect[totalNode-1][j])){			
				i=j;
				printf(" %3d",i+1);
			}	
		}
		printf(" = %3d",activityConnect[totalNode-1][totalNode-1]);
	getch();
	return 0;
}

