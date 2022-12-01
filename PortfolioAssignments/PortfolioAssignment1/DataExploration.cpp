// Name:                    Rikita Patangay
// Class:                   CS4375.003
// Professor:               Mazidi
// Assignment:              Portfolio Component 1: Data Exploration

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

// this is a function to read in the file which we will be gettting data from
void readInFile(string filename, vector<double> &rm, vector<double> &medv)
{
    ifstream inFile(filename);

    // error will be thrown if file cannot be opened
    if (!inFile.is_open())
        throw runtime_error("File could not be opened.");

    string line;
    getline(inFile, line);

    // initializing variable for the rest of the values in the file
    string firstNum;
    string secondNum;

    while (getline(inFile, line))
    {
        stringstream ss(line);

        getline(ss, firstNum, ',');
        getline(ss, secondNum);

        // this is pushes the first value into firstNum and second value into secondNum
        rm.push_back(stof(firstNum));
        medv.push_back(stof(secondNum));
    }
    inFile.close();
}

// get the sum of a vector
double getSum(vector<double> v)
{
    double sumofVector = 0;

    for (int i = 0; i < v.size(); i++)
    {
        sumofVector += v[i];
    }
    // return sum
    return sumofVector;
}

// get the mean of a vector
double getMean(vector<double> v)
{
    // divide the sum of vector by the length
    double mean = getSum(v) / v.size();

    return mean;
}

// get the median of a vector
double getMedian(vector<double> v)
{

    double median;

    // this sorts the vector in ascending values
    sort(v.begin(), v.end());

    // if the length if the vector is even median is average of middle two elements
    if (v.size() % 2 == 0)
    {
        median = (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2;
    }
    // but if the vector length is odd then the median will be the middle element
    else
    {
        median = v[v.size() / 2];
    }
    return median;
}

// get the range of a vector
double getRange(vector<double> v)
{
    // have the max and min values initizalied to crazy high and low numbers
    double maxValue = -1000000000;
    double minValue = 1000000000;

    double range;

    // going through all values in vector
    for (int i = 0; i < v.size(); i++)
    {
        // maxValue = the chosen value if the chosen value is higher than maxValue
        if (v[i] > maxValue)
        {
            maxValue = v[i];
        }

        // if chosen value is less than minValue, minValue= chosen value
        if (v[i] < minValue)
        {
            minValue = v[i];
        }
    }
    // maxValue - minValue is the range
    range = maxValue - minValue;
    return range;
}

// get covariance between the vectors
double calculateCovariance(vector<double> x, vector<double> y)
{
    // get vectors x and y mean
    double meanOfx = getMean(x);
    double meanOfy = getMean(y);

    // calculating numerator for the formula
    double numeratorofCovariance = 0;
    for (int i = 0; i < x.size(); i++)
    {
        numeratorofCovariance += (x[i] - meanOfx) * (y[i] - meanOfy);
    }

    // calculate denominator for formula
    double denominatorofCovariance = x.size() - 1;

    // covariance = numerator/denominator
    double covarianceofVectors = numeratorofCovariance / denominatorofCovariance;

    return covarianceofVectors;
}

// function to get correlation between two vectors x and y
double computeCorrelation(vector<double> x, vector<double> y)
{
    double varianceofX = calculateCovariance(x, x);
    double sigmaX = sqrt(varianceofX);

    double varianceofY = calculateCovariance(y, y);
    double sigmaY = sqrt(varianceofY);

    double covarianceofXY = calculateCovariance(x, y);

    double correlation = covarianceofXY / (sigmaX * sigmaY);

    return correlation;
}

int main()
{
    // initializing the vectors rm and medv
    vector<double> rm;
    vector<double> medv;

    // initializing filename Boston.csv manually
    string filename = "Boston.csv";

    // store data in 2 vectors
    readInFile(filename, rm, medv);

    // Printing out all Stats.

    cout << "\nNumber of records: " << rm.size() << endl;

    cout << "\nStats for rm" << endl;
    cout << "Sum: " << getSum(rm) << "\n";
    cout << "Mean: " << getMean(rm) << "\n";
    cout << "Median: " << getMedian(rm) << "\n";
    cout << "Range: " << getRange(rm) << "\n";

    cout << "\nStats for medv" << endl;
    cout << "Sum: " << getSum(medv) << "\n";
    cout << "Mean: " << getMean(medv) << "\n";
    cout << "Median: " << getMedian(medv) << "\n";
    cout << "Range: " << getRange(medv) << "\n";

    cout << "\nCovariance: " << calculateCovariance(rm, medv) << "\n";
    cout << "Correlation: " << computeCorrelation(rm, medv) << "\n";

    cout << "\n Program terminated." << endl;

    return 0;
}
