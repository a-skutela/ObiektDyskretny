build:
	g++ -std=c++11 ../src/lab1.cpp ../src/ARXModel/ARXModel.cpp ../src/Serialization/serialization.cpp -o lab1

build_win:
	g++ -std=c++11 ../src/lab1.cpp ../src/ARXModel/ARXModel.cpp ../src/Serialization/serialization.cpp  -o lab1.exe

run: build
	./lab1

run_win: build_win
	./lab1.exe

lab2_build:
	g++ -std=c++11 ../src/lab2.cpp ../src/ARXModel/ARXModel.cpp ../src/Serialization/serialization.cpp ../src/Regulator/PIDRegulator.cpp ../src/Feedback/FeedbackLoop.cpp -o lab2

lab2_run:
	./lab2

lab2_build_win:
	g++ -std=c++11 ../src/lab2.cpp ../src/ARXModel/ARXModel.cpp ../src/Serialization/serialization.cpp ../src/Regulator/PIDRegulator.cpp ../src/Feedback/FeedbackLoop.cpp -o lab2.exe

lab2_run_win:
	./lab2.exe

	
lab3_build_win:
	g++ -std=c++11 ../src/lab3.cpp ../src/ARXModel/ARXModel.cpp ../src/Serialization/serialization.cpp ../src/Regulator/PIDRegulator.cpp ../src/Feedback/FeedbackLoop.cpp ../src/SignalGeneration/ConstantSignal.cpp ../src/SignalGeneration/RectSignal.cpp ../src/SignalGeneration/SinSignal.cpp ../src/SignalGeneration/TriangleSignal.cpp ../src/SignalGeneration/WhiteNoiseSignal.cpp ../src/SignalGeneration/Decorators/SignalDecorator.cpp ../src/SignalGeneration/Decorators/AddSinDecorator.cpp ../src/SignalGeneration/Decorators/AddRectDecorator.cpp ../src/SignalGeneration/Decorators/AddTriangleDecorator.cpp ../src/SignalGeneration/Decorators/AddWhiteNoiseDecorator.cpp ../src/SignalGeneration/Decorators/AddConstantDecorator.cpp ../src/SignalGeneration/Decorators/ClampDecorator.cpp -o lab3.exe

lab3_run_win:
	./lab3.exe