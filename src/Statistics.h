#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>
#include <cmath>

using namespace std;

class Statistics {
    public:

        /** Media para valores discretos. **/
        static double getMean(vector<double> data) {
            double sum = 0.0;
            for(double a : data) {
                sum += a;
            }
            return sum/data.size();
        };

        /** Varianza para valores discretos. **/
        static double getVariance(vector<double> data) {
            double mean = getMean(data);
            double temp = 0;
            for(double a : data) {
                temp += (mean-a)*(mean-a);
            }
            return temp/data.size();
        };

        static double getStdDev(vector<double> data) {
            return sqrt(getVariance(data));
        };


    protected:
    private:
};

#endif // STATISTICS_H
