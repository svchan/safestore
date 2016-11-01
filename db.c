#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <err.h>
#include "db.h"

int newdb(const char *name)
{
	char *errmsg;
	sqlite3 *db;
	int rc;
	size_t len;
	DIR *dirp;
	char *sql = "CREATE TABLE PW(" \ 
		"NAME        TEXT," \
         	"KEY         TEXT);";
	struct dirent *dirent;

	/* checks if db already exists */
	len = strlen(name);
	dirp = opendir("/home/sv/devel/safestore/");
	if (dirp != NULL) {
		while ((dirent = readdir(dirp)) != NULL)
			if (dirent->d_namlen == len &&
			      strcmp(dirent->d_name, name) == 0) {
				puts("Database already exists");
				closedir(dirp);
				return 1;
			}
		closedir(dirp);
	} else
		err(1, "db.c: newdb");

	
	
	rc = sqlite3_open(name, &db);
	if (rc != 0)
		err(1, "db.c: newdb");
	else
		puts("New db created.");
	/* init database */
	rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL Error db.c : %s", errmsg);
		sqlite3_free(errmsg);
	}
	
	sqlite3_close(db);

	return 0;
}
