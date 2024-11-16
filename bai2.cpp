#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;


int getRegionFactor(const string& region) {
    if (region == "NH") return 1;  // Nội hạt
    if (region == "LC") return 2;  // Lân cận
    if (region == "X") return 3;   // Xa
    if (region == "RX") return 4;  // Rất xa
    return 0;  // Nếu không hợp lệ
}


bool isNightTime(const string& time) {
    int hour, minute;
    char colon;
    stringstream timeStream(time);
    timeStream >> hour >> colon >> minute;
    return (hour >= 23 || hour < 5);
}


bool isWeekend(const string& date) {
  
    int day, month, year;
    char slash;
    stringstream dateStream(date);
    dateStream >> day >> slash >> month >> slash >> year;


    struct tm timeStruct = {0};
    timeStruct.tm_mday = day;
    timeStruct.tm_mon = month - 1;
    timeStruct.tm_year = year - 1900; 
    mktime(&timeStruct);

    
    return (timeStruct.tm_wday == 0 || timeStruct.tm_wday == 6);
}

int main() {
    
    ifstream khachhang("khachhang.txt");
    ifstream cuocgoi("cuocgoi.txt");
    ofstream ketqua("ketqua.txt");

    if (!khachhang.is_open()) {
        cerr << "Không thể mở khachhang.txt!" << endl;
        return 1;
    }
    if (!cuocgoi.is_open()) {
        cerr << "Không thể mở cuocgoi.txt!" << endl;
        return 1;
    }
    if (!ketqua.is_open()) {
        cerr << "Không thể tạo ketqua.txt!" << endl;
        return 1;
    }

    
    map<string, string> customers;
    string line;
    while (getline(khachhang, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string phone = line.substr(pos + 2); 
            customers[phone] = name;
        }
    }

    
    ketqua << "Tên khách hàng; Số điện thoại; Số phút; Thời gian gọi; Ngày gọi; Vùng; Tiền" << endl;

    
    while (getline(cuocgoi, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);
        size_t pos4 = line.find(';', pos3 + 1);

        if (pos4 != string::npos) {
            
            string phone = line.substr(0, pos1);
            int minutes = stoi(line.substr(pos1 + 2, pos2 - pos1 - 2));
            string time = line.substr(pos2 + 2, pos3 - pos2 - 2);
            string date = line.substr(pos3 + 2, pos4 - pos3 - 2);
            string region = line.substr(pos4 + 2);

            
            int regionFactor = getRegionFactor(region);
            int cost = 1100 * minutes * regionFactor;

            
            if (isNightTime(time) || isWeekend(date)) {
                cost = cost * 0.7;  
            }

           
            string customerName = customers.count(phone) > 0 ? customers[phone] : "Không xác định";

           
            ketqua << customerName << "; "
                   << phone << "; "
                   << minutes << "; "
                   << time << "; "
                   << date << "; "
                   << region << "; "
                   << fixed << setprecision(0) << cost << endl; 
        }
    }

    khachhang.close();
    cuocgoi.close();
    ketqua.close();

    cout << "Đã ghi dữ liệu từ khachhang.txt và cuocgoi.txt vào ketqua.txt!" << endl;

    return 0;
}
