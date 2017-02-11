#Cameron Elwood
#V00152812
#November 10, 2016
#Seng 265
#in this i have added 2 additional features.
#
#the first is all errors will be printed to an error file, where they will be documented.
#the file either is called Error_(filename).txt or Error_input_record.txt
#
#
#the second is a new formating system. Encryption. having .EC key will cause all text after it to be encrypted by the key
#EC = encryptKey
#the way the encryption works is by taking the key, and converting it into a list of integer values from 0 - 64, correspoding
#with values from a white space, a-z, A-Z, and 0-9 these are stored in a dictionary
#then the string (that is to be encrypted) will have each character (except for punctuation) increased by the corresponding
#key value. This will wrap around as to be sure it doesnt leave the proper range.
#a second dictionary will use the numbers to address the letters corresponding with them, and will be put into a string to be returned.
#
#DC = decryptKey
#this command will work the same as EC, except it will take in the encrypted text and use a key to decrpyt the text. it takes a string
#aswell, which needs to be the same as the key the encrypted the text.
#
#SC = StopCryption
#this command will stop the Cryption process, wether its encrypting or decrypting. it takes in no additional paramaters, and will ignore any given.
#
#for information on the regex commands, refer to the original version.

import re
import sys
import fileinput

class Formatter:
	#initializes a formatter object. taking in 2 strings which are checked as the stream for input. if both are invalid it uses stdin
	def __init__(self, filename, inputs):
		self.filename = filename
		self.inputs = inputs
		self.outputs = ""
		self.returnList = []
		self.__format_flags = {'LW' : 0,
							'LWNum' : 0,
							'LS' : 0,
							'LSNum' : 0,
							'LM' : 0,
							'LMNum' : 0,
							'FT' : 0,
							'EC' : 0,
							'ECKey' : "",
							'DC' : 0,
							'DCKey' : "",
							'SC' : 0}
		self.__identify_output()
		self.__create_list()
		
	#this identifys the input, if both values are None then it uses stdin, if the filename is valid it reads in the file, if the input array is valid it uses the input array
	#if the file doesnt exist it uses stdin	
	def identify_output(self):
			if self.filename == None:
				if self.inputs != None:
					for line in self.inputs:
						self.outputs = self.outputs + line + '\n'
					self.outputs = self.outputs[:-1]
					return
		
			try:	
				for lines in fileinput.input():
					self.outputs = self.outputs + lines
		
			except FileNotFoundError:
				print("file not found, type input: ")
				largs = []
				for lines in fileinput.input(largs):
					self.outputs = self.outputs + lines
	
	#takes in the input and parses it through a series of regex commands.
	def create_list(self):
		if(self.filename != None):
			input = "Error_" + str(self.filename)
		else:
			input = "Error_input_record.txt"
		f = open(input, 'w')
		obj = re.findall(r"((?<!.)\n|(?<=\n) +(?=\n))|(?<!.)((\.[FL][SWMT] ?[\w\+\-]+|\.[EDS]C ?(?:\w+)?)(?:.+)?)|([^\n]+)", self.outputs) #regex1
		#obj[0] refers to solo new lines, as in a \n after another \n
		#obj[1] refers to an error statment with format commands
		#obj[2] refers to valid format commands
		#obj[3] refers to everything else (so the text to be formatted)
		lengthOfInput = len(obj)
		lineNum = 0
		while(lineNum < lengthOfInput):
			if(obj[lineNum][2] != ""):
				if(obj[lineNum][2] != obj[lineNum][1]):
					f.write("Error on line: "+str(lineNum) + "\nRemoving text: " + obj[lineNum][1][len(obj[lineNum][2]):] + "\n")
				self.__ID_formatters(obj[lineNum][2], lineNum, f)
				lineNum = lineNum + 1
			elif(self._Formatter__format_flags["FT"] == 1):
				if(obj[lineNum][3] != ""):
					strg = ""
					while(lineNum < lengthOfInput and obj[lineNum][2] == "" and obj[lineNum][0] == ""):
						strglist = re.split(r"(?<=\s) +|^ +(?=\s)| (?= +[\n])|(?<=.) +(?![\w.—\-,\":!?'[\](){}<> ])|^ (?=\w)", obj[lineNum][3]) #regex2
						i = 0
						strgSeg = ""
						while(i < len(strglist)):
							strgSeg = strgSeg + strglist[i]
							i = i + 1
						check = re.findall(r" \.", strgSeg)	#this hints at the fact of an error. its no match found run time is significantly faster then the more detailed one.
															#This has a huge impact on efficiency for no match returns
						if(check != []):
							strgSegSection = re.subn(r" \.L[WSM] ?\d?\d? ?| \.FT ?o?[nf]?f? ?", " ", strgSeg) #regex3 remove invalid '.' commands and leave a single white spaces between the words
							strgSeg = strgSegSection[0]
							if(strgSegSection[1] != 0):
								f.write("Improper use of format command on line: " + str(lineNum) + "\n")
						strgSegTwo = re.sub(r"$", ' ', strgSeg) #regex 4, used to make sure there are spaces between each line of input
						strg = strg + strgSegTwo
						lineNum = lineNum + 1
					formatLineString = ""
					formatLineEnd = ""
					marginCount = self._Formatter__format_flags["LMNum"]
					widthCount = self._Formatter__format_flags["LWNum"]
					if(self._Formatter__format_flags["FT"] == 1):
						while(marginCount > 0):
							formatLineString = formatLineString + " "
							marginCount = marginCount - 1
							widthCount = widthCount - 1
					regExp = r"(?<![\w\.\-[\](){}><!—\"?,\-;:']).{1," + str(widthCount-1) + "}[^ ](?![\w.,;<[\](){}>—:\-?\"!'])" #regex5
					groups = re.findall(regExp, strg)
					if(self._Formatter__format_flags["LS"] == 1 and self._Formatter__format_flags["FT"] == 1):
						formatLineEnd = "\n"
					for lines in groups:
						if(lines != ""):
							if(self._Formatter__format_flags["EC"] == 1 or self._Formatter__format_flags["DC"] == 1):
								lines = self.__crypt_text(lines)
							self.returnList.append(formatLineString + lines + formatLineEnd*int(self._Formatter__format_flags["LSNum"]))	
			if(lineNum < lengthOfInput and obj[lineNum][0] != ""):
				self.returnList.append("\n"*(int(self._Formatter__format_flags["FT"])*int(self._Formatter__format_flags["LSNum"])))
				lineNum = lineNum + 1
			if(lineNum < lengthOfInput and obj[lineNum][3] != "" and self._Formatter__format_flags["FT"] == 0):
				self.returnList.append(obj[lineNum][3])
				lineNum = lineNum + 1
	
	#this method identifys the formatter flag which has been caught by the regex. It has a large amount of error catching involved for invalid inputs
	def ID_formatters(self, obj, lineNum, f):
		formatterType = re.split(r" ", obj)
		if formatterType[0][1:] in self._Formatter__format_flags:
			if(formatterType[0][1:] == "LM"):
				try:
					int(formatterType[1][0])
					self._Formatter__format_flags["LMNum"] = int(formatterType[1])
				except ValueError:
					try:
						self._Formatter__format_flags["LMNum"] = self._Formatter__format_flags["LMNum"] + int(formatterType[1])
						
						if(int(self._Formatter__format_flags['LMNum']) > int(self._Formatter__format_flags['LWNum']) - 20):
							f.write("LMNum to large, reducing to be usable. LMNum: " +self._Formatter__format_flags['LMNum']+ "\n")
							self._Formatter__format_flags['LMNum'] = int(self._Formatter__format_flags['LWNum']) - 20	
								
						if(int(self._Formatter__format_flags['LMNum']) < 0):
							f.write("LMNum negative, resetting to 0. LMNum: " +self._Formatter__format_flags['LMNum']+ "\n")
							self._Formatter__format_flags['LMNum'] = 0
							
					except ValueError:
						f.write("invalid paramater for LM: " + str(formatterType[1]) + " on line: " + lineNum + "\n")#LM error handler
						return
				self._Formatter__format_flags["LM"] = 1
			elif(formatterType[0][1:] == "FT"):
				if(formatterType[1] == "on"):
					self._Formatter__format_flags["FT"] = 1
				elif(formatterType[1] == "off"):
					self._Formatter__format_flags["FT"] = 0
				else:
					f.write("invalid paramater for FT: " + str(formatterType[1]) + " on line: " + lineNum + "\n")#FT error handler
					return
			elif(formatterType[0][1:] == "EC"):
				if(self._Formatter__format_flags["DC"] == 1):
					f.write("error, DC flag set and EC Flag command before SC command on line: "+str(lineNum)+"\n")
					return
				elif(formatterType[1] == ""):
					f.write("error, EC input invalid. Line: " +str(lineNum)+"\n")
					return
				else:
					self._Formatter__format_flags["EC"] = 1
					self._Formatter__format_flags["ECKey"] = formatterType[1]
			elif(formatterType[0][1:] == "DC"):
				if(self._Formatter__format_flags["EC"] == 1):
					f.write("error, EC flag set and DC Flag command before SC command on line: "+str(lineNum)+ "\n")
					return
				elif(formatterType[1] == ""):
					f.write("error, DC input invalid. Line: " +str(lineNum)+ "\n")
				else:
					self._Formatter__format_flags["DC"] = 1
					self._Formatter__format_flags["DCKey"] = formatterType[1]
			elif(formatterType[0][1:] == "SC"):
				if(self._Formatter__format_flags["EC"] == 0 and self._Formatter__format_flags["DC"] == 0):
					f.write("error, EC flag or DC flag not set and SC command called: "+str(lineNum) + "\n")
					return
				else:
					self._Formatter__format_flags["DC"] = 0
					self._Formatter__format_flags["EC"] = 0
			elif(formatterType[0][1:] == "LW"):
				try:
					self._Formatter__format_flags["LWNum"] = int(formatterType[1])
				except ValueError:
					f.write("invalid paramater for LW: " + str(formatterType[1]) + " on line: " + lineNum + "\n")#LW error handler
					return
				self._Formatter__format_flags["FT"] = 1
				self._Formatter__format_flags["LW"] = 1
			
			else:
				try:
					int(formatterType[0][1:]) #this will try to make a - sign an int, which will be an error for LS
					if(int(formatterType[1]) > 2 and str(formatterType[0][1:]) == "LS"):
						int("+") #this will just throw an error if the LS num is greater then 2, this will thrown an error always so we skip all the formatting sutff.
					self._Formatter__format_flags[formatterType[0][1:]+"Num"] = formatterType[1]
					self._Formatter__format_flags[formatterType[0][1:]] = 1
				except ValueError:
					f.write("invlad format command due to paramaters: " + str(obj) + " on line: " + str(lineNum) + "\n") #every other command error handler for invalid input (right now just LS)
					return
		else:
			f.write("invalid command: " + str(obj) + " on line: "+ str(lineNum) + "\n")#invalid command error handler
		return
	#this is where the text is encrypted into lines
	#it takes in a line of text
	#it returns a line of text
	#it only doesnt encrypt punctuation, and it deals with this using try except, but i wouldent call it an error
	#since it is intended to work this way
	def crypt_text(self, line):
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
		if(self._Formatter__format_flags["EC"] == 1):
			numkey = []
			i = 0
			k = len(self._Formatter__format_flags["ECKey"])
			while(i < k):
				numkey.append(alphabet[self._Formatter__format_flags["ECKey"][i]])
				i = i + 1
			i = 0
			j = 0
			returnline = ""
			f = 1
			while(f<2):
				try:
					try:
						num = int(alphabet[line[i]])
					except KeyError:
						returnline = returnline + line[i]
						i = i + 1
						continue
					num2 = int(numkey[j])
					newnum = num + num2
					if(newnum > 62):
						newnum = newnum % 62
					returnline = returnline + alphabet2[str(newnum)]
					i = i + 1
					if(j < len(numkey)-1):
						j = j + 1
					else:
						j = 0
				except IndexError:
					f = 5	
			return returnline
		elif(self._Formatter__format_flags["DC"] == 1):
			numkey = []
			i = 0
			k = len(self._Formatter__format_flags["DCKey"])
			while(i < k):
				numkey.append(alphabet[self._Formatter__format_flags["DCKey"][i]])
				i = i + 1
			i = 0
			j = 0
			returnline = ""
			f = 1
			while(f<2):
				try:
					try:
						num = int(alphabet[line[i]])
					except KeyError:
						returnline = returnline + line[i]
						i = i + 1
						continue
					num2 = int(numkey[j])
					newnum = num - num2
					if(newnum < 0):
						newnum = newnum % 62
					returnline = returnline + alphabet2[str(newnum)]
					i = i + 1
					if(j < len(numkey)-1):
						j = j + 1
					else:
						j = 0
				except IndexError:
					f = 5
			return returnline
		else:
			return line
	
	#new lines at the end of the file that are undesired are removed here. otherwise it just returns the list of formatted strings
	def get_lines(self):
		if(self._Formatter__format_flags["FT"] == 1 and self._Formatter__format_flags["LS"] == 1):
			holderString = self.returnList[-1]
			clearnewlines = re.sub(r"\n", "", holderString)
			clearnewlines = "".join(clearnewlines)
			if(clearnewlines != ""):
				del self.returnList[-1]
				self.returnList.append(clearnewlines)
		return self.returnList
	__create_list = create_list
	__ID_formatters = ID_formatters
	__identify_output = identify_output
	__crypt_text = crypt_text
