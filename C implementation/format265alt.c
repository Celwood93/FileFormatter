
#include <stdio.h>
#include <stdlib.h>
#include "formatter.h"

int main(int argc, char *argv[]) {
	if(argc > 1){
	char ** toPassIn;
	FILE * fp;
	if(argc < 2){
		fp = stdin;
		
	}else{
		fp = fopen(argv[1], "r");
		if(fp == NULL){
				fprintf(stderr, "Error reading file : arv[1]: %s\n", argv[1]);
				return 0;
			}
	}
	toPassIn = format_file(fp); 

	 if(toPassIn == 0 ){
		 fprintf(stderr, "cap'in i think its broken..\n");
		 return 0;
	 }else{
		int i = 0;
		while(toPassIn[i] != NULL){
			printf("%s", toPassIn[i]);
			free(toPassIn[i]);
			i++;
		}
		
		free(fp);
		free(toPassIn); 
	 }
	 
		
	}
	return 0;
}
