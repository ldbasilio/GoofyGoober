#pragma once

#include <string>
#include <vector>

class QuestionManager
{
private:
    std::vector<std::string> questions;
    std::vector<int> availableIndexes;
    int currentIndex;

public:
    QuestionManager();

    bool loadQuestions(const std::string& filename);
    bool loadProgress(const std::string& filename);
    bool saveProgress(const std::string& filename);

    std::string getRandomQuestion();
    void markCurrentQuestionAnswered();

    bool hasQuestionsLeft() const;
    int getQuestionCount() const;
    int getRemainingCount() const;
};