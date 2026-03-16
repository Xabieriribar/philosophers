*This project has been created as part of the 42 curriculum by
xabieriribar.*

# Philosophers

## Description

The **Philosophers** project explores one of the classic problems in
computer science: the **Dining Philosophers Problem**, which illustrates
issues related to **concurrency, synchronization, and resource
sharing**.

In this simulation, several philosophers sit around a table with a fork
placed between each pair of philosophers. They repeat the following
cycle:

1.  Thinking
2.  Eating
3.  Sleeping

To eat, a philosopher must hold **two forks simultaneously**: the one on
their left and the one on their right. Since forks are shared resources,
the program must carefully coordinate access to them to avoid
**deadlocks**, **data races**, and **starvation**.

The goal of the project is to implement a correct and efficient
simulation using **threads and mutexes** in C while respecting strict
timing constraints.

The simulation stops when:

-   A philosopher dies because they did not start eating within
    `time_to_die` milliseconds since their last meal, or
-   All philosophers have eaten a specified number of times (if that
    optional argument is provided).

This project focuses on developing a deep understanding of
**multithreading, synchronization primitives, and timing control**.

------------------------------------------------------------------------

## Instructions

### Compilation

To compile the program, run:

    make

This will generate the executable:

    philo

### Cleaning the project

    make clean

Remove objects and executable:

    make fclean

Recompile everything:

    make re

------------------------------------------------------------------------

## Usage

Run the program with:

    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

### Parameters

  ---------------------------------------------------------------------------------------
  Argument                                    Description
  ------------------------------------------- -------------------------------------------
  number_of_philosophers                      Number of philosophers and forks

  time_to_die                                 Time (ms) before a philosopher dies if they
                                              do not start eating

  time_to_eat                                 Time (ms) spent eating

  time_to_sleep                               Time (ms) spent sleeping

  number_of_times_each_philosopher_must_eat   Optional: simulation stops once all
                                              philosophers eat this many times
  ---------------------------------------------------------------------------------------

### Example

    ./philo 4 410 200 200

Another example with a meal limit:

    ./philo 5 800 200 200 7

The simulation stops once each philosopher has eaten **at least 7
times**.

------------------------------------------------------------------------

## Program Behavior

The program outputs events in the following format:

    timestamp philosopher_id action

Possible actions:

    has taken a fork
    is eating
    is sleeping
    is thinking
    died

Example output:

    0 1 has taken a fork
    0 1 has taken a fork
    0 1 is eating
    200 1 is sleeping
    400 1 is thinking

The timestamp represents the number of milliseconds since the start of
the simulation.

------------------------------------------------------------------------

## Implementation Details

Key design elements of this implementation include:

-   Each philosopher is represented by a thread
-   Each fork is protected by a mutex
-   Shared state such as simulation stop conditions and meal timing are
    protected by dedicated mutexes
-   A monitoring thread continuously checks whether a philosopher has
    died
-   Fork acquisition order alternates between philosophers to reduce the
    risk of deadlock
-   Precise sleep functions are used to maintain accurate timing
    behavior

Synchronization ensures:

-   No two philosophers can hold the same fork simultaneously
-   State updates remain thread-safe
-   Output messages do not overlap

------------------------------------------------------------------------

## Resources

### Documentation

-   POSIX Threads Programming Guide
-   pthread manual pages
-   The Dining Philosophers Problem

Recommended reading:

https://man7.org/linux/man-pages/man7/pthreads.7.html
https://en.wikipedia.org/wiki/Dining_philosophers_problem

------------------------------------------------------------------------

## Use of AI

AI tools were used in a supportive and educational capacity, primarily
for:

-   Reviewing synchronization strategies
-   Debugging timing-related issues
-   Improving documentation clarity
-   Discussing concurrency design decisions

All generated suggestions were reviewed, understood, and adapted before
being applied to the code.
