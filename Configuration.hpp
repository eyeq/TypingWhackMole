#pragma once

#include <fstream>
#include <random>

const enum DIFFICULTY
{
	EASY,
	NORMAL,
	HARD,
	NUM_DIFFICULTY
};

const struct DIFFICULT
{
	int maxNum;
	int minTime;
	unsigned int VanishProbability;
	unsigned int EmargeProbability;
};

class Configuration
{
public:
	Configuration();
	~Configuration();
	bool IsVanish();
	bool IsEmarge();
	bool SetScore(int);
	int GetHighScore();
	int GetHighScore(DIFFICULTY);
	int GetLatestScore(DIFFICULTY);
	int GetMaxNum();
	int GetMinTime();
	void SetDifficulty(DIFFICULTY);
private:
	static bool isInit;
	static int highScores[];
	static int latestScores[];
	static DIFFICULT diffs[];
	DIFFICULTY selectDifficult;
	void init();
};
