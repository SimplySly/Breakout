#pragma once
#define DEFAULT_LIFE 3

class PlayerInfo
{
public:
	PlayerInfo();


	void SetToDefault();
	bool HasLife() const; //does player have at least one life?
	int GetNoLives() const;
	int GetCurrentLevel() const;
	unsigned int GetScore() const;

	void LoseLife();
	void LevelCompleted();
	void AddScore(unsigned int score);
private:
	int m_Lives;
	int m_CurrentLevel;
	unsigned int m_Score;
};

