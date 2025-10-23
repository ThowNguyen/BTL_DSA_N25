#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ====== STRUCT NGƯỜI DÙNG ======
struct User {
    int userid;
    string username;
    string password;
    string role; // "admin" hoặc "user"
    string hoTen;
    string dob;   // ngày sinh
    string mssv;  // mã số sinh viên
    vector<string> borrowedTitles; // danh sách tiêu đề sách đang mượn
    vector<string> dueDates;
    User* next; 
};

// ====== STRUCT SÁCH ======
struct Book {
    string isbn;
    string title;
    string subject;
    string author;
    string publisher;
    string date;
    int pages;
    int copies;
    Book* next;
};

// ====== CLASS LIBRARY ======
class Library {
private:
    vector<User> users;
    Book* booksHead;

public:
    Library() {
        booksHead = nullptr;
        tao_du_lieu();
    }

    // ==== HIỂN THỊ ====
    void hien_thi_nguoi_dung(User& user);
    void hien_thi_tat_ca_nguoi_dung();
    void hien_thi_sach(Book* book);
    void hien_thi_tat_ca_sach();

    // ==== NGƯỜI DÙNG ====
    void them_nguoi_dung();
    void xoa_nguoi_dung(string& username);
    void sua_nguoi_dung(string& username);

    // ==== SÁCH ====
    void them_sach();
    void sua_sach(string& title);
    void xoa_sach(string& title);

    // ==== HỆ THỐNG ====
    bool kiem_tra_dang_nhap(string& username, string& password, string& role);
    void menu_admin(User& curAdmin);
    void menu_user(User& curUser);
    void tao_du_lieu();
    void run();
};

// ====== HIỂN THỊ NGƯỜI DÙNG ======
void Library::hien_thi_nguoi_dung(User& user) {
    cout << "\n-----------------------------------\n";
    cout << "Ho ten: " << user.hoTen << "\n";
    cout << "Ngay sinh: " << user.dob << "\n";
    cout << "MSSV: " << user.mssv << "\n";
    cout << "Username: " << user.username << "\n";
    cout << "Role: " << user.role << "\n";
    cout << "Sach dang muon:\n";
    if (user.borrowedTitles.empty())
        cout << "  (Khong co sach muon)\n";
    else {
        for (size_t i = 0; i < user.borrowedTitles.size(); ++i) {
            cout << "  - " << user.borrowedTitles[i];
            if (i < user.dueDates.size()) cout << " (Het han: " << user.dueDates[i] << ")";
            cout << "\n";
        }
    }
}

// ====== HIỂN THỊ DANH SÁCH NGƯỜI DÙNG ======
void Library::hien_thi_tat_ca_nguoi_dung() {
    cout << "\n===== DANH SACH NGUOI DUNG =====\n";
    if (users.empty()) {
        cout << "Chua co nguoi dung nao.\n";
        return;
    }
    for (auto& u : users) {
        hien_thi_nguoi_dung(u);
    }
}

// ====== HIỂN THỊ SÁCH ======
void Library::hien_thi_sach(Book* book) {
    cout << "ISBN: " << book->isbn << "\n";
    cout << "Ten: " << book->title << "\n";
    cout << "Chu de: " << book->subject << "\n";
    cout << "Tac gia: " << book->author << "\n";
    cout << "NXB: " << book->publisher << "\n";
    cout << "Ngay XB: " << book->date << "\n";
    cout << "Trang: " << book->pages << "\n";
    cout << "So ban: " << book->copies << "\n";
    cout << "---------------------------\n";
}

void Library::hien_thi_tat_ca_sach() {
    cout << "\n===== DANH SACH SACH =====\n";
    if (!booksHead) {
        cout << "Thu vien chua co sach nao.\n";
        return;
    }
    Book* tmp = booksHead;
    while (tmp) {
        hien_thi_sach(tmp);
        tmp = tmp->next;
    }
}

// ====== THÊM NGƯỜI DÙNG ======
void Library::them_nguoi_dung() {
    cout << "\n--- THEM NGUOI DUNG ---\n";
    User newUser;
    newUser.userid = users.size() + 1;
    cin.ignore();

    cout << "Nhap ho ten: ";
    getline(cin, newUser.hoTen);
    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    getline(cin, newUser.dob);
    cout << "Nhap MSSV: ";
    getline(cin, newUser.mssv);
    cout << "Nhap username: ";
    cin >> newUser.username;
    cout << "Nhap password: ";
    cin >> newUser.password;
    cout << "Nhap role (user/admin): ";
    cin >> newUser.role;

    // nhập số sách mượn
    int soSach;
    cout << "Nhap so sach nguoi nay dang muon: ";
    cin >> soSach;
    cin.ignore();
    for (int i = 0; i < soSach; i++) {
        string title;
        cout << "  Nhap ten sach thu " << i + 1 << ": ";
        getline(cin, title);
        newUser.borrowedTitles.push_back(title);
        string due;
        cout << "  Nhap ngay het han (dd/mm/yyyy): ";
        getline(cin, due);
        newUser.dueDates.push_back(due);
    }

    users.push_back(newUser);
    cout << "Da them nguoi dung thanh cong!\n";
}

// ====== XÓA NGƯỜI DÙNG ======
void Library::xoa_nguoi_dung(string& username) {
    auto it = find_if(users.begin(), users.end(), [&](User& u) { return u.username == username; });
    if (it != users.end()) {
        users.erase(it);
        cout << "Da xoa nguoi dung: " << username << "\n";
    } else {
        cout << "Khong tim thay nguoi dung.\n";
    }
}

// ====== SỬA NGƯỜI DÙNG ======
void Library::sua_nguoi_dung(string& username) {
    for (auto& u : users) {
        if (u.username == username) {
            cin.ignore();
            cout << "Nhap ho ten moi: "; getline(cin, u.hoTen);
            cout << "Nhap ngay sinh moi: "; getline(cin, u.dob);
            cout << "Nhap MSSV moi: "; getline(cin, u.mssv);
            cout << "Nhap password moi: "; cin >> u.password;
            cout << "Nhap role moi (user/admin): "; cin >> u.role;
            cout << "Cap nhat thanh cong.\n";
            return;
        }
    }
    cout << "Khong tim thay nguoi dung.\n";
}

// ====== THÊM SÁCH ======
void Library::them_sach() {
    cout << "\n--- THEM SACH ---\n";
    Book* newBook = new Book;
    cout << "ISBN: "; cin >> newBook->isbn;
    cin.ignore();
    cout << "Ten sach: "; getline(cin, newBook->title);
    cout << "Chu de: "; getline(cin, newBook->subject);
    cout << "Tac gia: "; getline(cin, newBook->author);
    cout << "Nha XB: "; getline(cin, newBook->publisher);
    cout << "Ngay XB: "; getline(cin, newBook->date);
    cout << "So trang: "; cin >> newBook->pages;
    cout << "So ban copy: "; cin >> newBook->copies;
    newBook->next = nullptr;

    if (!booksHead) booksHead = newBook;
    else {
        Book* tmp = booksHead;
        while (tmp->next) tmp = tmp->next;
        tmp->next = newBook;
    }
    cout << "Da them sach: " << newBook->title << "\n";
}

// ====== SỬA, XÓA SÁCH ======
void Library::sua_sach(string& title) {
    Book* tmp = booksHead;
    while (tmp) {
        if (tmp->title == title) {
            cout << "Nhap thong tin moi cho sach:\n";
            cout << "ISBN: "; cin >> tmp->isbn;
            cin.ignore();
            cout << "Ten sach: "; getline(cin, tmp->title);
            cout << "Chu de: "; getline(cin, tmp->subject);
            cout << "Tac gia: "; getline(cin, tmp->author);
            cout << "NXB: "; getline(cin, tmp->publisher);
            cout << "Ngay XB: "; getline(cin, tmp->date);
            cout << "Trang: "; cin >> tmp->pages;
            cout << "Ban copy: "; cin >> tmp->copies;
            cout << "Da cap nhat sach.\n";
            return;
        }
        tmp = tmp->next;
    }
    cout << "Khong tim thay sach.\n";
}

void Library::xoa_sach(string& title) {
    Book* tmp = booksHead;
    Book* prev = nullptr;
    while (tmp) {
        if (tmp->title == title) {
            if (prev) prev->next = tmp->next;
            else booksHead = tmp->next;
            delete tmp;
            cout << "Da xoa sach: " << title << "\n";
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    cout << "Khong tim thay sach.\n";
}

// ====== KIỂM TRA ĐĂNG NHẬP ======
bool Library::kiem_tra_dang_nhap(string& username, string& password, string& role) {
    for (auto& u : users)
        if (u.username == username && u.password == password && u.role == role)
            return true;
    return false;
}

// ====== MENU ADMIN ======
void Library::menu_admin(User& curAdmin) {
    int choice;
    do {
        cout << "\n--- MENU ADMIN (" << curAdmin.username << ") ---\n";
        cout << "1. Them nguoi dung\n";
        cout << "2. Xoa nguoi dung\n";
        cout << "3. Sua nguoi dung\n";
        cout << "4. Xem danh sach nguoi dung\n";
        cout << "5. Them sach\n";
        cout << "6. Sua sach\n";
        cout << "7. Xoa sach\n";
        cout << "8. Xem tat ca sach\n";
        cout << "0. Dang xuat\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1: them_nguoi_dung(); break;
        case 2: {
            string u; cout << "Nhap username can xoa: "; cin >> u;
            xoa_nguoi_dung(u); break;
        }
        case 3: {
            string u; cout << "Nhap username can sua: "; cin >> u;
            sua_nguoi_dung(u); break;
        }
        case 4: hien_thi_tat_ca_nguoi_dung(); break;
        case 5: them_sach(); break;
        case 6: {
            cin.ignore();
            string t; cout << "Nhap ten sach can sua: "; getline(cin, t);
            sua_sach(t); break;
        }
        case 7: {
            cin.ignore();
            string t; cout << "Nhap ten sach can xoa: "; getline(cin, t);
            xoa_sach(t); break;
        }
        case 8: hien_thi_tat_ca_sach(); break;
        case 0: cout << "Dang xuat admin.\n"; return;
        default: cout << "Lua chon khong hop le.\n";
        }
    } while (true);
}

// ====== MENU USER ======
void Library::menu_user(User& curUser) {
    int choice;
    do {
        cout << "\n--- MENU NGUOI DUNG (" << curUser.username << ") ---\n";
        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Xem danh sach sach\n";
        cout << "0. Dang xuat\n";
        cout << "Lua chon: ";
        cin >> choice;

        switch (choice) {
        case 1: hien_thi_nguoi_dung(curUser); break;
        case 2: hien_thi_tat_ca_sach(); break;
        case 0: cout << "Dang xuat nguoi dung.\n"; return;
        default: cout << "Lua chon khong hop le.\n";
        }
    } while (true);
}

// ====== DỮ LIỆU MẪU ======
void Library::tao_du_lieu() {
    User admin{ 1, "admin", "123", "admin", "Quan Tri Vien", "01/01/2000", "A000", {}, {} };
    users.push_back(admin);
    User user{ 2, "user1", "pass1", "user", "Nguyen Van A", "02/02/2001", "B12345", {"Lap trinh C++"}, {"30/10/2025"} };
    users.push_back(user);

    Book* b1 = new Book{"CN2302CLCA0104", "Lap trinh C++", "CNTT", "Nguyen Van A", "NXB GD", "2024", 300, 5, nullptr};
    Book* b2 = new Book{"BK002", "Ky thuat dien", "Dien tu", "Le Van B", "NXB KH", "2020", 250, 3, nullptr};
    b1->next = b2;
    booksHead = b1;
}

// ====== CHƯƠNG TRÌNH CHÍNH ======
void Library::run() {
    cout << "===== CHAO MUNG BAN DEN THU VIEN =====\n";
    while (true) {
        cout << "\nBan muon dang nhap voi tu cach:\n";
        cout << "1. Nguoi dung\n";
        cout << "2. Quan tri vien (Admin)\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";
        int roleChoice; cin >> roleChoice;
        if (roleChoice == 0) {
            cout << "Thoat chuong trinh.\n";
            return;
        }
        if (roleChoice != 1 && roleChoice != 2) {
            cout << "Lua chon khong hop le.\n";
            continue;
        }

        string expectedRole = (roleChoice == 1 ? "user" : "admin");
        string username, password;
        cout << "Nhap username: "; cin >> username;
        cout << "Nhap password: "; cin >> password;

        if (!kiem_tra_dang_nhap(username, password, expectedRole)) {
            cout << "Dang nhap that bai!\n";
            continue;
        }

        for (auto& u : users) {
            if (u.username == username && u.password == password && u.role == expectedRole) {
                if (expectedRole == "admin") menu_admin(u);
                else menu_user(u);
                break;
            }
        }
    }
}

// ====== MAIN ======
int main() {
    Library lib;
    lib.run();
    return 0;
}
