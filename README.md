<div align="center">

  <!-- Project badge -->
  <a href=".">
    <img src="assets/README/minitalkm.png">
  </a>

  <!-- Project name -->
  <h1>minitalk</h1>

  <!-- Short description -->
  <p>A small data exchange program using UNIX signals.</p>

  <!-- Info badges -->
  <img src="https://img.shields.io/badge/Score-125%2F100-brightgreen?style=for-the-badge&labelColor=black" alt="Score">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&labelColor=black" alt="Language">
  <br>
  <img src="https://img.shields.io/github/last-commit/sdevsantiago/minitalk?display_timestamp=committer&style=for-the-badge&labelColor=black" alt="Last commit">
  <br>
  <img src="https://github.com/sdevsantiago/minitalk/actions/workflows/norminette.yml/badge.svg">
  <img src="https://github.com/sdevsantiago/minitalk/actions/workflows/makefile.yml/badge.svg">

</div>

---

## ℹ️ About Project

> PROJECT PURPOSE

DETAILED INFO

For detailed info, refer to this project [subject](docs/en.subject.pdf).

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Make utility
- Unix-like system (Linux, macOS, WSL)

### Install prerequisites

- Debian/Ubuntu

  ```bash
  sudo apt install build-essential
  ```

## 🔧 Build

1. **Clone the repository:**
    ```bash
    git clone https://github.com/sdevsantiago/minitalk.git
    cd Libft
    ```

2. **Compile the project:**
    ```bash
    make         # Full compilation
    make $(NAME) # Compile mandatory only
    make bonus   # Compile bonus only
    make DEBUG=1 # Compile with debug flags
    ```

3. **Clean build files:**
    ```bash
    make clean  # Remove object files
    make fclean # Remove all generated files
    make re     # Rebuild everything from scratch
    ```

#### Available Make Targets

| Command | Description |
|---------|-------------|
| `make` | Compiles all |
| `make all` | Same as `make` |
| `make clean` | Remove object files (*.o) |
| `make fclean` | Remove object files and binaries |
| `make re` | Clean and rebuild everything |

## 👨‍💻 Usage

### Basic Usage

- Run the server in one terminal, it's PID will be shown
```bash
./server
```

- Run the client in another terminal
```bash
./client <server_pid> <message>

./client <server_pid> $(head -c <n_chars> /dev/zero | tr '\0' '<character>')
```


## 📏 Norminette

The code strictly complies with 42's **Norminette v4**:

```bash
norminette *.c *.h
```

More info in the official [Norminette](https://github.com/42school/norminette) repository.

## 🙇‍♂️ Special thanks

- [lrcouto](https://github.com/lrcouto) and [ayogun](https://github.com/ayogun) for creating and publishing, respectively, the [42-project-badges](https://github.com/ayogun/42-project-badges) repository.
- [gcamerli](https://github.com/gcamerli) for creating the [42unlicense](https://github.com/gcamerli/42unlicense) repository.

## ⚖️ License

<div align="center">

<a href="./LICENSE">
<img src="https://img.shields.io/badge/License-42_Unlicense-red?style=for-the-badge&labelColor=black">
</a>

</div>

**This work is published under the terms of [42 Unlicense](LICENSE).** This means you are free to use, modify, and share this software.
