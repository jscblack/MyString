cc=clang++
exe=main
obj=main.o MyString.o

$(exe):$(obj)
	$(cc) -o $(exe) $(obj)
main.o:main.cpp
	$(cc) -c -Wall -O2 -std=c++17 main.cpp
MyString.o:MyString.cpp
	$(cc) -c -Wall -O2 -std=c++17 MyString.cpp
clean:
	erase .\*.o