FROM gcc:latest

WORKDIR /app

COPY . /app/

RUN make

# use this for linear search implementation
CMD [ "/app/ezdb" ]

# Use this for hashtable implementation
# CMD ["/app/ezdb", "-h"]