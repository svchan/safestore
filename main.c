#include <stdio.h>
#include <stdlib.h>
#include <histedit.h>
#include <string.h>
#include <err.h>
#include "db.h"

char *prompt(EditLine *);

int main(int argc, char *argv[])
{
	char *line;
	EditLine *el;
	int c;


	el = el_init("safestore", stdin, stdout, stderr);
	el_set(el, EL_PROMPT, &prompt);

	while(1) {
		line = el_gets(el, &c);
		line[c - 1] = '\0';

		if (strncmp("exit", line, 4) == 0)
			break;
		else if (strncmp("new", line, 3) == 0) 
			newdb(line + 4);
	}
	
	return 0;
}



char *prompt(EditLine *el)
{
	return "safestore> ";
}
