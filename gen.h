#ifndef GEN_H
#define GEN_H
#include <QApplication>
#include <QTextEdit>
#include <QWidget>
#include <QPushButton>
#include <iostream>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include <math.h>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include "algoritm.h"
#include "fosfitkinetika.h"
using namespace std;
namespace Ui {
class gen;
}

class gen : public QWidget
{
    Q_OBJECT

public:
    void show();
    explicit gen();
    ~gen();
    QMessageBox msgBox;
private:
    QWidget window;
    QPushButton okButton, closeButton;
    QGridLayout layout;
    QLineEdit kol_osob, kol_genov, kol_pokoleniy, all_p_mutation_down,
        all_p_mutation_up, p_mutation_down, p_mutation_up;
    QLabel kol_osob_l, kol_genov_l, kol_pokoleniy_l, all_p_mutation_down_l,
        all_p_mutation_up_l, p_mutation_down_l, p_mutation_up_l;
    int ncol, nrow,
        N,M,KOL_POKOLENIY,
        ALL_P_MUTATION_DOWN,
        ALL_P_MUTATION_UP,
        P_MUTATION_DOWN,
        P_MUTATION_UP;
private slots:
    void start();
    void quit();
};

#endif // GEN_H
