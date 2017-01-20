/*Buffer - Circular Queue Implementation -STATIC VERSION*/

#include <stdlib.h>
//#include "stm32f0xx.h"
#include "Buffer.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



extern void Buffer_add(Buffer* buff, char* str){
	if(buff -> full >= BUFFER_TOTAL_SIZE){
		while(1); //error loading into full
	}
	strcpy(buff -> memmory[buff -> index_to_load],str);
	buff -> index_to_load = ((buff -> index_to_load)+1)%(BUFFER_TOTAL_SIZE);
	buff -> full++;
}

extern bool Buffer_full(Buffer* buff){
	if(buff -> full >= BUFFER_TOTAL_SIZE){
		return true;
	}
	return false;
}
extern void Buffer_pop(Buffer* buff) {
	if(buff -> full <= 0){
		while(1); //error when trying to remove when empty
	}
	strcpy(buff -> popped,buff -> memmory[buff -> index_to_pop]);
	strcpy(buff -> memmory[buff -> index_to_pop],"\0");
	buff -> index_to_pop = ((buff -> index_to_pop)+1)%(BUFFER_TOTAL_SIZE);
	buff -> full--;
}

extern void Buffer_init(Buffer* buff){
	for(int i = 0; i < BUFFER_TOTAL_SIZE;i++){
		strcpy(buff -> memmory[i],"\0");
	}
	buff -> index_to_pop = 0;
	buff -> index_to_load = 0;
	buff -> full = 0;
}


/*
int main(){
	char test[4] = {'a','b','c','\0'};
	for(int i = 0; i < 4; i++){
		printf("%c\n",test[i]);
	}
	
	Buffer buff;
	Buffer_init(&buff);
	Buffer_add(&buff,"wasd");
	Buffer_add(&buff,"1337");
	Buffer_add(&buff,"b7o4");
	Buffer_add(&buff,"b7o4");
	Buffer_add(&buff,"b7o4");
	
	Buffer_pop(&buff);
	Buffer_pop(&buff);
	Buffer_pop(&buff);
	Buffer_pop(&buff);
	Buffer_pop(&buff);

	
	return 0;
	
}
*/
