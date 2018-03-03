.PHONY: test

test:
	g++ test_main.cpp word_counter.cpp fortune.cpp -std=c++1z -lpthread -o test
	./test

clean:
	rm -f test
