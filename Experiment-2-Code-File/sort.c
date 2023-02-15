#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//file for handling the input
FILE* data=NULL;
FILE* output=NULL;

//functions for sorting
void swap(int arr[], int ix, int iy){
	int temp=arr[ix];
	arr[ix]=arr[iy];
	arr[iy]=temp;
}

//for merge-sort
void mergeSort(int arr[], int start, int end){
	if(start<end){	
		int mid, ptr1, ptr2, tempInd;
		mid=(start+end)/2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid+1, end);
		int* tempArr=(int*)malloc((end+1)*sizeof(int));
		for(int i=start; i<=end; i++)
			tempArr[i]=arr[i];
		ptr1=start;
		ptr2=mid+1;
		tempInd=start;
		while(ptr1<=mid&&ptr2<=end){
			if(tempArr[ptr1]>=tempArr[ptr2]){
				arr[tempInd]=tempArr[ptr2];
				ptr2++;
				tempInd++;
			}
			else if(tempArr[ptr1]<tempArr[ptr2]){
				arr[tempInd]=tempArr[ptr1];
				ptr1++;
				tempInd++;
			}
		}
		while(ptr1<=mid){
			arr[tempInd]=tempArr[ptr1];
			ptr1++;
			tempInd++;
		}
		while(ptr2<=end){
			arr[tempInd]=tempArr[ptr2];
			ptr2++;
			tempInd++;
		}
        free(tempArr);
	}
}

//for quick-sort
int partition(int arr[], int low, int high){
	//considering first element as the pivot
	int pivot=arr[low], i=low+1, j=high;
	do{
		while(i<=high&&arr[i]<=pivot)
			i++;
		while(j>=low&&arr[j]>pivot)
			j--;
		if(i<j)
			swap(arr,i,j);
	}while(i<j);
	if(low!=j)
		swap(arr,low,j);
	return j;
}

void quickSort(int arr[], int low, int high){
	if(low<high){
		int partIndex=partition(arr,low,high);
		quickSort(arr,low,partIndex-1);
		quickSort(arr,partIndex+1,high);
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

    //sorting and printing out the time taken
    output=fopen("output.txt","w");
    double timeI, timeS;
    for(int i=100; i<=100000; i+=100){
        arrayLoading(tempArr,i);
        t=clock();
        mergeSort(tempArr,0,i-1);
        t=clock()-t;
        timeI=((double)t)/CLOCKS_PER_SEC;
        arrayLoading(tempArr,i);
        t=clock();
        quickSort(tempArr,0,i-1);
        t=clock()-t;
        timeS=((double)t)/CLOCKS_PER_SEC;
        fprintf(output,"%d\t\t%lf\t\t%lf\n",i,timeI,timeS);
        printf("Block count -----> %d\n",i);
    }
    fclose(output);
}