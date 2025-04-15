# Signals
UNIX specific

Standard messages

Each signal has its own meaning

Signals can be caught and interpreted

SIGUSR1 and SIGUSR2 don't have a default behaviour and exist for the programmer to use

Two main functions to interpret signals:
- signal - Handles one single signal
- sigaction - Stores a signal in a struct, which can be assigned to a handler

Send signals:
- kill(pid, signum)

## Signals that can't be interpreted
- SIGKILL - tells the OS to kill (stop) the program
