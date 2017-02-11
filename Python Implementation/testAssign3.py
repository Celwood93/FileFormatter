import re
import sys
import fileinput

format_flags = {'LW' : 0,
				'LWNum' : 0,
				'LS' : 0,
				'LSNum' : 0,
				'LM' : 0,
				'LMNum' : 0,
				'FT' : 0,
				}

def main():
	#testTheArrayToString()
	#testFileInput()
	#create_list()
	#g = create_unformatted_list() 
	#print(g)
	strg = "12345"
	i = 0
	
	line = "poopy balls"
	key = "jagged"
	key2 = "WhenInDoubtScreamAndShout"
	#Encryption_Test(line, key)
	
	format_flags["lol"] = 0
	format_flags["lol"] == False
	print(str(format_flags["lol"]) + " <-- works?")
	
	
	
	
	#create_list()

def Encryption_Test(line, key):
	alphabet2 ={'0' : ' ',
				'1' : 'a',
				'2' : 'b',
				'3' : 'c',
				'4' : 'd',
				'5' : 'e',
				'6' : 'f',
				'7' : 'g',
				'8' : 'h',
				'9' : 'i',
				'10' : 'j',
				'11' : 'k',
				'12' : 'l',
				'13' : 'm',
				'14' : 'n',
				'15' : 'o',
				'16' : 'p',
				'17' : 'q',
				'18' : 'r',
				'19' : 's',
				'20' : 't',
				'21' : 'u',
				'22' : 'v',
				'23' : 'w',
				'24' : 'x',
				'25' : 'y',
				'26' : 'z',
				'27' : 'A',
				'28' : 'B',
				'29' : 'C',
				'30' : 'D',
				'31' : 'E',
				'32' : 'F',
				'33' : 'G',
				'34' : 'H',
				'35' : 'I',
				'36' : 'J',
				'37' : 'K',
				'38' : 'L',
				'39' : 'M',
				'40' : 'N',
				'41' : 'O',
				'42' : 'P',
				'43' : 'Q',
				'44' : 'R',
				'45' : 'S',
				'46' : 'T',
				'47' : 'U',
				'48' : 'V',
				'49' : 'W',
				'50' : 'X',
				'51' : 'Y',
				'52' : 'Z',
				'53' : '0',
				'54' : '1',
				'55' : '2',
				'56' : '3',
				'57' : '4',
				'58' : '5',
				'59' : '6',
				'60' : '7',
				'61' : '8',
				'62' : '9',
				}
	alphabet = {' ' : 0,
				'a' : 1,
				'b' : 2,
				'c' : 3,
				'd' : 4,
				'e' : 5,
				'f' : 6,
				'g' : 7,
				'h' : 8,
				'i' : 9,
				'j' : 10,
				'k' : 11,
				'l' : 12,
				'm' : 13,
				'n' : 14,
				'o' : 15,
				'p' : 16,
				'q' : 17,
				'r' : 18,
				's' : 19,
				't' : 20,
				'u' : 21,
				'v' : 22,
				'w' : 23,
				'x' : 24,
				'y' : 25,
				'z' : 26,
				'A' : 27,
				'B' : 28,
				'C' : 29,
				'D' : 30,
				'E' : 31,
				'F' : 32,
				'G' : 33,
				'H' : 34,
				'I' : 35,
				'J' : 36,
				'K' : 37,
				'L' : 38,
				'M' : 39,
				'N' : 40,
				'O' : 41,
				'P' : 42,
				'Q' : 43,
				'R' : 44,
				'S' : 45,
				'T' : 46,
				'U' : 47,
				'V' : 48,
				'W' : 49,
				'X' : 50,
				'Y' : 51,
				'Z' : 52,
				'0' : 53,
				'1' : 54,
				'2' : 55,
				'3' : 56,
				'4' : 57,
				'5' : 58,
				'6' : 59,
				'7' : 60,
				'8' : 61,
				'9' : 62,
				}
				
	k = len(key)
	print(k)
	strg = []
	i = 0
	while(i < k):
		strg.append(alphabet[key[i]])
		i = i + 1
	print(strg)
	i = 0
	j = 0
	newstrg = ""
	f = 1
	while(f<2):
		try:
			num = int(alphabet[line[i]])
			num2 = int(strg[j])
			newnum = num + num2
			if(newnum > 64):
				newnum = nuwnum % 64
			newstrg = newstrg + alphabet2[str(newnum)]
			i = i + 1
			if(j < len(strg)-1):
				j = j + 1
			else:
				j = 0
			print("pass2")
		except IndexError:
			print("num: " + str(num)+" num2: " +str(num2) + " newnum: "+ str(newnum)+ " i: "+ str(i) + " j: "+ str(j))
			f = 5
			print("f = 5 now")
			continue
	print("word: "+newstrg)
	print("pass")
	i = 0
	j = 0
	newstrg2 = ""
	print("length of line: " + str(len(line)))
	while(1<2):
		try:
			print(newstrg[i])
			num = int(alphabet[newstrg[i]])
			num2 = int(strg[j])
			newnum = num - num2
			if(newnum < 0):
				newnum = newnum % 64
			newstrg2 = newstrg2 + alphabet2[str(newnum)]
			i = i + 1
			if(j < len(strg)-1):
				j = j + 1
			else:
				j = 0
			print("pass2")
		except IndexError:
			print("num: " + str(num)+" num2: " +str(num2) + " newnum: "+ str(newnum)+ " i: "+ str(i) + " j: "+ str(j))
			break
	print(newstrg2)
	


def newTestsArithmeticHA():
		str = "-5"
		str = int(str)
		num = 0 + str
		print(num)
	
def listTest():
		# testerList = ["hello there", "how are we today", "buddy?", "remove this character::!"]
		# tester = "hello there how are we today buddy remove this character::!"
		# print(testerList[-1:][0][:-1])
		# str = testerList[-1:][0][:-1]
		# del testerList[-1:]
		# testerList.append(str)
		# print(testerList)
		# str = tester[:-1]
		# print("str")
		# print(str)
		
		#useful maybe baby?
		# i = 0
		# while(i < self._Formatter__format_flags["LMNum"]):
			# if(self.returnList[-1:] == ["\n"]):
				# del self.returnList[-1]
			# i = i + 1
		# return self.returnList
		testList2 = ["zero", "one", "two", "three", "four", "\n"]
		testList3 = ["zero", "one", "two", "three", "four", "\n", "\n"]
		testList4 = ["zero", "one", "two", "three", "four", "\n", "\n", "\n"]
		#print(testList4[-2:-1])
		while(testList4[-2:-1] == ["\n"]):
			print(testList4[-2:-1])
			#print(testList4[-1:])
			if(testList4[-1:] == ["\n"]):
				print(testList4[-1:])
				del testList4[-1]
		print(testList4)
		i = 0
		while(i < 1):
			if(testList3[-1:] == ["\n"]):
				i = i + 1
				del testList3[-1]
		print(testList3)
		
		testListnew = ["zero", "one", "two", "three", "four", "five?\n"]
		holderString = testListnew[-1]
		print(holderString + "+++++")
		clearnewlines = re.sub(r"\n", "", holderString)
		str(clearnewlines)
		print(clearnewlines)
		if(clearnewlines != None):
			del testListnew[-1]
			testListnew.append(clearnewlines)
			
		print(testListnew)
def create_list():
	output = testFileInput()
	returnList = []
	obj = re.findall(r"(?<!.)(\.[FL][SWMT] ?\w+)(?:.+)?|([^\n]+)|((?<!.)\n)", output) #i do this to capture all the values ON THE SAME LINE as the .command -> to make it so i can keep keep the characters after the . command and put them into the output id change the regex command to have the .+? in brackets. however that would create a new group and thats annoying.
	print(obj)
	print(len(obj))
	lengthOfInput = len(obj)
	lineNum = 0
	while(lineNum < lengthOfInput):
		if(obj[lineNum][0] != ""):
			ID_formatters(obj[lineNum][0])
			lineNum = lineNum + 1
		if(format_flags["FT"] == 1):
			if(obj[lineNum][1] != ""):
				strg = ""
				while(lineNum < lengthOfInput and obj[lineNum][0] == "" and obj[lineNum][2] == ""):
					strglist = re.split(r"(?<=\s) +|^ +(?=\s)| (?= +[\n\0])", obj[lineNum][1])
					i = 0
					strgSeg = ""
					while(i < len(strglist)):
						strgSeg = strgSeg + strglist[i]
						i = i + 1
					strgSegTwo = re.sub(r"(?<![\n ])\b(?![\w .,;!?:'])|(?<=.)(?=\n)", ' ', strgSeg)
					strg = strg + strgSegTwo
					lineNum = lineNum + 1
				formatLineString = ""
				formatLineEnd = ""
				marginCount = format_flags["LMNum"]
				widthCount = format_flags["LWNum"]
				if(format_flags["FT"] == 1):
					while(marginCount > 0):
						formatLineString = formatLineString + " "
						marginCount = marginCount - 1
						widthCount = widthCount - 1
				regExp = r"(?<!\w).{," + str(widthCount) + "}(?!\w)"
				groups = re.findall(regExp, strg)
				if(format_flags["LS"] == 1 and format_flags["FT"] == 1):
					formatLineEnd = "\n"
				#print(groups)
				for lines in groups:
					#extraBullShit(lines) #for the extra bullshit (encoding method)
					#print(formatLineString + lines + formatLineEnd*format_flags["LSNum"])
					returnList.append(formatLineString + lines + formatLineEnd*format_flags["LSNum"])
				
		if(lineNum < lengthOfInput and obj[lineNum][2] != ""):
			returnList.append("\n"*(1+format_flags["FT"]*format_flags["LSNum"]))
			
		if(lineNum < lengthOfInput and obj[lineNum][1] != "" and format_flags["FT"] == 0):
			returnList.append(obj[lineNum][1])
			
		lineNum = lineNum + 1
	print(returnList)
		
	
def testFileInput():
	returninp = ""
	try:	
		for lines in fileinput.input():
			returninp = returninp + lines
		
	
			
			
	except FileNotFoundError:
		print("file not found, type input: \n")
		largs = []
		for lines in fileinput.input(largs):
			returninp = returninp + lines

	return returninp
	
		
def create_unformatted_list():
	output = testTheArrayToString()
	unformatted_list = []
	outputs = [ \
        ".LW 30",
        "Properly formatting  a   file where",
        "there  ",
        "is",
		"\n"
        "    a smattering of white space throughout",
        "  really means eliminating that  ",
        "extra",
        "   white ",
        "      space",
        "such that the result",
        "    looks neat    ",
        "                   and",
        "                         very",
        "            tidy."
    ]
	try:
		
		obj = re.findall(r"[^\n]+|(?<!.)\n", output)
		i = 0
		j = len(obj)
		while(i<j):
			reter = obj[i]
			unformatted_list.append(reter)
			i = i + 1
			
			
	except FileNotFoundError:
		sys.exit(0)
	return unformatted_list

def testTheArrayToString():
	input = [ \
        ".LW 30",
        "Properly formatting  a   file where",
        "there  ",
        "is",
		"\n"
        "    a smattering of white space throughout",
        "  really means eliminating that  ",
        "extra",
        "   white ",
        "      space",
        "such that the result",
        "    looks neat    ",
        "                   and",
        "                         very",
        "            tidy."
    ]
	returninput = ""
	for lines in input:
		returninput = returninput + lines + "\n"
		
	return returninput
	
def testCreateList():
	returnList = []
	adderString = ""
	stringHold = testTheArrayToString()
	print(stringHold)
	print("\n")
	obj = re.findall(r"(\w+[?!.:;,\"'/]? |\w+[?!.:;,\"'/]?)|(\n|\r|\f|\v|\0)|(?<!.)(\.[FL][SWMT] [\d\w]{1,2}\w?)|(\.[FL][SWMT] ?\d?\d?)", stringHold)
	print("original:")
	print(obj)
	i = 0
	j = len(obj)
	p = 0
	uf = create_unformatted_list() #wont need this, will just be self.unformatted_list
	q = len(uf)
	while(i<j and p<q):
		if(obj[i][2] == "" and format_flags['FT'] == 0):
			returnList.append(uf[p])
			while(obj[i][1] == ""):
				i = i + 1
			p = p + 1
		elif(obj[i][2] != ""):
			ID_formatters(obj[i][2]) #i think it needs self aswell when its in a function
	
	# if(obj[0][2] != ""):
		# print("this is a thing: " + obj[0][2])
	# if(obj[0][2] == ""):
		# print("nothing here :(")
	# else:
		# print("its here!: "+ obj[0][2])
	# print(len(obj))
	# baby = 0
	# balloon = [1,2,3,4,5,6,7,8,9]
	# while(baby < len(balloon)):
		# print(balloon[baby])
		# baby = baby + 2
		
def ID_formatters(obj):
	formatterType = re.split(r" ", obj)
	if formatterType[0][1:] in format_flags:
		if(formatterType[0][1:] == "LM"):
			try:
				int(formatterType[1][0])
				format_flags["LMNum"] = int(formatterType[1])
			except ValueError:
				format_flags["LMNum"] = format_flags["LMNum"] + int(formatterType[1])
				
				if(int(format_flags['LMNum']) > int(format_flags['LWNum'])-20):
					format_flags['LMNum'] = int(format_flags['LWNum']) - 20	
				
				if(int(format_flags['LMNum']) < 0):
					format_flags['LMNum'] = 0
		elif(formatterType[0][1:] == "FT"):
			if(formatterType[1] == "on"):
				format_flags["FT"] = 1
			elif(formatterType[1] == "off"):
				format_flags["FT"] = 0
			else:
				#include a print out to the error file here for invlide input
				return
		elif(formatterType[0][1:] == "LW"):
			try:
				format_flags["LWNum"] = int(formatterType[1])
			except ValueError:
				#print an error
				return
			format_flags["FT"] = 1
			format_flags["LW"] = 1
			
		else:
			format_flags[formatterType[0][1:]] = 1
			try:
				format_flags[formatterType[0][1:]+"Num"] = formatterType[1]
			except ValueError:
				#include a print out to the error file here aswell
				return
	else:
		#include a print out to the error file here for invalid input
		return
	return

if __name__ == "__main__":
	main()