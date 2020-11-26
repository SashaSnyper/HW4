#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

/**
 * Удаляет из вектора все повторения и сортирует его
 * @param v
 * @return
 */
vector<int> getSet(vector<int> v) {
    sort(v.begin(), v.end());
    vector <int>::iterator it;
    it = unique_copy (v.begin(), v.end(), v.begin());
    v.resize(distance(v.begin(), it));
    return v;
}

/**
 * ВВод вектора
 * @param name
 * @return
 */
vector<int> getVector(const string& name){
    vector<int> v;
    int item;
    cout << "Size of " << name << "=";
    int len;
    cin >> len;
    for (int i = 0; i < len; i++){
        cout << name << "[" << i << "]=";
        cin >> item;
        v.push_back(item);
    }
    return getSet(v);
}

int main ()
{
    // Задаю вектор вручную, т.к. не все гладко с рандомом в c++ как в c#,
    // К тому же это все-таки самый удобный вариант для тестирования правильности работы программы
    vector<int> A = getVector("A");
    vector<int> B = getVector("B");
    vector<int> C = getVector("C");
    bool ans1;
    bool ans2;
    bool ans3;
    bool ans4;
#pragma omp parallel sections
    {
#pragma omp section
        {
            vector<int> t;
            set_union(A.begin(), A.end(),
                             B.begin(), B.end(),
                             back_inserter(t));
            ans1 = (t == C);
            //Можно использовать для наглядности оптимизации выполнения с omp
            //sleep(1);
        }
#pragma omp section
        {
            vector<int> t;
            set_intersection(A.begin(), A.end(),
                      B.begin(), B.end(),
                      back_inserter(t));
            ans2 = (t == C);
            //sleep(1);
        }
#pragma omp section
        {
            vector<int> t;
            set_difference(A.begin(), A.end(),
                             B.begin(), B.end(),
                             back_inserter(t));
            ans3 = (t == C);
            //sleep(1);
        }
#pragma omp section
        {
            vector<int> t;
            set_difference(B.begin(), B.end(),
                             A.begin(), A.end(),
                             back_inserter(t));
            ans4 = (t == C);
            //sleep(1);
        }
    }
    string out1 = ans1 ? "true" : "false";
    cout << "C=AuB-" << out1 << endl;
    string out2 = ans2 ? "true" : "false";
    cout << "C=AnB-" << out2 << endl;
    string out3 = ans3 ? "true" : "false";
    cout << "C=A/B-" << out3 << endl;
    string out4 = ans4 ? "true" : "false";
    cout << "C=B/A-" << out4 << endl;
    return 0;
}
