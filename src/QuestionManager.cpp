#include "QuestionManager.h"

#include <fstream>
#include <random>
#include <sstream>

QuestionManager::QuestionManager()
{
    currentIndex = -1;
}

bool QuestionManager::loadQuestions(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        return false;
    }

    questions.clear();

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        size_t separator = line.find('|');

        if (separator != std::string::npos)
        {
            Question question;

            question.id = std::stoi(line.substr(0, separator));
            question.text = line.substr(separator + 1);

            questions.push_back(question);
        }
        else
        {
            questions.push_back(line);
        }
    }

    if (questions.empty())
    {
        return false;
    }

    availableIndexes.clear();

    for (int i = 0; i < static_cast<int>(questions.size()); i++)
    {
        availableIndexes.push_back(i);
    }

    return true;
}

bool QuestionManager::loadProgress(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        return false;
    }

    availableIndexes.clear();

    int index;

    while (file >> index)
    {
        if (index >= 0 && index < static_cast<int>(questions.size()))
        {
            availableIndexes.push_back(index);
        }
    }

    if (availableIndexes.empty())
    {
        for (int i = 0; i < static_cast<int>(questions.size()); i++)
        {
            availableIndexes.push_back(i);
        }
    }

    return true;
}

bool QuestionManager::saveProgress(const std::string& filename)
{
    std::ofstream file(filename);

    if (!file)
    {
        return false;
    }

    for (int index : availableIndexes)
    {
        file << index << "\n";
    }

    return true;
}

std::string QuestionManager::getRandomQuestion()
{
    if (availableIndexes.empty())
    {
        for (int i = 0; i < static_cast<int>(questions.size()); i++)
        {
            availableIndexes.push_back(i);
        }
    }

    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> distribution(0, static_cast<int>(availableIndexes.size()) - 1);

    int randomPosition = distribution(generator);

    currentIndex = availableIndexes.at(randomPosition);

    return questions.at(currentIndex);
}

void QuestionManager::markCurrentQuestionAnswered()
{
    if (currentIndex == -1)
    {
        return;
    }

    for (int i = 0; i < static_cast<int>(availableIndexes.size()); i++)
    {
        if (availableIndexes.at(i) == currentIndex)
        {
            availableIndexes.erase(availableIndexes.begin() + i);
            break;
        }
    }

    currentIndex = -1;
}

bool QuestionManager::saveResponse(const std::string& filename, const std::string& question, const std::string& answer)
{
    std::ofstream file(filename, std::ios::app);

    if (!file)
    {
        return false;
    }

    file << "QUESTION:\n";
    file << question << "\n\n";

    file << "ANSWER:\n";
    file << answer << "\n\n";

    file << "----------------------------------------\n\n";

    return true;
}

bool QuestionManager::hasQuestionsLeft() const
{
    return !availableIndexes.empty();
}

int QuestionManager::getQuestionCount() const
{
    return static_cast<int>(questions.size());
}

int QuestionManager::getRemainingCount() const
{
    return static_cast<int>(availableIndexes.size());
}