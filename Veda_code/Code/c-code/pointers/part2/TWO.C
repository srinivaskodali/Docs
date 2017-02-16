// shows the details of passing parameter to functions
// Version : 1.0
// Author : Team -C

// comonly used example to demonstrate how parameters will be passed

void swap ( int *a, int* b){
	int temp;
	temp = *a;
	*a=*b;
	*b=temp;
}
main(){
	int x=10,y=20;
	printf(" before swap x = %d y = %d\n",x,y);
	swap(&x,&y);
	printf(" After swap x = %d y = %d\n",x,y);
}
