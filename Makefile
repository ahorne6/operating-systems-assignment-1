msg:
	@echo 'Targets are: '
	@echo ' producer'
	@echo ' consumer'
	@echo ' run'
	@echo  ' clean'




consumer: ./consumer.cpp
	g++ "./consumer.cpp" -pthread -o ./out/consumer


producer: ./producer.cpp
	g++ "./producer.cpp" -pthread -o ./out/producer


run: ./src
	
	make producer
	make consumer
	clear
	./out/producer shmfile & ./out/consumer shmfile

clean:
	rm -f ./out/consumer
	rm -f ./out/producer