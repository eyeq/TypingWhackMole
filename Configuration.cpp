#include "Configuration.hpp"

bool Configuration::isInit = false;
int Configuration::highScores[NUM_DIFFICULTY];
int Configuration::latestScores[NUM_DIFFICULTY];
DIFFICULT Configuration::diffs[NUM_DIFFICULTY];

Configuration::Configuration()
{
	selectDifficult = EASY;
	init();
}

Configuration::~Configuration()
{
	std::wofstream ofs(L"scores.txt");
	for(int i = 0; i < NUM_DIFFICULTY; ++i)
	{
		ofs << highScores[i] << std::endl
			<< latestScores[i] << std::endl;
	}
}

void Configuration::init()
{
	if (isInit)
		return;
	isInit = true;
	std::wifstream ifs(L"scores.txt");
	for(int i = 0; i < NUM_DIFFICULTY; ++i)
	{
		ifs >> highScores[i] >> latestScores[i];
	}

	diffs[EASY].maxNum = 2;
	diffs[EASY].minTime = 512;
	diffs[EASY].VanishProbability = 10;
	diffs[EASY].EmargeProbability = 10;

	diffs[NORMAL].maxNum = 4;
	diffs[NORMAL].minTime = 126;
	diffs[NORMAL].VanishProbability = 10;
	diffs[NORMAL].EmargeProbability = 100;

	diffs[HARD].maxNum = 26;
	diffs[HARD].minTime = 32;
	diffs[HARD].VanishProbability = 50;
	diffs[HARD].EmargeProbability = 10;
}

bool Configuration::IsVanish()
{
	std::random_device rd;
	return rd() % 1000 < diffs[selectDifficult].VanishProbability;
}

bool Configuration::IsEmarge()
{
	std::random_device rd;
	return rd() % 1000 < diffs[selectDifficult].EmargeProbability;
}

bool Configuration::SetScore(int score)
{
	latestScores[selectDifficult] = score;
	if(score < highScores[selectDifficult])
		return false;
	highScores[selectDifficult] = score;
	return true;
}
int Configuration::GetHighScore()
{
	return GetHighScore(selectDifficult);
}

int Configuration::GetHighScore(DIFFICULTY dif)
{
	return highScores[dif];
}

int Configuration::GetLatestScore(DIFFICULTY dif)
{
	return latestScores[dif];
}

int Configuration::GetMaxNum()
{
	return diffs[selectDifficult].maxNum;
}

int Configuration::GetMinTime()
{
	return diffs[selectDifficult].minTime;
}

void Configuration::SetDifficulty(DIFFICULTY d0)
{
	selectDifficult = d0;
}
