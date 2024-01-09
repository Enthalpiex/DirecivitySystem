#include <iostream>
#include <vector>

int main() {
    int timeSegment;
    int totalTime = 0;
    std::vector<double> efficiencies;

    while (true) {
        system("chcp 65001");
        std::cout << "请输入时间段（以H为单位），输入-1结束：";
        std::cin >> timeSegment;

        if (timeSegment == -1) {
            break;
        }
        totalTime += timeSegment;
    }

    std::cout << "总时间为：" << totalTime << "小时" << std::endl;

    for (int i = 0; i < totalTime; i++) {
        double efficiency;
        std::cout << "请输入时间段 " << i + 1 << " 的效率：";
        std::cin >> efficiency;

        efficiencies.push_back(efficiency);

        if (i + 1 == totalTime) {
            break;
        }
    }

    return 0;
}