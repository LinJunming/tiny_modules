ALL=main libencoder.so

libencoder.so:encoder.cpp
	g++ -o $@ -fPIC  $< -shared -I./ -std=c++11
main:
	g++ -o $@ main.cpp -L./ -lencoder -std=c++11 -lpthread

clean:
	rm -rf $(ALL) *.o *.so