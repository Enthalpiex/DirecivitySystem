//作者不保证此文件可以使用
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main()
{
    int a = 0;
    int b = 0;
    char continueInput = 'y';

    while (continueInput == 'y' || continueInput == 'Y')
    {
        system("chcp 65001"); // 设置控制台字符编码为 UTF-8

        cout << "请输入开始时间（格式：hhmm）：";
        cin >> a;

        cout << "请输入结束时间（格式：hhmm）：";
        cin >> b;

        // 判断输入格式是否正确
        if (a < 0 || a > 2359 || b < 0 || b > 2359)
        {
            cout << "输入格式错误，请重新输入！" << endl;
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
        if(diff==100)
        {
            hours = 1;
        }
        else if(diff>100||diff<0)
        {
            H = diff / 100;
            M = diff - 100 * H;
            hours = H + M / 60.0;
            //cout<< hours<<" "<< diff<<endl;
        }
        else
        {
            if(a/100!=b/100)
            {
                M = diff - 40;
                hours = M / 60.0;
                //cout<< hours<<" "<< diff<<endl;
            }
            else if(diff<60)
            {
                hours = diff / 60.0;
            }
            else
            {
                hours = -1;
                flag = -1;
            }
        }

        cout << fixed << setprecision(2); // 设置输出精度为两位小数
        cout << "时间差为：" << hours << "H" << endl;
        if(flag==-1)
        {
            flag=0;
            cout
        }
        cout << "是否继续输入？(y-是，n-否)：";
        cin >> continueInput;
    }

    return 0;
}
