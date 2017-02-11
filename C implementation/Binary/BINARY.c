#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>





int binaryBullshit(){
	//doing tests on binary values to further my knowledge
	int x = 0x14;
	int i = 0x00;
	printf("%d\n", x);
	int y = 0x03;
	int j = 0x05;
	int h = y | j;
	printf("%d\n", h);
	int b = -0x06;
	if(1>(h = j | b)){
		printf("worked!` :%d\n", h);
		h = j | ~b;
		printf("works? :%d\n", h);
	}
	printf("%d\n", h);
	x = 0x21;
	y = x & 0xF0;
	j = x & 0x0F;
	printf("expecting %d : %d \nexpecting %d : %d\n",0x20, y, 0x01, j);
	i = 0x03;
	j = 5;
	h = i + j;
	printf(">%d\n",h);
	
	if((i = 0x0005 + 0x000A) > (j = (0x1e05>>8) - 0x0014)){
		i = (i = i - 0x000A) | j;
		
	}
	j = i&0x00FF;
	printf("%d\n",0x1e14);
	printf("%d\n", i);
	printf("%d\n", (j>>=8));
	int DF = 0x10000000;
	int DG = 010000000000;
	printf("DF: %d\n", DF);
	return 0;
	for(int poo = 0; poo < 10; poo++){
		printf("DF: %d\n", DF);
		//printf("DG: %d\n", DG);
		DF = DF>>1;
		DG = DG >>1;
	}
	for(int poo = 0; poo < 10; poo++){
		printf("DF: %d\n", DF);
		//printf("DG: %d\n", DG);
		DF = DF<<1;
		DG = DG <<1;
	}
	for(int poo = 0; poo < 6; poo++){
		printf("DF: %d\n", DF);
		//printf("DG: %d\n", DG);
		DF = DF>>1;
		DG = DG >>1;
	}
	
	
	
	
	
}

int binaryBullshitTester(int value){;

	int lw = 0;
	int ls = 0;
	int ft = 0;
	int lm = 0;
	int lsnum = 0;
	int lwnum = 0;
	int lmnum = 0;
	if(0){
	printf("before value: %d\n", value);
	printf("lw: %d\n", (lw = (value&0xF0000000) >> 28));
	printf("ls: %d\n", (ls = (value&0x0F000000) >> 24));
	printf("ft: %d\n", (ft = (value&0x00F00000) >> 20));
	printf("lm: %d\n", (lm = (value&0x000F0000) >> 16));
	printf("lsnum: %d\n", (lsnum = (value&0x0000F000) >> 12));
	printf("lwnum: %d\n", (lwnum = (value&0x00000FF0) >> 4));
	printf("lmnum: %d\n", (lmnum = (value&0x0000000F)));
	printf("after value: %d\n", value);
	}
	if(1){
		//better tester - use with debugging commands
	/* int test = 0x000;
	test = test << 1;
	test = test + 1;
	test = test << 1;
	test = test + 1;
	test = test << 1;
	test = test + 0;
	test = test << 1;
	test = test + 1;
	printf(">%03x\n", test);
	int hmm = atoi("+");
	printf(">%d\n",1 + hmm);
	hmm = atoi("-3");
	printf(">%d\n",1 + hmm); */
	//value = ff.flag;
	
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
	return 0;
}


int binaryUpdatesBullshit(){
	int value = 0xd01e05;
	binaryBullshitTester(value);
	return 0;
	value = 0x101101e5;
	value = value & 0xFF0FFFFF;
	binaryBullshitTester(value);
	value = value | 0x00100000;
	binaryBullshitTester(value);
	value = value + 0x00000005;
	binaryBullshitTester(value);
	value = value - 0x00000005;
	binaryBullshitTester(value);
	int i = -1;
	int j = (int) (pow(i, -1) + 1);
	int y = j;
	printf("?>%d\n", y);
	i = 15;
	j = (int) (pow(i, -1) + 1);
	y = j;
	printf(">%d\n", y);
	int k = -1;
	int l = 30;
	int g = /*LW*/((((int) (pow(i, -1) + 1))*0xF0000000 | (l<<4))|0x0FFFF00F) + /*LS*/((((int) (pow(i, -1) + 1))*0x0F0000000 | (l<<4))|0xF0FF0FFF) + ((((int) (pow(i, -1) + 1))*0x0F0000000 | (l<<4))|0xF0FF0FFF);
	printf(">%08x\n", g);
	printf("%d", 0x00000001&0xFFFFFFFF);
	return 0;
	
	
	
}
	int testStrTok(char * tokker){
		char HEREITLIES[256];
		strncpy(HEREITLIES, tokker, 256);
		char * token;
		char tokenThingy[25];
		token = strtok(HEREITLIES, " ");
		printf(">%s\n", token);
		return 0;
		
		
		
	}






int main(){
	char * tokmebaby = "this is a test, a test to see, what could be... hurray";
	testStrTok(tokmebaby);
	printf("here");
	/* char lw[5];
	itoa((((0x001e05&0x00FF00) >> 8)-((0x001e05&0x0000FF))), lw, 10);
	//itoa(30-5, lw, 10);
	printf(">%s", lw); */
	int aInt = 368;
	char str[15];
	sprintf(str, "%d", aInt);
	printf(">>%s", str);
	char lw[5];
	itoa((((0x001e05&0x00FF00) >> 8)-((0x001e05&0x0000FF))), lw, 10);
	char regexSource[23] = "(.{1,";
	char otherSource[16] = "";
	strncat(otherSource, lw, 6);
	strncat(otherSource, "})($| )", 10);
	strncat(regexSource, otherSource, 16);
	printf(">%s", regexSource);
	//binaryUpdatesBullshit();
	return 0;
}

