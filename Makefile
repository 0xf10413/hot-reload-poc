all: generate-proto client

client:
	cd c++ && make

generate-proto: proto/dummy.proto
	python -m grpc_tools.protoc -I./proto --python_out=python/generated \
		--grpc_python_out=python/generated ./proto/dummy.proto
	protoc -I ./proto --cpp_out=c++/generated proto/dummy.proto
	protoc -I ./proto --grpc_out=c++/generated \
		--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` proto/dummy.proto

run-client: client
	cd c++ && make launch

run-server: generate-proto
	cd python && python main.py
