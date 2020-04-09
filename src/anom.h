#ifndef anom_h
#define anom_h

#include <vector>
using namespace std;

vector<double>* midas(vector<int>& src, vector<int>& dst, vector<int>& times, int num_rows, int num_buckets);
vector<double>* midasR(vector<int>& src, vector<int>& dst, vector<int>& times, int num_rows, int num_buckets, double factor);

#endif /* anom_hpp */
