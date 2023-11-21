#!/bin/bash

docker build -t ezdb:1.0.0 .

# Run the Docker container
docker run -it ezdb:1.0.0