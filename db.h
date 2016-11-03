#ifndef DB_H_
#define DB_H_

int newdb(const char *);
sqlite3 *opendb(const char *);
int checkdb(const char *);

#endif
