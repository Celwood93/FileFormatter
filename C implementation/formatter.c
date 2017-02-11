
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"
#include <regex.h>
#include <math.h>


struct FORMAT_FLAGS {
	int flag;
	char ** formattedArray;
	int pia; //place in formatted array
	int max; //max in array
	
	
} ff = {0x000000, NULL, 0, 5};


void checkflag(int value){
	int lw = 0;
	int ls = 0;
	int ft = 0;
	int lm = 0;
	int lsnum = 0;
	int lwnum = 0;
	int lmnum = 0;
	
	printf("before value: %06x\n", value);
	printf("ft: %d\n", (ft = (value&0x800000) >> 23));
	printf("lw: %d\n", (lw = (value&0x400000) >> 22));
	printf("ls: %d\n", (ls = (value&0x200000) >> 21));
	printf("lm: %d\n", (lm = (value&0x100000) >> 20));
	printf("lsnum: %d\n", (lsnum = (value&0x0F0000) >> 16));
	printf("lwnum: %d\n", (lwnum = (value&0x00FF00) >> 8));
	printf("lmnum: %d\n", (lmnum = (value&0x0000FF)));
	printf("after value: %06x\n", value);
}


int formatLineGroup(char * seg){
	//printf(">%d", ((ff.flag&0x800000) >> 23));
	
		//checkflag(ff.flag);
	if(!((ff.flag&0x800000) >> 23)){
		if(ff.pia == ff.max -1){
			ff.max = ff.max*2;
			ff.formattedArray = realloc(ff.formattedArray, sizeof(char*)*ff.max);
			if(ff.formattedArray == NULL){
				fprintf(stderr, "realloc error at formatlinegroup\n");
				return 0;
		}
		}
		ff.formattedArray[ff.pia] = malloc(sizeof(char)*strlen(seg)+1);
		if(ff.formattedArray[ff.pia] == NULL){
				fprintf(stderr, "realloc error at formatlinegroup\n");
				return 0;
		}
		strncpy(ff.formattedArray[ff.pia], seg, strlen(seg)+1);
		#ifdef DEBUG
		printf("nof > %s\n", seg);
		#endif
		ff.pia++;
		
	}else if(!strncmp(seg, "\n", 3)){
		
		int size = ((ff.flag&0x0F0000)>> 16)+2;
		char segn[size];
		strncpy(segn, "", strlen(segn)+1);
		int sco = 0;
		while(sco < ((ff.flag&0x0F0000)>>16)+1){
			strncat(segn, "\n", 2);
			sco ++;
		}
		
		if(ff.pia == ff.max -1){
			ff.max = ff.max*2;
			ff.formattedArray = realloc(ff.formattedArray, sizeof(char*)*ff.max);
			if(ff.formattedArray == NULL){
				fprintf(stderr, "realloc error at formatlinegroup\n");
				return 0;
		}
		}
		ff.formattedArray[ff.pia] = malloc(sizeof(char)*strlen(segn)+1);
		if(ff.formattedArray[ff.pia] == NULL){
				fprintf(stderr, "realloc error at formatlinegroup\n");
				return 0;
		}
		strncpy(ff.formattedArray[ff.pia], segn, strlen(segn)+1);
		#ifdef DEBUG
		printf("nof > %s\n", segn);
		#endif
		ff.pia++;
		
		
	}else{
		char * token;
		char tokString[strlen(seg)+1];
		char segCopy[strlen(seg)+1];
		strncpy(segCopy, seg, strlen(seg)+1);
		//printf(">strg%s", seg);
		//checkflag(ff.flag);
		//printf("hereb");
		token = strtok(segCopy, " \n");
		//printf("here");
		if(token == NULL){
		//	fprintf(stderr, "empty token at formatlinegroup\n");
			return 0;
		}
		strncpy(tokString, token, strlen(token)+1);
		token = strtok(NULL, " \n");
		while(token != NULL){
			strncat(tokString, " ", 2);
			strncat(tokString, token, strlen(token)+1);
			token = strtok(NULL, " \n");
		}
		
	char lw[8];
	int in = ((ff.flag&0x00FF00) >> 8)-(ff.flag&0x0000FF) - 1;
	sprintf(lw, "%d", in);
	//printf("num%d", ff.pia);
	char regexSource[25] = "([^ ](.{1,";
	char otherSource[16] = "";
	strncat(otherSource, lw, 7);
	strncat(otherSource, "}))($| )", 11);
	strncat(regexSource, otherSource, 17);
	size_t maxGroups = 5;
	regex_t regexC;
	int offset;
	regmatch_t arrGroup[maxGroups];
	char * matchPointer;
	
	if(regcomp(&regexC, regexSource, REG_EXTENDED)){
		fprintf(stderr, "regex failed to compile");
		return 0;
	};
		int size = (ff.flag&0x0000FF)+2;
		char margin[size];
		strncpy(margin, "", strlen(margin)+1);
		int sco = 0;
		while(sco < (ff.flag&0x0000FF)){
			strncat(margin, " ", 2);
			sco ++;
		}
		size = ((ff.flag&0x0F0000)>> 16)+2;
		char spacing[size];
		strncpy(spacing, "", strlen(spacing)+1);
		sco = 0;
		while(sco < ((ff.flag&0x0F0000)>>16)+1){
			strncat(spacing, "\n", 2);
			sco ++;
		}
	matchPointer = tokString;
	char * transitionPointer;
	while(!regexec(&regexC, matchPointer, maxGroups, arrGroup, 0)){//we break when match fails

		if(ff.pia == ff.max-1){
			ff.max = ff.max*2;
			ff.formattedArray = realloc(ff.formattedArray, sizeof(char*)*ff.max);
			if(ff.formattedArray == NULL){
				fprintf(stderr,"Malloc error in regex run for lines");
				return 0;
			}
		}
		char copyPointer[strlen(matchPointer)+1];
		strncpy(copyPointer, matchPointer, strlen(matchPointer)+1);
		//copyPointer[arrGroup[1].rm_eo] = 0;
		//offset = arrGroup[1].rm_eo+1;
		//changes
		copyPointer[arrGroup[1].rm_eo] = 0;
		offset = arrGroup[1].rm_eo+arrGroup[3].rm_eo-arrGroup[3].rm_so;
		transitionPointer = calloc((strlen(copyPointer) + ((ff.flag&0x0F0000)>> 16) + (ff.flag&0x0000FF) + 2), sizeof(char));
		if(transitionPointer == NULL){
			fprintf(stderr, "error with calloc in format line group\n");
		}
		strncpy(transitionPointer, margin, strlen(margin));
		strncat(transitionPointer, copyPointer, strlen(copyPointer));
		strncat(transitionPointer, spacing, strlen(spacing)); //invalid write?
		ff.formattedArray[ff.pia] = malloc(sizeof(char)*strlen(transitionPointer) + 1);
		if(ff.formattedArray[ff.pia] == NULL){
				fprintf(stderr, "realloc error at formatlinegroup\n");
				return 0;
		}
		strncpy(ff.formattedArray[ff.pia], transitionPointer, strlen(transitionPointer)+1);
		matchPointer = matchPointer + offset;
		ff.pia++;
		free(transitionPointer);
	}
	
	regfree(&regexC);
	
	
	
}
return 0;
}
char * copyValue(char * matchPointer, regmatch_t solution, char * returnPointer){
	char copyPointer[strlen(matchPointer+solution.rm_so)+1];
	strncpy(copyPointer, matchPointer+solution.rm_so, strlen(matchPointer+solution.rm_so)+1);
	copyPointer[solution.rm_eo-solution.rm_so] = 0;
	#ifdef DEBUG
	printf("testing copyValue: \n%s\n", copyPointer);
	#endif
	returnPointer = realloc(returnPointer, sizeof(char)*strlen(copyPointer) + 1);
	if(returnPointer == NULL){
		fprintf(stderr, "error in copyValue");
	}
	strncpy(returnPointer, copyPointer, strlen(copyPointer)+1);
	return returnPointer;
}

int format_output(char** input){
	char * source;
	source = malloc(sizeof(char)*strlen(input[0])+1);
	strncpy(source, input[0], strlen(input[0])+1);
	char * regexSource = "(([.]LW) ([^\n]*)\n?|([.]FT) (on|(off))\n?|([.]LS) ([^\n]*)\n?|([.]LM) ((([+])|([-]))?[^\n]*)\n?|(\n)|(^))(([^.\n]([^\n]+)?\n?)*)?";
	size_t maxMatchs = 10;
	size_t maxGroups = 19;
	char ** returnArray;
	returnArray = malloc(sizeof(char*)*maxMatchs);
	if(returnArray == NULL){
					fprintf(stderr,"Malloc error in regex run");
					return 0;
				}
	regex_t regexC;
	regmatch_t arrGroup[maxGroups];
	unsigned int matchIncrementer;
	char * matchPointer;
	if(regcomp(&regexC, regexSource, REG_EXTENDED)){
		fprintf(stderr, "regex failed to compile");
		return 0;
	};
	matchIncrementer = 0;
	matchPointer = source;
	char * holder = malloc(1);
	while(!regexec(&regexC, matchPointer, maxGroups, arrGroup, 0)){//we break when match fails
		
		if(matchIncrementer == maxMatchs-1){
			maxMatchs = maxMatchs*2;
			returnArray =  realloc(returnArray, sizeof(char*)*maxMatchs);
			if(returnArray == NULL){
					fprintf(stderr,"Malloc error in regex run");
					return 0;
				}
		}
		unsigned int groupIncrementer = 0;
		unsigned int offset = 0;
		offset = arrGroup[0].rm_eo;
		int list[6] = {2, 4, 7, 9, 14, 15};
		for(groupIncrementer = 0; groupIncrementer < 6; groupIncrementer++){
			//sets 1 or 0 based on wether or not its -1 or >0
			int j = arrGroup[list[groupIncrementer]].rm_eo;
			#ifdef DEBUG
			printf("j: %d\ngroup: %d\n", j, list[groupIncrementer]);
			#endif
			if(j > 0){
				//LW(also triggers FT on)
				if(list[groupIncrementer] == 2){
					#ifdef DEBUG
					checkflag(ff.flag);
					#endif
					holder = copyValue(matchPointer, arrGroup[3], holder);
					ff.flag = ((ff.flag & 0xFF00FF) | (atoi(holder) << 8));
					ff.flag = ((ff.flag & 0xbFFFFF) | 0x400000);
					ff.flag = ((ff.flag & 0x7FFFFF) | (0x000001 << 23));
					#ifdef DEBUG
					checkflag(ff.flag);
					#endif
					
				}else//LS
				if(list[groupIncrementer] == 7){
					#ifdef DEBUG
					checkflag(ff.flag);
					#endif
					holder = copyValue(matchPointer, arrGroup[8], holder);
					ff.flag = ((ff.flag & 0xF0FFFF) | (atoi(holder) << 16));
					ff.flag = ((ff.flag & 0xdFFFFF) | 0x200000);
					#ifdef DEBUG
					checkflag(ff.flag);
					#endif
					
				}else//FT
				if(list[groupIncrementer] == 4){
					#ifdef DEBUG
					checkflag(ff.flag);
					#endif
					int on = (int) (pow(arrGroup[5].rm_eo, -1) + 1);
					int off = (int) (pow(arrGroup[6].rm_eo, -1) + 1);
					int which = !(on&off);
					ff.flag = ((ff.flag & 0x7FFFFF) | (which << 23));
					#ifdef DEBUG
					checkflag(ff.flag);
					#endif
					
				}else //LM
				if(list[groupIncrementer] == 9){
					#ifdef DEBUG
					checkflag(ff.flag);
					#endif
					int originalLm = ((ff.flag & 0x0000FF));
					int originalLW = ((ff.flag & 0x00FF00) >> 8);
					int coeff = (int) (pow(arrGroup[11].rm_eo, -1) + 1);
					int num = (int) (pow(arrGroup[10].rm_eo, -1) + 1);
					holder = copyValue(matchPointer, arrGroup[10], holder);
					//printf(">>s%s", holder);
					int newLM = atoi(holder);
					//printf(">%d",newLM);
					if(coeff&num){
						//printf("?>%d",newLM);
						newLM = originalLm + newLM;
						if(newLM<0){
							newLM = 0;
						}
						if(newLM > originalLW-20){
							newLM = originalLW-20;
						}
					}
					ff.flag = ((ff.flag & 0xFFFF00)| newLM);
					ff.flag = ((ff.flag & 0xeFFFFF) | 0x100000);
					#ifdef DEBUG
					checkflag(ff.flag);
					#endif
					
				}else//\n
				if(list[groupIncrementer] == 14){
					//processline \n
					formatLineGroup("\n");
					#ifdef DEBUG
					printf("newLine\n");
					#endif
				}else//start w/o command
				if(list[groupIncrementer] == 15){
					#ifdef DEBUG
					printf("enter 15 \n");
					#endif
				}//error
				else{
					fprintf(stderr, "Error with groups"); 
					return 0;
				}
				break;
			}
			
		}
		char copyPointer[strlen(matchPointer)+arrGroup[16].rm_so+1];
		strncpy(copyPointer, matchPointer+arrGroup[16].rm_so, strlen(matchPointer)+1);
		copyPointer[arrGroup[16].rm_eo-arrGroup[16].rm_so] = 0;
		formatLineGroup(copyPointer);
		#ifdef DEBUG
		printf("this: \n%s", copyPointer);
		#endif
		
		//process group16
		//these will see some change with the inclusion of formatting shinnanigans
		char copyofPointer[strlen(matchPointer)+1];
		strncpy(copyofPointer, matchPointer, strlen(matchPointer)+1);
		copyofPointer[arrGroup[0].rm_eo] = 0;
		returnArray[matchIncrementer] = malloc(sizeof(char)*strlen(copyofPointer)+1);
		if(returnArray[matchIncrementer] == NULL){
					fprintf(stderr,"Malloc error in regex run");
					return 0;
				}
		strncpy(returnArray[matchIncrementer], copyofPointer, strlen(copyofPointer)+1);
		//value is in the return array
		matchPointer = matchPointer + offset;
		
		//reduce the list to exculde previously found stuff
		matchIncrementer++;
		if(!strcmp(matchPointer, "")){
			break;
		}
	}

	free(holder);
	regfree(&regexC);
	int i = 0;
	for(i = 0; i<matchIncrementer; i++){
		#ifdef DEBUG
		printf("match %d: %s\n", i, returnArray[i]);
		#endif
		free(returnArray[i]);
	}
	free(returnArray);
	free(source);
	return 0;

}



char **format_file(FILE *infile) {
	ff.formattedArray = malloc(sizeof(char*)*ff.max);
	//need to figure out when to clear - maybe copy it into an array and clear then return the array? that way memory isnt allocated anymore
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		char ** toPassIn;
		size_t n = 10;
		size_t count = 0;
		
		toPassIn = malloc(sizeof(char*)*1);
		if(toPassIn == NULL){
			fprintf(stderr,"Malloc error in formatter.c format_file");
			return 0;
		}
		toPassIn[0] = malloc(sizeof(char)*n);
		if(toPassIn[0] == NULL){
			fprintf(stderr,"Malloc error in formatter.c format_file");
			return 0;
		}
		while ((read = getline(&line, &len, infile)) != -1) {
			if(n < count + read){
				n = n*2+read;
				toPassIn[0] = realloc(toPassIn[0], sizeof(char)*n);
				if(toPassIn[0] == NULL){
					fprintf(stderr,"Malloc error in formatter.c format_file");
					return 0;
				}
			}
			
			strncat(toPassIn[0], line, read);
			count = count + read;
		}
		if(line){
			free(line);
		}
		format_output(toPassIn);
		int i = 0;
		while(toPassIn[i] != NULL){
			#ifdef DEBUG
			printf("%s", toPassIn[i]);
			#endif
			free(toPassIn[i]);
			i++;
		}
		free(toPassIn[i]);
		free(toPassIn);
		//#ifdef DEBUG
		
		//printf("place: %s", ff.formattedArray[ff.pia-2]);
		//printf("place: %s", ff.formattedArray[ff.pia-1]);
		//#endif
		//testing without this line of code
		//strncpy(ff.formattedArray[ff.pia-1], "\0", 2);
		int sip = ((ff.flag&0x0F0000)>>16);
		while(sip != 0){
			ff.formattedArray[ff.pia-1][strlen(ff.formattedArray[ff.pia-1])-1] = '\0';
			sip = sip - 1;
		}
		ff.formattedArray[ff.pia] = 0;
		return ff.formattedArray;
}


char **format_lines(char **lines, int num_lines) {
		ff.formattedArray = malloc(sizeof(char*)*ff.max);
		//need to figure out when to clear - maybe copy it into an array and clear then return the array? that way memory isnt allocated anymore
		char ** toPassIn;
		size_t n = 10;
		size_t count = 0;
		int i = 0;
		
		toPassIn = malloc(sizeof(char*)*1);
		if(toPassIn == NULL){
			fprintf(stderr,"Malloc error in formatter.c format_file");
			return 0;
		}
		toPassIn[0] = malloc(sizeof(char)*n);
		if(toPassIn[0] == NULL){
			fprintf(stderr,"Malloc error in formatter.c format_file");
			return 0;
		}
		i = 0;
		while(i < num_lines){
			if(n < count + strlen(lines[i])){
				n = n*2+strlen(lines[i]);
				toPassIn[0] = realloc(toPassIn[0], sizeof(char)*n);
				if(toPassIn[0] == NULL){
					fprintf(stderr,"Malloc error in formatter.c format_file");
					return 0;
				}
			}
			strncat(toPassIn[0], lines[i], strlen(lines[i])+1);
			count = count + strlen(lines[i]);
			i++;
		}
		
		format_output(toPassIn);
		i = 0;
		while(toPassIn[i] != NULL){
			#ifdef DEBUG
			printf("match %d:\n%s\n", i, toPassIn[i]);
			#endif
			free(toPassIn[i]);
			i++;
		}
		free(toPassIn);
		int sip = ((ff.flag&0x0F0000)>>16);
		while(sip != 0){
			ff.formattedArray[ff.pia][strlen(ff.formattedArray[ff.pia])-1] = '\0';
			sip = sip - 1;
		}
		return ff.formattedArray;
}
