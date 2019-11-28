import sys
sys.path.append("./generated")
import dummy_pb2_grpc
import dummy_pb2
import grpc
from concurrent import futures
from time import sleep
from contextlib import contextmanager

import logging
logging.getLogger().setLevel(logging.DEBUG)

class Servicer(dummy_pb2_grpc.MqServicer):
    def Start(self, request, context):
        logging.info("Start: request %s and context %s", request, context)
        return dummy_pb2.StartR()

    def Stop(self, request, context):
        logging.info("Stop: request %s and context %s", request, context)
        return dummy_pb2.StopR()

@contextmanager
def autoclose(server):
    server.start()
    yield server
    server.stop()

if __name__ == "__main__":
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    dummy_pb2_grpc.add_MqServicer_to_server(Servicer(), server)
    server.add_insecure_port('[::]:50051')
    with autoclose(server):
        server.wait_for_termination()
