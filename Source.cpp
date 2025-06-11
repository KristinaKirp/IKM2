#include "Header.h"

void BallGame::run() {
    cout << "����� ���������� � ��������� �������!\n"
        << "����� �� ������� �����, ������� ���������� ����� �������.\n"
        << "��� ��������� ��� ������ ���������� �����, ��������� ������� ��.\n" << endl;

    string ballCountStr;
    cout << "������� ����� ���������� �������: ";
    getline(cin, ballCountStr); // ����������� ������, ����� �������� �������� ����� ������

    int ballsTotal = 0;
    if (!InputValidator::validateBallCount(ballCountStr, ballsTotal)) {
        return; // �����, ���� �������� ������ �� �����
    }

    list<int> ballColors = getBallColors(ballsTotal);
    int removedBalls = removeConsecutiveBalls(ballColors);

    cout << "����� ���������� �������� �������: " << removedBalls << endl;
}

// Reads the ball colors from user input. Returns a list of ball colors.
list<int> BallGame::getBallColors(int& ballCount) {
    list<int> colorList;

    cout << "������� " << ballCount << " ����� ����� (����� �� 0 �� 9): " << endl;
    for (int i = 0; i < ballCount; ++i) {
        int colorInput;
        // Use a loop until valid input is obtained.
        while (!(cin >> colorInput) || !InputValidator::validateBallColor(colorInput)) {
            // Clear error flags and throw away invalid input
            cout << "������ �����! ����������, ������� ���������� �������� ����� ������ (����� ����� �� 0 �� 9): ";
            cin.clear();  // Reset error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard wrong input
        }
        colorList.push_back(colorInput);
    }
    return colorList;
}

// This function is meant to count and remove groups of consecutively matching balls.
// There may be a more clever algorithm, but this version is straightforward and feels "human".
int BallGame::removeConsecutiveBalls(list<int>& ballList) {
    if (ballList.empty()) {
        cout << "��� ������� ��� ���������!" << endl;
        return 0;
    }

    int totalDestroyed = 0;
    bool groupRemoved;  // flag to check if any group was removed in a pass

    // Loop until a full pass is made without any removals
    do {
        groupRemoved = false;
        auto currentPos = ballList.begin();

        // If there's nothing in the list, break out (shouldn't happen because of earlier check)
        if (currentPos == ballList.end())
            break;

        int currentColor = *currentPos;
        int consecutiveCount = 1;
        auto groupStart = currentPos;
        ++currentPos;
        while (currentPos != ballList.end()) {
            if (*currentPos == currentColor) {
                consecutiveCount++;
            }
            else {
                // If we encountered enough consecutive balls, remove them.
                if (consecutiveCount >= 3) {
                    groupRemoved = true;
                    totalDestroyed += consecutiveCount;
                    ballList.erase(groupStart, currentPos);
                    break;  // restart the iteration after removal
                }
                // Otherwise, start counting the next group
                currentColor = *currentPos;
                consecutiveCount = 1;
                groupStart = currentPos;
            }
            ++currentPos;
        }

        // After the while loop, check the last group if no removal happened in the loop.
        if (!groupRemoved && consecutiveCount >= 3) {
            totalDestroyed += consecutiveCount;
            ballList.erase(groupStart, ballList.end());
            groupRemoved = true;
        }
        // Note: sometimes I'll leave such redundant checks for clarity even if they might be merged

    } while (groupRemoved);

    return totalDestroyed;
}

/*
    Validates the count of balls entered by the user.
    I added some extra checks to avoid weird inputs. Sometimes I overdo input validation.
*/
bool InputValidator::validateBallCount(const string& rawInput, int& result) {
    if (rawInput.empty()) {
        cout << "������! ������� �����." << endl;
        return false;
    }

    // Not allowing more than 6 digits (i.e., up to 999999)
    if (rawInput.length() > 6) {
        cout << "������! ����� ������� �������." << endl;
        return false;
    }

    for (char ch : rawInput) {
        if (!isdigit(ch)) {
            cout << "������! ����������, ������� ������ ����� ��� ������ ��������." << endl;
            return false;
        }
    }

    // Avoid numbers starting with zero (unless it's a single '0')
    if (rawInput[0] == '0' && rawInput.length() > 1) {
        cout << "������! ����� �� ����� ���������� � 0." << endl;
        return false;
    }

    try {
        result = stoi(rawInput);
        return true;
    }
    catch (...) {
        // I catch all exceptions here - a bit lazy but it works for now.
        cout << "������! ������������ �����." << endl;
        return false;
    }
}

/*
    Checks if a ball color value is within the acceptable range [0, 9].
    I generally trust the user, but this is just a safety check.
*/
bool InputValidator::validateBallColor(int color) {
    // I use || here because if color is either less than 0 or greater than 9 it's invalid.
    if (color < 0 || color > 9) {
        cout << "������! ���� ������ ���� �� 0 �� 9." << endl;
        return false;
    }
    return true;
}