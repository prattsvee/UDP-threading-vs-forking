Instructions for Compiling and Running the Server, Client, and Calculator Programs

1. Compilation Steps:

Server:
   $ make -f server.mk



Client:
   $ make -f client.mk



2. Running the Programs:

Server:
   $ ./server

Client:
   $ ./client


TO EDIT SERVER IP OR PORT -
   edit them in the server_config.h and client_config.h files

3. Interacting with the Server:

- Once the server is running, it listens for UDP connections on port 8888.
- The client program can be used to send commands to the server via UDP.
- The commands supported by the server include:
  - HELO: Displays a welcome message.
  - HELP: Displays a list of available commands.
  - BYE: Closes the connection.
  - AREA, VOL, TEMP, WGT: Selects a mode for unit conversion.
  - Conversion requests based on the selected mode (e.g., "SQRMT SQRFT 10").

4. Interacting with the Calculator:

- The calculator program provides functions for unit conversion in the following categories: area, volume, temperature, and weight.
- Execute the calculator program to access these conversion functions directly.
- The available conversion functions can be called with appropriate input parameters.
- For example, to convert 10 square meters to square feet:
  $ ./calculator
  > SQRMT SQRFT 10
