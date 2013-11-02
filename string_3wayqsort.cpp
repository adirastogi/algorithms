#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;
#define charAt(str,pos)   (pos>strlen(str))?0:*(str+pos)


void threeWayStringQsort(char** str_array, int start , int end, int offset){

    //empty subarray
    if(start>=end)
        return;

    /*partition on the first character of the strings first*/
    char pivot = charAt(str_array[end],offset);
    int empty_count=0, i,j,k;
    for(i = k = start-1, j = start; j <=end  ; j++){
        if(charAt(str_array[j],offset) < pivot){
	  char* temp = str_array[j];
	  str_array[j] = str_array[k+1];
	  str_array[k+1] = str_array[i+1];
	  str_array[i+1] = temp;
          k++;
          i++;
        }
        else if(charAt(str_array[j],offset) == pivot){
            char* temp = str_array[k+1];
            str_array[k+1] = str_array[j];
            str_array[j] = temp;
            k++;
        }
	if(charAt(str_array[j],offset)==0)
	    empty_count++;
    }
    
    //remove the finished strings from the left subarray and then call sort
    threeWayStringQsort(str_array,start+empty_count,i,offset);
    //call sort on the equal subarrya with offset + 1
    threeWayStringQsort(str_array,i+1,k,offset+1);
    //call sort on the right subarray
    threeWayStringQsort(str_array,k+1,end,offset);

}


int main(){
    char* str_array[] = {
        "she sells seashells",
        "zillo",
        "shenanignas",
        "tortuga",
        "bhsues",
        "abcde",
        "shellsort"
    };
    threeWayStringQsort(str_array,0,6,0);
    cout<<"The sorted strings are \n";
    for(int i =0; i < 7 ; i++)
	cout<<str_array[i]<<"\n";
    return 0;
}





