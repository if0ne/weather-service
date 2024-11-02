FROM drogonframework/drogon

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make

CMD ["./build/weather-service"]

EXPOSE 8002
