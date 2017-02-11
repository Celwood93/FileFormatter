# Error Handling Documentation

All errors are printed to a document instead of the console as an aditional feature
some errors are not printed to the console and only to the document.

---

## Error Handling in identify_output

**In the event that an invalid filename is given**  
the user will be prompted to instead use stdin

---

## Error Handling in create_list

**In the event of a valid format command being followed by input characters**  
For example:

`.LW 30 hello world`

would be reduced to

`.LW 30`

However, if the "hello world" part of the text was desired in  
output, it could instead be moved to be in the fourth group of  
obj via regex command alternations.

The error will cause an output of: 

`Error on line: (lineNumber) Removing text: (removed text)`

**In the event of a formatting command that is out of place**  
For example

`Hello .LW 30 world`

The .LW 30 would be replaced with a white space. 

`Hello world`

This only works if .LW has a white space before it.   
Only numbers will be removed after .LW, and only 2 digits.  
.FT will remove 'off', 'on', 'o', 'of', 'onf' from either  
the start of a word or as an entire word, for example:

`Hello .FT offString World`

will return

`Hello String World`

The error will cause an output of:  

`Importer use of format command on line (lineNumber)`

To include a format command in the text, put quotation marks  
or brackets around the command, for example

`Hello ".FT off" String World`

would be unchanged

---

## Error Handling in ID_formatters
**In the event of a format command that is not part of the registered format command list**  
the command is ignored and an error statment will be printed:

`invalid command: (command and paramater) on line: (lineNumber)`

**In the event of an invalid paramater for LM**  
The flag will not be set and an error statment will be printed:

`invalid paramater for LM: (paramater) on line: (lineNum)`

Automatic handling for out of boundary paramaters is also include in LM handling.
This will print an error to an error file, but not to the console:

`LM paramater adjusted on line: (lineNum)`


**In the event of an invalid FT paramater**  
The flag will not change
and an error statment will be printed:

`invalid paramater for FT: (paramater) on line: (lineNum)`

**In the event of an invalid LS command**  
An error is printed and nothing is updated. This includes having  
the input number be negative or having the number be greater then 2

Error print statment:

`invlad format command due to paramaters: (format command + paramater) on line: (lineNumber)`

---
