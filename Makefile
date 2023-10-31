clean:
	rm ladyherring

run:
	g++ src/ladyherring.cc src/Search.cc src/Evaluate.cc -o ladyherring
	./ladyherring