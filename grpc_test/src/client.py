import grpc
import time
import service_pb2
import service_pb2_grpc

def run():
    with grpc.insecure_channel('192.168.2.101:50078') as channel:
        stub = service_pb2_grpc.DACStub(channel)
        loginfo = service_pb2.LoginInfo(account="tu001", password="tu001_")

        start = time.time()
        factor = service_pb2.Factor(name="test_factor_shun",
                                    type="high",
                                    author="hjiang",
                                    createtime="2019-01-01 10:10:10",
                                    description="This is the end of the world",
                                    remark="zhangjiang")
        factor_req = service_pb2.FactorRequest(loginfo = loginfo, factor = factor)
        response = stub.CreateFactor(factor_req)
        print(time.time() - start)
        print(response)
        
        start = time.time()
        request = service_pb2.FcAclRequest(loginfo = loginfo, factorname = "test_factor_shun", factortype = "high", operation = 1)
        response = stub.CheckFcAcl(request)
        print(time.time() - start)
        print(response)


if __name__ == '__main__':
    run()
