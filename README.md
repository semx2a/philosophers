# Project: Philosophers

## Overview

The Philosophers project is a deep dive into the world of multithreading in C.It focuses on the fundamentals of threading processes and introduces the concept of mutexes.

The project is themed around the famous ["Dining Philosophers"](https://en.wikipedia.org/wiki/Dining_philosophers_problem) problem, a classic conundrum used widely in computer science to understand synchronization issues in concurrent programming.

## Skills and Knowledge

- **Multithreading:** Gain hands-on experience with creating and managing multiple threads in a C program. This is a crucial skill for developing efficient software that can take advantage of multi-core processors.
- **Mutexes:** Learn how to use mutexes to prevent data races and ensure that threads don't use the same resources at the same time, thus avoiding [deadlock](https://en.wikipedia.org/wiki/Deadlock). This is a fundamental concept in concurrent programming that helps ensure data integrity and consistency.
- **Problem Solving:** Tackle the "Dining Philosophers" problem, a complex problem that requires careful planning and coordination of threads. This has helped me improve my algorithmic thinking skills and ability to solve complex problems.

## Usage

To compile the program, run the following command:

```bash
make
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

## Display

The program will display the following information:
```bash
11800 1 has taken a fork
11800 5 is sleeping
11800 4 has taken a fork
11800 4 has taken a fork
11800 4 is eating
```

The first number is the timestamp, the second number is the philosopher's ID, and the third is the action the philosopher is performing.

## Testing

The project has been tested with the following test cases:

- **Basic Test:** 5 800 200 200 - No philosophers should die.
- **Basic Test:** 4 410 200 200 - No philosophers should die.
- **Basic Test:** 5 800 200 200 7 - No philosophers should die, and the simulation should stop when all philosophers have eaten 7 times.

- **Basic Test:** 1 800 200 200 - The philosopher should not eat and die.
- **Basic Test:** 4 310 200 100 - A philosophers should die.
- **Basic Test:** 2 60 60 60 - No philosophers should die.
