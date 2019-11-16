All:
	g++ ./source/a.cpp -O1 -o a.out
	g++ ./source/b.cpp -O1 -o b.out
	g++ ./source/c.cpp -O1 -o c.out
	g++ ./source/d.cpp -O1 -o d.out
	g++ ./source/e.cpp -O1 -o e.out
	g++ ./source/f.cpp -O1 -o f.out

a:
	g++ ./source/a.cpp -O1 -o a.out

b:
	g++ ./source/b.cpp -O1 -o b.out

c:
	g++ ./source/c.cpp -O1 -o c.out

d:
	g++ ./source/d.cpp -O1 -o d.out

e:
	g++ ./source/e.cpp -O1 -o e.out
f:
	g++ ./source/f.cpp -O1 -o f.out

run:
	make All
	./a.out
	./b.out
	./c.out
	./d.out
	./e.out
	./f.out