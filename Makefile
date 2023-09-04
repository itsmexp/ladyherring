test:
	g++ ladyherring.cc -o ladyherring
	./ladyherring < ladyherring.in

clean:
	rm ladyherring

run:
	g++ ladyherring.cc Search.cc Evaluate.cc -o ladyherring
	./ladyherring