#ifndef PARSERCSV_H
#define PARSERCSV_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "Enum.h"
#include "TestRow.h"
#include "Crimen.h"
#include "Feature.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

class ParserCSV {
    public:
        ParserCSV(string trainPath, string testPath, string submissionPath);
        vector<Crimen*>* parseTrain();
        TestRow* getNextTestRow();
        void writeRowSubmission(vector<double>* probsPerCrime);
        bool closeSubmission();
        virtual ~ParserCSV();
    protected:
    private:
        string trainPath;
        string testPath;
        string submissionPath;

        ifstream test;
        bool testHasSkippedHeader = false;

        ofstream submission;
        bool submissionHasHeader = false;
        long countSubmissionRows = 0;

        bool trainWasPreprocessed = false;

        vector<Crimen*>* preprocessCrimes();
        void completeCrimesAttributes(vector<Crimen*>* crimenes);
        void tokenizeLineToCrime(string line, vector<Crimen*>* crimenes);
        int parseCategory(string category);
        int parseDayOfWeek(string dayOfWeek);
        int parseDistrict(string district);
        int parseFeature(string feature, vector<string> featureVector);
        TestRow* parseLineToTestRow(string line);
        void updateFeatureCounters(Feature* feature, int currentValue);
        void putHeaderInSubmission();
};

#endif // PARSERCSV_H
