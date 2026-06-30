#include <iostream>
using namespace std;

class MangDong
{
private:
    int* duLieu;
    int soLuong;
    int sucChua;

    // tăng kích thước khi đầy
    void moRong()
    {
        sucChua *= 2;

        int* moi = new int[sucChua];

        for (int i = 0; i < soLuong; i++)
        {
            moi[i] = duLieu[i];
        }

        delete[] duLieu;
        duLieu = moi;
    }

public:
    // khởi tạo
    MangDong()
    {
        sucChua = 5;
        soLuong = 0;
        duLieu = new int[sucChua];
    }

    // huỷ
    ~MangDong()
    {
        delete[] duLieu;
    }

    // thêm cuối
    void themCuoi(int giaTri)
    {
        if (soLuong == sucChua)
        {
            moRong();
        }

        duLieu[soLuong] = giaTri;
        soLuong++;
    }

    // thêm đầu
    void themDau(int giaTri)
    {
        if (soLuong == sucChua)
        {
            moRong();
        }

        for (int i = soLuong; i > 0; i--)
        {
            duLieu[i] = duLieu[i - 1];
        }

        duLieu[0] = giaTri;
        soLuong++;
    }

    // chèn vào vị trí
    void chen(int viTri, int giaTri)
    {
        if (viTri < 0 || viTri > soLuong)
        {
            cout << "Vi tri khong hop le\n";
            return;
        }

        if (soLuong == sucChua)
        {
            moRong();
        }

        for (int i = soLuong; i > viTri; i--)
        {
            duLieu[i] = duLieu[i - 1];
        }

        duLieu[viTri] = giaTri;
        soLuong++;
    }

    // xoá theo vị trí
    void xoaTai(int viTri)
    {
        if (viTri < 0 || viTri >= soLuong)
        {
            cout << "Vi tri khong hop le\n";
            return;
        }

        for (int i = viTri; i < soLuong - 1; i++)
        {
            duLieu[i] = duLieu[i + 1];
        }

        soLuong--;
    }

    // xoá cuối
    void xoaCuoi()
    {
        if (soLuong == 0)
        {
            cout << "Mang rong\n";
            return;
        }

        soLuong--;
    }

    // tìm giá trị
    int tim(int giaTri)
    {
        for (int i = 0; i < soLuong; i++)
        {
            if (duLieu[i] == giaTri)
            {
                return i;
            }
        }
        return -1;
    }

    // lấy giá trị
    int lay(int viTri)
    {
        if (viTri < 0 || viTri >= soLuong)
        {
            return -1;
        }

        return duLieu[viTri];
    }

    // sửa giá trị
    void gan(int viTri, int giaTri)
    {
        if (viTri < 0 || viTri >= soLuong)
        {
            return;
        }

        duLieu[viTri] = giaTri;
    }

    // số phần tử
    int laySoLuong()
    {
        return soLuong;
    }

    // sức chứa
    int laySucChua()
    {
        return sucChua;
    }

    // rỗng hay không
    bool rong()
    {
        return soLuong == 0;
    }

    // xoá hết
    void xoaHet()
    {
        soLuong = 0;
    }

    // in mảng
    void in()
    {
        cout << "Mang: ";

        for (int i = 0; i < soLuong; i++)
        {
            cout << duLieu[i] << " ";
        }

        cout << endl;
    }
};

int main()
{
    MangDong arr;

    arr.themCuoi(10);
    arr.themCuoi(20);
    arr.themCuoi(30);

    arr.in();

    arr.themDau(5);

    arr.in();

    arr.chen(2, 100);

    arr.in();

    arr.xoaTai(1);

    arr.in();

    arr.xoaCuoi();

    arr.in();

    cout << "Tim 100 tai vi tri: " << arr.tim(100) << endl;

    cout << "So luong: " << arr.laySoLuong() << endl;

    cout << "Suc chua: " << arr.laySucChua() << endl;

    return 0;
}