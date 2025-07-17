/*
疑点备注：static_cast<Show>为什么能这样用？这是啥语句？
*/

#include <iostream>
#include <random>
#include <string>

enum Show { ROCK = 0, SCISSORS = 1, PAPER = 2 };

// 枚举值转换字符串
std::string showToString(Show c) {
    switch (c) {
    case ROCK: return "石头";
    case SCISSORS: return "剪刀";
    case PAPER: return "布";
    default: return "未知";
    }
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(ROCK, PAPER);
    Show sys = static_cast<Show>(distrib(gen)); // 系统选择

    bool br = false;
    do {
        br = false;

        int userInput;
        std::cout << "玩家出示（0=石头, 1=剪刀, 2=布）: ";
        std::cin >> userInput;

        if (userInput < ROCK || userInput > PAPER) {
            std::cout << "无效输入！请输入0-2的数字\n";
            continue;
        }

        //转换成枚举
        Show user = static_cast<Show>(userInput);

        std::cout << "玩家: " << showToString(user)
            << " vs 系统: " << showToString(sys) << "\n";

        if ((user == ROCK && sys == SCISSORS) ||
            (user == SCISSORS && sys == PAPER) ||
            (user == PAPER && sys == ROCK)) {
            std::cout << "玩家胜\n";
        }
        else if ((user == ROCK && sys == PAPER) ||
            (user == SCISSORS && sys == ROCK) ||
            (user == PAPER && sys == SCISSORS)) {
            std::cout << "系统胜\n";
        }
        else {
            std::cout << "平局，重新开始\n";
            sys = static_cast<Show>(distrib(gen)); // 重新生成系统选择
            br = true;
        }
    } while (br);

    return 0;
}