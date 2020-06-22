#pragma once
#include <iostream>
#include <string>
#include <vector>

class Game //���������� ������� (Receiver)
{
public:
    void create() {
        std::cout << "Create game " << std::endl;
    }
    void open(std::string file) {
        std::cout << "Open game from " << file << std::endl;
    }
    void save(std::string file) {
        std::cout << "Save game in " << file << std::endl;
    }
    void make_move(std::string move) {
        std::cout << "Make move " << move << std::endl;
    }
};

std::string getPlayerInput(std::string prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

// ������� �����
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
protected:
    Command(Game* p) : pgame(p) {}
    Game* pgame;
};

class CreateGameCommand : public Command
{
public:
    CreateGameCommand(Game* p) : Command(p) {}
    void execute() {
        pgame->create();
    }
};

class OpenGameCommand : public Command
{
public:
    OpenGameCommand(Game* p) : Command(p) {}
    void execute() {
        std::string file_name;
        file_name = getPlayerInput("Enter file name:");
        pgame->open(file_name);
    }
};

class SaveGameCommand : public Command
{
public:
    SaveGameCommand(Game* p) : Command(p) {}
    void execute() {
        std::string file_name;
        file_name = getPlayerInput("Enter file name:");
        pgame->save(file_name);
    }
};

class MakeMoveCommand : public Command
{
public:
    MakeMoveCommand(Game* p) : Command(p) {}
    void execute() {
        // �������� ���� ��� ���������� ������������ ������
        pgame->save("TEMP_FILE");
        std::string move;
        move = getPlayerInput("Enter your move:");
        pgame->make_move(move);
    }
};

class UndoCommand : public Command
{
public:
    UndoCommand(Game* p) : Command(p) {}
    void execute() {
        // ����������� ���� �� ���������� �����
        pgame->open("TEMP_FILE");
    }
};


int command()
{
    
    Game game;
    // �������� �������� ������
    std::vector<Command*> v;
    // ������� ����� ���� 
    v.push_back(new CreateGameCommand(&game));
    // ������ ��������� �����
    v.push_back(new MakeMoveCommand(&game));
    v.push_back(new MakeMoveCommand(&game));
    // ��������� ��� ��������
    v.push_back(new UndoCommand(&game));
    // ��������� ����
    v.push_back(new SaveGameCommand(&game));

    for (size_t i = 0; i < v.size(); ++i)
        v[i]->execute();

    for (size_t i = 0; i < v.size(); ++i)
        delete v[i];

    return 0;
}

/*
+
1. ������� ������ ����������� ����� ���������, ����������� ��������, � ���������, ������� �� ��������������� ���������.
2. ��������� ����������� ������� ������ � ������ ��������.
3. ��������� ����������� ���������� ������ ��������.
4. ��������� �������� ������� ������� �� �������.
5. ��������� ������� ����������/����������.

-
1.  ��������� ��� ��������� ��-�� �������� ��������� �������������� �������.
*/