
build:
	g++ -std=c++11 ../src/lab1.cpp ../src/ARXModel/ARXModel.cpp ../src/Serialization/serialization.cpp -o lab1

build_win:
	g++ -std=c++11 ../src/lab1.cpp ../src/ARXModel/ARXModel.cpp ../src/Serialization/serialization.cpp  -o lab1.exe

run: build
	./lab1

run_win: build_win
	./lab1.exe

lab2_build:
	g++ -std=c++11 ../src/lab2.cpp ../src/ARXModel/ARXModel.cpp ../src/Serialization/serialization.cpp ../src/Regulator/PIDRegulator.cpp -o lab2

lab2_run:
	./lab2