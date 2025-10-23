#include <iostream>
#include <windows.h>   // de doi mau va chinh console
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cctype>
#include <iomanip>
using namespace std;

// ---------------- GIAO DIEN CONSOLE ----------------
void thay_doi_kich_thuoc(int chieu_rong, int chieu_cao) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT khu_vuc_hien_thi = {0, 0, static_cast<short>(chieu_rong - 1), static_cast<short>(chieu_cao - 1)};
    SetConsoleWindowInfo(hOut, TRUE, &khu_vuc_hien_thi);
}

void doi_mau(int mau) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mau);
}

void in_giao_dien() {
    doi_mau(9); // Mau xanh duong
    cout << R"(  

           __       __  .______   .______          ___      .______     ____    ____ 
          |  |     |  | |   _  \  |   _  \        /   \     |   _  \    \   \  /   / 
          |  |     |  | |  |_)  | |  |_)  |      /  ^  \    |  |_)  |    \   \/   /  
          |  |     |  | |   _  <  |      /      /  /_\  \   |      /      \_    _/   
          |  `----.|  | |  |_)  | |  |\  \----./  _____  \  |  |\  \----.   |  |     
          |_______||__| |______/  | _| `._____/__/     \__\ | _| `._____|   |__|     
                                                                           


            __...--~~~~~-._   _.-~~~~~--...__                                                                          _  
          //               `V'               \\            _ __ ___   __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_ 
         //                 |                 \\          | '_ ` _ \ / _` | '_ \ / _` |/ _` |/ _ \ '_ ` _ \ / _ \ '_ \| __|
        //__...--~~~~~~-._  |  _.-~~~~~~--...__\\         | | | | | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_ 
       //__.....----~~~~._\ | /_.~~~~----.....__\\        |_| |_| |_|__,_|_| |_|__,_|\__, |\___|_| |_| |_|__,_|_| |_|__,_|
      ====================\\|//====================                         |___/
                    ---`                                                                                     

    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  

 )" << endl;
    doi_mau(7); // Reset ve mau trang
}

// ======= TIEN ICH TAM DUNG =======
void tam_dung() {
    doi_mau(9); // Mau xanh duong cho thong bao tam dung
    cout << "\nNhan Enter de tiep tuc...";
    doi_mau(7);
    string tmp;
    getline(cin, tmp);
}

// ---------------- HELPERS HIEN THI ----------------
static const string PHAN_CACH = "------------------------------------------------------------";

void in_phan_cach() {
    doi_mau(7);
    cout << PHAN_CACH << "\n";
}

void in_tieu_de(const string& tieu_de) {
    const int do_rong = 60;
    int do_dai_tieu_de = tieu_de.length() + 2;
    int so_dau_bang = do_rong - do_dai_tieu_de - 4;
    if (so_dau_bang < 0) so_dau_bang = 0;
    int bang_trai = so_dau_bang / 2;
    int bang_phai = so_dau_bang - bang_trai;
    doi_mau(10); // Mau xanh la cho tieu de
    cout << "[ " << string(bang_trai, '=') << " " << tieu_de << " " 
         << string(bang_phai, '=') << " ]\n";
    doi_mau(7);
}

// ---------------- STRUCTS ----------------
struct NguoiDung {
    int ma_nguoi_dung;
    string ten_dang_nhap;
    string mat_khau;
    string vai_tro;
    string ho_ten;
    string ngay_sinh;
    string mssv;
    vector<string> ds_sach_muon;
    vector<string> ds_ngay_het_han;
};

struct Sach {
    string isbn;
    string ten_sach;
    string chu_de;
    string tac_gia;
    string dich_gia;
    string nxb;
    string ngay_xb;
    int so_trang;
    int so_ban;
    Sach* tiep_theo;
};

// ---------------- CLASS THU VIEN ----------------
class ThuVien {
private:
    vector<NguoiDung> ds_nguoi_dung;
    Sach* dau_sach;

public:
    ThuVien() {
        dau_sach = nullptr;
        tao_du_lieu();
    }

    ~ThuVien() {
        Sach* tmp = dau_sach;
        while (tmp) {
            Sach* tiep = tmp->tiep_theo;
            delete tmp;
            tmp = tiep;
        }
        dau_sach = nullptr;
    }

    // hien thi
    void hien_nguoi_dung(NguoiDung& nguoi);
    void hien_tat_ca_nguoi_dung();
    void hien_sach(Sach* sach);
    void hien_tat_ca_sach();
    void hien_sach_khung(Sach* sach, int vi_tri);
    void hien_sach_noi_bat();
    void tim_sach();

    // thao tac
    void them_nguoi_dung_moi();
    void xoa_nguoi_dung(const string& ten_dang_nhap);
    void sua_nguoi_dung(const string& ten_dang_nhap);

    void them_sach_moi();
    void sua_sach(const string& ten_sach);
    void xoa_sach(const string& ten_sach);
    
    void muon_sach(const string& ten_dang_nhap, const string& ten_sach);
    void tra_sach(const string& ten_dang_nhap, const string& ten_sach);

    void hien_ds_nguoi_dung_tom_tat();

    bool kiem_tra_dang_nhap(const string& ten_dang_nhap, const string& mat_khau, const string& vai_tro);
    void menu_quan_tri(NguoiDung& quan_tri);
    void menu_nguoi_dung(NguoiDung& nguoi);
    void tao_du_lieu();
    void chay();

private:
    string cat_chu(const string& chu, int do_rong_toi_da);
    void hien_tu_sach_ngang(const vector<Sach*>& ds);
    static string viet_thuong(const string& s);
};

// ====== HELPER viet_thuong ======
string ThuVien::viet_thuong(const string& s) {
    string ket_qua;
    ket_qua.reserve(s.size());
    for (unsigned char c : s) ket_qua.push_back(static_cast<char>(tolower(c)));
    return ket_qua;
}

// ====== CAT CHU HELPER ======
string ThuVien::cat_chu(const string& chu, int do_rong_toi_da) {
    if (chu.length() <= static_cast<size_t>(do_rong_toi_da)) return chu;
    string ket_qua;
    size_t vi_tri = 0;
    while (vi_tri < chu.length()) {
        size_t vi_tri_khoang_trang = chu.find(' ', vi_tri);
        if (vi_tri_khoang_trang == string::npos || vi_tri_khoang_trang - vi_tri > static_cast<size_t>(do_rong_toi_da)) {
            if (ket_qua.empty()) {
                ket_qua = chu.substr(vi_tri, do_rong_toi_da) + "...";
            } else {
                ket_qua += "\n" + chu.substr(vi_tri, do_rong_toi_da) + "...";
            }
            break;
        } else if (ket_qua.empty() || (ket_qua.length() + (vi_tri_khoang_trang - vi_tri) + 1 <= static_cast<size_t>(do_rong_toi_da))) {
            if (!ket_qua.empty()) ket_qua += " ";
            ket_qua += chu.substr(vi_tri, vi_tri_khoang_trang - vi_tri);
            vi_tri = vi_tri_khoang_trang + 1;
        } else {
            ket_qua += "\n";
            ket_qua += chu.substr(vi_tri, vi_tri_khoang_trang - vi_tri);
            vi_tri = vi_tri_khoang_trang + 1;
        }
    }
    return ket_qua;
}

// ====== HIEN NGUOI DUNG (chi tiet) ======
void ThuVien::hien_nguoi_dung(NguoiDung& nguoi) {
    in_tieu_de("THONG TIN NGUOI DUNG");
    cout << "Ho ten : " << (nguoi.ho_ten.empty() ? "(Khong co)" : nguoi.ho_ten) << "\n";
    cout << "Ngay sinh: " << (nguoi.ngay_sinh.empty() ? "(Khong co)" : nguoi.ngay_sinh) << "\n";
    cout << "MSSV: " << (nguoi.mssv.empty() ? "(Khong co)" : nguoi.mssv) << "\n";
    cout << "Ten dang nhap: " << (nguoi.ten_dang_nhap.empty() ? "(Khong co)" : nguoi.ten_dang_nhap) << "\n";
    cout << "Vai tro: " << (nguoi.vai_tro.empty() ? "(Khong co)" : nguoi.vai_tro) << "\n";
    cout << "\nSach dang muon:\n";
    if (nguoi.ds_sach_muon.empty()) {
        cout << "  (Khong co sach muon)\n";
    } else {
        for (size_t i = 0; i < nguoi.ds_sach_muon.size(); ++i) {
            doi_mau(14); // Mau vang cho ten sach muon
            cout << "  - " << nguoi.ds_sach_muon[i];
            doi_mau(7);
            if (i < nguoi.ds_ngay_het_han.size()) cout << " (Het han: " << nguoi.ds_ngay_het_han[i] << ")";
            cout << "\n";
        }
    }
    doi_mau(11); // Mau cyan cho debug
    cout << "[DEBUG] Do dai ten dang nhap: " << nguoi.ten_dang_nhap.length() << "\n";
    doi_mau(7);
    in_phan_cach();
    cout << "\n";
}

// ====== HIEN TAT CA NGUOI DUNG ======
void ThuVien::hien_tat_ca_nguoi_dung() {
    system("cls");
    in_tieu_de("DANH SACH NGUOI DUNG");
    if (ds_nguoi_dung.empty()) {
        doi_mau(12);
        cout << "Chua co nguoi dung nao.\n";
        doi_mau(7);
        in_phan_cach();
        cout.flush();
        tam_dung();
        return;
    }
    for (auto& nguoi : ds_nguoi_dung) {
        hien_nguoi_dung(nguoi);
    }
    tam_dung();
}

// ====== HIEN DS NGUOI DUNG TOM TAT ======
void ThuVien::hien_ds_nguoi_dung_tom_tat() {
    system("cls");
    in_tieu_de("DANH SACH NGUOI DUNG (TOM TAT)");
    if (ds_nguoi_dung.empty()) {
        doi_mau(12);
        cout << "Chua co nguoi dung nao trong he thong.\n";
        doi_mau(7);
        in_phan_cach();
        tam_dung();
        return;
    }

    doi_mau(11); // Mau cyan cho tieu de cot
    cout << left << setw(20) << "Ten dang nhap"
         << setw(30) << "Ho Ten"
         << setw(10) << "So Sach" << "\n";
    doi_mau(7);
    in_phan_cach();

    for (const auto& nguoi : ds_nguoi_dung) {
        int dem = (int)nguoi.ds_sach_muon.size();
        string ten = nguoi.ho_ten;
        if (ten.empty()) ten = "(Khong co)";
        cout << left << setw(20) << (nguoi.ten_dang_nhap.empty() ? "(Khong co)" : nguoi.ten_dang_nhap)
             << setw(30) << (ten.size() > 28 ? ten.substr(0, 25) + "..." : ten)
             << setw(10) << dem << "\n";
    }
    in_phan_cach();
    tam_dung();
}

// ====== HIEN SACH (don le) ======
void ThuVien::hien_sach(Sach* sach) {
    in_phan_cach();
    cout << "ISBN: " << sach->isbn << "\n";
    doi_mau(14); // Mau vang cho ten sach
    cout << "Ten: " << sach->ten_sach << "\n";
    doi_mau(7);
    cout << "Chu de: " << sach->chu_de << "\n";
    doi_mau(14); // Mau vang cho tac gia
    cout << "Tac gia: " << sach->tac_gia << "\n";
    doi_mau(7);
    if (!sach->dich_gia.empty()) cout << "Dich gia: " << sach->dich_gia << "\n";
    cout << "NXB: " << sach->nxb << "\n";
    cout << "Ngay XB: " << sach->ngay_xb << "\n";
    cout << "So trang: " << sach->so_trang << "\n";
    cout << "So ban: " << sach->so_ban << "\n";
    in_phan_cach();
    cout << "\n";
}

// Helper: can chinh chuoi
static string chen_khoang_trang(const string& s, int do_rong) {
    if ((int)s.length() == do_rong) return s;
    if ((int)s.length() < do_rong) return s + string(do_rong - s.length(), ' ');
    if (do_rong <= 3) return s.substr(0, do_rong);
    return s.substr(0, do_rong - 3) + "...";
}

// Ham: hien thi mot hang (3 sach) dang o ngang ASCII
void ThuVien::hien_tu_sach_ngang(const vector<Sach*>& ds) {
    if (ds.empty()) {
        doi_mau(12);
        cout << "Khong co sach de hien thi.\n";
        doi_mau(7);
        return;
    }

    const int so_sach_moi_hang = 3;
    const int do_rong_noi_dung = 34;
    const string khoang_cach = "   ";

    for (size_t bat_dau = 0; bat_dau < ds.size(); bat_dau += so_sach_moi_hang) {
        size_t ket_thuc = min(bat_dau + so_sach_moi_hang, ds.size());
        // Vien tren
        for (size_t i = bat_dau; i < ket_thuc; ++i) {
            cout << "+" << string(do_rong_noi_dung, '-') << "+";
            if (i + 1 < ket_thuc) cout << khoang_cach;
        }
        cout << "\n";

        // Dong Ten sach
        for (size_t i = bat_dau; i < ket_thuc; ++i) {
            string nhan = "Ten: ";
            string noi_dung = ds[i]->ten_sach;
            string dong = nhan + chen_khoang_trang(noi_dung, do_rong_noi_dung - (int)nhan.length());
            cout << "|";
            doi_mau(14); // Mau vang cho ten sach
            cout << chen_khoang_trang(dong, do_rong_noi_dung);
            doi_mau(7);
            cout << "|";
            if (i + 1 < ket_thuc) cout << khoang_cach;
        }
        cout << "\n";

        // Dong Tac gia
        for (size_t i = bat_dau; i < ket_thuc; ++i) {
            string nhan = "Tac gia: ";
            string noi_dung = ds[i]->tac_gia;
            string dong = nhan + chen_khoang_trang(noi_dung, do_rong_noi_dung - (int)nhan.length());
            cout << "|";
            doi_mau(14); // Mau vang cho tac gia
            cout << chen_khoang_trang(dong, do_rong_noi_dung);
            doi_mau(7);
            cout << "|";
            if (i + 1 < ket_thuc) cout << khoang_cach;
        }
        cout << "\n";

        // Dong Chu de
        for (size_t i = bat_dau; i < ket_thuc; ++i) {
            string nhan = "The loai: ";
            string noi_dung = ds[i]->chu_de;
            string dong = nhan + chen_khoang_trang(noi_dung, do_rong_noi_dung - (int)nhan.length());
            cout << "|" << chen_khoang_trang(dong, do_rong_noi_dung) << "|";
            if (i + 1 < ket_thuc) cout << khoang_cach;
        }
        cout << "\n";

        // Dong NXB + So ban
        for (size_t i = bat_dau; i < ket_thuc; ++i) {
            string trai = "NXB: " + ds[i]->nxb;
            string phai = "So ban: " + to_string(ds[i]->so_ban);
            int do_rong_trai = (int)trai.length();
            int do_rong_phai = (int)phai.length();
            int con_trong = do_rong_noi_dung - 1;
            string dong;
            if (do_rong_trai + do_rong_phai + 1 <= con_trong) {
                int khoang_giua = con_trong - do_rong_trai - do_rong_phai;
                dong = trai + string(khoang_giua, ' ') + phai;
            } else {
                string trai_cat = chen_khoang_trang(trai, max(0, con_trong - do_rong_phai - 1));
                int khoang_giua = max(1, con_trong - (int)trai_cat.length() - do_rong_phai);
                dong = trai_cat + string(khoang_giua, ' ') + phai;
                dong = chen_khoang_trang(dong, do_rong_noi_dung);
            }
            cout << "|" << chen_khoang_trang(dong, do_rong_noi_dung) << "|";
            if (i + 1 < ket_thuc) cout << khoang_cach;
        }
        cout << "\n";

        // Vien duoi
        for (size_t i = bat_dau; i < ket_thuc; ++i) {
            cout << "+" << string(do_rong_noi_dung, '-') << "+";
            if (i + 1 < ket_thuc) cout << khoang_cach;
        }
        cout << "\n\n";
    }
}

// ====== HIEN TAT CA SACH ======
void ThuVien::hien_tat_ca_sach() {
    system("cls");
    in_tieu_de("DANH SACH SACH");
    if (!dau_sach) {
        doi_mau(12);
        cout << "Thu vien chua co sach nao.\n";
        doi_mau(7);
        in_phan_cach();
        tam_dung();
        return;
    }
    vector<Sach*> ds;
    Sach* tmp = dau_sach;
    while (tmp) {
        ds.push_back(tmp);
        tmp = tmp->tiep_theo;
    }
    hien_tu_sach_ngang(ds);
    tam_dung();
}

// ====== HIEN SACH TRONG KHUNG ======
void ThuVien::hien_sach_khung(Sach* sach, int vi_tri) {
    const int do_rong = 35;
    string vien = string(do_rong + 2, '-');
    cout << vien << "\n";

    auto chen = [](const string& chuoi, int tong_rong) {
        string ket_qua = chuoi;
        int can_them = tong_rong - (int)chuoi.length();
        if (can_them > 0) {
            ket_qua += string(can_them, ' ');
        }
        return ket_qua;
    };

    string ten_cat = cat_chu("Ten: " + sach->ten_sach, do_rong);
    cout << "| ";
    doi_mau(14); // Mau vang cho ten sach
    cout << chen(ten_cat, do_rong);
    doi_mau(7);
    cout << "|\n";

    cout << "| " << chen("Chu de: " + sach->chu_de, do_rong) << "|\n";
    cout << "| ";
    doi_mau(14); // Mau vang cho tac gia
    cout << chen("Tac gia: " + sach->tac_gia, do_rong);
    doi_mau(7);
    cout << "|\n";
    if (!sach->dich_gia.empty()) {
        cout << "| " << chen("Dich gia: " + sach->dich_gia, do_rong) << "|\n";
    }
    cout << "| " << chen("NXB: " + sach->nxb, do_rong) << "|\n";
    cout << "| " << chen("Ngay XB: " + sach->ngay_xb, do_rong) << "|\n";
    cout << "| " << chen("So trang: " + to_string(sach->so_trang), do_rong) << "|\n";
    cout << "| " << chen("So ban: " + to_string(sach->so_ban), do_rong) << "|\n";
    cout << vien << "\n";
}

// ====== HIEN SACH NOI BAT ======
void ThuVien::hien_sach_noi_bat() {
    system("cls");
    in_tieu_de("SACH NOI BAT");
    if (!dau_sach) {
        doi_mau(12);
        cout << "Chua co sach nao.\n";
        doi_mau(7);
        in_phan_cach();
        tam_dung();
        return;
    }
    vector<Sach*> ds;
    Sach* tmp = dau_sach;
    int dem = 0;
    while (tmp && dem < 6) {
        ds.push_back(tmp);
        tmp = tmp->tiep_theo;
        dem++;
    }
    hien_tu_sach_ngang(ds);
}

// ====== TIM SACH ======
void ThuVien::tim_sach() {
    system("cls");
    in_tieu_de("TIM KIEM SACH");

    if (!dau_sach) {
        doi_mau(12);
        cout << "Thu vien chua co sach nao.\n";
        doi_mau(7);
        in_phan_cach();
        tam_dung();
        return;
    }

    vector<string> ds_chu_de;
    vector<string> ds_tac_gia;
    vector<string> ds_nxb;

    Sach* tmp = dau_sach;
    while (tmp) {
        if (!tmp->chu_de.empty() && find(ds_chu_de.begin(), ds_chu_de.end(), tmp->chu_de) == ds_chu_de.end()) {
            ds_chu_de.push_back(tmp->chu_de);
        }
        if (!tmp->tac_gia.empty() && find(ds_tac_gia.begin(), ds_tac_gia.end(), tmp->tac_gia) == ds_tac_gia.end()) {
            ds_tac_gia.push_back(tmp->tac_gia);
        }
        if (!tmp->nxb.empty() && find(ds_nxb.begin(), ds_nxb.end(), tmp->nxb) == ds_nxb.end()) {
            ds_nxb.push_back(tmp->nxb);
        }
        tmp = tmp->tiep_theo;
    }

    doi_mau(14); // Mau vang cho goi y tim kiem
    cout << "--- GOI Y TIM KIEM ---\n\n";
    cout << "<< The loai >> : ";
    for (int i = 0; i < min((int)ds_chu_de.size(), 6); ++i) {
        cout << ds_chu_de[i] << (i < 5 && i < (int)ds_chu_de.size() - 1 ? ", " : "");
    }
    if (ds_chu_de.size() > 6) cout << "...";
    cout << "\n\n";

    cout << "<< Tac gia >> : ";
    for (int i = 0; i < min((int)ds_tac_gia.size(), 6); ++i) {
        cout << ds_tac_gia[i] << (i < 5 && i < (int)ds_tac_gia.size() - 1 ? ", " : "");
    }
    if (ds_tac_gia.size() > 6) cout << "...";
    cout << "\n\n";

    cout << "<< NXB >> : ";
    for (int i = 0; i < min((int)ds_nxb.size(), 6); ++i) {
        cout << ds_nxb[i] << (i < 5 && i < (int)ds_nxb.size() - 1 ? ", " : "");
    }
    if (ds_nxb.size() > 6) cout << "...";
    cout << "\n\n";
    doi_mau(7);

    in_phan_cach();

    int loai;
    cout << "Chon tieu chi tim kiem:\n";
    doi_mau(9); // Mau xanh duong cho lua chon
    cout << "1. Theo ten sach\n";
    cout << "2. Theo tac gia\n";
    cout << "3. Theo nha xuat ban\n";
    cout << "4. Theo the loai\n";
    cout << "5. Quay lai\n";
    doi_mau(7);
    cout << "Lua chon: ";

    if (!(cin >> loai)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        doi_mau(12);
        cout << "Lua chon khong hop le.\n";
        doi_mau(7);
        tam_dung();
        return;
    }

    if (loai == 5) return;
    if (loai < 1 || loai > 4) {
        doi_mau(12);
        cout << "Lua chon khong hop le.\n";
        doi_mau(7);
        tam_dung();
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string tu_khoa;
    cout << "Nhap tu khoa tim kiem: ";
    getline(cin, tu_khoa);
    string tu_khoa_thuong = viet_thuong(tu_khoa);

    tmp = dau_sach;
    bool tim_thay = false;
    vector<Sach*> ket_qua;

    while (tmp) {
        bool khop = false;
        switch (loai) {
            case 1:
                if (viet_thuong(tmp->ten_sach).find(tu_khoa_thuong) != string::npos) khop = true;
                break;
            case 2:
                if (viet_thuong(tmp->tac_gia).find(tu_khoa_thuong) != string::npos) khop = true;
                break;
            case 3:
                if (viet_thuong(tmp->nxb).find(tu_khoa_thuong) != string::npos) khop = true;
                break;
            case 4:
                if (viet_thuong(tmp->chu_de).find(tu_khoa_thuong) != string::npos) khop = true;
                break;
        }

        if (khop) { ket_qua.push_back(tmp); tim_thay = true; }
        tmp = tmp->tiep_theo;
    }

    if (!tim_thay) {
        doi_mau(12);
        cout << "\nKhong tim thay sach nao phu hop voi tu khoa '" << tu_khoa << "'.\n";
        doi_mau(7);
        in_phan_cach();
        tam_dung();
        return;
    } else {
        doi_mau(10);
        in_tieu_de("KET QUA TIM KIEM");
        doi_mau(7);
        hien_tu_sach_ngang(ket_qua);
        tam_dung();
    }
}

// ====== THEM NGUOI DUNG MOI ======
void ThuVien::them_nguoi_dung_moi() {
    system("cls");
    in_tieu_de("THEM NGUOI DUNG");
    NguoiDung nguoi_moi;
    nguoi_moi.ma_nguoi_dung = (int)ds_nguoi_dung.size() + 1;

    // Kiem tra ten dang nhap hop le
    bool ten_hop_le = false;
    do {
        cout << "Nhap ten dang nhap: ";
        getline(cin, nguoi_moi.ten_dang_nhap);
        // Loai bo khoang trang dau va cuoi
        while (!nguoi_moi.ten_dang_nhap.empty() && nguoi_moi.ten_dang_nhap.front() == ' ')
            nguoi_moi.ten_dang_nhap.erase(0, 1);
        while (!nguoi_moi.ten_dang_nhap.empty() && nguoi_moi.ten_dang_nhap.back() == ' ')
            nguoi_moi.ten_dang_nhap.pop_back();
        
        if (nguoi_moi.ten_dang_nhap.empty()) {
            doi_mau(12);
            cout << "Ten dang nhap khong duoc de trong. Vui long nhap lai.\n";
            doi_mau(7);
        } else {
            // Kiem tra xem ten dang nhap da ton tai chua
            bool da_ton_tai = false;
            for (const auto& nguoi : ds_nguoi_dung) {
                if (nguoi.ten_dang_nhap == nguoi_moi.ten_dang_nhap) {
                    da_ton_tai = true;
                    break;
                }
            }
            if (da_ton_tai) {
                doi_mau(12);
                cout << "Ten dang nhap da ton tai. Vui long nhap ten khac.\n";
                doi_mau(7);
            } else {
                ten_hop_le = true;
                doi_mau(10);
                cout << "Ten dang nhap da nhap: " << nguoi_moi.ten_dang_nhap << "\n";
                doi_mau(7);
            }
        }
    } while (!ten_hop_le);

    cout << "Nhap ho ten: ";
    getline(cin, nguoi_moi.ho_ten);
    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    getline(cin, nguoi_moi.ngay_sinh);
    cout << "Nhap MSSV: ";
    getline(cin, nguoi_moi.mssv);
    cout << "Nhap mat khau: ";
    getline(cin, nguoi_moi.mat_khau);
    cout << "Nhap vai tro (user/admin): ";
    getline(cin, nguoi_moi.vai_tro);

    int so_sach = 0;
    cout << "Nhap so sach nguoi nay dang muon: ";
    if (!(cin >> so_sach)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        so_sach = 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < so_sach; i++) {
        string ten_sach;
        cout << "  Nhap ten sach thu " << i + 1 << ": ";
        getline(cin, ten_sach);
        nguoi_moi.ds_sach_muon.push_back(ten_sach);
        string ngay_het_han;
        cout << "  Nhap ngay het han (dd/mm/yyyy): ";
        getline(cin, ngay_het_han);
        nguoi_moi.ds_ngay_het_han.push_back(ngay_het_han);
    }

    ds_nguoi_dung.push_back(nguoi_moi);
    doi_mau(10);
    cout << "\nDa them nguoi dung thanh cong! Ten dang nhap: " << nguoi_moi.ten_dang_nhap << "\n";
    doi_mau(7);
    in_phan_cach();
    tam_dung();
}

// ====== XOA NGUOI DUNG ======
void ThuVien::xoa_nguoi_dung(const string& ten_dang_nhap) {
    system("cls");
    in_tieu_de("XOA NGUOI DUNG");
    auto it = find_if(ds_nguoi_dung.begin(), ds_nguoi_dung.end(),
                      [&](const NguoiDung& nguoi) { return nguoi.ten_dang_nhap == ten_dang_nhap; });
    if (it != ds_nguoi_dung.end()) {
        ds_nguoi_dung.erase(it);
        doi_mau(10);
        cout << "Da xoa nguoi dung: " << ten_dang_nhap << "\n";
        doi_mau(7);
    } else {
        doi_mau(12);
        cout << "Khong tim thay nguoi dung.\n";
        doi_mau(7);
    }
    in_phan_cach();
    tam_dung();
}

// ====== SUA NGUOI DUNG ======
void ThuVien::sua_nguoi_dung(const string& ten_dang_nhap) {
    system("cls");
    in_tieu_de("SUA NGUOI DUNG");
    auto it = find_if(ds_nguoi_dung.begin(), ds_nguoi_dung.end(),
                      [&](const NguoiDung& nguoi) { return nguoi.ten_dang_nhap == ten_dang_nhap; });
    if (it == ds_nguoi_dung.end()) {
        doi_mau(12);
        cout << "Khong tim thay nguoi dung.\n";
        doi_mau(7);
        in_phan_cach();
        tam_dung();
        return;
    }
    NguoiDung& nguoi = *it;
    cout << "Nhap ho ten moi (de trong neu khong doi): ";
    string tmp;
    getline(cin, tmp);
    if (!tmp.empty()) nguoi.ho_ten = tmp;
    cout << "Nhap ngay sinh moi (dd/mm/yyyy, de trong neu khong doi): ";
    getline(cin, tmp);
    if (!tmp.empty()) nguoi.ngay_sinh = tmp;
    cout << "Nhap MSSV moi (de trong neu khong doi): ";
    getline(cin, tmp);
    if (!tmp.empty()) nguoi.mssv = tmp;
    cout << "Nhap mat khau moi (de trong neu khong doi): ";
    getline(cin, tmp);
    if (!tmp.empty()) nguoi.mat_khau = tmp;
    cout << "Nhap vai tro moi (user/admin, de trong neu khong doi): ";
    getline(cin, tmp);
    if (!tmp.empty()) nguoi.vai_tro = tmp;
    doi_mau(10);
    cout << "\nCap nhat thanh cong.\n";
    doi_mau(7);
    in_phan_cach();
    tam_dung();
}

// ====== THEM SACH MOI ======
void ThuVien::them_sach_moi() {
    system("cls");
    in_tieu_de("THEM SACH");
    Sach* sach_moi = new Sach;
    cout << "ISBN: ";
    getline(cin, sach_moi->isbn);
    cout << "Ten sach: "; 
    getline(cin, sach_moi->ten_sach);
    cout << "Chu de: "; 
    getline(cin, sach_moi->chu_de);
    cout << "Tac gia: "; 
    getline(cin, sach_moi->tac_gia);
    cout << "Dich gia: "; 
    getline(cin, sach_moi->dich_gia);
    cout << "Nha XB: "; 
    getline(cin, sach_moi->nxb);
    cout << "Ngay XB: "; 
    getline(cin, sach_moi->ngay_xb);
    cout << "So trang: ";
    if (!(cin >> sach_moi->so_trang)) { 
        cin.clear(); 
        sach_moi->so_trang = 0; 
    }
    cout << "So ban copy: ";
    if (!(cin >> sach_moi->so_ban)) { 
        cin.clear(); 
        sach_moi->so_ban = 0; 
    }
    sach_moi->tiep_theo = nullptr;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!dau_sach) dau_sach = sach_moi;
    else {
        Sach* tmp = dau_sach;
        while (tmp->tiep_theo) tmp = tmp->tiep_theo;
        tmp->tiep_theo = sach_moi;
    }
    doi_mau(10);
    cout << "\nDa them sach: " << sach_moi->ten_sach << "\n";
    doi_mau(7);
    in_phan_cach();
    tam_dung();
}

// ====== SUA SACH ======
void ThuVien::sua_sach(const string& ten_sach) {
    system("cls");
    in_tieu_de("SUA SACH");
    Sach* tmp = dau_sach;
    while (tmp) {
        if (tmp->ten_sach == ten_sach) {
            cout << "Nhap thong tin moi cho sach:\n";
            cout << "ISBN: ";
            getline(cin, tmp->isbn);
            cout << "Ten sach: "; 
            getline(cin, tmp->ten_sach);
            cout << "Chu de: "; 
            getline(cin, tmp->chu_de);
            cout << "Tac gia: "; 
            getline(cin, tmp->tac_gia);
            cout << "Dich gia: "; 
            getline(cin, tmp->dich_gia);
            cout << "NXB: "; 
            getline(cin, tmp->nxb);
            cout << "Ngay XB: "; 
            getline(cin, tmp->ngay_xb);
            cout << "So trang: ";
            if (!(cin >> tmp->so_trang)) { 
                cin.clear(); 
                tmp->so_trang = 0; 
            }
            cout << "So ban copy: ";
            if (!(cin >> tmp->so_ban)) { 
                cin.clear(); 
                tmp->so_ban = 0; 
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            doi_mau(10);
            cout << "\nDa cap nhat sach.\n";
            doi_mau(7);
            in_phan_cach();
            tam_dung();
            return;
        }
        tmp = tmp->tiep_theo;
    }
    doi_mau(12);
    cout << "Khong tim thay sach.\n";
    doi_mau(7);
    in_phan_cach();
    tam_dung();
}

// ====== XOA SACH ======
void ThuVien::xoa_sach(const string& ten_sach) {
    system("cls");
    in_tieu_de("XOA SACH");
    Sach* tmp = dau_sach;
    Sach* prev = nullptr;
    while (tmp) {
        if (tmp->ten_sach == ten_sach) {
            if (prev) prev->tiep_theo = tmp->tiep_theo;
            else dau_sach = tmp->tiep_theo;
            delete tmp;
            doi_mau(10);
            cout << "Da xoa sach: " << ten_sach << "\n";
            doi_mau(7);
            in_phan_cach();
            tam_dung();
            return;
        }
        prev = tmp;
        tmp = tmp->tiep_theo;
    }
    doi_mau(12);
    cout << "Khong tim thay sach.\n";
    doi_mau(7);
    in_phan_cach();
    tam_dung();
}

// ====== MUON SACH ======
void ThuVien::muon_sach(const string& ten_dang_nhap, const string& ten_sach) {
    system("cls");
    in_tieu_de("MUON SACH");
    auto it = find_if(ds_nguoi_dung.begin(), ds_nguoi_dung.end(),
                      [&](const NguoiDung& u) { return u.ten_dang_nhap == ten_dang_nhap; });
    if (it == ds_nguoi_dung.end()) {
        doi_mau(12);
        cout << "Khong tim thay nguoi dung: " << ten_dang_nhap << "\n";
        doi_mau(7);
        in_phan_cach();
        tam_dung();
        return;
    }
    NguoiDung& user = *it;
    Sach* tmp = dau_sach;
    while (tmp) {
        if (tmp->ten_sach == ten_sach && tmp->so_ban > 0) {
            tmp->so_ban--;
            user.ds_sach_muon.push_back(ten_sach);
            string dueDate;
            cout << "Nhap ngay het han (dd/mm/yyyy): ";
            getline(cin, dueDate);
            user.ds_ngay_het_han.push_back(dueDate);
            doi_mau(10);
            cout << "\nDa muon sach '" << ten_sach << "' cho nguoi dung '" << ten_dang_nhap << "'\n";
            doi_mau(7);
            in_phan_cach();
            tam_dung();
            return;
        }
        tmp = tmp->tiep_theo;
    }
    doi_mau(12);
    cout << "Sach khong co san hoac da het ban.\n";
    doi_mau(7);
    in_phan_cach();
    tam_dung();
}

// ====== TRA SACH ======
void ThuVien::tra_sach(const string& ten_dang_nhap, const string& ten_sach) {
    system("cls");
    in_tieu_de("TRA SACH");
    auto it = find_if(ds_nguoi_dung.begin(), ds_nguoi_dung.end(),
                      [&](const NguoiDung& u) { return u.ten_dang_nhap == ten_dang_nhap; });
    if (it == ds_nguoi_dung.end()) {
        doi_mau(12);
        cout << "Khong tim thay nguoi dung: " << ten_dang_nhap << "\n";
        doi_mau(7);
        in_phan_cach();
        tam_dung();
        return;
    }
    NguoiDung& user = *it;
    for (size_t i = 0; i < user.ds_sach_muon.size(); ++i) {
        if (user.ds_sach_muon[i] == ten_sach) {
            user.ds_sach_muon.erase(user.ds_sach_muon.begin() + i);
            if (i < user.ds_ngay_het_han.size()) user.ds_ngay_het_han.erase(user.ds_ngay_het_han.begin() + i);
            Sach* tmp = dau_sach;
            while (tmp) {
                if (tmp->ten_sach == ten_sach) {
                    tmp->so_ban++;
                    doi_mau(10);
                    cout << "Da tra sach '" << ten_sach << "' cho nguoi dung '" << ten_dang_nhap << "'\n";
                    doi_mau(7);
                    in_phan_cach();
                    tam_dung();
                    return;
                }
                tmp = tmp->tiep_theo;
            }
            doi_mau(10);
            cout << "Da cap nhat danh sach muon (sach co the da bi xoa khoi thu vien).\n";
            doi_mau(7);
            in_phan_cach();
            tam_dung();
            return;
        }
    }
    doi_mau(12);
    cout << "Khong tim thay sach trong danh sach muon cua nguoi dung.\n";
    doi_mau(7);
    in_phan_cach();
    tam_dung();
}

// ====== KIEM TRA DANG NHAP ======
bool ThuVien::kiem_tra_dang_nhap(const string& ten_dang_nhap, const string& mat_khau, const string& vai_tro) {
    for (auto& u : ds_nguoi_dung)
        if (u.ten_dang_nhap == ten_dang_nhap && u.mat_khau == mat_khau && u.vai_tro == vai_tro)
            return true;
    return false;
}

// ====== MENU QUAN TRI ======
void ThuVien::menu_quan_tri(NguoiDung& curAdmin) {
    int choice;
    while (true) {
        system("cls");
        doi_mau(9); // Mau xanh duong cho thong bao chao mung
        cout << "Chao mung " << curAdmin.ten_dang_nhap << "!\n";
        doi_mau(7);
        in_tieu_de(string("MENU ADMIN (") + curAdmin.ten_dang_nhap + ")");
        doi_mau(9); // Mau xanh duong cho cac lua chon
        cout << "1. Them nguoi dung\n";
        cout << "2. Xoa nguoi dung\n";
        cout << "3. Sua nguoi dung\n";
        cout << "4. Xem danh sach nguoi dung\n";
        cout << "5. Them sach\n";
        cout << "6. Sua sach\n";
        cout << "7. Xoa sach\n";
        cout << "8. Xem tat ca sach\n";
        cout << "9. Tim kiem sach\n";
        cout << "10. Muon sach cho nguoi dung\n";
        cout << "11. Tra sach cho nguoi dung\n";
        cout << "12. Hien thi danh sach nguoi dung tom tat\n";
        cout << "0. Dang xuat\n";
        doi_mau(7);
        cout << "\nLua chon: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            doi_mau(12);
            cout << "Lua chon khong hop le. Thu lai.\n";
            doi_mau(7);
            tam_dung();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // xoa newline sau khi nhap so

        switch (choice) {
        case 1:
            them_nguoi_dung_moi();
            break;
        case 2: {
            string u; 
            cout << "Nhap ten dang nhap can xoa: "; 
            getline(cin, u);
            xoa_nguoi_dung(u);
            break;
        }
        case 3: {
            string u; 
            cout << "Nhap ten dang nhap can sua: "; 
            getline(cin, u);
            sua_nguoi_dung(u);
            break;
        }
        case 4:
            hien_tat_ca_nguoi_dung();
            break;
        case 5:
            them_sach_moi();
            break;
        case 6: {
            string t; 
            cout << "Nhap ten sach can sua: "; 
            getline(cin, t);
            sua_sach(t);
            break;
        }
        case 7: {
            string t; 
            cout << "Nhap ten sach can xoa: "; 
            getline(cin, t);
            xoa_sach(t);
            break;
        }
        case 8:
            hien_tat_ca_sach();
            break;
        case 9:
            tim_sach();
            break;
        case 10: {
            hien_ds_nguoi_dung_tom_tat();
            string u, t;
            cout << "Nhap ten dang nhap nguoi muon: "; 
            getline(cin, u);
            cout << "Nhap ten sach can muon: "; 
            getline(cin, t);
            muon_sach(u, t);
            break;
        }
        case 11: {
            hien_ds_nguoi_dung_tom_tat();
            string u, t;
            cout << "Nhap ten dang nhap nguoi tra: "; 
            getline(cin, u);
            cout << "Nhap ten sach can tra: "; 
            getline(cin, t);
            tra_sach(u, t);
            break;
        }
        case 12:
            hien_ds_nguoi_dung_tom_tat();
            tam_dung();
            break;
        case 0:
            doi_mau(10);
            cout << "Dang xuat admin.\n";
            doi_mau(7);
            tam_dung();
            return;
        default:
            doi_mau(12);
            cout << "Lua chon khong hop le.\n";
            doi_mau(7);
            tam_dung();
        }
    }
}

// ====== MENU NGUOI DUNG ======
void ThuVien::menu_nguoi_dung(NguoiDung& curUser) {
    int choice;
    while (true) {
        system("cls");
        doi_mau(9); // Mau xanh duong cho thong bao chao mung
        cout << "Chao mung " << curUser.ten_dang_nhap << "!\n";
        doi_mau(7);
        in_tieu_de(string("MENU USER (") + curUser.ten_dang_nhap + ")");
        doi_mau(9); // Mau xanh duong cho cac lua chon
        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Xem danh sach sach\n";
        cout << "3. Tim kiem sach\n";
        cout << "4. Muon sach\n";
        cout << "5. Tra sach\n";
        cout << "0. Dang xuat\n";
        doi_mau(7);
        cout << "\nLua chon: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            doi_mau(12);
            cout << "Lua chon khong hop le. Thu lai.\n";
            doi_mau(7);
            tam_dung();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // xoa newline sau khi nhap so

        switch (choice) {
        case 1:
            system("cls");
            hien_nguoi_dung(curUser);
            tam_dung();
            break;
        case 2:
            hien_tat_ca_sach();
            break;
        case 3:
            tim_sach();
            break;
        case 4: {
            string t; 
            cout << "Nhap ten sach can muon: "; 
            getline(cin, t);
            muon_sach(curUser.ten_dang_nhap, t);
            break;
        }
        case 5: {
            string t; 
            cout << "Nhap ten sach can tra: "; 
            getline(cin, t);
            tra_sach(curUser.ten_dang_nhap, t);
            break;
        }
        case 0:
            doi_mau(10);
            cout << "Dang xuat nguoi dung.\n";
            doi_mau(7);
            tam_dung();
            return;
        default:
            doi_mau(12);
            cout << "Lua chon khong hop le.\n";
            doi_mau(7);
            tam_dung();
        }
    }
}

// ====== TAO DU LIEU ======
void ThuVien::tao_du_lieu() {
    NguoiDung admin{ 1, "admin", "123", "admin", "Quan Tri Vien", "01/01/2000", "A000", {}, {} };
    ds_nguoi_dung.push_back(admin);
    NguoiDung user{ 2, "user1", "pass1", "user", "Nguyen Van A", "02/02/2001", "B12345", {"Lap trinh C++"}, {"30/10/2025"} };
    ds_nguoi_dung.push_back(user);

    Sach* tmp = new Sach{"9786041", "Tieng chim hot trong bui man gai", "Tieu thuyet lang man", "Colleen McCullough", "Pham Manh Hung", "NXB Van hoc", "1977", 738, 3, nullptr};
    dau_sach = tmp;

    auto pushBook = [&](const Sach& b) {
        Sach* n = new Sach{b.isbn, b.ten_sach, b.chu_de, b.tac_gia, b.dich_gia, b.nxb, b.ngay_xb, b.so_trang, b.so_ban, dau_sach};
        dau_sach = n;
    };

    pushBook({"9786042", "Ly tri va tinh cam", "Tieu thuyet lang man", "Jane Austen", "Lan Young", "NXB Van hoc", "2018", 412, 5, nullptr});
    pushBook({"9786043", "Neu em khong phai mot giac mo", "Tieu thuyet lang man", "Marc Levy", "Nguyen Thi Bach Tuyet", "NXB Van hoc", "2021", 301, 4, nullptr});
    pushBook({"9788931", "Co Hai Con Meo Ngoi Ben Cua So", "Tieu thuyet lang man", "Nguyen Nhat Anh", "", "NXB Tre", "2012", 208, 6, nullptr});
    pushBook({"9786044", "Ben nhau tron doi", "Tieu thuyet lang man", "Co Man", "Nguyen Thanh Phuoc", "NXB Van hoc", "2007", 437, 3, nullptr});
    pushBook({"9786045", "Thien Son Mo Tuyet", "Tieu thuyet lang man", "Phi Nga Tu Ton", "Phuong Sang", "NXB Van hoc", "2017", 463, 2, nullptr});
    pushBook({"9786046", "Kieu hanh va dinh kien", "Tieu thuyet lang man", "Jane Austen", "Duong Le", "NXB Van hoc", "2018", 536, 4, nullptr});
    pushBook({"9786047", "Su im lang cua bay cuu", "Tieu thuyet trinh tham", "Thomas Harris", "Pham Hong Anh", "NXB Van hoc", "2019", 302, 3, nullptr});
    pushBook({"9786048", "An mang tren chuyen tau toc hanh Phuong Dong", "Tieu thuyet trinh tham", "Agatha Christie", "Nguyen Quang", "NXB Van hoc", "2018", 320, 5, nullptr});
    pushBook({"9786049", "Ke tam xuong", "Tieu thuyet trinh tham", "Jeffery Deaver", "Nguyen Le Chi", "NXB Van hoc", "2015", 512, 2, nullptr});
    pushBook({"97860413", "Xu Cat", "Tieu thuyet khoa hoc vien tuong", "Frank Herbert", "Tran Tien Cao Dang", "NXB Van hoc", "2021", 714, 3, nullptr});
    pushBook({"97860414", "Chua te nhung chiec nhan", "Tieu thuyet gia tuong", "J.R.R. Tolkien", "Nguyen Thi Thu Yen", "NXB Van hoc", "2012", 1500, 2, nullptr});
    pushBook({"9785861", "Sapiens: Luoc Su Loai Nguoi", "Lich su", "Yuval Noah Harari", "Nguyen Thuy Chung", "NXB Tri Thuc", "2021", 554, 5, nullptr});
    pushBook({"97860418", "Bi Mat Cua Alexander Dai De", "Lich su", "Arrian", "Nguyen Vi Thien Ai", "NXB Dan Tri", "2023", 520, 3, nullptr});
    pushBook({"9788934", "Cu Phat Den", "Truyen ngan", "Nguyen Nhat Anh", "", "NXB Kim Dong", "1985", 110, 7, nullptr});
    pushBook({"97860427", "Thanh Pho Thang Tu", "Tho", "Nguyen Nhat Anh", "", "NXB Tac pham moi", "1984", 95, 6, nullptr});
    pushBook({"97860437", "Nguyen ly truyen thong", "Hoc tap nghien cuu", "Nguyen Thi Hong Minh, Nguyen Duc Thuan", "", "NXB Thong tin va Truyen thong", "2019", 356, 2, nullptr});
    pushBook({"97860438", "Ky thuat anten va truyen song", "Hoc tap nghien cuu", "Do Xuan Tien, Nguyen Thi Hong Minh", "", "NXB Bach Khoa Ha Noi", "2020", 412, 2, nullptr});
    pushBook({"97860439", "Mang may tinh va vien thong", "Hoc tap nghien cuu", "Nguyen Van Hiep, Huynh Quyet Thang", "", "NXB Thong tin va Truyen thong", "2018", 420, 3, nullptr});
    pushBook({"97860440", "Ky thuat truyen thong khong day", "Hoc tap nghien cuu", "Theodore S. Rappaport", "PGS.TS. Nguyen Van Duc", "NXB Khoa hoc va Ky thuat", "2010", 888, 1, nullptr});
    pushBook({"97860441", "Digital Design", "Hoc tap nghien cuu", "M. Morris Mano", "Nguyen Trong Thang", "NXB Khoa hoc va Ky thuat", "2013", 720, 2, nullptr});
    pushBook({"97860442", "Electronic Devices and Circuit Theory", "Hoc tap nghien cuu", "Robert L. Boylestad", "Nguyen Huu Loc", "NXB Khoa hoc va Ky thuat", "2011", 972, 1, nullptr});
}

// ====== CHUONG TRINH CHINH ======
void ThuVien::chay() {
    while (true) {
        system("cls");
        hien_sach_noi_bat();

        in_tieu_de("MENU CHINH");
        doi_mau(9); // Mau xanh duong cho cac lua chon
        cout << "1. Tim kiem sach\n";
        cout << "2. Dang nhap\n";
        cout << "3. Thoat\n";
        doi_mau(7);
        cout << "\nLua chon: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            doi_mau(12);
            cout << "\nLua chon khong hop le.\n";
            doi_mau(7);
            tam_dung();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // xoa newline sau khi nhap so

        if (choice == 3) {
            doi_mau(10);
            cout << "Thoat chuong trinh.\n";
            doi_mau(7);
            break;
        } else if (choice == 1) {
            tim_sach();
            continue;
        } else if (choice == 2) {
            cout << "\nBan muon dang nhap voi tu cach:\n";
            doi_mau(9); // Mau xanh duong cho lua chon vai tro
            cout << "1. Nguoi dung\n";
            cout << "2. Quan tri vien (Admin)\n";
            doi_mau(7);
            cout << "Lua chon: ";
            int roleChoice;
            if (!(cin >> roleChoice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                doi_mau(12);
                cout << "Lua chon khong hop le.\n";
                doi_mau(7);
                tam_dung();
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // xoa newline sau khi nhap so

            if (roleChoice != 1 && roleChoice != 2) {
                doi_mau(12);
                cout << "Lua chon khong hop le.\n";
                doi_mau(7);
                tam_dung();
                continue;
            }

            string expectedRole = (roleChoice == 1 ? "user" : "admin");
            string username, password;
            cout << "Nhap username: ";
            getline(cin, username);
            cout << "Nhap password: ";
            getline(cin, password);

            if (!kiem_tra_dang_nhap(username, password, expectedRole)) {
                doi_mau(12);
                cout << "\nDang nhap that bai!\n";
                doi_mau(7);
                in_phan_cach();
                tam_dung();
                continue;
            }

            for (auto& u : ds_nguoi_dung) {
                if (u.ten_dang_nhap == username && u.mat_khau == password && u.vai_tro == expectedRole) {
                    if (expectedRole == "admin") menu_quan_tri(u);
                    else menu_nguoi_dung(u);
                    break;
                }
            }
            continue;
        } else {
            doi_mau(12);
            cout << "Lua chon khong hop le.\n";
            doi_mau(7);
            tam_dung();
            continue;
        }
    }
}

// ====== MAIN ======
int main() {
    system("chcp 65001 > nul"); // UTF-8
    system("mode con: cols=160 lines=50");
    thay_doi_kich_thuoc(160, 50);

    in_giao_dien();

    doi_mau(9); // Mau xanh duong cho thong bao nhan phim
    cout << "\n\nNhan phim bat ky de tiep tuc...";
    doi_mau(7);
    cin.get();

    ThuVien lib;
    lib.chay();
    return 0;
}
