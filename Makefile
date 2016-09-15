all:
	gcc ppmrw.c -o ppmrw

run:
	./ppmrw 6 in6.ppm out.ppm

clean:
	rm ppmrw
	rm out.ppm
	clear
