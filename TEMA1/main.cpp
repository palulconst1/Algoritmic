#include <iostream>
#include <fstream>
#include <chrono>
#include<cstdlib>
#include<ctime>


using namespace std;
using namespace std::chrono;

ifstream fin ("numere");
ofstream fout ("testari.out");

long long max_length,MAX_VALUE;
long long v[10000000], n, a[10000000], w[10000000];
long long mx, t, teste;
double start, stop, start1, stop1, start2, stop2, start3, stop3;

int part (long long l[], long long low, long long high)
{
    long long pivot = l[high];
    long long i = (low - 1);
    for (long long j = low; j <= high - 1; j++)
    {
        if (l[j] < pivot)
        {
            i++;
            swap(l[i], l[j]);
        }
    }
    swap(l[i + 1], l[high]);
    return (i + 1);
}

void quick_sort(long long l[], long long low, long long high)
{
    if (low < high)
    {
        long long pi = part(l, low, high);

        quick_sort(l, low, pi - 1);
        quick_sort(l, pi + 1, high);
    }
}

void countSort(long long l[], long long n, long long exp)
{
    long long output[n];
    long long i, x[10] = {0};
    for (i = 0; i < n; i++)
        x[ (l[i]/exp)%10 ]++;
    for (i = 1; i < 10; i++)
        x[i] += x[i - 1];
    for (i = n - 1; i >= 0; i--)
    {
        output[x[ (l[i]/exp)%10 ] - 1] = l[i];
        x[ (l[i]/exp)%10 ]--;
    }
    for (i = 0; i < n; i++)
        l[i] = output[i];
}

void radix_sort(long long l[], long long n)
{
    for (long long exp = 1; mx/exp > 0; exp *= 10)
        countSort(l, n, exp);
}

void citire()
{
    for(long long i=0;i<n;i++)
        {
            fin>>v[i];
            a[i]=v[i];
            if(v[i]>mx)
                mx=v[i];
        }
}

void afisare()
{
    for(long long i=0;i<n;i++)
        fout<<v[i]<<' ';
}

int verificare()
    {
    for(long long i=0;i<n-1;i++)
        if(v[i]>v[i+1])
            return 0;

        return 1;
    }

void count_sort()
    {
        long long j=0;
    for(long long i=0;i<n;i++)
            w[v[i]]++;
    for(long long i=0;i<=mx;i++)
            while(w[i])
            {
                v[j]=i;
                j++;
                w[i]--;
            }
    }

void bubble_sort()
{
    bool ok;
    long long i;
    do
    {
        ok=true;
        for(i=0;i<n-1;i++)
        {
            if(v[i]>v[i+1])
            {
                ok=false;
                swap(v[i], v[i+1]);
            }
        }
    }
    while(!ok);
}

void gen()
{
    ofstream fout ("numere");
    long long len, x;
    srand(time(NULL));
    len=max_length;
    for(long long j = 1; j <= len; j++)
        {
        x = rand();
        x <<= 15;
        x ^= rand();
        x %= MAX_VALUE;
        fout << x << " ";
        if(j%25==0)
            fout<<endl;
        }
    fout.close();
}

void merg(long long arr[], long long l, long long m, long long r)
{
    long long i, j, k;
    long long n1 = m - l + 1;
    long long n2 =  r - m;
    long long L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(long long arr[], long long l, long long r)
{
    if (l < r)
    {
        long long m = l+(r-l)/2;

        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);

        merg(arr, l, m, r);
    }
}

int main()
{
    cout<<"Introduceti numarul de teste, fiecare cu numarul de numere si marimea lor maxima:"<<endl;
    cin>>teste;max_length>>MAX_VALUE;
    for(int k=1; k<=teste;k++)
    {
    cin>>max_length>>MAX_VALUE;
    n=max_length;
    if(max_length<=1000000)
    {
    gen();
    citire();
    if(n)
    {
        if(max_length<10000)
        {
        auto start = high_resolution_clock::now();
        bubble_sort();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        if(verificare())
        {
            fout<<"BUBBLE SORTEAZA BINE! ";
            fout<<"TIMP: "<< duration.count() << endl;
        }
        else
            fout<<"BUBBLE NU SORTEAZA BINE";
        }
        else
            fout<<"Prea multe nr pt BUBBLE "<<endl;
        for(long long y=0;y<n; y++)
        v[y]=a[y];

        if(max_length<=1000000)
        {
        auto start1 = high_resolution_clock::now();
        count_sort();
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        if(verificare())
        {
            fout<<"COUNT SORTEAZA BINE! ";
            fout<<"TIMP: "<< duration1.count() << endl;
        }
        else
            fout<<"COUNT NU SORTEAZA BINE";
        }
        else
            fout<<"Prea multe nr pt COUNT "<<endl;
            for(long long y=0;y<n; y++)
            v[y]=a[y];

        if(max_length<1000000)
            {
        auto start2 = high_resolution_clock::now();
        radix_sort(v, n);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        if(verificare())
        {
            fout<<"RADIX SORTEAZA BINE! ";
            fout<<"TIMP: "<< duration2.count() << endl;
        }
        else
            fout<<"RADIX NU SORTEAZA BINE";
    }
    else
        fout<<"Prea multe nr pt RADIX "<<endl;
        for(long long y=0;y<n; y++)
            v[y]=a[y];
        auto start3 = high_resolution_clock::now();
        quick_sort(v, 0, n-1);
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(stop3 - start3);
        if(verificare())
        {
            fout<<"QUICK SORTEAZA BINE! ";
            fout<<"TIMP: "<< duration3.count() << endl;
        }
        else
            fout<<"QUICK NU SORTEAZA BINE";
            for(long long y=0;y<n; y++)
            v[y]=a[y];
        if(max_length<1000000)
        {
            auto start4 = high_resolution_clock::now();
        merge_sort(v, 0, n-1);
        auto stop4 = high_resolution_clock::now();
        auto duration4 = duration_cast<microseconds>(stop4 - start4);
        if(verificare())
        {
            fout<<"MERGE SORTEAZA BINE! ";
            fout<<"TIMP: "<< duration4.count() << endl;
        }
        else
            fout<<"MERGE NU SORTEAZA BINE";
        }
        else
            fout<<"Prea multe nr pt MERGE "<<endl;
    }
    else
        fout<<"vectorul este vid";
    }
    else
        fout<<"sunt prea multe numere pentru generare"<<endl;
        fout<<endl;
}
}
