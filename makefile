generate-input:
	g++ -std=c++20 input_generator.cpp -lcurl && ./a.out

run-main:
	g++ -std=c++20 main.cpp && ./a.out

run-grasp:
	g++ -std=c++20 grasp.cpp && ./a.out

run-memetic:
	g++ -std=c++20 memetic.cpp && ./a.out

run-genetic:
	g++ -std=c++20 genetic.cpp && ./a.out