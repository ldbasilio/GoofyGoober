#include <iostream>
#include <string>
#include "QuestionManager.h"

int main()
{
    QuestionManager manager;

    if (!manager.loadQuestions("data/questions.txt"))
    {
        std::cout << "Error: Could not load questions.txt\n";
        return 1;
    }

    manager.loadProgress("data/progress.txt");

    std::cout << "GoofyGoober Journal App\n";
    std::cout << "Loaded " << manager.getQuestionCount() << " questions.\n\n";

    std::string question = manager.getRandomQuestion();

    std::cout << "Question:\n";
    std::cout << question << "\n\n";

    std::cout << "Your answer: ";
    std::string answer;
    std::getline(std::cin, answer);

    manager.markCurrentQuestionAnswered();
    manager.saveProgress("data/progress.txt");

    std::cout << "\nAnswer saved later. Progress updated.\n";

    return 0;
}