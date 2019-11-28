all: generate-proto

generate-proto:
	python -m grpc_tools.protoc -I./proto --python_out=python/generated \
		--grpc_python_out=python/generated ./proto/dummy.proto
