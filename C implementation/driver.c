


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formatter.h"

int main(int argc, char *argv[]) {
	char **result;
    
	char *lines[] = {
		".LW30 30",
		"While there    are enough characters   here to",
		"fill",
		"   at least one line, there is",
		"plenty",
		"of",
		"            white space that needs to be",
		"eliminated",
		"from the original",
		"         text file."	
	};
	char **line;


	result = format_lines(lines, 10);

	if (result == NULL) {
		printf("%s: it appears 'format_lines' is not yet complete\n",
			argv[0]);
		exit(1);
	}

	for (line = result; *line != NULL; line++) {
		printf("%s", *line);
		free(*line);
	}
	free(line);

	exit(0);
}
