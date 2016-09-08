all:
	gcc ppmrw.c -o ppmrw

run:
	./ppmrw 6 in.ppm out.ppm

clean:
	rm ppmrw
