#include<bits/stdc++.h>
using namespace std;
string menu="\t+-----+--------------------------------+-------+-------+\n \t| STT | Ho Ten                         | Tuoi  | Diem  |\n \t+-----+--------------------------------+-------+-------+\n";
// khởi tạo 1 struct sinh viên ( mang những thông tin chung về sinh viên)
struct sinhVien {
    string fullName;
    int age;
    float score;
    sinhVien() {
        fullName = "";
        age = 0;
        score = 0;
    }
};
// hàm nhập thông tin sinh viên
sinhVien nhapThongTin() {
    sinhVien info;
    cout<<"Nhap ten : ";
    getline(cin,info.fullName);
    cout<<"Nhap tuoi: ";
    cin>>info.age;
    cout<<"Nhap diem: ";
    cin>>info.score;
    return info;
}
// hàm chuyển thành chữ in thường
void chuyen_in_thuong(string &s) {
    for (int i = 0; i < s.length(); i++) {
        s[i]=tolower(s[i]);
    }
}
// đọc dữ liệu từ file
vector<sinhVien> doc_file(const string &ten_file) {
    vector<sinhVien> danhSach;
    ifstream file(ten_file);
    string line;
    while (getline(file,line)) {
        stringstream ss(line);
        sinhVien info;
        string score_str, age_str;
        getline(ss, info.fullName,';');
        getline(ss, age_str,';');
        getline(ss, score_str,';');
        info.age = stoi(age_str);
        info.score = stof(score_str);
        danhSach.push_back(info);
    }
    return danhSach;
}
// ghi dữ liệu vào file
void ghi_vao_file(const string &tenFile,const vector<sinhVien>& danhSach) {
    ofstream file(tenFile);
    for (const auto &x : danhSach) {
        file << x.fullName<<";"<< x.age << ";" << x.score<<";\n";
    }
}

// hàm thêm sinh viên
sinhVien them_sinh_vien(vector<sinhVien> &danhSach) {
    cin.ignore();
    sinhVien moi = nhapThongTin();
    danhSach.push_back(moi);
    ghi_vao_file("D:\\DO_AN\\ThongTin.txt",danhSach);
    cout << "Da them sinh vien vao danh sach\n";
    return moi;
}
//hàm sửa sinh viên có số thứ tự n;
void sua_sinh_vien(vector<sinhVien> &danhSach) {
    int stt;
    cout<<"Nhap so thu tu sinh vien can sua: ";
    cin >> stt;
    if (stt < 1 || stt > danhSach.size()) {
        cout << "\t(!) Vi tri khong hop le\n";
        return;
    }
    cin.ignore();
    sinhVien &change = danhSach[stt-1];
    cout << "\t\t(?) Nhap ten moi (nhap enter bo qua neu khong sua): ";
    string newName;
    getline(cin, newName);
    if(!newName.empty()){
        change.fullName = newName;
    }
    cout << "\t\t(?) Nhap tuoi moi (nhap 0 bo qua neu khong sua): ";
    int newAge; cin >> newAge;
    if(newAge > 0){
        change.age = newAge;
    }
    cout << "\t\t(?) Nhap diem moi (nhap -1 bo qua neu khong sua): ";
    float newScore;
    cin >> newScore;
    if (newScore >= 0) {
        change.score = newScore;
    }
    ghi_vao_file("D:\\DO_AN\\ThongTin.txt", danhSach);
    cin.ignore();
    cout << "\t(*) Da cap nhat thanh cong thong tin sinh vien so thu tu " << stt << "\n";
}
// hàm xoá sinh viên khỏi danh sách
void xoa_sinh_vien(vector< sinhVien> &danhSach) {
    int stt;
    cout << " Nhap so thu tu cua sinh vien can xoa: ";
    cin >> stt;
    if (stt < 1 || stt > danhSach.size()) {
        cout << "\t(!) Vi tri khong hop le\n";
    }
    else {
        danhSach.erase(danhSach.begin() + stt-1);
        ghi_vao_file("D:\\DO_AN\\ThongTin.txt",danhSach);
        cout<<"\t Da xoa thanh cong sinh vien so thu tu " << stt << endl;
    }
}
void tim_kiem(const vector<sinhVien> &danhSach) {
    int lua_chon;
    cout << "\t1 - tim kiem theo so thu tu\n";
    cout << "\t2 - tim kiem theo ky tu ten\n";
    cout << "\t(?) Nhap lua chon: "; cin >> lua_chon;
    if (lua_chon==1) {
        cout <<"\t\t Moi ban nhap so thu tu can tim: ";
        int x;
        cin >> x;
        if (x < 1 || x > danhSach.size() ) {
            cout << "\t(!) Vi tri khong hop le\n";
        }
        else {
            cout << menu;
            int stt = x;
           const sinhVien &tt = danhSach[stt-1];
            cout << "\t| " << setw(3) << left<< stt << " | "
               << setw(30) << left << tt.fullName << " | "
               << setw(5) << left << tt.age << " | "
               << setw(5) << left<< fixed << setprecision(1) << tt.score << " |\n";
            cout << "\t+-----+--------------------------------+-------+-------+\n";
        }
    }
    else{
            cout << "\t\tMoi ban nhap ki tu: ";
            cin.ignore();
            string check;
            cin>>check;
            vector<sinhVien> danhSachTimKiem;
            for (const auto& tt1 : danhSach) {
                string name = tt1.fullName;
                chuyen_in_thuong(name);
                if (name.find(check) != string::npos) {
                    danhSachTimKiem.push_back(tt1);
                }
            }
            if (danhSachTimKiem.empty()) {
                cout << "\t(!)Khong tim thay sinh vien nao phu hop!\n";
            }
            else {
                cout << menu;
                int stt = 1;
                for (const auto& tt2 : danhSachTimKiem) {
                    cout << "\t| " << setw(3) << left<< stt++ << " | "
                       << setw(30) << left << tt2.fullName << " | "
                       << setw(5) << left << tt2.age << " | "
                       << setw(5) << left<< fixed << setprecision(1) << tt2.score << " |\n";
                    cout << "\t+-----+--------------------------------+-------+-------+\n";
                }
            }
    }

}
// sắp xếp danh sách sinh viên theo điểm
void sap_xep(vector<sinhVien> &danhSach) {
    for (int i = 0; i < danhSach.size(); i++) {
        sinhVien &sapXep = danhSach[i];
        for (int j = i + 1;j < danhSach.size();j++) {
            sinhVien &sapXep2 = danhSach[j];
            if (sapXep.score < sapXep2.score) {
                swap(sapXep, sapXep2);
            }
            else {
                continue;
            }
        }
    }
    ghi_vao_file("D:\\DO_AN\\ThongTin.txt",danhSach);
    cout <<"Da sap xep danh sach theo thu tu diem giam dan!\n";
}
// thống kê tỉ lệ học sinh và điểm trung bình
void thong_ke(vector<sinhVien> &danhSach) {
    float diemTB=0;
    float max=-1e9;
    int sinhVienGioi=0,sinhVienKha=0,sinhVienKem=0;
    for (const auto&thongKe : danhSach) {
        diemTB+=thongKe.score;
        if (thongKe.score >=8.0) sinhVienGioi++;
        else if (thongKe.score >=6.5) sinhVienKha++;
        else sinhVienKem++;
        if (thongKe.score > max) max = thongKe.score;
    }
    cout <<"\t(!)Diem trung binh ca lop: "<<diemTB*1.0/danhSach.size()<<endl;
    cout <<"\t(!)Ti le sinh vien gioi: "<<sinhVienGioi*100.0/danhSach.size()<<"%"<<endl;
    cout <<"\t(!)Ti le sinh vien kha: "<<sinhVienKha*100.0/danhSach.size()<<"%"<<endl;
    cout <<"\t(!)Ti le sinh vien kem: "<<sinhVienKem*100.0/danhSach.size()<<"%"<<endl;
    for (const auto& thongKe : danhSach) {
        cout << "\t\t" << thongKe.fullName <<" "<<thongKe.score<<" "<<endl;
    }
}
//sao lưu vào file
void sao_luu(const vector<sinhVien> &danhSach) {
    cout <<"\t(!) Dang sao luu du lieu: "<<endl;
    ghi_vao_file("D:\\DO_AN\\ThongTin.txt",danhSach);
    cout<<"\t(!)Da sao luu thanh cong!"<<endl;
}
//in ra danh sách sinh viên
void display(const vector<sinhVien> &danhSach){
    cout << menu;
    int stt = 1;
    for (const auto& tt : danhSach) {
        cout << "\t| " << setw(3) << left<< stt++ << " | "
           << setw(30) << left << tt.fullName << " | "
           << setw(5) << left << tt.age << " | "
           << setw(5) << left<< fixed << setprecision(1) << tt.score << " |\n";
    }
    cout << "\t+-----+--------------------------------+-------+-------+\n";
}
int main(){
    cout <<"***********CHUONG TRINH QUAN LY SINH VIEN***********\n";
   while (true) {
       int choice;
        cout << "1 - In theo danh sach\n";
        cout << "2 - Them\n";
        cout << "3 - Sua\n";
        cout << "4 - Xoa\n";
        cout << "5 - Tim kiem\n";
        cout << "6 - Sap xep\n";
        cout << "7 - Thong ke\n";
        cout << "8 - Sao luu\n";
        cout << "9 - Thoat\n";
        cout << "[-->] Nhap lenh: ";
        cin >> choice;
        vector<sinhVien> danhSach=doc_file("D:\\DO_AN\\ThongTin.txt");
        switch (choice) {
            case 1:
                display(danhSach);
                break;
            case 2:
                them_sinh_vien(danhSach);
                break;
            case 3:
                sua_sinh_vien(danhSach);
                break;
            case 4:
                xoa_sinh_vien(danhSach);
                break;
            case 5:
                tim_kiem(danhSach);
                break;
            case 6:
                sap_xep(danhSach);
                break;
            case 7:
                thong_ke(danhSach);
                break;
            case 8:
                sao_luu(danhSach);
                break;
            case 9:
                return 0;
            default:
                break;
        }
    }
}