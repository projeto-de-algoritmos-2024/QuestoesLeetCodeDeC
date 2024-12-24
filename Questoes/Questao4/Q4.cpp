#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class MedianElement {
private:
    vector<int> vector_1, vector_2;

public:
  MedianElement(vector<int> &vector_1, vector<int> &vector_2) {
    sort(vector_1.begin(), vector_1.end());
    sort(vector_2.begin(), vector_2.end());
    this->vector_1 = vector_1;
    this->vector_2 = vector_2;
  }

  int getElement(int min_k) {
    int index_v1 = 0, index_v2 = 0; 

    while (true) {
      if (index_v1 == vector_1.size())
        return vector_2[index_v2 + min_k - 1];

      if (index_v2 == vector_2.size()) 
        return vector_1[index_v1 + min_k - 1];
    

      if (min_k == 1)
        return min(vector_1[index_v1], vector_2[index_v2]);
          

      int newIndex1 = min(index_v1 + min_k / 2 - 1, (int)vector_1.size() - 1);
      int newIndex2 = min(index_v2 + min_k / 2 - 1, (int)vector_2.size() - 1);

      int pivot1 = vector_1[newIndex1];
      int pivot2 = vector_2[newIndex2];

      if (pivot1 <= pivot2) {
        min_k -= (newIndex1 - index_v1 + 1);
        index_v1 = newIndex1 + 1;
      } else {
        min_k -= (newIndex2 - index_v2 + 1);
        index_v2 = newIndex2 + 1;
      }
    }
  }
};

double CalcMedian(vector<int>& vector_1, vector<int>& vector_2) {
    int len = vector_1.size() + vector_2.size();
    MedianElement median(vector_1, vector_2);

    if (len % 2 == 1) {
        return median.getElement(len / 2 + 1);
    } else {
        return (median.getElement(len / 2) + median.getElement(len / 2 + 1)) / 2.0;
    }
}

//descomente para testar localmente

int main() {
    vector<int> vector_1 = {1, 3};
    vector<int> vector_2 = {2};
    cout << "Mediana: " << CalcMedian(vector_1, vector_2) << endl;

    vector_1 = {1, 2};
    vector_2 = {3, 4};
    cout << "Mediana: " << CalcMedian(vector_1, vector_2) << endl; 

    vector_1 = {0, 0};
    vector_2 = {0, 0};
    cout << "Mediana: " << CalcMedian(vector_1, vector_2) << endl;

    vector_1 = {};
    vector_2 = {1};
    cout << "Mediana: " << CalcMedian(vector_1, vector_2) << endl; 

    vector_1 = {2};
    vector_2 = {};
    cout << "Mediana: " << CalcMedian(vector_1, vector_2) << endl; 

    return 0;
}


