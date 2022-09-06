#include "qpso.h"

// Description of the problem: https://www.sfu.ca/~ssurjano/griewank.html
double griewankBenchmarkFunc(double* pos, int dim){

    double first_value = 0;
    double second_value = 1.0;

    for (int i=0; i<dim; i++){
        if (pos[i] >= 600 || pos[i] <= -600){
            return INFINITY;
        }
    }

    for(int i=1; i<dim; i++){
        first_value += pow(pos[i],2)/4000.0;
    }

    for(int i=1; i<dim; i++){
        second_value *= cos(pos[i]/sqrt(i+1));
    }
    
    return  first_value - second_value + 1;
}

// Please find additional information on Schwefel Optimisation problem here:
// https://www.sfu.ca/~ssurjano/schwef.html
double schwefelBenchmarkFunc(double* pos, int dim){


    double sum = 0;
    for (int i=0; i<dim; i++){

        // x vector has a boundary of (-500, 500)
        if (pos[i] >= 500 || pos[i] <= -500){
            return INFINITY;
        }
        sum += pos[i]*sin(sqrt(abs(pos[i])));
    }

    double y = 418.9829*dim - sum;

    // Constr.: f(x) > 0
    y = (y > 0) ? y : INFINITY;

    return y;

}

// Source of the optimisation problem: https://www.sfu.ca/~ssurjano/goldpr.html
double goldsteinPriceBenchmarkFunc(double* pos, int dim){

    double x1 = pos[0];
    double x2 = pos[1];

    if(x1 > 2 || x2 > 2 || x1 < -2 || x2 < -2){
        return INFINITY;
    }

    double fact1a = pow(x1 + x2 + 1, 2);
    double fact1b = 19.0 - (14*x1) + 3*pow(x1, 2) - (14*x2) + (6*x1*x2) + 3*pow(x2, 2);
    double fact1 = 1 + (fact1a*fact1b);

    double fact2a = pow(2*x1 - 3*x2, 2);
    double fact2b = 18 - 32*(x1) + 12*pow(x1, 2) + (48*x2) - (36*x1*x2) + 27*pow(x2, 2);
    double fact2 = 30 + (fact2a*fact2b);

    double y = fact1*fact2;
    
    return y;
}

void runSchwefelTesting(){

    cout << "Schwefel function benchmarking" << "\n";

    QPSOptimiser::Swarm testSwarm(200, 30, schwefelBenchmarkFunc);

    testSwarm.solve(2000);
    testSwarm.printResults(false);

}

void runGriewankTesting(){

    cout << "Griewank function benchmarking" << "\n";

    QPSOptimiser::Swarm testSwarm(200, 30, griewankBenchmarkFunc);

    testSwarm.solve(1000);
    testSwarm.printResults(false);
}

void runGoldsteinPriceTest(){

    cout << "Goldstein price function benchmarking" << "\n";

    QPSOptimiser::Swarm testSwarm(300, 30, goldsteinPriceBenchmarkFunc);
    testSwarm.solve(1000);
    testSwarm.printResults(false);

}

int main(){

    runGoldsteinPriceTest(); 

    runGriewankTesting();

    runSchwefelTesting();

}
