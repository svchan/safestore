#ifndef DB_H_
#define DB_H_

int newdb(const char *);
int insertdb(sqlite3 *, char *, char *);
sqlite3 *opendb(const char *);
int closedb(sqlite3 *);
int checkdb(const char *);

#endif
