#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include "QuestionManager.h"

void showMenu()
{
    std::cout << "1. Get Random Question\n";
    std::cout << "2. View Progress\n";
    std::cout << "3. View Previous Responses\n";
    std::cout << "4. Search Response by Question Number\n";
    std::cout << "5. View Statistics\n";
    std::cout << "6. Reset Progress\n";
    std::cout << "7. Exit\n";
}

void viewResponses()
{
    std::ifstream file("data/responses.txt");

    if (!file)
    {
        std::cout << "\nNo responses found yet.\n";
        return;
    }

    std::string line;
    bool hasContent = false;

    std::cout << "\n========== Previous Responses ==========\n\n";

    while (std::getline(file, line))
    {
        std::cout << line << "\n";
        hasContent = true;
    }

    if (!hasContent)
    {
        std::cout << "No responses found yet.\n";
    }
}

void searchResponseByQuestionNumber()
{
    std::ifstream file("data/responses.txt");

    if (!file)
    {
        std::cout << "\nNo responses file found.\n";
        return;
    }

    std::cout << "\nEnter question number: ";

    int targetNumber;
    std::cin >> targetNumber;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string target = "QUESTION #" + std::to_string(targetNumber) + ":";

    std::string line;
    bool found = false;

    while (std::getline(file, line))
    {
        if (line.find(target) != std::string::npos)
        {
            found = true;

            std::cout << "\n========================================\n";

            do
            {
                std::cout << line << "\n";

                if (line == "----------------------------------------")
                {
                    break;
                }

            } while (std::getline(file, line));

            std::cout << "========================================\n";

            break;
        }
    }

    if (!found)
    {
        std::cout << "\nNo saved response found for question #"
                  << targetNumber << ".\n";
    }
}

void answerQuestion(QuestionManager& manager)
{
    Question question = manager.getRandomQuestion();

    std::cout << "\nQuestion:\n";
    std::cout << "#" << question.id << "\n";
    std::cout << question.text << "\n\n";

    std::cout << "1. Answer this question\n";
    std::cout << "2. Skip and get another later\n";
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 2)
    {
        std::cout << "\nQuestion skipped. It will stay in the available list.\n";
        return;
    }

    std::cout << "\nYour answer: ";
    std::string answer;
    std::getline(std::cin, answer);

    if (!manager.saveResponse("data/responses.txt", question, answer))
    {
        std::cout << "Error: Could not save response.\n";
        return;
    }

    manager.markCurrentQuestionAnswered();

    if (!manager.saveProgress("data/progress.txt"))
    {
        std::cout << "Error: Could not save progress.\n";
        return;
    }

    std::cout << "\nAnswer saved. Progress updated.\n";
}

void resetProgress(QuestionManager& manager)
{
    std::cout << "\nAre you sure you want to reset progress? (y/n): ";

    char confirm;
    std::cin >> confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (confirm != 'y' && confirm != 'Y')
    {
        std::cout << "\nReset cancelled.\n";
        return;
    }

    manager.loadQuestions("data/questions.txt");

    if (!manager.saveProgress("data/progress.txt"))
    {
        std::cout << "Error: Could not reset progress.\n";
        return;
    }

    std::cout << "\nProgress reset. All questions are available again.\n";
}

void viewStatistics(QuestionManager& manager)
{
    int totalQuestions = manager.getQuestionCount();
    int remainingQuestions = manager.getRemainingCount();
    int answeredQuestions = totalQuestions - remainingQuestions;

    double completion = 0.0;

    if (totalQuestions > 0)
    {
        completion = (static_cast<double>(answeredQuestions) / totalQuestions) * 100.0;
    }

    std::cout << "\n========== Journal Statistics ==========\n";
    std::cout << "Total Questions: " << totalQuestions << "\n";
    std::cout << "Answered Questions: " << answeredQuestions << "\n";
    std::cout << "Remaining Questions: " << remainingQuestions << "\n";
    std::cout << "Completion: " << std::fixed << std::setprecision(2)
              << completion << "%\n";
}

int main()
{
    QuestionManager manager;

    if (!manager.loadQuestions("data/questions.txt"))
    {
        std::cout << "Error: Could not load questions.txt\n";
        return 1;
    }

    manager.loadProgress("data/progress.txt");

    int choice = 0;

    while (choice != 7)
    {
        showMenu();

        if (!(std::cin >> choice))
        {
            std::cout << "\nInvalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            answerQuestion(manager);
        }
        else if (choice == 2)
        {
            std::cout << "\nTotal Questions: " << manager.getQuestionCount() << "\n";
            std::cout << "Remaining Questions: " << manager.getRemainingCount() << "\n";
            std::cout << "Answered Questions: "
                      << manager.getQuestionCount() - manager.getRemainingCount()
                      << "\n";
        }
        else if (choice == 3)
        {
            viewResponses();
        }
        else if (choice == 4)
        {
            searchResponseByQuestionNumber();
        }
        else if (choice == 5)
        {
            viewStatistics(manager);
        }
        else if (choice == 6)
        {
            resetProgress(manager);
        }
        else if (choice == 7)
        {
            std::cout << "\nGoodbye!\n";
        }
        else
        {
            std::cout << "\nInvalid choice. Please choose 1-7.\n";
        }
    }

    return 0;
}