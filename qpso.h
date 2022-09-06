#include <iostream>
#include <math.h>

using namespace std;

namespace QPSOptimiser{

    class Particle{
    public:
        double *pPosition;
        double *plocalBest;

        void init(int dimensions){
            pPosition = new double[dimensions];
            plocalBest   = new double[dimensions];
        }
    };

    class Swarm{
    public:
        Particle *pParticle;
        double *pGlobalBest;
        int swarmSize_;
        int dim;
        int totalIterations;
        double (*evaluateFunc)(double *pos, int dim);

        Swarm(int swarmSize, int dimensions, double (*evaluateFunc_) (double* pos, int dim)){
            swarmSize_ = swarmSize;
            dim = dimensions;

            pGlobalBest = new double[dimensions];

            pParticle = new Particle[swarmSize];

            for(int i=0;i<swarmSize;i++){
                pParticle[i].init(dim);
            }

            initialise(*evaluateFunc_);
        }

        void printResults(bool showArguments = true){

            if (showArguments)
            {
                for(int i=0; i<dim; i++){
                    cout << "Argument #" + std::to_string(i) + " is equal to " << pGlobalBest[i] << "\n";
                }
            }

            cout << "Swarm size: " << swarmSize_ << "\n";
            cout << "Total iterations: " << totalIterations << "\n";
            cout << "Global Best: " << evaluateFunc(pGlobalBest, dim) << "\n";
        }

        void solve(int totalIters){

            // Set new random seed
            srand(time(0));

            totalIterations = totalIters;

            for(int iter=0; iter<totalIters; iter++){

                // Calculate contraction expansion paramter
                double beta = 0.5+(0.5*(totalIters - iter)/totalIters);

                // Set up tradeoff strategy between exploration and exploitation
                double c1 = ((double)iter / totalIters);
                double c2 = 1.0 - ((double)iter / totalIters);

                for(int i=0; i<swarmSize_; i++){
                    
                    for(int j=0; j<dim; j++){

                        // Generate random values
                        double fuzzyState = getRandom();
                        double randPersonal = getRandom();
                        double randGlobal = getRandom();
                        double u = getRandom();

                        // Calculate delta potential well
                        double La = (randPersonal*c1*pParticle[i].plocalBest[j] + randGlobal*c2*pGlobalBest[j])/(randPersonal*c1 + randGlobal*c2);
                        double randState = (fuzzyState > 0.5) ? 1.0 : -1.0;

                        // Update position of the given Particle
                        pParticle[i].pPosition[j] = La + randState*log(1/u)*beta*abs(La-pParticle[i].pPosition[j]);             
                    }

                    // Update Particle's best finding
                    if(evaluateFunc(pParticle[i].pPosition,dim)<evaluateFunc(pParticle[i].plocalBest,dim)){
                        for(int k=0;k<dim;k++){
                            pParticle[i].plocalBest[k] = pParticle[i].pPosition[k];
                        }
                    }

                    // Update global best finding
                    if(evaluateFunc(pParticle[i].plocalBest,dim)<evaluateFunc(pGlobalBest,dim)){
                        for(int k=0; k<dim; k++){
                            pGlobalBest[k] = pParticle[i].plocalBest[k];
                        }
                    }
                }
            }
        }

    private:
        double getRandom(){
            return ((double) rand()/ RAND_MAX);
        }

        void initialise(double (*evaluateFunc_) (double* pos, int dim))
        {
            evaluateFunc=evaluateFunc_;
            
            for(int j=0;j<dim;j++){
                pGlobalBest[j] = getRandom();
            }

            for(int i=0; i<swarmSize_; i++){
                for(int j=0; j<dim; j++){
                    pParticle[i].pPosition[j] = getRandom();
                    pParticle[i].plocalBest[j] = pParticle[i].pPosition[j];
                }

                if(evaluateFunc(pParticle[i].plocalBest,dim)<evaluateFunc(pGlobalBest, dim)){
                    for(int k=0; k<dim; k++)
                        pGlobalBest[k] = pParticle[i].plocalBest[k];
                }
            }
        }
    };
}