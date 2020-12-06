main: build/objects/Object.o build/objects/GravField.o build/objects/Field.o build/objects/logging.o build/objects/ObjectHandler.o build/objects/Model.o build/objects/GenericBaseClass.o build/objects/3DBody.o build/objects/BinaryReader.o build/objects/BinaryCreator.o build/objects/BinaryShared.o build/objects/main.o
		g++-8 build/objects/Object.o build/objects/GravField.o build/objects/Field.o build/objects/logging.o build/objects/ObjectHandler.o build/objects/Model.o build/objects/GenericBaseClass.o build/objects/3DBody.o build/objects/BinaryReader.o build/objects/BinaryCreator.o build/objects/BinaryShared.o build/objects/main.o -o ./physics-model -lstdc++fs

clean:
		rm -r ./build/objects
		mkdir ./build/objects
		rm ./physics-model

makefile:
		python3 ./build/generate_makefile.py

build/objects/Object.o: ./physics/Object.cpp ./physics/Object.h
		g++-8 -c ./physics/Object.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/Object.o

build/objects/GravField.o: ./physics/GravField.cpp ./physics/GravField.h
		g++-8 -c ./physics/GravField.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/GravField.o

build/objects/Field.o: ./physics/Field.cpp ./physics/Field.h
		g++-8 -c ./physics/Field.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/Field.o

build/objects/logging.o: ./control/logging.cpp ./control/logging.h
		g++-8 -c ./control/logging.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/logging.o

build/objects/ObjectHandler.o: ./control/ObjectHandler.cpp ./control/ObjectHandler.h
		g++-8 -c ./control/ObjectHandler.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/ObjectHandler.o

build/objects/Model.o: ./control/Model.cpp ./control/Model.h
		g++-8 -c ./control/Model.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/Model.o

build/objects/GenericBaseClass.o: ./control/GenericBaseClass.cpp ./control/GenericBaseClass.h
		g++-8 -c ./control/GenericBaseClass.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/GenericBaseClass.o

build/objects/3DBody.o: ./3d/3DBody.cpp ./3d/3DBody.h
		g++-8 -c ./3d/3DBody.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/3DBody.o

build/objects/BinaryReader.o: ./serialization/BinaryReader.cpp ./serialization/BinaryReader.h
		g++-8 -c ./serialization/BinaryReader.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/BinaryReader.o

build/objects/BinaryCreator.o: ./serialization/BinaryCreator.cpp ./serialization/BinaryCreator.h
		g++-8 -c ./serialization/BinaryCreator.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/BinaryCreator.o

build/objects/BinaryShared.o: ./serialization/BinaryShared.cpp ./serialization/BinaryShared.h
		g++-8 -c ./serialization/BinaryShared.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/BinaryShared.o

build/objects/main.o: ./main.cpp
		g++-8 -c ./main.cpp -I . -Wall -Wno-sign-compare -std=c++17 -o ./build/objects/main.o

