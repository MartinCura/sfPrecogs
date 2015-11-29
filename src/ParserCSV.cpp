#include "ParserCSV.h"

const int CANT_CATEGORIAS = 39;

using namespace std;

ParserCSV::ParserCSV(string trainPath, string testPath, string submissionPath) {
    this.trainPath = trainPath;
    this.testPath = testPath;
    this.submissionPath = submissionPath;
}

vector<Crimen*> ParserCSV::parseTrain() {
    vector<Crimen*> crimenes = preprocessCrimes(train);
    completeCrimesAttributes(train, crimenes);
    return crimenes;
}

void ParserCSV::writeRowSubmission(vector<double> probsPerCrime) {
    if ( ! this.submission.is_open() )
        openSubmission();

    string linea;
    if ( ! this.submissionHasHeader ) {
        // TODO: Escribir header del csv.
        this.submissionHasHeader = true;
    }

    // TODO: Escribir row de probabilidades.

}

/** Devuelve nullptr si ya se leyo todo el test.csv. **/
TestRow* ParserCSV::getNextTestRow() {
    if ( ! this.test.is_open() )
        openTest();

    string linea;
    if ( ! this.testHasSkippedHeader ) {
        getline (this.test, linea);     // No leo el header, lo salteo.
        this.testHasSkippedHeader = true;
    }

    if ( this.test.good() ) {
        getline(this.test, linea);
        TestRow* row = parseLineToTestRow(linea);
        return row;
    } else {
        this.test.close();
        return nullptr;
    }

}

ParserCSV::~ParserCSV() {
    if ( this.test.is_open() )
        this.test.close();
    if ( this.submission.is_open() )
        this.submission.close();
}

ifstream ParserCSV::openTrain() {
    return ifstream file ( trainPath );
}

ifstream ParserCSV::openTest() {
    ifstream file ( testPath );
    this.test = file;
    return file;
}

ofstream ParserCSV::openSubmission() {
    ofstream file ( submissionPath );
    this.submission = file;
    return file;
}

/** Primera lectura del train. **/
vector<Crimen*> ParserCSV::preprocessCrimes(ifstream train) {
    vector<Crimen*> crimenes(CANT_CATEGORIAS, nullptr);  // Inicializo vector de crimenes en null.

    ifstream train = openTrain();
    if ( train.is_open() ) {
        string linea;
        getline (train, linea);     // No utilizo el header.
        while ( train.good() ) {
            getline (train, linea);
            tokenizeLineToCrime(linea, &crimenes);
        }
    }
    train.close();

    this.trainWasPreprocessed = true;

    return crimenes;
}

/** Segunda lectura del train (para la varianza, la media ya la tengo) **/
void ParserCSV::completeCrimesAttributes(ifstream train, vector<Crimen*>* crimenes) {
    ifstream train = openTrain();
    if ( train.is_open() ) {
        string linea;
        getline (train, linea);     // No utilizo el header.
        while ( train.good() ) {
            getline (train, linea);
            tokenizeLineToCrime(linea, &crimenes);
        }
    }
    train.close();

    this.trainWasPreprocessed = false;
}

/** Pasa una linea a crimen con sus features y contadores respectivos. **/
void ParserCSV::tokenizeLineToCrime(string line, vector<Crimen*> &crimenes) {
    istringstream streamLine(line);
    string featureString;
    Crimen* categoria;
    int i = 0;
    while(getline(streamLine, featureString, ',')) {
        switch (i) {
            case TrainColumns.CATEGORY: {   // La Category es la primera columna del CSV. Por lo tanto, todas las features siguientes seran validas.
                    int categoryIndex = parseCategory(featureString);
                    if ( ! crimenes[i]) {
                        categoria = new Crimen(categoryIndex);
                        crimenes[i] = categoria
                    } else {
                        categoria = crimenes[i];
                    }
                }
                break;
            case TrainColumns.DISTRICT: {
                    int districtValue = parseDistrict(featureString);
                    updateFeatureCounters(categoria->f_district, districtValue);
                }
                break;
            case TrainColumns.YEAR: {
                    int yearValue = int(featureString);
                    updateFeatureCounters(categoria->f_anio, yearValue);
                }
                break;
            case TrainColumns.MONTH: {
                    int monthValue = int(featureString);
                    updateFeatureCounters(categoria->f_mes, monthValue);
                }
                break;
            case TrainColumns.DAYOFWEEK: {
                    int dayOfWeekValue = int(featureString);
                    updateFeatureCounters(categoria->f_dayWeek, dayOfWeekValue);
                }
                break;
            case TrainColumns.HOUR: {
                    int hourValue = int(featureString);
                    updateFeatureCounters(categoria->f_hora, hourValue);
                }
                break;
            case TrainColumns.CUAD: {
                    int cuadValue = int(featureString);
                    updateFeatureCounters(categoria->f_cuad, cuadValue);
                }
                break;
            default:
                break;
        }
    }
}

int ParserCSV::parseCategory(string category) {
    vector<string> categoriasCrimen(CANT_CATEGORIAS) { "ARSON", "ASSAULT", "BAD CHECKS", "BRIBERY", "BURGLARY", "DISORDERLY CONDUCT", "DRIVING UNDER THE INFLUENCE", "DRUG/NARCOTIC", "DRUNKENNESS", "EMBEZZLEMENT", "EXTORTION", "FAMILY OFFENSES",
    "FORGERY/COUNTERFEITING", "FRAUD", "GAMBLING", "KIDNAPPING", "LARCENY/THEFT", "LIQUOR LAWS", "LOITERING", "MISSING PERSON", "NON-CRIMINAL", "OTHER OFFENSES", "PORNOGRAPHY/OBSCENE MAT", "PROSTITUTION", "RECOVERED VEHICLE",
        "ROBBERY", "RUNAWAY", "SECONDARY CODES", "SEX OFFENSES FORCIBLE", "SEX OFFENSES NON FORCIBLE", "STOLEN PROPERTY", "SUICIDE", "SUSPICIOUS OCC", "TREA", "TRESPASS", "VANDALISM", "VEHICLE THEFT",
            "WARRANTS", "WEAPON LAWS" };

    vector<string>::iterator it;
    int categoryIndex = 0;
    for ( it = categoriasCrimen.begin(); it < categoriasCrimen.end(); it++, i++ ) {
        if ( ! it->compare(category) ) {
            categoryIndex = i;
            break;
        }
    }

    return categoryIndex


    /*
    int categoryIndex;
    if ( ! category.compare("ARSON") )
        categoryIndex = CategoriasCrimen.ARSON;
    else if ( ! category.compare("ASSAULT") )
        categoryIndex = CategoriasCrimen.ASSAULT;
    else if ( ! category.compare("BAD CHECKS") )
        categoryIndex = CategoriasCrimen.BAD_CHECKS;
    else if ( ! category.compare("BRIBERY") )
        categoryIndex = CategoriasCrimen.BRIBERY;
    else if ( ! category.compare("BURGLARY") )
        categoryIndex = CategoriasCrimen.BURGLARY;
    else if ( ! category.compare("DISORDERLY CONDUCT") )
        categoryIndex = CategoriasCrimen.DISORDERLY_CONDUCT;
    else if ( ! category.compare("DRIVING UNDER THE INFLUENCE") )
        categoryIndex = CategoriasCrimen.DRIVING_UNDER_INFLUENCE;
    else if ( ! category.compare("DRUG/NARCOTIC") )
        categoryIndex = CategoriasCrimen.DRUG_NARCOTIC;
    else if ( ! category.compare("DRUNKENNESS") )
        categoryIndex = CategoriasCrimen.DRUNKENNESS;
    else if ( ! category.compare("EMBEZZLEMENT") )
        categoryIndex = CategoriasCrimen.EMBEZZLEMENT;
    else if ( ! category.compare("EXTORTION") )
        categoryIndex = CategoriasCrimen.EXTORTION;
    else if ( ! category.compare("FAMILY OFFENSES") )
        categoryIndex = CategoriasCrimen.FAMILY_OFFENSES;
    else if ( ! category.compare("FORGERY/COUNTERFEITING") )
        categoryIndex = CategoriasCrimen.FORGERY_COUNTERFEITING;
    else if ( ! category.compare("FRAUD") )
        categoryIndex = CategoriasCrimen.FRAUD;
    else if ( ! category.compare("GAMBLING") )
        categoryIndex = CategoriasCrimen.GAMBLING;
    else if ( ! category.compare("KIDNAPPING") )
        categoryIndex = CategoriasCrimen.KIDNAPPING;
    else if ( ! category.compare("LARCENY/THEFT") )
        categoryIndex = CategoriasCrimen.LARCENY_THEFT;
    else if ( ! category.compare("LIQUOR LAWS") )
        categoryIndex = CategoriasCrimen.LIQUOR_LAWS;
    else if ( ! category.compare("LOITERING") )
        categoryIndex = CategoriasCrimen.LOITERING;
    else if ( ! category.compare("MISSING PERSON") )
        categoryIndex = CategoriasCrimen.MISSING_PERSON;
    else if ( ! category.compare("NON-CRIMINAL") )
        categoryIndex = CategoriasCrimen.NON_CRIMINAL;
    else if ( ! category.compare("OTHER OFFENSES") )
        categoryIndex = CategoriasCrimen.OTHER_OFFENSES;
    else if ( ! category.compare("PORNOGRAPHY/OBSCENE MAT") )
        categoryIndex = CategoriasCrimen.PORNOGRAPHY;
    else if ( ! category.compare("PROSTITUTION") )
        categoryIndex = CategoriasCrimen.PROSTITUTION;
    else if ( ! category.compare("RECOVERED VEHICLE") )
        categoryIndex = CategoriasCrimen.RECOVERED_VEHICLE;
    else if ( ! category.compare("ROBBERY") )
        categoryIndex = CategoriasCrimen.ROBBERY;
    else if ( ! category.compare("RUNAWAY") )
        categoryIndex = CategoriasCrimen.RUNAWAY;
    else if ( ! category.compare("SECONDARY CODES") )
        categoryIndex = CategoriasCrimen.SECONDARY_CODES;
    else if ( ! category.compare("SEX OFFENSES FORCIBLE") )
        categoryIndex = CategoriasCrimen.SEX_OFFENSES_FORCIBLE;
    else if ( ! category.compare("SEX OFFENSES NON FORCIBLE") )
        categoryIndex = CategoriasCrimen.SEX_OFFENSES_NON_FORCIBLE;
    else if ( ! category.compare("STOLEN PROPERTY") )
        categoryIndex = CategoriasCrimen.STOLEN_PROPERTY;
    else if ( ! category.compare("SUICIDE") )
        categoryIndex = CategoriasCrimen.SUICIDE;
    else if ( ! category.compare("SUSPICIOUS OCC") )
        categoryIndex = CategoriasCrimen.SUSPICIOUS_OCC;
    else if ( ! category.compare("TREA") )
        categoryIndex = CategoriasCrimen.TREA;
    else if ( ! category.compare("TRESPASS") )
        categoryIndex = CategoriasCrimen.TRESPASS;
    else if ( ! category.compare("VANDALISM") )
        categoryIndex = CategoriasCrimen.VANDALISM;
    else if ( ! category.compare("VEHICLE THEFT") )
        categoryIndex = CategoriasCrimen.VEHICLE_THEFT;
    else if ( ! category.compare("WARRANTS") )
        categoryIndex = CategoriasCrimen.WARRANTS;
    else if ( ! category.compare("WEAPON LAWS") )
        categoryIndex = CategoriasCrimen.WEAPON_LAWS;
    */

}

int ParserCSV::parseDayOfWeek(string dayOfWeek) {
    vector<string> daysOfTheWeek(7) { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    vector<string>::iterator it;
    int dayOfWeekIndex = 0;
    for ( it = daysOfTheWeek.begin(); it < daysOfTheWeek.end(); it++, i++ ) {
        if ( ! it->compare(category) ) {
            dayOfWeekIndex = i;
            break;
        }
    }
    return dayOfWeekIndex
}

int ParserCSV::parseDistrict(string district) {
    vector<string> districts(7) { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    vector<string>::iterator it;
    int districtIndex = 0;
    for ( it = districts.begin(); it < districts.end(); it++, i++ ) {
        if ( ! it->compare(category) ) {
            districtIndex = i;
            break;
        }
    }
    return districtIndex
}

void ParserCSV::updateFeatureCounters(Feature* feature, currentValue) {
    if ( ! this.trainWasPreprocessed ) {
        feature->cantidad++
        feature->sumatoria += currentValue;
    } else if ( this.trainWasPreprocessed )
        feature->varianza += ( 1 / feature->cantidad ) * ( currentValue - feature->getMedia() )
}

TestRow* ParserCSV::parseLineToTestRow(string line) {
    istringstream streamLine(line);
    string featureString;
    int i = 0;
    int districtValue, yearValue, monthValue, dayOfWeekValue, hourValue, cuadValue;
    while( getline(streamLine, featureString, ',') ) {
        switch (i) {
            case TestColumns.DISTRICT:
                districtValue = parseDistrict(featureString);
                break;
            case TestColumns.YEAR:
                yearValue = int(featureString);
                break;
            case TestColumns.MONTH:
                monthValue = int(featureString);
                break;
            case TestColumns.DAYOFWEEK:
                dayOfWeekValue = int(featureString);
                break;
            case TestColumns.HOUR:
                hourValue = int(featureString);
                break;
            case TestColumns.CUAD:
                cuadValue = int(featureString);
                break;
            default:
                break;
        }
    }
    TestRow* row = new TestRow(districtValue, yearValue, monthValue, dayOfWeekValue, hourValue, cuadValue);
    return row;
}
