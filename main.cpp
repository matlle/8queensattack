#include <iostream>
#include <vector>

#define GENOME_LENGTH 8
#define MAX_ATTACKS 28

int F = 0; // Sum total of fitnesses
int N = 0; // Number of individuals in the population

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
bool isMatingPoolFull(Individual **);
void rouletteWheelSelection(Individual **, std::vector<Individual *> *);
void crossover(std::vector<Individual *> *, Individual **);
void mutation(Individual **);
Individual *foundFittestIndividual(Individual **population);

int main() {
    srand(time(NULL));
    std::cout << "[==== 8 Queens attack problem ====]" << std::endl;
    do {
        std::cout << "Enter an number of individuals: ";
        std::cin >> N;
    } while (N & 1); // N should be an even number
    Individual *population[N];
    std::vector<Individual *> matingPool;
    Individual *fittestIndividual = nullptr;

    for(int i = 0; i < N; i++) {
        population[i] = new Individual;
        createRandomGene(population[i]);
        countAttacks(population[i]);
        population[i]->fitness = MAX_ATTACKS - population[i]->number_of_attacks;
        std::cout << "G(" << i << "): " << population[i]->gene_str << " ; Noa = " << population[i]->number_of_attacks << " ; Fitness = " << population[i]->fitness << std::endl;
        displayChessBoardByIndividual(population[i]);
        std::cout << std::endl;
    }

    do {
        computeAllFitnessSubintervals(population);
        rouletteWheelSelection(population, &matingPool);
        crossover(&matingPool, population);
        computeAllFitnessSubintervals(population);
        fittestIndividual = foundFittestIndividual(population);
        if(fittestIndividual != nullptr) {
            break;
        }
        mutation(population);
        computeAllFitnessSubintervals(population);
    } while ((fittestIndividual = foundFittestIndividual(population)) == nullptr);

    std::cout << "Found fittest individual: " << fittestIndividual << std::endl;

    return 0;
}

bool isMatingPoolFull(Individual **matingPool) {
    bool r = true;
    for(int i = 0; i < N; i++) {
        if(matingPool[i] == nullptr) {
            r = false;
            break;
        }
    }
    return r;
}

void rouletteWheelSelection(Individual **population, std::vector<Individual *> *matingPool) {
    std::cout << "Roulette wheel selection..." << std::endl;
    int random = rand() % F;
    for(int i = 0; i < N; i++) {
        if(random >= population[i]->fitness_subinterval_from && random < population[i]->fitness_subinterval_to) {
            matingPool->push_back(population[i]);
        }
    }
}

void crossover(std::vector<Individual *> *matingPool, Individual **population) {
    std::cout << "Crossover..." << std::endl;
    if(matingPool->size() < 2) return;
    for(int i = 0; i <= matingPool->size() / 2; i += 2) {
        int crosssite = rand() % GENOME_LENGTH + 1;
        for(int g = GENOME_LENGTH - 1; g > crosssite; g--) {
            int t = matingPool->at(i)->gene[g];
            matingPool->at(i)->gene[g] = matingPool->at(i + 1)->gene[g];
            matingPool->at(i + 1)->gene[g] = t;
        }
        matingPool->at(i)->gene_str = "";
        matingPool->at(i + 1)->gene_str = "";
        for(int g = 0; g < GENOME_LENGTH; g++) {
            matingPool->at(i)->gene_str += std::to_string(matingPool->at(i)->gene[g]) + "-";
        }
        matingPool->at(i)->gene_str = matingPool->at(i)->gene_str.substr(0, matingPool->at(i)->gene_str.size() - 1);
        for(int g = 0; g < GENOME_LENGTH; g++) {
            matingPool->at(i + 1)->gene_str += std::to_string(matingPool->at(i + 1)->gene[g]) + "-";
        }
        matingPool->at(i + 1)->gene_str = matingPool->at(i + 1)->gene_str.substr(0, matingPool->at(i + 1)->gene_str.size() - 1);
        countAttacks(matingPool->at(i));
        countAttacks(matingPool->at(i + 1));
        matingPool->at(i)->fitness = MAX_ATTACKS - matingPool->at(i)->number_of_attacks;
        matingPool->at(i + 1)->fitness = MAX_ATTACKS - matingPool->at(i + 1)->number_of_attacks;
    }
    for(int i = 0; i < matingPool->size(); i++) {
        for(int j = 0; j < N; j++) {
            if(population[j]->fitness < matingPool->at(i)->fitness) {
                population[j] = matingPool->at(i);
                break;
            }
        }
    }
}

void mutation(Individual **matingPool) {
    std::cout << "Mutation..." << std::endl;
    int r = rand() % N;
    Individual *individual = matingPool[r];
    if(individual != nullptr) {
        int r1 = rand() % GENOME_LENGTH;
        int r2 = rand() % GENOME_LENGTH + 1;
        individual->gene[r1] = r2;
        individual->gene_str = "";
        for(int i = 0; i < GENOME_LENGTH; i++) {
            individual->gene_str += std::to_string(individual->gene[i]) + "-";
        }
        individual->gene_str = individual->gene_str.substr(0, individual->gene_str.size() - 1);
        countAttacks(individual);
        individual->fitness = MAX_ATTACKS - individual->number_of_attacks;
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