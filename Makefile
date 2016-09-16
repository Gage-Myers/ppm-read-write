all:
	gcc ppmrw.c -o ppmrw

run:
	./ppmrw 6 in.ppm out6.ppm
	./ppmrw 3 in.ppm out3.ppm

clean:
	rm ppmrw
	rm out6.ppm
	rm out3.ppm
	clear
