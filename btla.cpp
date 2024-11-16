#include <bits/stdc++.h>
using namespace std;

class Coffee {
private:
    string ten;
    float gia;
    int namsanxuat;
    float danhgia;

public:
    Coffee() {}

    Coffee(string ten, float gia, int namsanxuat, float danhgia)
        : ten(ten), gia(gia), namsanxuat(namsanxuat), danhgia(danhgia) {}

    friend istream& operator>>(istream &is, Coffee &cf) {
        cout << "Nhap ten cafe: ";
        is.ignore(); 
        getline(is, cf.ten);
        cout << "Nhap gia: ";
        is >> cf.gia;
        cout << "Nhap nam san xuat: ";
        is >> cf.namsanxuat;
        cout << "Nhap danh gia: ";
        is >> cf.danhgia;
        return is;
    }

    friend ostream& operator<<(ostream &os, const Coffee &cf) {
        os << "Ten cafe: " << cf.ten << "\t";
        os << "Gia: " << cf.gia << "\t";
        os << "Nam SX: " << cf.namsanxuat << "\t";
        os << "Danh gia: " << cf.danhgia << "\t";
        return os;
    }

    bool operator<(const Coffee &other) const {
        return danhgia < other.danhgia;
    }
};

class Danhsach {
private:
    vector<Coffee> danhsach;

public:
    void themCoffee(const Coffee &cf) {
        danhsach.push_back(cf);
    }

    void nhap() {
        int soluong;
        cout << "Nhap so luong cafe: ";
        cin >> soluong;
        cin.ignore();  
        for (int i = 0; i < soluong; i++) {
            cout << "Nhap thong tin cafe thu " << i + 1 << ":\n";
            Coffee cf;
            cin >> cf;
            themCoffee(cf);
        }
    }

    void xuat() const {
        for (int i = 0; i < danhsach.size(); i++) {
            cout << danhsach[i] << endl;
        }
    }

    void sapXep() {
        sort(danhsach.begin(), danhsach.end());
    }

    Coffee max() {
        if (danhsach.empty()) {
            throw runtime_error("Danh sach rong, khong the tim cafe co danh gia cao nhat.");
        }
        return *max_element(danhsach.begin(), danhsach.end());
    }

    Coffee min() {
        if (danhsach.empty()) {
            throw runtime_error("Danh sach rong, khong the tim cafe co danh gia thap nhat.");
        }
        return *min_element(danhsach.begin(), danhsach.end());
    }
};

class App {
public:
    void menu() {
        Danhsach ds;
        int chon;
        do {
            cout << "MENU QUAN LY CAFE\n";
            cout << "1. Them cafe\n";
            cout << "2. Xuat danh sach cafe\n";
            cout << "3. Sap xep danh sach theo danh gia\n";
            cout << "4. Tim cafe co danh gia cao nhat\n";
            cout << "5. Tim cafe co danh gia thap nhat\n";
            cout << "0. Thoat\n";
            cout << "Chon: ";
            cin >> chon;
            switch (chon) {
                case 1: {
                    ds.nhap();
                    break;
                }
                case 2: {
                    ds.xuat();
                    break;
                }
                case 3: {
                    ds.sapXep();
                    cout << "Danh sach sau khi sap xep theo danh gia:\n";
                    ds.xuat();
                    break;
                }
                case 4: {
                    try {
                        Coffee maxCF = ds.max();
                        cout << "Cafe co danh gia cao nhat:\n" << maxCF << endl;
                    } catch (const exception& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
                case 5: {
                    try {
                        Coffee minCF = ds.min();
                        cout << "Cafe co danh gia thap nhat:\n" << minCF << endl;
                    } catch (const exception& e) {
                        cout << e.what() << endl;
                    }
                    break;
                }
            }
        } while (chon != 0);
    }
};

int main() {
    App app;
    app.menu();
    return 0;
}
