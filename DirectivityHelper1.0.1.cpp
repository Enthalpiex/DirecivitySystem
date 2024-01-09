#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <locale>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <sstream>

struct Project {
    int id;
    std::vector<double> timeSegments;
};

std::vector<Project> readProjects() {
    std::vector<Project> projects;
    int numProjects;

    std::cout << "请输入项目数量：";
    std::cin >> numProjects;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < numProjects; i++) {
        Project project;
        std::cout << "请输入第 " << i + 1 << " 个项目的时间片段（以-1结束输入）：";

        double timeSegment;
        while (std::cin >> timeSegment) {
            if (timeSegment == -1) {
                project.id = i + 1;
                projects.push_back(project);
                break;
            }
            project.timeSegments.push_back(timeSegment);
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return projects;
}

void CopyToClipboard(const char* text) {
    if (OpenClipboard(nullptr)) {
        EmptyClipboard();

        size_t size = strlen(text) + 1;
        HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, size);

        if (hClipboardData != nullptr) {
            char* buffer = static_cast<char*>(GlobalLock(hClipboardData));
            strcpy_s(buffer, size, text);
            GlobalUnlock(hClipboardData);

            SetClipboardData(CF_TEXT, hClipboardData);
        }

        CloseClipboard();
    }
}

std::string doubleToStringWithPrecision(double value, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

void printUsagePercentages(const std::vector<Project>& projects) {
    double totalUsageTime = 0.0;

    for (const Project& project : projects) {
        double totalTime = 0.0;
        for (double timeSegment : project.timeSegments) {
            totalTime += timeSegment;
        }
        totalUsageTime += totalTime;
    }

    std::cout << "各项目在当天的使用时间占比如下：" << std::endl;
    for (int i = 0; i < projects.size(); i++) {
        double usagePercentage = (projects[i].timeSegments.size() / totalUsageTime) * 100;
        std::cout << "项目 " << projects[i].id << ": " << usagePercentage << "%" << std::endl;
    }
}

int main() {
    
    std::locale::global(std::locale("")); // 设置字符编码为默认值
    int choice;
    system("chcp 65001");
    std::cout << "    ____ _               _   _       _ _                    _                   _   ___   _ "<<std::endl;
    std::cout << "   / __ \\_)_ __ ___  ___| |_(_)_   _(_) |_ _   _  /\\  /\\___| |_ __   ___ _ __  / | / _ \\ / |"<<std::endl;
    std::cout << "  / / / / | '__/ _ \\/ __| __| \\ \\ / / | __| | | |/ /_/ / _ \\ | '_ \\ / _ \\ '__| | || | | || |"<<std::endl;
    std::cout << " / /_/ /| | | |  __/ (__| |_| |\\ V /| | |_| |_| / __  /  __/ | |_) |  __/ |    | || |_| || |"<<std::endl;
    std::cout << " \\____/ |_|_|  \\___|\\___|\\__|_| \\_/ |_|\\__|\\__, \\/ /_/ \\___|_| .__/ \\___|_|    |_(_)___(_)_|"<<std::endl;
    std::cout << "                                           |___/             |_|                            "<< std::endl;
    std::cout << std::endl;
    while (true) {
        std::cout << "请选择功能：" << std::endl;
        std::cout << "1. 时间差计算" << std::endl;
        std::cout << "2. 时间占比计算" << std::endl;
        std::cout << "3. 效率计算" << std::endl;
        std::cout << "请输入对应的数字(1-3)：";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int a = 0;
                int b = 0;
                char continueInput = 'y';

                while (true) {
                    std::cout << "请输入开始时间(格式: hhmm):";
                    std::cin >> a;

                    std::cout << "请输入结束时(格式: hhmm):";
                    std::cin >> b;

                    if (a < 0 || a > 2359 || b < 0 || b > 2359) {
                        std::cout << "输入格式错误，请重新输入!" << std::endl;
                        continue;
                    }
                            double hours;
                    int H=0,M=0,flag=0;
                    // 计算时间差
                    int diff = b - a;
                    if (diff < 0)
                    {
                        diff += 2400;
                    }
                    if(diff-(diff/100*100)==0)
                    {
                        hours = diff/100;
                        H = diff/100;
                        M = 0;
                        //std::cout<<"DIFFBAIWEI"<< hours <<std::endl;
                    }
                    else if(diff-(diff/100*100)<60)
                    {
                        H = diff / 100;
                        M = diff - 100 * H;
                        hours = H + M / 60.0;
                        //cout<< hours<<" "<< diff<<endl;
                    }
                    else if(diff-(diff/100*100)>=60)
                    {
                        H = diff / 100;
                        //std::cout<<"H"<< H <<std::endl;
                        M = diff-(diff/100*100) - 40;
                        //std::cout<<"M"<< M <<std::endl;
                        hours = H + M / 60.0;
                    }
                    else
                    {
                        hours = -1;
                        flag = -1;
                    }
                    int bar;
                    int b =M/5;
                    if(M/5-b>0.5)
                    {
                        bar = 12*H + b + 1;
                    }
                    else
                    {
                        bar = 12*H + b;
                    }
                    // 将 double 转换为字符串，保留两位小数
                    std::string hoursString = doubleToStringWithPrecision(hours, 2);
                    // 输出到控制台
                    std::cout << "时间差为: " << hoursString << "H (" << bar << "bar)" << std::endl;
                    // 将结果输出到剪贴板
                    std::string clipboardContent = hoursString + "H (" + std::to_string(bar) + "bar)";
                    CopyToClipboard(clipboardContent.c_str());
                    std::cout << "结果已复制" << std::endl;
                    std::cout << "按下任意按键继续输入，按下 ESC 键返回主菜单" << std::endl;
                    char key = _getch();
                    if (key == 27) {
                        break;
                    }
                }
                break;
            }
            case 2: {
                std::vector<Project> projects = readProjects();
                printUsagePercentages(projects);

                std::cout << "按下任意按键继续输入，按下 ESC 键返回主菜单。" << std::endl;
                char key = _getch();
                if (key == 27) {
                    break;
                }
                break;
            }
            case 3:
                // 效率计算功能的代码
                break;
            default:
                std::cout << "无效的选择，请重新输入。" << std::endl;
                continue;
        }

        char continueChoice;
        std::cout << "是否继续使用工具？(Y/N):";
        std::cin >> continueChoice;

        if (continueChoice != 'Y' && continueChoice != 'y') {
            break;
        }
    }

    return 0;
}