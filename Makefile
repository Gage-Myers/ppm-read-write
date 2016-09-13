all:
	gcc ppmrw.c -o ppmrw

run:
	./ppmrw 3 in6.ppm out.ppm

clean:
	rm ppmrw
	clear
