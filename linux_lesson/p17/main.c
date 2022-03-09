#include<stdio.h>

#define MAX 10
int main(){
	int i = 0;
	int arr[MAX] = {1,2,3,4,5,6,7,8,9,0};
	for(;i < MAX; i++){
		printf("%d\n",arr[i]);
	}
	return 0;
}
