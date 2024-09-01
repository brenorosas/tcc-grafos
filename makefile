generate-input:
	g++ -std=c++20 input_generator.cpp -lcurl && ./a.out

run-main:
	g++ -std=c++20 main.cpp && ./a.out
