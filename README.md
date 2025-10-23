# Pipex

Pipex is a re-implementation of the Unix shell pipeline mechanic written in C.
It accepts an input file (or a `here_doc` stream), a sequence of commands, and
an output file, then chains those commands together using POSIX pipes. The
project is part of the 42 cursus and emphasises process management, file
descriptor juggling, and robust error handling.

## Features

- Execute an arbitrary number of shell commands connected by pipes.
- Support for `here_doc` to feed a heredoc as the first command's standard
  input.
- Automatic lookup of commands inside the user's `PATH` with graceful
  fallbacks when an executable cannot be found.
- Detailed error reporting propagated through the exit code of the final
  command in the pipeline.
- Memory tracking via the bundled `garbadge` collector to avoid leaks even
  when exiting early.

## Project Layout

```
├── includes/          # Public headers and core data structures
├── src/
│   ├── commands/      # Queue creation, pipe wiring, execution helpers
│   ├── env/           # Minimal getenv implementation
│   ├── errors/        # Error reporting helpers
│   ├── parsing/       # Argument splitting and command parsing
│   └── utils/         # Safe wrappers around common syscalls
├── dependencies/
│   └── ft_libc/       # 42-style libc reimplementation (cloned on demand)
├── Makefile           # Build rules
└── README.md          # You are here
```

## Building

The only external requirement is `make` and a POSIX-compatible C toolchain.
The bundled `Makefile` automatically fetches the custom `ft_libc` dependency if
it is not already present.

```bash
make
```

This produces the `pipex` executable in the project root. To clean the build
artifacts, run `make clean`; to remove the executable as well, run `make fclean`.

## Usage

Pipex mimics the shell syntax `cmd1 < infile | cmd2 | ... | cmdN > outfile`.
The general invocation pattern is:

```bash
./pipex infile "cmd1 arg1 arg2" "cmd2 arg" ... "cmdN" outfile
```

When the first argument is `here_doc`, Pipex reads from standard input until it
encounters the limiter string and then uses the captured text as the input of
the first command:

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

### Examples

Run a two-stage pipeline that filters lines containing "error" and counts them:

```bash
./pipex logs.txt "grep error" "wc -l" report.txt
```

Use `here_doc` to feed inline content to a command chain:

```bash
./pipex here_doc EOF "cat" "tr '[:lower:]' '[:upper:]'" output.txt
# Type lines of text, end with EOF on its own line
```

### Embedding Pipex in Another Program

Because Pipex is a standalone binary, you can launch it from another C
application using `execve`. The snippet below forwards an existing argument
vector to Pipex after forking:

```c
#include <unistd.h>
#include <stdlib.h>

int run_pipex(char *in, char *out)
{
    char *argv[] = {
        "./pipex",
        in,
        "grep error",
        "wc -l",
        out,
        NULL
    };

    if (fork() == 0) {
        execve(argv[0], argv, NULL);
        _exit(EXIT_FAILURE);
    }
    return 0;
}
```

## Exit Codes

- `0`: the full pipeline executed successfully.
- `1`: a generic failure occurred (e.g., invalid arguments, I/O errors).
- `127`: the last command was not found.

Other exit codes bubble up from the final command in the pipeline.

## License

This project follows the rules of the 42 school curriculum; consult your campus
regarding reuse or redistribution policies.
