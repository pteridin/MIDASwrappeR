#include <iostream>
#include <vector>
#include "anom.hpp"
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

//' Get the MIDAS score
//'
//' @param input A data.frame with columns src (source, int), dst (destination, int) & times (timestamp of the edge, int) representing transaction edges
//' @param rows Number of rows/hash functions. Default is 2
//' @param buckets Number of buckets. Default is 769
//' @param alpha Temporal Decay Factor. Default is 0.6
//' @param norelations Run Midas instead of Midas-R. Default is False
//' @param undirected If graph is undirected. Default is False
//' @return NumericVector of MIDAS-Scores
//' @export
// [[Rcpp::export]]
NumericVector getMIDASScore(List input, int rows = 2, int buckets = 769,  double alpha = .6, bool norelations = false, bool undirected = false) {
    if (rows < 1) {
        cerr << "Number of hash functions should be positive." << endl;
        exit(0);
    }

    if (buckets < 2) {
        cerr << "Number of buckets should be atleast 2" << endl;
        exit(0);
    }

    if (alpha <= 0 || alpha >= 1) {
        cerr << "Alpha: Temporal Decay Factor must be between 0 and 1." << endl;
        exit(0);
    }

    vector<int> src = as<std::vector<int>>(as<IntegerVector>(input["src"]));
    vector<int> dst = as<std::vector<int>>(as<IntegerVector>(input["dst"]));
    vector<int> times = as<std::vector<int>>(as<IntegerVector>(input["times"]));
    
    if (src.size() == 0) {
        cerr << "Size of dataset must be greater than 0." << endl;
        exit(0);
    }

    if(undirected) {
        vector<int> usrc(2*src.size());
        vector<int> udst(2*src.size());
        vector<int> utimes(2*src.size());
        
        for(int i = 0; i<src.size();i++) {
            usrc[i] = src[i];
            udst[i] = dst[i];
            utimes[i] = times[i];
            usrc[i] = dst[i];
            udst[i] = src[i];
            utimes[i] = times[i];
        }
        src.clear();
        dst.clear();
        times.clear();
        
        src = usrc;
        dst = udst;
        times = utimes;
    }

    cout << "Finished Loading Data"<< endl;

    vector<double>* scores;
    clock_t start_time = clock();
    if (norelations == true)
        scores = midas(src, dst, times, rows, buckets);
    else
        scores = midasR(src, dst, times, rows, buckets, alpha);

    cout << "Time taken: " << ((double)(clock() - start_time)) / CLOCKS_PER_SEC << " s" << endl;

    return wrap(*scores);
}
