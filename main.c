#include <stdio.h>
#include <stdlib.h>
#include <histedit.h>
#include <string.h>
#include <sqlite3.h>
#include <err.h>
#include "db.h"

char **getargs(char *);
char *prompt(EditLine *);

int main(int argc, char *argv[])
{
	char *line, **args;
	sqlite3 *db;
	EditLine *el;
	int c;

	el = el_init("safestore", stdin, stdout, stderr);
	el_set(el, EL_PROMPT, &prompt);

	while (1) {
		line = el_gets(el, &c);
		line[c - 1] = '\0';

		if (strncmp("exit", line, 4) == 0)
			break;
		else if (strncmp("new", line, 3) == 0) {
			args = getargs(line);
			if (args[1] != NULL)
				newdb(args[1]);
		} else if(strncmp("open", line, 4) == 0 ) {
			args = getargs(line);
			if (args[1] != NULL)
				db = opendb(args[1]);
		} else if(strncmp("close", line, 4) == 0) {
			if (db != NULL)
				closedb(db);
		} else if(strncmp("insert", line, 6) == 0) {
			insertdb(db, "asdf\0", "asdf\0");
		}


	}

	free(args);
	free(line);
	return 0;
}

char **getargs(char *buf)
{
	int spaces = 1, i;
	char *p, *tmp, **args;

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
		args[i] = tmp;
		p = strchr(p, '\0');
		p++;
	}

	return args;
}

char *prompt(EditLine *el)
{
	return "safestore> ";
}
