FROM gcc:latest
WORKDIR /app

COPY . .
RUN g++ task-8-2.cpp -o fight

CMD ["./fight"]

#mostafa
