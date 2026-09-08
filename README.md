# License

This project is licensed under the [MIT License](LICENSE).

# Descritption

This is a simplified implementation of an HTTP/1.1 server aimed at learning about TCP/IP applications and the HTTP protocol specifically.

# Workflow

## TCP server layer

Creates sockets and accepts the client.

## HTTP parser layer

Reads received bytes and parses them into a HTTP message.

# Current Status

The HTTP request parser is implemented, and the server currently responds with `505 Not Implemented`.

The project is intended as a learning exercise.