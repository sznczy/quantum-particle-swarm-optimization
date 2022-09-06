# Quantum Particle Swarm Optimizer
## _General-purpose Mathematical Optimizer_

## About

This is a general-purpose mathematical optimization library for C++. By applying this library, you can solve single- and multi-variable optimizations, constrained and unconstrained problems and even non-convex problems.

## Theory behind the algorithm

This solution is based on combination of particle swarm optimization and delta potential well from quantum physics.
The mathematical optimizer inspired by quantum mechanics is a new way to enhance classical optimization techniques to have higher chance in finding of global minima, while the C++ implementation is a great tool for faster running.

## Vision

I wanted to provide a reliable tool that applies state-of-the-art approaches and it is also fast and easily integrable into other programming environments as well. For example, wrapping C++ code into .Net environment or into Python, is also possible and helps a lot to improve the running speed of your projects as well.

## How different is it from original Particle Swarm Optimization?

- Delta potential well is applied to calculate movements of particles
- Velocity parameter is removed
- Linearly rebalancing explorative and exploiting ratios to controll the importance of the local and global minima for the swarm
- There re only two required input parameters from the user:
    - swarm size
    - dimension of the problem
- Thus, no apriori knowledge is necessary to find better solutions. This solver is ready to manage your problem without any fine-tuning.

## Building and running project

This library requires [GCC](https://github.com/gcc-mirror/gcc) v9+ to run.

After cloning the repo, you can run the tester:

```sh
cd quantum-particle-swarm-optimization
g++ -O -Wall tester.cpp -o tester
./tester
```

You can expect an output like this:

```sh
Goldstein price function benchmarking
Swarm size: 300
Total iterations: 1000
Global Best: 3
Griewank function benchmarking
Swarm size: 200
Total iterations: 1000
Global Best: 0
Schwefel function benchmarking
Swarm size: 200
Total iterations: 2000
Global Best: 947.507
```

## Want to add to your existing project?

Apply this header in your C++ project:

```
#include "qpso.h"
```

Then you can call the Swarm Optimizer:

```
QPSOptimiser::Swarm testSwarm(200, 30, foo); // swarmSize = 200; dimensions = 30; problem to solve = foo
testSwarm.solve(1000); // Iteration number is 1000
testSwarm.print_results(true); // If argument is True, then it will show the calculated arguments' values
```

## Development

Want to contribute? Great!

Please send a message to me and we can discuss.

## License

MIT
