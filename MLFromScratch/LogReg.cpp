
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

const int MAXIMUM_VALUE = 1046;

class dataField
{
    // vectors defined and initialized
public:
    vector<double> X;
    vector<double> peoplewhoSurvived;
    vector<double> pclass;
    vector<double> sexOfPerson;
    vector<double> ageOfPerson;
    int numOfinstances;
};

// this is used for storing the values in a matrix
class Matrix
{
private:
    int rowsOfMatrix = 1;
    int columnsofMatrix = 1;

public:
    Matrix(int x, int y) : rowsOfMatrix(x), columnsofMatrix(y), matrixVals(rowsOfMatrix * columnsofMatrix) {}

    void setMatrixValue(int x, int y, double value) { matrixVals[x * columnsofMatrix + y] = value; }

    double getMatrixValue(int x, int y) { return matrixVals[x * columnsofMatrix + y]; }

    int getMatrixRows() { return rowsOfMatrix; }

    int getMatrixColumns() { return columnsofMatrix; }

    int getMatrixSize() { return rowsOfMatrix * columnsofMatrix; }

    vector<double> matrixVals;

    // fill matrix with vector
    void fillMat(vector<double> x)
    {
        if (x.size() == rowsOfMatrix * columnsofMatrix)
        {
            for (int i = 0; i < columnsofMatrix; i++)
            {
                for (int j = 0; j < columnsofMatrix; j++)
                {
                    matrixVals[i * columnsofMatrix + j] = x[i * columnsofMatrix + j];
                }
            }
        }
    }
    // print matrix rows
    void printMat()
    {
        for (int i = 0; i < rowsOfMatrix; i++)
        {
            for (int j = 0; j < columnsofMatrix; j++)
            {
                cout << matrixVals[i * columnsofMatrix + j] << "   ";
            }
        }
    }

    // gets a vector that has the column
    vector<double> getColumnVector(int col)
    {
        vector<double> columnVector;
        columnVector.resize(rowsOfMatrix);
        for (int i = 0; i < rowsOfMatrix; i++)
        {
            columnVector[i] = matrixVals[i * columnsofMatrix + col];
        }
        return columnVector;
    }

    // make the matrix column equal the vector found

    void setColumnVector(vector<double> vec, int col)
    {
        for (int i = 0; i < rowsOfMatrix; i++)
        {
            matrixVals[i * columnsofMatrix + col] = vec[i];
        }
    }

    // makes the matrix row equal the vector found
    void setRowVector(vector<double> vec, int row)
    {
        for (int i = 0; i < columnsofMatrix; i++)
        {
            matrixVals[row * columnsofMatrix + i] = vec[i];
        }
    }

    // fills the matrix column with a found integer

    void setColumnVec(int num, int col)
    {
        for (int i = 0; i < rowsOfMatrix; i++)
        {
            matrixVals[i * columnsofMatrix + col] = num;
        }
    }
};

// matrix multiplied by other matrix
Matrix matMultiply(Matrix A, Matrix B)
{
    int Arows = A.getMatrixRows();
    int Acolumns = A.getMatrixColumns();
    int Brows = B.getMatrixRows();
    int Bcolumns = B.getMatrixColumns();
    Matrix C(Arows, Bcolumns);
    double dotProduct = 0;

    for (int i = 0; i < Arows; i++)
    {
        // get all of the dot products from row A
        for (int j = 0; j < Bcolumns; j++)
        {

            for (int k = 0; k < Acolumns; k++)
            {
                dotProduct += A.getMatrixValue(i, k) * B.getMatrixValue(k, j);
            }
            C.setMatrixValue(i, j, dotProduct);
            dotProduct = 0;
        }
    }
    return C;
}

// transpose matrix
Matrix matrixTranspose(Matrix A)
{
    Matrix T(A.getMatrixColumns(), A.getMatrixRows());
    for (int i = 0; i < A.getMatrixColumns(); i++)
    {
        T.setRowVector(A.getColumnVector(i), i);
    }
    return T;
}

// matrix multiplied by num
Matrix matMultiply(Matrix A, double num)
{
    for (int i = 0; i < A.getMatrixRows(); i++)
    {
        for (int j = 0; j < A.getMatrixColumns(); j++)
        {
            A.setMatrixValue(i, j, (A.getMatrixValue(i, j) * num));
        }
    }
    return A;
}

// matrix addition
Matrix matAdd(Matrix A, Matrix B)
{
    Matrix C(A.getMatrixRows(), A.getMatrixColumns());
    for (int i = 0; i < A.getMatrixRows(); i++)
    {
        for (int j = 0; j < A.getMatrixColumns(); j++)
        {
            C.setMatrixValue(i, j, (A.getMatrixValue(i, j) + B.getMatrixValue(i, j)));
        }
    }
    return C;
}

// matrix subtraction
Matrix matSubtract(Matrix A, Matrix B)
{
    Matrix C(A.getMatrixRows(), A.getMatrixColumns());
    for (int i = 0; i < A.getMatrixRows(); i++)
    {
        for (int j = 0; j < A.getMatrixColumns(); j++)
        {
            C.setMatrixValue(i, j, (A.getMatrixValue(i, j) - B.getMatrixValue(i, j)));
        }
    }
    return C;
}

// calc Sigmoid value using function
Matrix sigmoidFunction(Matrix A)
{
    const double e = 2.71828182845904;
    vector<double> sigmoidVal;
    sigmoidVal.resize(A.getMatrixRows());
    Matrix C(A.getMatrixRows(), 1);
    for (int i = 0; i < A.getMatrixRows(); i++)
    {
        double tempValue = 1 / (1 + pow(e, (A.getMatrixValue(i, 0) * -1)));
        sigmoidVal.at(i) = tempValue;
    }

    C.setColumnVector(sigmoidVal, 0);
    return C;
}

// calc Probability with data
Matrix probability(Matrix A)
{
    const double e = 3;
    Matrix P(A.getMatrixRows(), 1);
    double temp = 0;
    for (int i = 0; i < A.getMatrixRows(); i++)
    {
        temp = pow(e, A.getMatrixValue(i, 0)) / (1 + A.getMatrixValue(i, 0));
        P.setMatrixValue(i, 0, temp);
    }
    return P;
}

// calculate prediction of dta
Matrix predictionOfData(Matrix A)
{
    Matrix X(A.getMatrixRows(), 1);
    for (int i = 0; i < A.getMatrixRows(); i++)
    {
        if (A.getMatrixValue(i, 0) > 0.5)
        {
            X.setMatrixValue(i, 0, 1);
        }
        else
        {
            X.setMatrixValue(i, 0, 0);
        }
    }
    return X;
}

double accuracyofData(Matrix pred, Matrix test)
{
    double mean;
    double correct = 0;
    for (int i = 0; i < pred.getMatrixRows(); i++)
    {
        if (pred.getMatrixValue(i, 0) == test.getMatrixValue(i, 0))
        {
            correct++;
        }
    }
    return correct / pred.getMatrixRows();
} // calc Accuracy

// fill Train DF
dataField trainDataframe(dataField df, int numRows)
{
    dataField train;

    train.X.resize(numRows);
    train.pclass.resize(numRows);
    train.peoplewhoSurvived.resize(numRows);
    train.sexOfPerson.resize(numRows);
    train.ageOfPerson.resize(numRows);
    train.numOfinstances = numRows;

    for (int i = 0; i < numRows; i++)
    {
        train.X.at(i) = df.X.at(i);
        train.ageOfPerson.at(i) = df.ageOfPerson.at(i);
        train.pclass.at(i) = df.pclass.at(i);
        train.sexOfPerson.at(i) = df.sexOfPerson.at(i);
        train.peoplewhoSurvived.at(i) = df.peoplewhoSurvived.at(i);
    }
    return train;
}

// fill Test DF
dataField testDataFrame(dataField df, int numRows)
{
    dataField test;
    int num_instances = df.numOfinstances;
    int count = 0;

    test.X.resize(numRows);
    test.pclass.resize(numRows);
    test.peoplewhoSurvived.resize(numRows);
    test.sexOfPerson.resize(numRows);
    test.ageOfPerson.resize(numRows);
    test.numOfinstances = numRows;

    for (int i = num_instances - numRows; i < num_instances; i++)
    {
        test.X[count] = df.X[i];
        test.ageOfPerson[count] = df.ageOfPerson[i];
        test.pclass[count] = df.pclass[i];
        test.sexOfPerson[count] = df.sexOfPerson[i];
        test.peoplewhoSurvived[count] = df.peoplewhoSurvived[i];
        count++;
    }
    return test;
}

// calc True Positive
double countTruePos(Matrix survived, Matrix predict)
{
    double TruePos = 0;
    for (int i = 0; i < survived.getMatrixRows(); i++)
    {
        if (survived.getMatrixValue(i, 0) == predict.getMatrixValue(i, 0) && survived.getMatrixValue(i, 0) == 1)
            TruePos++;
    }
    return TruePos;
}

// calc True Negative
double countTrueNeg(Matrix survived, Matrix predict)
{
    double TrueNeg = 0;
    for (int i = 0; i < survived.getMatrixRows(); i++)
    {
        if (survived.getMatrixValue(i, 0) == predict.getMatrixValue(i, 0) && survived.getMatrixValue(i, 0) == 0)
            TrueNeg++;
    }
    return TrueNeg;
}

void LogisticRegression(dataField train, dataField test)
{
    Matrix weightbySex(2, 1);
    weightbySex.setColumnVec(1, 0);

    Matrix labelsfromData(train.numOfinstances, 1);
    labelsfromData.setColumnVector(train.peoplewhoSurvived, 0);
    Matrix data_matrix_sex(train.numOfinstances, 2);

    data_matrix_sex.setColumnVec(1, 0);
    data_matrix_sex.setColumnVector(train.sexOfPerson, 1);

    Matrix errorSex(train.numOfinstances, 1);
    Matrix probabilitySex(train.numOfinstances, 1);

    double learn_rate = 0.001;

    auto start = std::chrono::system_clock::now();

    // training data model for logistic regression
    for (int i = 0; i < 10000; i++)
    {
        probabilitySex = sigmoidFunction(matMultiply(data_matrix_sex, weightbySex));

        errorSex = matSubtract(labelsfromData, probabilitySex);

        weightbySex = matAdd(weightbySex, matMultiply(matMultiply(matrixTranspose(data_matrix_sex), errorSex), learn_rate));
    }

    auto end = std::chrono::system_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // predict data
    Matrix test_matrix_sex(test.numOfinstances, 2);
    test_matrix_sex.setColumnVec(1, 0);
    test_matrix_sex.setColumnVector(test.sexOfPerson, 1);

    // compare to test data
    Matrix test_labels(test.numOfinstances, 1);
    test_labels.setColumnVector(test.peoplewhoSurvived, 0);

    Matrix predicted_sex = matMultiply(test_matrix_sex, weightbySex);
    Matrix probabilitiy_sex = probability(predicted_sex);
    Matrix predictions_sex = predictionOfData(probabilitiy_sex);
    double accuracy_sex = accuracyofData(predictions_sex, test_labels);

    // predict deaths in data
    double PredictionisFalse = 0;
    for (int i = 0; i < predictions_sex.getMatrixRows(); i++)
    {
        if (predictions_sex.getMatrixValue(i, 0) == 0)
        {
            PredictionisFalse++;
        }
    }
    // predict amount survived
    double predictionisTrue = predictions_sex.getMatrixRows() - PredictionisFalse;

    double TruePosi = countTruePos(predictions_sex, test_labels);
    double TrueNegi = countTrueNeg(predictions_sex, test_labels);
    double FalsePos = predictionisTrue - TruePosi;
    double FalseNeg = PredictionisFalse - TrueNegi;

    cout << "Survived (Coefficients):\n";

    weightbySex.printMat();

    cout << "\n"
         << endl;

    cout << "Predicted values:\n";
    cout << "Accuracy:   " << accuracy_sex << endl;
    cout << "Sensitivity:   " << TruePosi / (TruePosi + FalseNeg) << endl;
    cout << "Specificity:   " << TrueNegi / (TrueNegi + FalsePos) << endl;
    cout << "Training Time of the algorithm:   " << elapsed.count() << "ms" << endl;
}

int main()
{
    ifstream inFile;                                                      // opening the data file
    string line;                                                          // initializing variable for strings read in
    string Xinput, survivedInput, pclassInput, sexInput, ageInput, empty; // variables for labels that is being read in
    dataField titanicDataset;                                             // df (titanic data)

    titanicDataset.X.resize(MAXIMUM_VALUE);
    titanicDataset.pclass.resize(MAXIMUM_VALUE);
    titanicDataset.peoplewhoSurvived.resize(MAXIMUM_VALUE);
    titanicDataset.sexOfPerson.resize(MAXIMUM_VALUE);
    titanicDataset.ageOfPerson.resize(MAXIMUM_VALUE);

    string filename = "titanicdata.csv"; // adding in filename to be opened
    inFile.open(filename);               // open file
    if (!inFile.is_open())               // if file does not open
    {
        cout << "Cannot open file: " << filename << endl; // error msg saying file cannot be opened
    }

    getline(inFile, line); // read in lines

    int numofObservations = 0;

    while (inFile.good())
    {
        inFile.get();
        getline(inFile, Xinput, '"');
        inFile.get();
        getline(inFile, pclassInput, ',');
        getline(inFile, survivedInput, ',');
        getline(inFile, sexInput, ',');
        getline(inFile, ageInput, '\n');

        // read data and split it/store data
        titanicDataset.X.at(numofObservations) = stof(Xinput);
        titanicDataset.pclass.at(numofObservations) = stof(pclassInput);
        titanicDataset.peoplewhoSurvived.at(numofObservations) = stof(survivedInput);
        titanicDataset.sexOfPerson.at(numofObservations) = stof(sexInput);
        titanicDataset.ageOfPerson.at(numofObservations) = stof(ageInput);

        numofObservations++;
    }

    titanicDataset.X.resize(numofObservations);
    titanicDataset.pclass.resize(numofObservations);
    titanicDataset.peoplewhoSurvived.resize(numofObservations);
    titanicDataset.sexOfPerson.resize(numofObservations);
    titanicDataset.ageOfPerson.resize(numofObservations);

    titanicDataset.numOfinstances = int(titanicDataset.X.size());
    inFile.close();

    // split into train/test and perform the Logistic Regression Model
    dataField trainingData = trainDataframe(titanicDataset, 800);
    dataField testData = testDataFrame(titanicDataset, titanicDataset.numOfinstances - 800);

    LogisticRegression(trainingData, testData); // run the logistic regression
}