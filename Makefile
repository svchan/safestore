all: 
	cc main.c db.c -lsqlite3 -ledit -lcurses -o safestore
	strip safestore
debug:
	cc main.c db.c -lsqlite3 -ledit -lcurses -o safestore -g

