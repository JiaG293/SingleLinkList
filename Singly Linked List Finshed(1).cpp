#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;



struct sinhvien
{
	string hoten;
	string masv;
	string namsinh;
	float dtb;
};
typedef struct sinhvien SINHVIEN;



struct node
{
	SINHVIEN data; 
	struct node *Next;
};
typedef struct node NODE;



struct list
{
	NODE *Head;
	NODE *Tail;
};
typedef struct list LIST;



void KhoiTaoDanhSach(LIST &l)
{
	l.Head = NULL;
	l.Tail = NULL;
}



NODE *KhoiTaoNode(SINHVIEN x)
{
	NODE *p = new NODE;
	if (p == NULL)
	{
		cout << "\nCap phat that bai !";
		return NULL;
	}
	p->data = x;
	p->Next = NULL;
	return p;
}



void ThemDau(LIST &l, NODE *p)
{

	if (l.Head == NULL)
	{
		l.Head = l.Tail = p;
	}
	else
	{
		p->Next = l.Head;
		l.Head = p; 
	}
}



void ThemCuoi(LIST &l, NODE *p)
{

	if (l.Head == NULL)
	{
		l.Head = l.Tail = p; 
	}
	else
	{
		l.Tail->Next = p;
		l.Tail = p; 
	}
}



void XoaDau(LIST &l)
{
	if (l.Head == NULL)
	{
		return;
	}
	NODE *p = l.Head;
	l.Head = l.Head->Next;
	delete p;
}



void XoaCuoi(LIST &l)
{
	if (l.Head == NULL)
	{
		return;
	}
	if (l.Head->Next == NULL)
	{
		XoaDau(l);
		return;
	}
	for (NODE *k = l.Head; k != NULL; k = k->Next)
	{
		if (k->Next == l.Tail)
		{
			delete l.Tail; 
			k->Next = NULL; 
			l.Tail = k;
			return;
		}
	}
}



void Doc_Thong_Tin_1_Sinh_Vien(ifstream &filein, SINHVIEN &sv)
{
	
	getline(filein, sv.hoten, ','); 

	
	getline(filein, sv.masv, ','); 


	getline(filein, sv.namsinh, ',');


	filein >> sv.dtb;


	string temp;
	getline(filein, temp);
}



void Doc_Danh_Sach_Sinh_Vien(ifstream &filein, LIST &l)
{

	while (!filein.eof())
	{
	
		SINHVIEN sv;
		Doc_Thong_Tin_1_Sinh_Vien(filein, sv);
	
		NODE *p = KhoiTaoNode(sv);
	
		ThemCuoi(l, p);
	}
}



void Giai_Phong_Vung_Nho(LIST &l)
{
	NODE *p = NULL;
	while (l.Head != NULL)
	{
		p = l.Head;
		l.Head= l.Head->Next;
		delete p;
	}
}



void Ghi_Thong_Tin_1_Sinh_Vien(ofstream &fileout, SINHVIEN sv)
{
	fileout << sv.hoten << ", ";
	fileout << sv.masv << ", ";
	fileout << sv.namsinh << ", ";
	fileout << sv.dtb;
}



void Hoan_Vi(SINHVIEN &x, SINHVIEN &y)
{
	SINHVIEN tam = x;
	x = y;
	y = tam;
}



void Sap_Xep_Tang_Dan(LIST &l)
{
	for (NODE *k = l.Head; k != NULL; k = k->Next)
	{
		for (NODE *h = k->Next; h != NULL; h = h->Next)
		{
			if (k->data.dtb > h->data.dtb)
				Hoan_Vi(k->data, h->data);
		}
	}
}



void Luu_File_Sap_Xep_Tang_Dan_Diem_Trung_Binh(LIST l)
{
	ofstream fileout;
	fileout.open("sapxepdiemtangdan.txt", ios::out);

	Sap_Xep_Tang_Dan(l);

	for (NODE *k = l.Head; k != NULL; k = k->Next)
	{
		Ghi_Thong_Tin_1_Sinh_Vien(fileout, k->data);
		fileout << endl;
	}
	fileout.close();
}



void Luu_File_Sinh_Vien_Diem_Trung_Binh_Max(LIST l)
{

	float max = l.Head->data.dtb;

	for (NODE *k = l.Head->Next; k != NULL; k = k->Next)
	{
		if (max < k->data.dtb)
			max = k->data.dtb;
	}
	ofstream fileout;
	fileout.open("diemtrungbinhcaonhat.txt", ios::out);

	for (NODE *k = l.Head; k != NULL; k = k->Next)
	{
		if (max == k->data.dtb)
		{
			Ghi_Thong_Tin_1_Sinh_Vien(fileout, k->data);
			fileout << endl;
		}
	}
	fileout.close();
}



string Ten_Sinh_Vien(string tensv)
{
	int length = tensv.length();
	int i;
	for (i = length - 1; i >= 0; i--)
	{
		if (tensv[i] == ' ')
		{
			break;
		}
	}
	return tensv.substr(i + 1);

}



void Xuat(SINHVIEN sv)
{
	cout << "\nHo ten:" << sv.hoten;
	cout << "\nMa sinh vien:" << sv.masv;
	cout << "\nNam sinh:" << sv.namsinh;
	cout << "\nDiem trung binh:" << sv.dtb;
}



void Xuat_Danh_Sach_Sinh_Vien(LIST l)
{
	int dem = 1;
	for (NODE *k = l.Head; k != NULL; k = k->Next)
	{
		cout << "\n\n\t\t SINH VIEN THU " << dem++;
		Xuat(k->data);
	}
}



void Tim_Kiem_Sinh_Vien_Dua_Vao_Ten(LIST l, string tensv)
{
	for (NODE *k = l.Head; k != NULL; k = k->Next)
	{

		string ten = Ten_Sinh_Vien(k->data.hoten);
		if (_stricmp((char *)ten.c_str(), (char *)tensv.c_str()) == 0)
		{
			Xuat(k->data); 
			cout << endl << endl;
		}
	}
}



void Menu() {
	cout <<"|=======================**=DANH SACH LIEN KET=**==============================|" << endl;
	cout <<"|================================MENU=========================================|" << endl;
	cout <<"|                   1. Khoi tao danh sach.                                    |" << endl;
	cout <<"|                   2. Doc danh sach sinh vien.                               |" << endl;
	cout <<"|                   3. Xuat danh sach sinh vien.                              |" << endl;
	cout <<"|                   4. Luu file sinh vien diem trung binh cao nhat.           |" << endl;
	cout <<"|                   5. Sap xep diem trung binh tang dan.                      |" << endl;
	cout <<"|                   6. Luu file sap xep diem trung binh sinh vien tang dan.   |" << endl;
	cout <<"|                   7. Tim kiem sinh vien dua vao ten.                        |" << endl;
	cout <<"|                   8. Giai phong vung nho.                                   |" << endl;
	cout <<"|                   10. Thoat.                                                |" << endl;
	cout <<"|=============================================================================|\n";
	
}



int ChonMenu()
{
	int n = 0;
	cout << " " << endl;
	cout << "=> Moi chon menu:      " ;
	cin >> n; 
	
	
	if (n > 0 || n < 10)
		return n;
	else return ChonMenu();
}



void XuLyMenu() 
{	
	LIST l;
	SINHVIEN x; 
	string tensinhvien;
	ifstream filein;
	filein.open("sinhvien.txt",ios::in);
	
	int chon = ChonMenu();
	switch (chon)
	{
	case 1:		
		cout << "1. Khoi tao danh sach." << endl;
		KhoiTaoDanhSach(l);
		break;
	case 2:
		cout << "2. Doc Danh sach sinh vien. " << endl;
		Doc_Danh_Sach_Sinh_Vien(filein,l);
		break;
	case 3:
		cout << "3. Xuat danh sach sinh vien." << endl;
		XoaCuoi(l); 
		Xuat_Danh_Sach_Sinh_Vien(l);
		cout<< "\n-------------------an Y de xoa va an bat kia bo qua--------------------"<<endl;
		char xoa[2];
		cin>>xoa;
		if(sizeof(xoa)==sizeof("Y")||sizeof(xoa)==sizeof("y"))
			system("cls");
		break;
	case 4:
		cout << "4. Luu file sinh vien diem trung binh cao nhat." << endl;
		Luu_File_Sinh_Vien_Diem_Trung_Binh_Max(l);
		cout<< "Luu file thanh cong.";
		break;
	case 5:
		cout << "5. Sap xep diem trung binh tang dan." << endl;
		Sap_Xep_Tang_Dan(l);
		cout<< "Sap xep thanh cong.";	
		break;
	case 6:
		cout << "6. Luu file sap xep diem trung binh sinh vien tang dan." << endl;
		Luu_File_Sap_Xep_Tang_Dan_Diem_Trung_Binh(l);
		cout<< "Luu file thanh cong.";
		break;
	case 7:
		cout << "7. Tim kiem sinh vien dua vao ten." << endl;
		cout<<"nhap ten sinh vien can tim: ";cin>>tensinhvien; 
		Tim_Kiem_Sinh_Vien_Dua_Vao_Ten(l,tensinhvien);
		break;
	case 8:
		cout<< "8. Giai phong vung nho.";
		Giai_Phong_Vung_Nho(l);
		cout<< "Giai phong vung nho thanh cong.";
		break;
	case 10:
		cout << "Thoat!!!\n" << endl;
		exit(1);
		break;
	}
}



int main()
{	
	
		Menu();
		
	while (true)
	{	
		XuLyMenu();
	}
	
	return 0;
}