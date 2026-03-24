# Philosophers

## Description

This project implements the Dining Philosophers problem using POSIX
threads and mutexes.

Each philosopher alternates between thinking, eating, and sleeping.
The simulation stops when a philosopher dies or, if the optional meal
limit is provided, when every philosopher has eaten enough times.

## Compilation

Build from inside the mandatory directory:

```sh
make
```

Rebuild from scratch:

```sh
make re
```

Remove object files:

```sh
make clean
```

Remove object files and the executable:

```sh
make fclean
```

## Usage

Run the program from inside `philo/`:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo 4 410 200 200
./philo 5 800 200 200 7
```

## Output

The program prints events in this format:

```text
timestamp philosopher_id action
```

Possible actions are:

- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`
