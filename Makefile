msg:
	@echo 'Targets are: '
	@echo ' producer'
	@echo ' consumer'
	@echo ' run'
	@echo  ' clean'




consumer: ./src/consumer.cpp
	g++ "./src/consumer.cpp" -pthread -o ./out/consumer


producer: ./src/producer.cpp
	g++ "./src/producer.cpp" -pthread -o ./out/producer


run: ./src
	
	make producer
	make consumer
	"start" "./../out/producer.exe shmfile" "&&" "start" "./../out/consumer.exe shmfile"  
# 	/../out/producer shmfile "&" /../out/consumer shmfile

clean:
	rm -f ./out/consumer
	rm -f ./out/producer