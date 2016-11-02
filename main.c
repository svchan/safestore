#include <stdio.h>
#include <stdlib.h>
#include <histedit.h>
#include <string.h>
#include <err.h>
#include "db.h"

int getargs(char *, char **);
char *prompt(EditLine *);

int main(int argc, char *argv[])
{
	char *line, **args;
	EditLine *el;
	int c;

	el = el_init("safestore", stdin, stdout, stderr);
	el_set(el, EL_PROMPT, &prompt);

	while (1) {
		line = el_gets(el, &c);
		line[c - 1] = '\0';

		if (strncmp("args", line, 4) == 0) {
			getargs(line, args);
			puts(bargs[0]);
		}
		if (strncmp("exit", line, 4) == 0)
			break;
		else if (strncmp("new", line, 3) == 0) 
			newdb(line + 4);
	}
	
	free(line);
	return 0;
}

int getargs(char *buf, char **args)
{
	int spaces = 1, i;
	char *p, *tmp;

	p = buf; 
	while (*p) {
		if ((*p == ' ')) {
			*p = '\0';
			spaces++;
		}
		p++;
	}

	args = malloc(sizeof(char *) * spaces);
	if (args == NULL)
		err(1, "main.c: getarg malloc");
	
	p = buf;
	for (i = 0; i < spaces; i++) {
		tmp = malloc(strlen(p) + 1);
		if (tmp == NULL)
			err(1, "main.c: getarg malloc");
		memcpy(tmp, p, (strlen(p) + 1));
		args[0] = tmp;
	}
	printf("%d\n", spaces);

	return 0;
}

char *prompt(EditLine *el)
{
	return "safestore> ";
}
