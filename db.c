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
	char *sql = "CREATE TABLE PW(" \ 
		"NAME        TEXT," \
         	"KEY         TEXT);";

	if (checkdir(name) == 1) {
		puts("Database already exists");
		return 1;
	}
	
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

int insertdb(sqlite3 *db, char *name, char *key)
{
	char *sql, *errmsg;
	int rc;

	asprintf(&sql, "INSERT INTO PW(NAME, KEY) " \
		       "VALUES (%s, %s);", name, key);

	rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL Error db.c : %s", errmsg);
		sqlite3_free(errmsg);
	}

	free(sql);
	return 0;
}

sqlite3 *opendb(const char *name)
{
	sqlite3 *ret;
	int rc;

	if (checkdir(name) != 1) {
		puts("db does not exsist");
		return NULL;
	}

	rc = sqlite3_open(name, &ret);
	if (rc != 0)
		err(1, "db.c: opendb");
	else
		puts("db opened");

	return ret;
}

int closedb(sqlite3 *db)
{
	if (db == NULL)
		return 1;
	
	sqlite3_close(db);
}

int checkdir(const char *name)
{
	DIR *dirp;
	struct dirent *dirent;
	size_t len;

	len = strlen(name);
	dirp = opendir("/home/sv/devel/safestore/");
	if (dirp != NULL) {
		while ((dirent = readdir(dirp)) != NULL)
			if (dirent->d_namlen == len &&
			    strcmp(dirent->d_name, name) == 0) {
			    	closedir(dirp);
				return 1;
			}
		closedir(dirp);
	} else
		err(2, "db.c: checkdir");
}
