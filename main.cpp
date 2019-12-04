#include <iostream>

#define GENOME_LENGTH 8
#define MAX_ATTACKS 28

int F = 0; // Sum total of fitnesses
int N = 0; // Number of individuals in the population
float PM = 0.0; // Probablity of mutation

struct Individual {
    int gene[GENOME_LENGTH] = {};
    std::string gene_str = "";
    int number_of_attacks = 0;
    int fitness = 0;
    int fitness_subinterval_from = 0;
    int fitness_subinterval_to = 0;
};

void createRandomGene(Individual *);
void countAttacks(Individual *);
void displayChessBoardByIndividual(const Individual *);
void computeAllFitnessSubintervals(Individual **);
void rouletteWheelSelection(Individual **, Individual **);
void crossover(Individual **, Individual **);
void mutation(Individual **);
Individual *foundFittestIndividual(Individual **population);

int main() {
    srand(time(nullptr));
    std::cout << "[==== 8 Queens attack problem ====]" << std::endl;
    do {
        std::cout << "Enter an number of individuals: ";
        std::cin >> N;
        std::cout << "Enter the probability of mutation (ex. 0.005): ";
        std::cin >> PM;
    } while (N & 1); // N should be an even number
    Individual *population[N]; // Population of individuals
    Individual *matingPool[2]; // Mating pool
    Individual *fittestIndividual = nullptr; // Final fittest individual with fitness = 28
    int ng = 1; // Number of generations

    for(int i = 0; i < N; i++) {
        population[i] = new Individual;
        createRandomGene(population[i]);
        countAttacks(population[i]);
        population[i]->fitness = MAX_ATTACKS - population[i]->number_of_attacks;
        if(population[i]->fitness == MAX_ATTACKS) {
            fittestIndividual = population[i];
            break;
        }
        std::cout << "G(" << i << "): " << population[i]->gene_str << " ; Noa = " << population[i]->number_of_attacks << " ; Fitness = " << population[i]->fitness << std::endl;
        displayChessBoardByIndividual(population[i]);
        std::cout << std::endl;
    }

    while(fittestIndividual == nullptr) {
        computeAllFitnessSubintervals(population);
        rouletteWheelSelection(population, matingPool);
        crossover(matingPool, population);
        if((fittestIndividual = foundFittestIndividual(population)) != nullptr) break;
        mutation(matingPool);
        computeAllFitnessSubintervals(population);
        fittestIndividual = foundFittestIndividual(population);
        ng++;
    }

    std::cout << "[+] Found fittest individual: " << fittestIndividual << "; Noa (number of attacks): " << fittestIndividual->number_of_attacks << "; Fitness: " << fittestIndividual->fitness << "; Genes: " << fittestIndividual->gene_str << std::endl;
    std::cout << std::endl;
    displayChessBoardByIndividual(fittestIndividual);
    std::cout << "\n[+] Fittest individual found after " << ng << " generations" << std::endl;

    return 0;
}

void rouletteWheelSelection(Individual **population, Individual **matingPool) {
    std::cout << "[-] Roulette wheel selection..." << std::endl;
    int c = 0;
    do {
        int random = rand() % F;
        for(int i = 0; i < N; i++) {
            if(random >= population[i]->fitness_subinterval_from && random < population[i]->fitness_subinterval_to) {
                matingPool[c] = population[i];
                c++;
                if(c >= 2) break;
            }
        }
    } while(c < 2);
}

void crossover(Individual **matingPool, Individual **population) {
    std::cout << "[-] Crossover..." << std::endl;
    int crosssite = rand() % GENOME_LENGTH + 1;
    for(int g = GENOME_LENGTH - 1; g > crosssite; g--) {
        int t = matingPool[0]->gene[g];
        matingPool[0]->gene[g] = matingPool[1]->gene[g];
        matingPool[1]->gene[g] = t;
    }
    matingPool[0]->gene_str = "";
    matingPool[1]->gene_str = "";
    for(int g = 0; g < GENOME_LENGTH; g++) {
        matingPool[0]->gene_str += std::to_string(matingPool[0]->gene[g]) + "-";
    }
    matingPool[0]->gene_str = matingPool[0]->gene_str.substr(0, matingPool[0]->gene_str.size() - 1);
    for(int g = 0; g < GENOME_LENGTH; g++) {
        matingPool[1]->gene_str += std::to_string(matingPool[1]->gene[g]) + "-";
    }
    matingPool[1]->gene_str = matingPool[1]->gene_str.substr(0, matingPool[1]->gene_str.size() - 1);
    countAttacks(matingPool[0]);
    countAttacks(matingPool[1]);
    matingPool[0]->fitness = MAX_ATTACKS - matingPool[0]->number_of_attacks;
    matingPool[1]->fitness = MAX_ATTACKS - matingPool[1]->number_of_attacks;
    computeAllFitnessSubintervals(population);
}

void mutation(Individual **matingPool) {
    std::cout << "[-] Mutation..." << std::endl;
    int r = rand() % (int)(1 / PM) + 1;
    for(int i = 0; i < 2; i++) {
        bool geneMutated = false;
        for(int j = 0; j < GENOME_LENGTH; j++) {
            int r1 = rand() % (int)(1 / PM) + 1;
            if(r1 == r) {
                int r2 = rand() % GENOME_LENGTH + 1;
                matingPool[i]->gene[j] = r2;
                geneMutated = true;
            }
        }
        if(geneMutated) {
            matingPool[i]->gene_str = "";
            for(int g = 0; g < GENOME_LENGTH; g++) {
                matingPool[i]->gene_str += std::to_string(matingPool[i]->gene[g]) + "-";
            }
            matingPool[i]->gene_str = matingPool[i]->gene_str.substr(0, matingPool[i]->gene_str.size() - 1);
            countAttacks(matingPool[i]);
            matingPool[i]->fitness = MAX_ATTACKS - matingPool[i]->number_of_attacks;
        }
    }
}

Individual *foundFittestIndividual(Individual **population) {
    Individual *bestIndividual = nullptr;
    for(int i = 0; i < N; i++) {
        if(population[i]->fitness == MAX_ATTACKS) {
            bestIndividual = population[i];
            break;
        }
    }
    return bestIndividual;
}

void computeAllFitnessSubintervals(Individual **population) {
    F = 0;
    for(int i = 0; i < N; i++) {
        if(i == 0) {
            population[i]->fitness_subinterval_from = 0;
            population[i]->fitness_subinterval_to = population[i]->fitness;
        } else {
            population[i]->fitness_subinterval_from = population[i - 1]->fitness_subinterval_to;
            population[i]->fitness_subinterval_to = population[i - 1]->fitness_subinterval_to + population[i]->fitness;
        }
        F += population[i]->fitness;
    }
}

void createRandomGene(Individual *individual) {
    for(int i = 0; i < GENOME_LENGTH; i++) {
        int r = rand() % GENOME_LENGTH + 1;
        individual->gene[i] = r;
        individual->gene_str += std::to_string(r) + "-";
    }
    individual->gene_str = individual->gene_str.substr(0, individual->gene_str.size() - 1);
}

void countAttacks(Individual *individual) {
    individual->number_of_attacks = 0;
    for(int i = 0; i < GENOME_LENGTH; i++) {
        for(int j = i + 1; j < GENOME_LENGTH; j++) {
            if(individual->gene[i] == individual->gene[j]) individual->number_of_attacks++;
            if(individual->gene[j] - individual->gene[i] == j - i) individual->number_of_attacks++;
            if(individual->gene[j] - individual->gene[i] == i - j) individual->number_of_attacks++;
        }
    }
}

void displayChessBoardByIndividual(const Individual *individual) {
    int i = 0;
    int nextPointY = GENOME_LENGTH - individual->gene[i];
    char pawns[GENOME_LENGTH][GENOME_LENGTH];
    for(int y = 0; y < GENOME_LENGTH; y++) {
        for(int x = 0; x < GENOME_LENGTH; x++) {
            pawns[y][x] = 'O';
        }
    }
    for(int c = 0; c < GENOME_LENGTH; c++) {
        pawns[nextPointY][c] = 'X';
        i++;
        nextPointY = GENOME_LENGTH - individual->gene[i];
    }
    for(int y = 0; y < GENOME_LENGTH; y++) {
        for(int x = 0; x < GENOME_LENGTH; x++) {
            std::cout << pawns[y][x] << "  ";
        }
        std::cout << std::endl;
    }
}