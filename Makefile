main: build/objects/Object.o build/objects/GravField.o build/objects/Field.o build/objects/logging.o build/objects/ObjectHandler.o build/objects/Model.o build/objects/GenericBaseClass.o build/objects/3DBody.o build/objects/BinaryReader.o build/objects/BinaryCreator.o build/objects/BinaryShared.o build/objects/main.o
		g++ build/objects/Object.o build/objects/GravField.o build/objects/Field.o build/objects/logging.o build/objects/ObjectHandler.o build/objects/Model.o build/objects/GenericBaseClass.o build/objects/3DBody.o build/objects/BinaryReader.o build/objects/BinaryCreator.o build/objects/BinaryShared.o build/objects/main.o -o ./physics-model -lstdc++fs

debug: build/objects/Object-debug.o build/objects/GravField-debug.o build/objects/Field-debug.o build/objects/logging-debug.o build/objects/ObjectHandler-debug.o build/objects/Model-debug.o build/objects/GenericBaseClass-debug.o build/objects/3DBody-debug.o build/objects/BinaryReader-debug.o build/objects/BinaryCreator-debug.o build/objects/BinaryShared-debug.o build/objects/main-debug.o
		g++ build/objects/Object-debug.o build/objects/GravField-debug.o build/objects/Field-debug.o build/objects/logging-debug.o build/objects/ObjectHandler-debug.o build/objects/Model-debug.o build/objects/GenericBaseClass-debug.o build/objects/3DBody-debug.o build/objects/BinaryReader-debug.o build/objects/BinaryCreator-debug.o build/objects/BinaryShared-debug.o build/objects/main-debug.o -g -o ./physics-model -lstdc++fs

clean:
		rm -r ./build/objects
		mkdir ./build/objects
		rm ./physics-model

makefile:
		python3 ./build/generate_makefile.py

build/objects/Object.o: ./physics/Object.cpp ./physics/Object.h
		g++ -c ./physics/Object.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/Object.o

build/objects/Object-debug.o: ./physics/Object.cpp ./physics/Object.h
		g++ -c ./physics/Object.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/Object-debug.o

build/objects/GravField.o: ./physics/GravField.cpp ./physics/GravField.h
		g++ -c ./physics/GravField.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/GravField.o

build/objects/GravField-debug.o: ./physics/GravField.cpp ./physics/GravField.h
		g++ -c ./physics/GravField.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/GravField-debug.o

build/objects/Field.o: ./physics/Field.cpp ./physics/Field.h
		g++ -c ./physics/Field.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/Field.o

build/objects/Field-debug.o: ./physics/Field.cpp ./physics/Field.h
		g++ -c ./physics/Field.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/Field-debug.o

build/objects/logging.o: ./control/logging.cpp ./control/logging.h
		g++ -c ./control/logging.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/logging.o

build/objects/logging-debug.o: ./control/logging.cpp ./control/logging.h
		g++ -c ./control/logging.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/logging-debug.o

build/objects/ObjectHandler.o: ./control/ObjectHandler.cpp ./control/ObjectHandler.h
		g++ -c ./control/ObjectHandler.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/ObjectHandler.o

build/objects/ObjectHandler-debug.o: ./control/ObjectHandler.cpp ./control/ObjectHandler.h
		g++ -c ./control/ObjectHandler.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/ObjectHandler-debug.o

build/objects/Model.o: ./control/Model.cpp ./control/Model.h
		g++ -c ./control/Model.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/Model.o

build/objects/Model-debug.o: ./control/Model.cpp ./control/Model.h
		g++ -c ./control/Model.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/Model-debug.o

build/objects/GenericBaseClass.o: ./control/GenericBaseClass.cpp ./control/GenericBaseClass.h
		g++ -c ./control/GenericBaseClass.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/GenericBaseClass.o

build/objects/GenericBaseClass-debug.o: ./control/GenericBaseClass.cpp ./control/GenericBaseClass.h
		g++ -c ./control/GenericBaseClass.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/GenericBaseClass-debug.o

build/objects/3DBody.o: ./3d/3DBody.cpp ./3d/3DBody.h
		g++ -c ./3d/3DBody.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/3DBody.o

build/objects/3DBody-debug.o: ./3d/3DBody.cpp ./3d/3DBody.h
		g++ -c ./3d/3DBody.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/3DBody-debug.o

build/objects/BinaryReader.o: ./serialization/BinaryReader.cpp ./serialization/BinaryReader.h
		g++ -c ./serialization/BinaryReader.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/BinaryReader.o

build/objects/BinaryReader-debug.o: ./serialization/BinaryReader.cpp ./serialization/BinaryReader.h
		g++ -c ./serialization/BinaryReader.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/BinaryReader-debug.o

build/objects/BinaryCreator.o: ./serialization/BinaryCreator.cpp ./serialization/BinaryCreator.h
		g++ -c ./serialization/BinaryCreator.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/BinaryCreator.o

build/objects/BinaryCreator-debug.o: ./serialization/BinaryCreator.cpp ./serialization/BinaryCreator.h
		g++ -c ./serialization/BinaryCreator.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/BinaryCreator-debug.o

build/objects/BinaryShared.o: ./serialization/BinaryShared.cpp ./serialization/BinaryShared.h
		g++ -c ./serialization/BinaryShared.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/BinaryShared.o

build/objects/BinaryShared-debug.o: ./serialization/BinaryShared.cpp ./serialization/BinaryShared.h
		g++ -c ./serialization/BinaryShared.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/BinaryShared-debug.o

build/objects/main.o: ./main.cpp
		g++ -c ./main.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/main.o

build/objects/main-debug.o: ./main.cpp
		g++ -c ./main.cpp -I . -Wall -Wno-sign-compare -std=c++17 -g -o ./build/objects/main-debug.o

