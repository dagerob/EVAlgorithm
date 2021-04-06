#include <iostream>
#include <vector>
#include <algorithm>
#include "NormMagicSquare.h"

#define POP_SIZE 100
#define GENERATIONS 100000
#define SIZE 20

int main()
{
    // initialize with random generation
    BaseEntity** generation = new BaseEntity*[POP_SIZE];
    for (int i = 0; i < POP_SIZE; i++) {
        BaseEntity* newEntity = new NormMagicSquare(SIZE);
        generation[i] = newEntity;
    }

    // sort from best to worst
    std::sort(generation, generation + POP_SIZE, [](BaseEntity* a, BaseEntity* b) {
        return *a < *b;
    });

    //for (int i = 0; i < POP_SIZE; i++) {
    //    generation[i]->print();
    //}

    //std::cout << "-------------------------------" << std::endl;

    for(int i = 0; i < GENERATIONS; i++){
        // remove the least best half
        // copy the best half and mutate it 
        for (int i = 0; i < POP_SIZE / 2; i++) {
            BaseEntity* toRemove = generation[i + (POP_SIZE / 2)];
            delete toRemove;
            generation[i + (POP_SIZE / 2)] = generation[i]->getChildWith(*generation[i+1]);
            generation[i + (POP_SIZE / 2)]->mutate(1);
            generation[i]->mutate(0.1);
        }

        // sort from best to worst
        std::sort(generation, generation + POP_SIZE, [](BaseEntity* a, BaseEntity* b) {
            return *a < *b;
        });

        //for (int i = 0; i < POP_SIZE; i++) {
        //    generation[i]->print();
        //}

        std::cout << "Generation: " << i << " best fitness: " << generation[0]->getFitness() << std::endl;
        //generation[POP_SIZE / 2]->print();

        if (generation[0]->getFitness() == 0) {
            generation[0]->print();
            break;
        }
    }
}
