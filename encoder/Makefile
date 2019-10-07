ALL=libencoder.so main

TARGET:$(ALL)

libencoder.so:encoder.cpp
	g++ -o $@ -fPIC  $< -shared -I./ -std=c++11 -g

main:main.cpp
	g++ -o $@ $< -L./ -lencoder -std=c++11 -lpthread -g

clean:
	rm -rf $(ALL) *.o *.so