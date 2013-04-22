simple_password
===============

generate password using crypt_r and recursively crack it

main.h --> Common include file

crack.cpp --> crack password

Makefile --> Makefile to generate binaries

README.md --> This file

simple_passwd.cpp --> generate hashed secret file


$ make --> generate binaries

$ ./gen_passwd --> Initialize a secret file with a password

$ ./crack --> crack a secret file (Only password with limited number of digits can be cracked)
