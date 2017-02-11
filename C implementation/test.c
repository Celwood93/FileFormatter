#include <stdio.h>
#include <stdlib.h>
//#include "formatter.h"
//#include "formatter.c"
#include <string.h>
#include <regex.h>
#include <math.h>

struct FORMAT_FLAGS {
	int flag;
	char ** formattedArray;
	int pia; //place in formatted array
	int max; //max in array
	
	
} ff = {0x000000, NULL, 0, 5};

int formatLineGroup(char * seg){
	
	if(!((ff.flag&0x800000) >> 23)){
		if(ff.pia == ff.max -1){
			ff.max = ff.max*2;
			ff.formattedArray = (char**)realloc(ff.formattedArray, sizeof(char*)*ff.max);
			if(ff.formattedArray == NULL){
				fprintf(stderr, "realloc error at formatlinegroup\n");
				return 0;
		}
		}
		ff.formattedArray[ff.pia] = (char *)malloc(sizeof(char)*strlen(seg)+1);
		if(ff.formattedArray[ff.pia] == NULL){
				fprintf(stderr, "realloc error at formatlinegroup\n");
				return 0;
		}
		strncpy(ff.formattedArray[ff.pia], seg, strlen(seg)+1);
		printf("nof > %s\n", seg);
		ff.pia++;
		
	}else{
		char * token;
		char tokString[strlen(seg)+1];
		char segCopy[strlen(seg)+1];
		strncpy(segCopy, seg, strlen(seg)+1);
		token = strtok(segCopy, " \n");
		if(token == NULL){
			fprintf(stderr, "empty token at formatlinegroup\n");
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
	int in = ((ff.flag&0x00FF00) >> 8)-(ff.flag&0x0000FF);
	sprintf(lw, "%d", in);
	char regexSource[25] = "([^ ](.{1,";
	char otherSource[16] = "";
	strncat(otherSource, lw, 6);
	strncat(otherSource, "}))($| )", 10);
	strncat(regexSource, otherSource, 16);
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
			ff.formattedArray = (char**)realloc(ff.formattedArray, sizeof(char*)*ff.max);
			if(ff.formattedArray == NULL){
				fprintf(stderr,"Malloc error in regex run for lines");
				return 0;
			}
		}
		char copyPointer[strlen(matchPointer)+1];
		strncpy(copyPointer, matchPointer, strlen(matchPointer)+1);
		copyPointer[arrGroup[1].rm_eo] = 0;
		printf(">%s<", copyPointer);
		offset = arrGroup[1].rm_eo+1;
		transitionPointer = (char*)calloc((strlen(copyPointer) + ((ff.flag&0x0F0000)>> 16) + (ff.flag&0x0000FF) + 1), sizeof(char));
		if(transitionPointer == NULL){
			fprintf(stderr, "error with calloc in format line group\n");
		}
		strncpy(transitionPointer, margin, strlen(margin));
		strncat(transitionPointer, copyPointer, strlen(copyPointer));
		strncat(transitionPointer, spacing, strlen(spacing));
		ff.formattedArray[ff.pia] = (char*)malloc(sizeof(char)*strlen(transitionPointer) + 1);
		if(ff.formattedArray[ff.pia] == NULL){
				fprintf(stderr, "realloc error at formatlinegroup\n");
				return 0;
		}
		printf("%s", transitionPointer);
		strncpy(ff.formattedArray[ff.pia], transitionPointer, strlen(transitionPointer)+1);
		matchPointer = matchPointer + offset;
		ff.pia++;
	}
	free(transitionPointer);
	regfree(&regexC);
	
}
return 0;
}


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
char ** format_file(FILE * fp){

		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		char ** toPassIn;
		size_t n = 10;
		size_t count = 0;
		
		toPassIn = (char**)malloc(sizeof(char*)*1);
		if(toPassIn == NULL){
			fprintf(stderr,"Malloc error in formatter.c format_file");
			return 0;
		}
		toPassIn[0] = (char*)malloc(sizeof(char)*n);
		if(toPassIn[0] == NULL){
			fprintf(stderr,"Malloc error in formatter.c format_file");
			return 0;
		}
		while ((read = getline(&line, &len, fp)) != -1) {
			if(n < count + read){
				n = n*2+read;
				toPassIn[0] = (char*)realloc(toPassIn[0], sizeof(char)*n);
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
		return toPassIn;
}

char **format_lines(char **lines, int num_lines) {
	char **result = NULL;

#ifdef DEBUG
	result = (char **)malloc(sizeof(char *) * 2);
	if (result == NULL) {
		return NULL;
	}

	result[0] = (char *)malloc(sizeof(char) * 80);
	if (result[0] == NULL) {
		return NULL;
	}
	strncpy(result[0], "(machine-like voice) EXTERMINATE THEM!", 79);

	result[1] = (char *)malloc(sizeof(char) * 2);
	if (result[1] == NULL) {
		return NULL;
	}
	result[1][0] = '\0';
#endif

	return result;
}

char * copyValue(char * matchPointer, regmatch_t solution, char * returnPointer){
	char copyPointer[strlen(matchPointer+solution.rm_so)+1];
	strncpy(copyPointer, matchPointer+solution.rm_so, strlen(matchPointer+solution.rm_so)+1);
	copyPointer[solution.rm_eo-solution.rm_so] = 0;
	#ifdef DEBUG
	printf("testing copyValue: \n%s\n", copyPointer);
	#endif
	returnPointer = (char*)realloc(returnPointer, sizeof(char)*strlen(copyPointer) + 1);
	if(returnPointer == NULL){
		fprintf(stderr, "error in copyValue");
	}
	strncpy(returnPointer, copyPointer, strlen(copyPointer)+1);
	return returnPointer;
}

int main(int argc, char *argv[]) {
	
	if(1){
	ff.formattedArray = (char **)malloc(sizeof(char*)*ff.max);
	if(ff.formattedArray == NULL){
					fprintf(stderr,"Malloc error in regex run");
					return 0;
	}
	char * seg = "testing to see if all this shit will work, fingers crossed it doesnt break.... testing testing";
	formatLineGroup(seg);
	
	
	
	
	
}
if(0){
	try{
		
	}except{
		in first part1
		param : 
		blah blah
	}
	char * source =  ".LW 30\n.LS 3\nProperly formatting  a   file where\nthere\nis\n.FT on\n\n\n    a smattering of white space throughout\n\n.FT off  really means \n.LS 1\n\neliminating that\nextra";
	char * regexSource = "(([.]LW) ([^\n]*)\n?|([.]FT) (on|(off))\n?|([.]LS) ([^\n]*)\n?|([.]LM) (([+])|([-]))?([^\n]*)\n?|(\n)|(^))(([^.\n]([^\n]+)?\n?)*)?";
	size_t maxMatchs = 10;
	size_t maxGroups = 19;
	char ** returnArray;
	returnArray = (char **)malloc(sizeof(char*)*maxMatchs);
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
	char * holder = (char*)malloc(1);
	while(!regexec(&regexC, matchPointer, maxGroups, arrGroup, 0)){//we break when match fails
		
		if(matchIncrementer == maxMatchs-1){
			maxMatchs = maxMatchs*2;
			returnArray = (char **) realloc(returnArray, sizeof(char*)*maxMatchs);
			if(returnArray == NULL){
					fprintf(stderr,"Malloc error in regex run");
					return 0;
				}
		}
		unsigned int groupIncrementer = 0;
		unsigned int offset = 0;
		offset = arrGroup[0].rm_eo;
		int list[6] = {2, 4, 7, 9, 14, 15};
		for(groupIncrementer = 0; groupIncrementer < 7; groupIncrementer++){
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
					int newLM = atoi(holder);
					if(coeff&num){
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
					#ifdef DEBUG
					printf("newLine\n");
					#endif
				}else//start w/o command
				if(list[groupIncrementer] == 15){
					
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
		printf("this: \n%s", copyPointer);
		
		//process group16
		//these will see some change with the inclusion of formatting shinnanigans
		char copyofPointer[strlen(matchPointer)+1];
		strncpy(copyofPointer, matchPointer, strlen(matchPointer)+1);
		copyofPointer[arrGroup[0].rm_eo] = 0;
		returnArray[matchIncrementer] = (char *)malloc(sizeof(char)*strlen(copyofPointer)+1);
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
		printf("match %d: %s\n", i, returnArray[i]);
		free(returnArray[i]);
	}
	free(returnArray);


}



if(0){
	//char * source = ".LW 30\nProperly formatting  a   file where\nthere\nis\n    a smattering of white space throughout\n  really means eliminating that\nextra\n.FT on\nhello there\n.LS 30\n.LM 30\n\nhello there\n\n\n   white\n      space\nsuch that the result\n    looks neat\n                   and\n                         very\n            tidy.\n.FT on\n\n   white\n      space\nsuch that the result\n    looks neat\n                   and\n                         very\n            tidy.";
	char * source = ".LS 30\nProperly formatting  a   file where\nthere\nis\n.FT on\n\n\n    a smattering of white space throughout\n\n  really means \n.LS on\n\neliminating that\nextra";
	//char * regexString = "[.][LF][WSMT] ([^.\n]([^\n]+)\n?)+|\n([^.\n]([^\n]+)\n?)*";
	char * regexString = "([.]LS ([^.\n]([^\n]+)?\n?)+)|([.]FT ([^.\n]([^\n]+)?\n?)+)|([.]LM ([^.\n]([^\n]+)?\n?)+)|([.]LW ([^.\n]([^\n]+)?\n?)+)|(\n([^.\n]([^\n]+)\n?)*)";
//some interesting functionality of this regex. it appears that only the first group in a set of ors will actually have any multiple matches with its multiple groups. if a way around this could be figured out so that all matches can have their groups matched, it would be relatively easy to find a way to identify which group is which, as to eliminate the need for identify formatter, as the flags would just be set based on which group was identified. should be possible, just need to do some testing. 
	size_t maxMatches = 20;
	size_t maxGroups = 25;
  
	regex_t regexCompiled;
	regmatch_t groupArray[maxGroups];
	unsigned int m;
	char * cursor;
	if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
		printf("Could not compile regular expression.\n");
		return 1;
	};

	m = 0;
	cursor = source;
	for (m = 0; m < maxMatches; m ++){
		if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0)){
			break;
		}  // No more matches
		unsigned int g = 0;
		unsigned int offset = 0;
		
		for (g = 0; g < maxGroups; g++){
          		if (groupArray[g].rm_so == (size_t)-1){
				break;
			}  // No more groups

			if (g == 0){
				offset = groupArray[g].rm_eo;
			}

			char cursorCopy[strlen(cursor) + 1];
			strcpy(cursorCopy, cursor);
			cursorCopy[groupArray[g].rm_eo] = 0;
			printf("Match %u, Group %u: [%2u-%2u]: %s\n",
			m, g, groupArray[g].rm_so, groupArray[g].rm_eo,
			cursorCopy + groupArray[g].rm_so);
		}
		cursor += offset;
	}

	regfree(&regexCompiled);

  	return 0;
	
	
	
}
if(0){
	char ** toPassIn;
	FILE * fp;
	if(argc < 2){
		fp = stdin;
		
	}else{
		fp = fopen(argv[1], "r");
		if(fp == NULL){
				fprintf(stderr, "Error reading file");
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
			printf("match %d:\n%s\n", i, toPassIn[i]);
			free(toPassIn[i]);
			i++;
		}
		free(toPassIn); 
	 }
	 
 }
 

	

return 0;
}

