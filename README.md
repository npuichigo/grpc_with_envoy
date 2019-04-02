# grpc_with_envoy

This repository is used to test whether the envoy gRPC-JSON transcoder has size limit when using google.api.HttpBody as output (https://github.com/envoyproxy/envoy/issues/6441). Besides, it shows how to use grpc together with envoy to provide restful apis for online services.

## Quick Start Guide

Clone the repository and dependencies:
```sh
git clone https://github.com/npuichigo/grpc_with_envoy.git
cd grpc_with_envoy
# Pull the dependent third_party repositories
git submodule update --init
```

From the repo root directory, test your service with docker-compose:
```sh
docker-compose up
```

Or deploy your service with docker swarm:

```sh
$ docker stack deploy -c docker-compose.yml grpc_service
```

Test restful api with curl:

```
curl localhost:8080/echo -4 -X POST -H "Content-Type:application/json" -d '{"input": "testdata/small.wav"}'
```

To shutdown:

```sh
docker stack rm grpc_service
```

## Test with grpc client

Just start with the docker image grpc-server:
```sh
docker run -it --name your_name grpc-server /bin/bash
./build/bin/grpc_server
```

Open another terminal to use the grpc client:
```sh
docker exec -it your_name /bin/bash
./build/bin/grpc_test_client --filename testdata/small.wav
```
