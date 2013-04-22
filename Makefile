
all: gen_passwd crack

gen_passwd: simple_passwd.cpp main.h
	g++ -O3 simple_passwd.cpp -o gen_passwd -lcrypt


crack: crack.cpp main.h
	g++ -O3 crack.cpp -o crack -lcrypt

clean:
	rm gen_passwd crack
