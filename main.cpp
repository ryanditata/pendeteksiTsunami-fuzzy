#include <iostream>
#include <iomanip>
using namespace std;

void fuzzification(float x, float a, float b, float c, float &u1, float &u2, float &u3) {
    if (x <= a) u1 = 1;
    else if (x > a && x < b) u1 = (b - x) / (b - a);
    else u1 = 0;

    if (x <= a || x >= c) u2 = 0;
    else if (x > a && x < b) u2 = (x - a) / (b - a);
    else if (x > b && x < c) u2 = (c - x) / (c - b);
    else if (x == b) u2 = 1;

    if (x <= b) u3 = 0;
    else if (x > b && x < c) u3 = (x - b) / (c - b);
    else u3 = 1;
}

void and_rules(float f1, float f2, float f3, float temp, float &conclusion) {
    if (f1 >= f2) temp = f2;
    else if (f1 >= f3) temp = f3;
    else temp = f1;
    if (temp >= conclusion) conclusion = temp;
}

void determine_sample(float a, float b, float c, float d, float &s1, float &s2, float &s3) {
    s1 = (a + b) / 2;
    s2 = (b + c) / 2;
    s3 = (c + d) / 2;
}

void defuzzification(float u1, float u2, float u3, float s1, float s2, float s3, float &result) {
    result = ((u1 * s1) + (u2 * s2) + (u3 * s3)) / (u1 + u2 + u3);
}

void range(float resiko_tsunami, int a=30, int b=70){
    if (resiko_tsunami <= a)
        cout << "RESIKO TSUNAMI RENDAH" << endl;
    else if (resiko_tsunami <= b)
        cout << "RESIKO TSUNAMI SEDANG" << endl;
    else
        cout << "RESIKO TSUNAMI TINGGI" << endl;
}

int main()
{
    float gelombang_laut, kecepatan_gempa, jarak_episenter;
    float uRendah, uSedang1, uTinggi;
    float uLambat, uSedang2, uCepat;
    float uDekat, uSedang3, uJauh;
    float rendah, sedang, tinggi;
    float sample1, sample2, sample3;
    float resiko_tsunami;

    cout << fixed << setprecision(2);

    cout << "==================================================" << endl;
    cout << "MASUKKAN KETINGGIAN GELOMBANG LAUT   (meter): ";
    cin >> gelombang_laut;
    cout << "MASUKKAN KECEPATAN GEMPA             (detik): ";
    cin >> kecepatan_gempa;
    cout << "MASUKKAN JARAK EPISENTER KE PANTAI      (km): ";
    cin >> jarak_episenter;
    cout << "==================================================" << endl;

    fuzzification(gelombang_laut, 1, 2, 3, uRendah, uSedang1, uTinggi);
    fuzzification(kecepatan_gempa, 3, 5, 7, uLambat, uSedang2, uCepat);
    fuzzification(jarak_episenter, 50, 75, 100, uDekat, uSedang3, uJauh);

    cout << "\nFuzzifikasi Ketinggian Gelombang Laut:" << endl;
    cout << "Rendah: " << uRendah << endl;
    cout << "Sedang: " << uSedang1 << endl;
    cout << "Tinggi: " << uTinggi << endl;

    cout << "\nFuzzifikasi Kecepatan Gempa:" << endl;
    cout << "Lambat: " << uLambat << endl;
    cout << "Sedang: " << uSedang2 << endl;
    cout << "Cepat : " << uCepat << endl;

    cout << "\nFuzzifikasi Jarak Episenter Ke Pantai:" << endl;
    cout << "Dekat : " << uDekat << endl;
    cout << "Sedang: " << uSedang3 << endl;
    cout << "Jauh  : " << uJauh << endl;

    sedang = rendah = tinggi = 0;
    and_rules(uRendah, uLambat, uDekat, sedang, sedang);
    and_rules(uRendah, uSedang2, uSedang3, rendah, rendah);
    and_rules(uRendah, uCepat, uJauh, rendah, rendah);
    and_rules(uSedang1, uLambat, uDekat, tinggi, tinggi);
    and_rules(uSedang1, uSedang2, uSedang3, tinggi, tinggi);
    and_rules(uSedang1, uCepat, uJauh, rendah, rendah);
    and_rules(uTinggi, uLambat, uDekat, tinggi, tinggi);
    and_rules(uTinggi, uSedang2, uSedang3, tinggi, tinggi);
    and_rules(uTinggi, uCepat, uJauh, sedang, sedang);

    cout << "\nKesimpulan Resiko Tsunami:" << endl;
    cout << "Rendah: " << rendah << endl;
    cout << "Sedang: " << sedang << endl;
    cout << "Tinggi: " << tinggi << endl;

    determine_sample(0 , 75, 80, 80, sample1, sample2, sample3);

    cout << "\nSampel untuk Defuzzifikasi:" << endl;
    cout << "Rendah: " << sample1 << " %" << endl;
    cout << "Sedang: " << sample2 << " %" << endl;
    cout << "Tinggi: " << sample3 << " %" << endl;

    defuzzification(rendah, sedang, tinggi, sample1, sample2, sample3, resiko_tsunami);

    cout << "\n==================================================" << endl;
    cout << resiko_tsunami << " %" << endl;
    range(resiko_tsunami);
    cout << "==================================================" << endl;

    return 0;
}
