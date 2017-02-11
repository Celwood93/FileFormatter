#Cameron Elwood
#V00152812
#November 10, 2016
#Seng 265

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
							'NL' : 0}
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
				for lines in fileinput.iniput(largs):
					self.outputs = self.outputs + lines
	
	#takes in the input and parses it through a series of regex commands.
	def create_list(self):
		#regex description
		#the first group (before the or, not groups) looks for new line character at the start of the line
		#the second looks for a new line character after a new line character, including white space and a new line infront of it
		#these 2 are the group that holds solo new line characters + white space
		#the third looks for format commands, and is group three, the second group is the format commands with any trailing characters (for error handling)
		#the last group just collects any other input lines, that dont fall into the other groups
		
		obj = re.findall(r"((?<!.)\n|(?<=\n) +(?=\n))|(?<!.)((\.[FL][SWMT] ?[\w\+\-]+)(?:.+)?)|([^\n]+)", self.outputs) #regex1
		#obj[0] refers to solo new lines, as in a \n after another \n
		#obj[1] refers to an error statment with format commands
		#obj[2] refers to valid format commands
		#obj[3] refers to everything else (so the text to be formatted)
		lengthOfInput = len(obj)
		lineNum = 0
		while(lineNum < lengthOfInput):
			if(obj[lineNum][2] != ""):
				if(obj[lineNum][2] != obj[lineNum][1]):
					sys.stderr.write("Error on ine: "+str(lineNum) + "\nRemoving text: " + obj[lineNum][1][len(obj[lineNum][2]):])
				self.__ID_formatters(obj[lineNum][2], lineNum)
				lineNum = lineNum + 1
			elif(self._Formatter__format_flags["FT"] == 1):
				if(obj[lineNum][3] != ""):
					strg = ""
					while(lineNum < lengthOfInput and obj[lineNum][2] == "" and obj[lineNum][0] == ""):
						#regex description
						#this will target white space characters that are not inbetween 2 characters
						#the first group will look for a white space ahead of it, then trailing white spaces after (this catches 1 of the 2+ white spaces between words)
						#the second group catches white space at the very start of the string since the previous command wont catch groups that are only one long
						#which is bad if its at the very start and wont work
						#the next one looks for white space up to a new line character (trailing white space)
						#the next line catches white space inbetween letters aswell, but in a different circumstance
						#the last one catches white space up to a word, without removing the word
						#alot of these overlap alot, and it could probably be optimized, but it was very challenging to
						#make it grab all the white space while avoiding white space i wanted to keep
						strglist = re.split(r"(?<=\s) +|^ +(?=\s)| (?= +[\n])|(?<=.) +(?![\w.—\-,\":!?'[\](){}<> ])|^ (?=\w)", obj[lineNum][3]) #regex2
						i = 0
						strgSeg = ""
						len(strglist)
						while(i < len(strglist)):
							strgSeg = strgSeg + strglist[i]
							i = i + 1
						check = re.findall(r" \.", strgSeg)	#this hints at the fact of an error. its no match found run time is significantly faster then the more detailed one.
															#This has a huge impact on efficiency for no match returns
						if(check != []):
						#regex desctiption
						#this will be used after " \." regex has found a match, it will then search for either an invalid (ie space before it) format command and replace it with a space
							strgSegSection = re.subn(r" \.L[WSM] ?\d?\d? ?| \.FT ?o?[nf]?f? ?", " ", strgSeg) #regex3 remove invalid '.' commands and leave a single white spaces between the words
							strgSeg = strgSegSection[0]
							if(strgSegSection[1] != 0):
								sys.stderr.write("Improper use of format command on line: " + str(lineNum))
						#regex description
						#used to make sure there are spaces between each line of input
						strgSegTwo = re.sub(r"$", ' ', strgSeg) 
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
					#regex description
					#this will collect groups of words that are dictated by the widthcount (LWNum) and will not run break up words, and always have start and end with a character value that is not
					#a space
					#probably could be done better, but it seemed pritty fast and accurate
					regExp = r"(?<![\w\.\-[\](){}><!—\"?,\-;:']).{1," + str(widthCount-1) + "}[^ ](?![\w.,;<[\](){}>—:\-?\"!'])" #regex5
					groups = re.findall(regExp, strg)
					if(self._Formatter__format_flags["LS"] == 1 and self._Formatter__format_flags["FT"] == 1):
						formatLineEnd = "\n"
					for lines in groups:
						if(lines != ""):
							self.returnList.append(formatLineString + lines + formatLineEnd*int(self._Formatter__format_flags["LSNum"]))	
			if(lineNum < lengthOfInput and obj[lineNum][0] != ""):
				self.returnList.append("\n"*(int(self._Formatter__format_flags["FT"])*int(self._Formatter__format_flags["LSNum"])))
				lineNum = lineNum + 1
			if(lineNum < lengthOfInput and obj[lineNum][3] != "" and self._Formatter__format_flags["FT"] == 0):
				self.returnList.append(obj[lineNum][3])
				lineNum = lineNum + 1
	
	#this method identifys the formatter flag which has been caught by the regex. It has a large amount of error catching involved for invalid inputs
	def ID_formatters(self, obj, lineNum):
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
							self._Formatter__format_flags['LMNum'] = int(self._Formatter__format_flags['LWNum']) - 20		
						if(int(self._Formatter__format_flags['LMNum']) < 0):
							self._Formatter__format_flags['LMNum'] = 0
							
					except ValueError:
						sys.stderr.write("invalid paramater for LM: " + str(formatterType[1]) + " on line: " + lineNum)#LM error handler
						return
				self._Formatter__format_flags["LM"] = 1
			elif(formatterType[0][1:] == "FT"):
				if(formatterType[1] == "on"):
					self._Formatter__format_flags["FT"] = 1
				elif(formatterType[1] == "off"):
					self._Formatter__format_flags["FT"] = 0
				else:
					sys.stderr.write("invalid paramater for FT: " + str(formatterType[1]) + " on line: " + lineNum)#FT error handler
					return
			elif(formatterType[0][1:] == "LW"):
				try:
					self._Formatter__format_flags["LWNum"] = int(formatterType[1])
				except ValueError:
					sys.stderr.write("invalid paramater for LW: " + str(formatterType[1]) + " on line: " + lineNum)#LW error handler
					return
				self._Formatter__format_flags["FT"] = 1
				self._Formatter__format_flags["LW"] = 1
			
			else:
				try:
					int(formatterType[1][0]) #this will try to make a - sign an int, which will be an error for LS
					if(int(formatterType[1]) > 2 and str(formatterType[0][1:]) == "LS"):
						int("+") #this will just throw an error if the LS num is greater then 2, this will thrown an error always so we skip all the formatting sutff.
					self._Formatter__format_flags[formatterType[0][1:]+"Num"] = formatterType[1]
					self._Formatter__format_flags[formatterType[0][1:]] = 1
				except ValueError:
					sys.stderr.write("invlad format command due to paramaters: " + str(obj) + " on line: " + str(lineNum)) #every other command error handler for invalid input (right now just LS)
					return
		else:
			sys.stderr.write("invalid command: " + str(obj) + " on line: "+ str(lineNum))#invalid command error handler
		return
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
