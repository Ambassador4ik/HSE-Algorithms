.PHONY: run gen-tests full analyze run-docker clean

run:
	cmake -S ./src/cpp/grader/ -B ./src/cpp/grader/build
	cmake --build ./src/cpp/grader/build
	cd ./src/cpp/grader && ./build/AutoGrader
	mv ./src/cpp/grader/results.csv ./src/py

gen-tests:
	cmake -S ./src/cpp/tests/ -B ./src/cpp/tests/build
	cmake --build ./src/cpp/tests/build
	cd ./src/cpp/tests && ./build/TestGen

full:
	make gen-tests
	make run

analyze:
	python ./src/py/main.py

run-docker:
	docker-compose build grader
	docker-compose run grader

clean:
	rm -rf ./src/cpp/grader/build/*
	rm -rf ./src/cpp/tests/build/*
	rm -rf ./src/cpp/tests/tests.json
	rm -rf ./src/cpp/grader/results.csv
