#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//file for handling the input
FILE* data=NULL;
FILE* output2=NULL;
FILE* counts=NULL;
int countF=0,countL=0,countM=0,countR=0;

//functions for sorting
void swap(int arr[], int ix, int iy){
	int temp=arr[ix];
	arr[ix]=arr[iy];
	arr[iy]=temp;
}

//for quick-sort considering first element as pivot
int partitionFirst(int arr[], int low, int high){
	int pivot=arr[low], i=low+1, j=high;
	do{
		while(i<=high&&arr[i]<=pivot)
			i++;
		while(j>=low&&arr[j]>pivot)
			j--;
		if(i<j){
			swap(arr,i,j);
			countF++;
		}
	}while(i<j);
	swap(arr,low,j);
	countF++;
	return j;
}

void quickSortFirst(int arr[], int low, int high){
	if(low<high){
		int partIndex=partitionFirst(arr,low,high);
		quickSortFirst(arr,low,partIndex-1);
		quickSortFirst(arr,partIndex+1,high);
	}
}

//for quick-sort considering last element as pivot
int partitionLast(int arr[], int low, int high){  
    int pivot=arr[high]; 
    int i=low-1;  
  
    for (int j=low; j<=high-1; j++){   
        if(arr[j]<pivot){  
            i++;  
            swap(arr,i,j);
			countL++;  
        }  
    }  
    swap(arr,i+1,high); 
	countL++;
    return (i + 1);  
}  
  
void quickSortLast(int arr[], int low, int high){  
    if(low<high){  
        int partIndex=partitionLast(arr,low,high); 
        quickSortLast(arr,low,partIndex-1);  
        quickSortLast(arr,partIndex+1,high);  
    }  
}  

//for quick-sort considering the middle element as the pivot
int partitionMid(int arr[], int low, int high){
	int pivotIndex=(low+high)/2;
	int pivot=arr[pivotIndex], i=low, j=high;
	do{
		while(i<=high&&arr[i]<=pivot)
			i++;
		while(j>=low&&arr[j]>pivot)
			j--;
		if(i<j){
			swap(arr,i,j);
			countM++;
		}
	}while(i<j);
	swap(arr,pivotIndex,j);
	countM++;
	return j;
}

void quickSortMid(int arr[], int low, int high){
	if(low<high){
		int partIndex=partitionMid(arr,low,high);
		quickSortMid(arr,low,partIndex-1);
		quickSortMid(arr,partIndex+1,high);
	}
}

//for quick-sort considering a random element as the pivot(taking 1st index from the start for example)
int partitionRandom(int arr[], int low, int high){
	int pivot=arr[low+1], i=low, j=high;
	do{
		while(i<=high&&arr[i]<=pivot)
			i++;
		while(j>=low&&arr[j]>pivot)
			j--;
		if(i<j){
			swap(arr,i,j);
			countR++;
		}
	}while(i<j);
	swap(arr,low+1,j);
	countR++;
	return j;
}

void quickSortRandom(int arr[], int low, int high){
	if(low<high){
		int partIndex=partitionRandom(arr,low,high);
		quickSortRandom(arr,low,partIndex-1);
		quickSortRandom(arr,partIndex+1,high);
	}
}

//for bringing the values into the array(for sorting)
void arrayLoading(int arr[],int endpoint){
    data=fopen("data.txt","r");
    for(int i=0; i<endpoint; i++){
        fscanf(data,"%d",&arr[i]);
    }
    fclose(data);
}

void main(){
    srand(time(NULL));
    clock_t t;
	int tempArr[100000];

    //intiating the data file
    data=fopen("data.txt","w");
    for(int i=0; i<100000; i++){
        fprintf(data,"%d\n",rand());
    }
    fclose(data);

    //sorting and printing out the time taken and also the count of swaps performed
    output2=fopen("output2.txt","w");
	counts=fopen("counts.txt","w");
    double timeI, timeS, timeQ, timeR;
    for(int i=100; i<=100000; i+=100){
        arrayLoading(tempArr,i);
        t=clock();
        quickSortFirst(tempArr,0,i-1);
        t=clock()-t;
        timeI=((double)t)/CLOCKS_PER_SEC;
        arrayLoading(tempArr,i);
        t=clock();
        quickSortLast(tempArr,0,i-1);
        t=clock()-t;
        timeS=((double)t)/CLOCKS_PER_SEC;
		arrayLoading(tempArr,i);
        t=clock();
        quickSortMid(tempArr,0,i-1);
        t=clock()-t;
        timeQ=((double)t)/CLOCKS_PER_SEC;
		arrayLoading(tempArr,i);
        t=clock();
        quickSortRandom(tempArr,0,i-1);
        t=clock()-t;
        timeR=((double)t)/CLOCKS_PER_SEC;
        fprintf(output2,"%d\t\t%lf\t\t%lf\t\t%lf\t\t%lf\n",i,timeI,timeS,timeQ,timeR);
        fprintf(counts,"%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i,countF,countL,countM,countR);
		countF=countL=countM=countR=0;
        printf("Block count -----> %d\n",i);
    }
    fclose(output2);
	fclose(counts);
}