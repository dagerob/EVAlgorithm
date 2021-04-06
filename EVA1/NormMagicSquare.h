#pragma once
#include "BaseEntity.h"
#include <random>
#include <iostream>

class NormMagicSquare : public BaseEntity {
	int size;
	int seed;
	std::mt19937 generator;
	std::uniform_int_distribution<int> distrib;
public:
	int* data;
	NormMagicSquare(int size, int seed);
	NormMagicSquare(int size);
	NormMagicSquare(const NormMagicSquare& other);
	bool mutate(float probability) override;
	float getFitness() const;
	void print() override;	
	BaseEntity* getChildWith(const BaseEntity& other) override;
	BaseEntity* getClone() const;
	~NormMagicSquare() override;
private:
	int getRandomValue();
	NormMagicSquare* mix(const NormMagicSquare& other);
	int getHorizontalsFitness() const;
	int getVerticalsFitness() const;
	int getDiagonalsFitness() const;
	int getMagicConstant() const;
};

NormMagicSquare::NormMagicSquare(int size, int seed) {
	this->seed = seed;
	this->size = size;
	generator = std::mt19937(seed);
	distrib = std::uniform_int_distribution<int>(1, size*size * 2);

	data = new int[size*size];
	for (int i = 0; i < size * size; i++) {
		data[i] = getRandomValue();
	}
}

NormMagicSquare::NormMagicSquare(int size) {
	this->size = size;
	std::random_device rd;
	this->seed = rd();
	generator = std::mt19937(rd());
	distrib = std::uniform_int_distribution<int>(1, size*size * 2);

	data = new int[size*size];
	for (int i = 0; i < size * size; i++) {
		data[i] = getRandomValue();
	}
}

NormMagicSquare::NormMagicSquare(const NormMagicSquare& other) {
	size = other.size;
	seed = other.seed;
	generator = std::mt19937(seed);
	distrib = std::uniform_int_distribution<int>(1, size * size * 2);
	data = new int[size * size];
	for (int i = 0; i < size * size; i++) {
		data[i] = other.data[i];
	}
}

BaseEntity* NormMagicSquare::getClone() const {
	return new NormMagicSquare(*this);
}

int NormMagicSquare::getRandomValue() {
	return distrib(generator);
}

void NormMagicSquare::print() {
	std::cout << "Fitness: " << getFitness() << "\n";
	getFitness();
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			std::cout << data[y * size + x] << "\t";
		}
		std::cout << std::endl;
	}
}

bool NormMagicSquare::mutate(float probability) {
	//std::uniform_real_distribution<float> distribReal(0, 1);
	//float randomVal = distribReal(generator);
	//if (randomVal >= probability) {
	//	return false;
	//}
	//std::uniform_int_distribution<int> distribInt(0, size - 1);
	//int column = distribInt(generator);
	//int row = distribInt(generator);
	//
	//distribInt = std::uniform_int_distribution<int>(-3, 3);
	//int variation = distribInt(generator);
	//std::cout << "mutation " << distrib(generator) << "\n";
	//data[row * size + column] += variation;
	//if (data[row * size + column] < 1) data[row * size + column] = 1;
	//return true;

	int realProbability = probability * 100;
	float randomVal = rand() % 101;
	if (randomVal >= realProbability) {
		return false;
	}
	std::uniform_int_distribution<int> distribInt(0, size - 1);
	int column = rand() % size;
	int row = rand() % size;

	int variation = (rand() % 6) - 3;
	//std::cout << "mutation " << variation << "\n";
	data[row * size + column] += variation;
	if (data[row * size + column] < 1) data[row * size + column] = 1;
	return true;
}

BaseEntity* NormMagicSquare::getChildWith(const BaseEntity& other) {
	BaseEntity* otherParent = other.getClone();
	BaseEntity* toReturn = mix(*dynamic_cast<NormMagicSquare*>(otherParent));
	delete otherParent;
	return toReturn;
}

NormMagicSquare* NormMagicSquare::mix(const NormMagicSquare& other) {
	NormMagicSquare* child = new NormMagicSquare(*this);
	for (int i = 0; i < size * size / 2; i++) {
		child->data[i] = other.data[i];
	}
	return child;
}

float NormMagicSquare::getFitness() const {
	return getHorizontalsFitness() + getVerticalsFitness() + getDiagonalsFitness();
}

int NormMagicSquare::getHorizontalsFitness() const{
	int fitness = 0;
	for (int y = 0; y < size; y++) {
		int thisRowSum = 0;
		for (int x = 0; x < size; x++) {
			thisRowSum += data[y * size + x];
		}
		fitness += (getMagicConstant() - thisRowSum) * (getMagicConstant() - thisRowSum);
	}
	return fitness;
}

int NormMagicSquare::getVerticalsFitness() const{
	int fitness = 0;
	for (int x = 0; x < size; x++) {
		int thisRowSum = 0;
		for (int y = 0; y < size; y++) {
			thisRowSum += data[y * size + x];
		}
		fitness += (getMagicConstant() - thisRowSum) * (getMagicConstant() - thisRowSum);
	}
	return fitness;
}

int NormMagicSquare::getDiagonalsFitness() const{
	int fitness = 0;
	int thisDiagonalSum = 0;
	for (int i = 0; i < size; i++) {
		thisDiagonalSum += data[i * size + i];
	}
	fitness += (getMagicConstant() - thisDiagonalSum) * (getMagicConstant() - thisDiagonalSum);
	thisDiagonalSum = 0;
	for (int i = 0; i < size; i++) {
		thisDiagonalSum += data[i * size + (size - 1 - i)];
	}
	fitness += (getMagicConstant() - thisDiagonalSum) * (getMagicConstant() - thisDiagonalSum);
	return fitness;
}

int NormMagicSquare::getMagicConstant() const{
	return size * ((size * size + 1) / 2);
}

NormMagicSquare::~NormMagicSquare() {
	delete[] data;
}