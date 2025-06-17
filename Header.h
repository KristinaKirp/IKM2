#pragma once

#include <iostream>
#include <string>
#include "Windows.h"
#include <limits>



using namespace std; 

// ����� ��� �������� ������������ ������
class inputValidator
{
public:
    // �������� ����� �� ������� ����� �����
    static bool validateBallCount(const string& rawInput, int& result);

    //�������� ����� �� ������� ����� �������
    static bool validateBallColor(const string& colorBall, int& colorInput);
};

struct ballNode
{
    int color;          // ���� ������
    ballNode* next;     // ��������� �� ��������� ����

    ballNode(int col) : color(col), next(nullptr) {}
};

class list 
{
private:
    ballNode* head;     // ��������� �� ������ ������
    ballNode* tail;     // ��������� �� ����� ������ (��� ����������� ����������)
    int size;          // ���������� ��������� � ������

public:
    // �����������
    list() : head(nullptr), tail(nullptr), size(0) {}

    // ���������� (������� ������)
    ~list()
    {
        clear();
    }

    // ���������� ������ � ����� ������
    void addBall(int color)
    {
        ballNode* newNode = new ballNode(color);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // ������� ������
    void clear() 
    {
        ballNode* current = head;
        while (current != nullptr) 
        {
            ballNode* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    // ��������� ���������� �������
    int getSize() const 
    {
        return size;
    }

    // �������� �� �������
    bool isEmpty() const
    {
        return size == 0;
    } 
    // ������������ � ������ ������  
    ballNode* getHead() const
    {
        return head;
    }

    void eraseBall(ballNode* start, ballNode* end)
    {
        if (!start || !head) return;

        ballNode* current = head;
        ballNode* prev = nullptr;
        ballNode* nodeToDelete = nullptr;
        int count = 0;

        // ������� ���� ����� start
        while (current != start && current != nullptr) {
            prev = current;
            current = current->next;
        }

        if (current != start) return; // start �� ������

        // ������� ���� �� start �� end
        while (current != end && current != nullptr) {
            nodeToDelete = current;
            current = current->next;
            delete nodeToDelete;
            count++;
        }
        if (prev) {
            prev->next = current; // ��������� ���������� ���� � end
        }
        else {
            head = current; // ���� ������� � ������ ������
        }

        // ��������� tail, ���� ������� �����
        if (current == nullptr) {
            tail = prev;
        }

        size -= count;
    }   

};


// ����� ��� ���������� ����� ����
class ballGame
{
public:

    void run();

private:
    // ������� ������ � ������� �� ���������� � ����
    list getBallColors(int ballCount);

    // �������� �� ������������� � �������� ������� �� 3 � ����� �������
    int removeConsecutiveBalls(list& ballList);
};