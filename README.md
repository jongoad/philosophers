# philosophers

A 42 cursus project to solve a variation of the dining philosophers problem.
<br></br>
## Description
philosophers is a project intended to introduce the concept of multi-threading by solving a variation of the dining philosophers problem. Using mutex locks, the problems of data races and resource sharing must be solved to create a stable simulation.

A full description can be found in the [subject](subject/en.subject.pdf) pdf.
<br></br>
## Usage
The program runs in a very similar manner to the shell implementation, however it does not use the same syntax. Pipex can be run using the following syntax (command and arguments must be wrapped in quotes):
``
$> ./philo [number of philo] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_to_eat]
``

The last argument (number of times for each philosopher to eat) is optional, and the program will run without it.

### Solution
My solution for the mandatory section involved using a rotating mutex-locked queue that controlled the order in which each thread was allowed access to the "forks".

## Bonus Section
The bonus section of philosophers involves solving the same problem, but using processes instead of threads. In this case, semphores must be used instead of mutexes. The additional challenge of the bonus section is how to manage communcation between the main simulation process, and subprocessed with a very restricted set of tools.

### Solution
My solution to the bonus section involved creating a sacrificial "messenger process" for each philospher process. This "messenger thread" did nothing by itself, but when the check_death thread launched from within each philosopher process detected a death had occured, the "messenger process" corresponding to that philosopher was killed. Then the main simulation could check the PID of the child process using a waitpid() call. This allows the entire simulation to quickly be ended by killing all the remaining processes.

## Final Grade
![125/100](img/125.png)