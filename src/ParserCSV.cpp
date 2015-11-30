#include "ParserCSV.h"

const int CANT_CATEGORIAS = 39;

const vector<string> categoriasCrimen { "ARSON", "ASSAULT", "BAD CHECKS", "BRIBERY", "BURGLARY", "DISORDERLY CONDUCT", "DRIVING UNDER THE INFLUENCE", "DRUG/NARCOTIC", "DRUNKENNESS", "EMBEZZLEMENT", "EXTORTION", "FAMILY OFFENSES",
            "FORGERY/COUNTERFEITING", "FRAUD", "GAMBLING", "KIDNAPPING", "LARCENY/THEFT", "LIQUOR LAWS", "LOITERING", "MISSING PERSON", "NON-CRIMINAL", "OTHER OFFENSES", "PORNOGRAPHY/OBSCENE MAT", "PROSTITUTION", "RECOVERED VEHICLE",
            "ROBBERY", "RUNAWAY", "SECONDARY CODES", "SEX OFFENSES FORCIBLE", "SEX OFFENSES NON FORCIBLE", "STOLEN PROPERTY", "SUICIDE", "SUSPICIOUS OCC", "TREA", "TRESPASS", "VANDALISM", "VEHICLE THEFT",
                "WARRANTS", "WEAPON LAWS" };
const vector<string> daysOfWeek { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const vector<string> districts { "BAYVIEW", "CENTRAL", "INGLESIDE", "MISSION", "NORTHERN", "PARK", "RICHMOND", "SOUTHERN", "TARAVAL", "TENDERLOIN" };

using namespace std;

ParserCSV::ParserCSV(string trainPath, string testPath, string submissionPath) {
    this->trainPath = trainPath;
    this->testPath = testPath;
    this->submissionPath = submissionPath;
}

vector<Crimen*>* ParserCSV::parseTrain() {
    vector<Crimen*>* crimenes = preprocessCrimes();
    completeCrimesAttributes(crimenes); // ESTO HACE QUE SE SUMEN 2 VECES
    return crimenes;
}

void ParserCSV::writeRowSubmission(vector<double>* probsPerCrime) {
    if ( ! this->submission.is_open() ) {
        this->submission.open( this->submissionPath );   // Open submission.
    }

    string linea;
    if ( ! this->submissionHasHeader ) {

        vector<string> header = categoriasCrimen;
        header.insert(header.begin(), "Id");   // Agrego campo Id.
        for ( vector<string>::iterator it = header.begin(); it != header.end(); ) {
            this->submission << *it;
            ++it;
            if (it != header.end())
                this->submission<< ",";
        }
        this->submissionHasHeader = true;
        this->submission<< endl;
    }

    probsPerCrime->insert(probsPerCrime->begin(), this->countSubmissionRows);   // Agrego Id.
    for ( vector<double>::iterator it = probsPerCrime->begin(); it != probsPerCrime->end(); ) {
        this->submission << *it;
        ++it;
        if (it != probsPerCrime->end())
                this->submission << ",";
    }
    this->submission<< endl;
    this->countSubmissionRows++;
}

bool ParserCSV::closeSubmission() {
    if ( this->submission.is_open() ) {
        this->submission.close();
        return true;
    } else {
        return false;
    }
}

/** Devuelve nullptr si ya se leyo todo el test.csv. **/
TestRow* ParserCSV::getNextTestRow() {
    if ( ! this->test.is_open() ) {
        this->test.open( this->testPath );   // Open test.
    }

    string linea;
    if ( ! this->testHasSkippedHeader ) {
        getline (this->test, linea);     // No leo el header, lo salteo.
        this->testHasSkippedHeader = true;
    }

    if ( this->test.good() ) {
        getline(this->test, linea);
        TestRow* row = parseLineToTestRow(linea);
        return row;
    } else {
        this->test.close();
        return nullptr;
    }

}

ParserCSV::~ParserCSV() {
    if ( this->test.is_open() )
        this->test.close();
    if ( this->submission.is_open() )
        this->submission.close();
}

/** Primera lectura del train. **/
vector<Crimen*>* ParserCSV::preprocessCrimes() {
    vector<Crimen*>* crimenes = new vector<Crimen*>(CANT_CATEGORIAS, nullptr);  // Inicializo vector de crimenes en null.

    int countRows = -1;//0; Para contabilizar la primera fila que no es una observación
    ifstream train ( trainPath );   // Open test.
    if ( train.is_open() ) {
        string linea;
        getline (train, linea);     // No utilizo el header.
        while ( train.good() ) {
            getline (train, linea);
            tokenizeLineToCrime(linea, crimenes);
            countRows++;
        }
        train.close();
    }

    // Calculo probabiidades por Laplace de cada categoria de crimen dentro del dataset.
    vector<Crimen*>::iterator it = crimenes->begin();
	while (it != crimenes->end()){
		Crimen* crimen = *it;
		crimen->proba_crimen = crimen->apariciones / (double) countRows;
		it++;
	}

    this->trainWasPreprocessed = true;

    return crimenes;
}

/** Segunda lectura del train (para la varianza, la media ya la tengo) **/
void ParserCSV::completeCrimesAttributes(vector<Crimen*>* crimenes) {
    ifstream train ( trainPath );   // Open test.
    if ( train.is_open() ) {
        string linea;
        getline (train, linea);     // No utilizo el header.
        while ( train.good() ) {
            getline (train, linea);
            tokenizeLineToCrime(linea, crimenes);
        }
    }
    train.close();

    this->trainWasPreprocessed = false;


    /** Verifico contadores y atributos. DEBUGGING! **/
    /*
    int i = 0;
    vector<Crimen*>::iterator it = crimenes->begin();
	while (it != crimenes->end()){
		Crimen* crimen = *it;
		it++;

        printf("CRIMEN %d: \n", i);
		cout << crimen->apariciones << endl;
		cout << crimen->getProbaCrimen() << endl;

        printf("ANIO:\n");
        cout << "cantidad" << crimen->f_anio->cantidad << endl;
        cout << "sumatoria" << crimen->f_anio->sumatoria << endl;
        cout << "varianza" << crimen->f_anio->varianza << endl;
        cout << "media" << crimen->f_anio->getMedia() << endl;

        printf("CUAD:\n");
        cout << "cantidad" << crimen->f_cuad->cantidad << endl;
        cout << "sumatoria" << crimen->f_cuad->sumatoria << endl;
        cout << "varianza" << crimen->f_cuad->varianza << endl;
        cout << "media" << crimen->f_cuad->getMedia() << endl;

        printf("DAY OF WEEK:\n");
        cout << "cantidad" << crimen->f_dayWeek->cantidad << endl;
        cout << "sumatoria" << crimen->f_dayWeek->sumatoria << endl;
        cout << "varianza" << crimen->f_dayWeek->varianza << endl;
        cout << "media" << crimen->f_dayWeek->getMedia() << endl;

        printf("DISTRICT:\n");
        cout << "cantidad" << crimen->f_district->cantidad << endl;
        cout << "sumatoria" << crimen->f_district->sumatoria << endl;
        cout << "varianza" << crimen->f_district->varianza << endl;
        cout << "media" << crimen->f_district->getMedia() << endl;

        printf("HORA:\n");
        cout << "cantidad" << crimen->f_hora->cantidad << endl;
        cout << "sumatoria" << crimen->f_hora->sumatoria << endl;
        cout << "varianza" << crimen->f_hora->varianza << endl;
        cout << "media" << crimen->f_hora->getMedia() << endl;

        printf("MES:\n");
        cout << "cantidad" << crimen->f_mes->cantidad << endl;
        cout << "sumatoria" << crimen->f_mes->sumatoria << endl;
        cout << "varianza" << crimen->f_mes->varianza << endl;
        cout << "media" << crimen->f_mes->getMedia() << endl;

        i++;
	}
	*/
}

/** Pasa una linea a crimen con sus features y contadores respectivos. **/
void ParserCSV::tokenizeLineToCrime(string line, vector<Crimen*>* crimenes) {
    istringstream streamLine(line);
    string featureString;
    Crimen* categoria;
    int i = 0;
    while(getline(streamLine, featureString, ',')) {
        // Remuevo comillas del featureString.
        char charsToRemove[] = "\"";
        for ( unsigned int j = 0; j < strlen(charsToRemove); ++j ) {
            featureString.erase( remove(featureString.begin(), featureString.end(), charsToRemove[j]), featureString.end() );
        }

        switch (i) {
            case CATEGORY_TRAIN: {   // La Category es la primera columna del CSV. Por lo tanto, todas las features siguientes seran validas.
                    int categoryIndex = parseCategory(featureString);
                    Crimen* crimen = crimenes->at(categoryIndex);
                    if ( ! crimen ) {
                        categoria = new Crimen();
                        crimenes->at(categoryIndex) = categoria;
                    } else {
                        categoria = crimen;
                        if ( ! this->trainWasPreprocessed )
                            crimen->apariciones++;
                    }
                }
                break;
            case DISTRICT_TRAIN: {
                    int districtValue = parseDistrict(featureString);
                    categoria->f_district->cantidad = categoria->apariciones;
                    updateFeatureCounters(categoria->f_district, districtValue);
                }
                break;
            case YEAR_TRAIN: {
                    int yearValue = atoi(featureString.data());
                    categoria->f_anio->cantidad = categoria->apariciones;
                    updateFeatureCounters(categoria->f_anio, yearValue);
                }
                break;
            case MONTH_TRAIN: {
                    int monthValue = atoi(featureString.data());
                    categoria->f_mes->cantidad = categoria->apariciones;
                    updateFeatureCounters(categoria->f_mes, monthValue);
                }
                break;
            case DAYOFWEEK_TRAIN: {
                    int dayOfWeekValue = atoi(featureString.data());
                    categoria->f_dayWeek->cantidad = categoria->apariciones;
                    updateFeatureCounters(categoria->f_dayWeek, dayOfWeekValue);
                }
                break;
            case HOUR_TRAIN: {
                    int hourValue = atoi(featureString.data());
                    categoria->f_hora->cantidad = categoria->apariciones;
                    updateFeatureCounters(categoria->f_hora, hourValue);
                }
                break;
            case CUAD_TRAIN: {
                    int cuadValue = atoi(featureString.data());
                    categoria->f_cuad->cantidad = categoria->apariciones;
                    updateFeatureCounters(categoria->f_cuad, cuadValue);
                }
                break;
            default:
                break;
        }
        i++;
    }
}

int ParserCSV::parseCategory(string category) {
    return parseFeature(category, categoriasCrimen);
}

int ParserCSV::parseDayOfWeek(string dayOfWeek) {
    return parseFeature(dayOfWeek, daysOfWeek);
}

int ParserCSV::parseDistrict(string district) {
    return parseFeature(district, districts);
}

int ParserCSV::parseFeature(string feature, vector<string> featureVector) {
    int featureIndex;
    int i = 0;
    for (vector<string>::const_iterator it = featureVector.begin() ; it != featureVector.end(); ++it){
        if ( it->compare(feature) == 0 ) {
            featureIndex = i;
            break;
        }
        i++;
    }
    return featureIndex;
}


void ParserCSV::updateFeatureCounters(Feature* feature, int currentValue) {
    if ( ! this->trainWasPreprocessed ) {
        feature->cantidad++;
        feature->sumatoria += currentValue;
    } else {
    	double aux = pow( (currentValue - feature->getMedia()), 2);
        feature->varianza += ( 1 / (double) feature->cantidad ) * ( aux );
    }
}

TestRow* ParserCSV::parseLineToTestRow(string line) {
    istringstream streamLine(line);
    string featureString;
    int i = 0;
    int districtValue, yearValue, monthValue, dayOfWeekValue, hourValue, cuadValue;
    while( getline(streamLine, featureString, ',') ) {
        switch (i) {
            case DISTRICT_TEST:
                districtValue = parseDistrict(featureString);
                break;
            case YEAR_TEST:
                yearValue = atoi(featureString.data());
                break;
            case MONTH_TEST:
                monthValue = atoi(featureString.data());
                break;
            case DAYOFWEEK_TEST:
                dayOfWeekValue = atoi(featureString.data());
                break;
            case HOUR_TEST:
                hourValue = atoi(featureString.data());
                break;
            case CUAD_TEST:
                cuadValue = atoi(featureString.data());
                break;
            default:
                break;
        }
        i++;
    }
    TestRow* row = new TestRow(districtValue, yearValue, monthValue, dayOfWeekValue, hourValue, cuadValue);
    return row;
}
