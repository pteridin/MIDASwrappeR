#include <iostream>
#include <vector>
#include "anom.h"
#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

//' Get the MIDAS score
//'
//' @param input A data.frame with columns src (source, int), dst (destination, int) & times (timestamp of the edge, int) representing transaction edges
//' @param rows Number of rows/hash functions. Default is 2
//' @param buckets Number of buckets. Default is 769
//' @param alpha Temporal Decay Factor. Only used when 'MIDAS-R' is used. Default is 0.6
//' @param norelations Run 'MIDAS' instead of 'MIDAS-R'. Default is False
//' @param undirected If graph is undirected. Default is False
//' @return NumericVector of MIDAS-Scores
//' @export
// [[Rcpp::export]]
NumericVector getMIDASScore(List input, int rows = 2, int buckets = 769,  double alpha = .6, bool norelations = false, bool undirected = false) {
    if (rows < 1) {
        Rcpp::stop("Number of hash functions should be positive.");
    }

    if (buckets < 2) {
        Rcpp::stop("Number of buckets should be atleast 2");
    }

    if (alpha <= 0 || alpha >= 1) {
        Rcpp::stop("Alpha: Temporal Decay Factor must be between 0 and 1.");
    }

    vector<int> src = as<std::vector<int> >(as<IntegerVector>(input["src"]));
    vector<int> dst = as<std::vector<int> >(as<IntegerVector>(input["dst"]));
    vector<int> times = as<std::vector<int> >(as<IntegerVector>(input["times"]));
    
    if (src.size() == 0) {
        Rcpp::stop("Size of dataset must be greater than 0.");
    }

    if(undirected) {
        vector<int> usrc;
        vector<int> udst;
        vector<int> utimes;
        
        // duplicate entries
        for(long unsigned int i=0; i<src.size(); i++) {
            usrc.push_back(src[i]);
            udst.push_back(dst[i]);
            utimes.push_back(times[i]);
            
            usrc.push_back(dst[i]);
            udst.push_back(src[i]);
            utimes.push_back(times[i]);
        }
        
        // clean up
        src.clear();
        dst.clear();
        times.clear();
        
        src = usrc;
        dst = udst;
        times = utimes;
    }

    

    vector<double>* scores;
    GetRNGstate();
    if (norelations == true)
        scores = midas(src, dst, times, rows, buckets);
    else 
        scores = midasR(src, dst, times, rows, buckets, alpha);
    PutRNGstate();


    return wrap(*scores);
}
