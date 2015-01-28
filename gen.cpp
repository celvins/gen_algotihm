#include "gen.h"
gen::gen(){
    okButton.setText(tr("OK"));
    closeButton.setText(tr("Exit"));
    QObject::connect(&okButton, SIGNAL(clicked()), this, SLOT(start()));
    QObject::connect(&closeButton, SIGNAL(clicked()), this, SLOT(quit()));

    kol_osob_l.setText(tr("РљРѕР»-РІРѕ РѕСЃРѕР±РµР№:"));
    kol_osob.setText(tr("10"));

    kol_genov_l.setText(tr("РљРѕР»-РІРѕ РіРµРЅРѕРІ:"));
    kol_genov.setText(tr("5"));

    kol_pokoleniy_l.setText(tr("РљРѕР»-РІРѕ РїРѕРєРѕР»РµРЅРёР№:"));
    kol_pokoleniy .setText(tr("2"));

    all_p_mutation_down_l.setText(tr("all_p_mutation_down:"));
    all_p_mutation_down.setText(tr("0"));

    all_p_mutation_up_l.setText(tr("all_p_mutation_up:"));
    all_p_mutation_up.setText(tr("25"));

    p_mutation_down_l.setText(tr("p_mutation_down:"));
    p_mutation_down.setText(tr("0"));

    p_mutation_up_l.setText(tr("p_mutation_up:"));
    p_mutation_up.setText(tr("25"));

    layout.addWidget(&kol_osob_l,0,0);
    layout.addWidget(&kol_osob,0,1);

    layout.addWidget(&kol_genov_l,1,0);
    layout.addWidget(&kol_genov,1,1);

    layout.addWidget(&kol_pokoleniy_l,2,0);
    layout.addWidget(&kol_pokoleniy,2,1);

    layout.addWidget(&all_p_mutation_down_l,3,0);
    layout.addWidget(&all_p_mutation_down,3,1);

    layout.addWidget(&all_p_mutation_up_l,4,0);
    layout.addWidget(&all_p_mutation_up,4,1);

    layout.addWidget(&p_mutation_down_l,5,0);
    layout.addWidget(&p_mutation_down,5,1);

    layout.addWidget(&p_mutation_up_l,6,0);
    layout.addWidget(&p_mutation_up,6,1);

    layout.addWidget(&okButton,7,3);
    layout.addWidget(&closeButton,7,5);
    window.setLayout(&layout);
    window.setWindowTitle(tr("Genethic Algoritm"));
}

gen::~gen(){}
void gen::quit(){window.close();}
void gen::show(){window.show();}
void gen::start(){
    N = kol_genov.text().toInt();
    M = kol_osob.text().toInt();
    KOL_POKOLENIY = kol_pokoleniy.text().toInt();
    ALL_P_MUTATION_DOWN = all_p_mutation_down.text().toInt();
    ALL_P_MUTATION_UP = all_p_mutation_up.text().toInt();
    P_MUTATION_DOWN = p_mutation_down.text().toInt();
    P_MUTATION_UP = p_mutation_up.text().toInt();
    algoritm(N, M, KOL_POKOLENIY, ALL_P_MUTATION_DOWN, ALL_P_MUTATION_UP, P_MUTATION_DOWN, P_MUTATION_UP);
}

