all:
	g++ -g -Wall TimeCode.cpp PaintDryTimer.cpp -o pdt
	g++ -std=c++11 -Wall TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa
	g++ -g -Wall TimeCode.cpp TimeCodeTests.cpp -o tct

run:
	./nasa
	./pdt
	./tct

try: all run