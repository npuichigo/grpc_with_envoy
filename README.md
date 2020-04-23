# grpc_with_envoy

This repository is used to test whether the envoy gRPC-JSON transcoder is able to handle streaming using google.api.HttpBody response. Besides, it shows how to use grpc together with envoy to provide restful apis for online services.

## Quick Start Guide

Clone the repository and dependencies:
```sh
git clone https://github.com/npuichigo/grpc_with_envoy.git
cd grpc_with_envoy
```

From the repo root directory, test your service with docker-compose:
```sh
docker-compose pull
docker-compose up
```

Or deploy your service with docker swarm:

```sh
$ docker stack deploy -c docker-compose.yml grpc_service
```

Test restful api with curl:

```
curl "localhost:8080/get?filename=testdata/music.mp3" -4 -v > test_chunk_music.mp3
```

To shutdown:

```sh
docker stack rm grpc_service
```
