# 42HN_philosophers
Summary:

This project aims to understand how threads work and how to communicate between them.

Foreword:

Philosophy (from Greek, philosophia, literally "love of wisdom") is the study of general and fundamental questions about existence, knowledge,
values, reason, mind, and language. Such questions are often posed as problems to be studied or resolved. The term was probably coined by Pythagoras
(c. 570 – 495 BCE). Philosophical methods include questioning, critical discussion, rational argument, and systematic presentation.
Classic philosophical questions include: Is it possible to know anything and to prove it? What is most real? Philosophers also pose more practical and
concrete questions such as: Is there a best way to live? Is it better to be just or unjust (if one can get away with it)? Do humans have free will?

Links:

Wikipedia about threads: https://en.wikipedia.org/wiki/Thread_(computing)

Subject PDF: https://github.com/akliek/42HN_philosophers/blob/master/en.subject.pdf

# Clone
Open a terminal and run following command:
```
git clone <repository url>
```
# Instalation
Then go to created repository and run following command:
```
make
```
# Run
After insatalation you can run simulation by runing following command:
```
./philo <number_of_philosopher> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
# What do these options mean?
```
      ◦ number_of_philosophers: is the number of philosophers and also the number of forks
      ◦ time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds
        after starting his last meal or the beginning of the simulation, it dies
      ◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time
        he will need to keep the two forks.
      ◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend sleeping.
      ◦ number_of_times_each_philosopher_must_eat: argument is optional, if all philosophers eat at least
        ’number_of_times_each_philosopher_must_eat’ the simulation will stop. If not specified, the simulation
        will stop only at the death of a philosopher.
```
