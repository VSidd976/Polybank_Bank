# Polybank_Bank

Polybank_Bank is a C++ backend service for the PolyBank.  
It provides a RESTful API for ATM and other clients, using modern C++,
Crow as the HTTP framework, PostgreSQL (via libpqxx) as the database,
and CMake as the build system.



## Instalation

Use git to install PolyBank_Bank.

```git
git clone https://github.com/VSidd976/Polybank_Bank.git
```

## Backend Dependencies (UNIX only)

This project is officially supported and tested only on **UNIX-like systems (Linux)**.  
All dependencies are resolved via **CMake + CPM**, except **Asio**,
which must be installed manually for Crow to work correctly.

### Required system packages

- **C++20** compiler (e.g. GCC or Clang)
- **CMake**
- **Asio**
- **PostgreSQL**

### Asio (manual installation – REQUIRED)

Crow depends on standalone **Asio**, and it must be installed manually:

```bash
sudo apt install -y libasio-dev
```

Without this package Crow will not compile correctly.

### CMake dependencies (downloaded automatically via CPM)

These libraries are fetched automatically during CMake configuration:

- **jwt-cpp** (JWT authentication)
- **Crow** (HTTP server)
- **nlohmann/json** (JSON handling)
- **libpqxx** (PostgreSQL C++ client)

No manual installation of these libraries is required.

## Database setup (PostgreSQL + cron)

To run this backend you need a working **PostgreSQL** database.  
The project also uses **cron-based jobs inside PostgreSQL**
to run background logic.

A full PostgreSQL installation and administration guide is out of scope of this README.
Any standard Linux installation of PostgreSQL will work, as long as you can:

- create a database,
- execute `db.sql` in that database (the same one you will use in `db_url`).

## Configuration

Before running the application, you need to create a configuration file `config.json`
in the project root directory based on the provided template `config.example.json`.

You can copy the template with:

```bash
cp config.example.json config.json
```

Then open `config.json` and fill it with your values:

```json
{
  "db_url": "postgresql://<USER>:<PASSWORD>@<HOST>:<PORT>/<DBNAME>",
  "jwt_secret": "your_secret",
  "jwt_expire_sec": 1000,
  "port": 18973
}
```

Where:
- `db_url` – PostgreSQL connection string
- `jwt_secret` – secret key used to sign JWT tokens. Use a long random string in real deployments
- `jwt_expire_sec` – token lifetime in seconds
- `port` – HTTP port where the backend server will listen

## Building

To build the backend, run the following commands in the project root directory:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

After a successful build, the executable and all required runtime files
are placed in the `app` directory inside the `build` folder.

To run the server on UNIX:

```bash
cd build/app
./Executable
```

The backend will start listening on the port specified in `config.json`
and will use the database configured in `db_url`.
