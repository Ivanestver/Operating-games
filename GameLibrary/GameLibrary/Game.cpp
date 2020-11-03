#include "pch.h"
#include <utility>
#include <limits.h>
#include "Game.h"

/// <summary>
/// ѕодсчитанный общий потенциал обороны
/// </summary>
static unsigned long wholePotentional = 0;
static float sumProbability = 0;

unsigned long GetWholePotentional(unsigned int *efficiency, unsigned int *amount, unsigned int k) {
	unsigned long result = 0;
	for (unsigned int i = 0; i < k; i++) {
		result += efficiency[i] * amount[i];
	}

	wholePotentional = result;

	return result;
}

float GetDestroyedMeans(float *probability, unsigned long i) {
	float result = 0;

	for (unsigned int j = 0; j < i; j++) {
		result += 1 / probability[i];
	}

	sumProbability = result;

	return wholePotentional / result;
}

float GetDestroyedMeans() {
	return wholePotentional / sumProbability;
}

float GetBestResult(unsigned long attack) {
	if (attack - GetDestroyedMeans() > 0)
		return attack - GetDestroyedMeans();
	else
		return 0;
}

float GetDistribution(float probability, unsigned int amount) {
	return (amount / probability) / sumProbability;
}