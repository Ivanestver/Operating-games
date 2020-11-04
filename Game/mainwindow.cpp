#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QLineEdit>
#include <QVBoxLayout>

uint position = 0;
uint types = 0;

double *p;
int *r;
int *Vk;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dirCount_valueChanged(int arg1)
{
    QLabel *direction = new QLabel(QString::number(arg1), this);
    QLineEdit *probability = new QLineEdit(this);

    ui->attack_grid->addWidget(direction);
    ui->attack_grid->addWidget(probability);
}

void MainWindow::on_meanCount_valueChanged(int arg1)
{
    QLabel *type = new QLabel(QString::number(arg1), this);
    QLineEdit *perOneUse = new QLineEdit(this);
    QLineEdit *count = new QLineEdit(this);

    ui->defence_grid->addWidget(type);
    ui->defence_grid->addWidget(perOneUse);
    ui->defence_grid->addWidget(count);
}

void MainWindow::on_calc_clicked()
{
    const int type = ui->meanCount->text().toInt();
    const int direction = ui->dirCount->text().toInt();

    p = new double[direction];

    // set possibilities
    for (int i = 0; i < direction; i++){
        QLineEdit *line = (QLineEdit*)ui->attack_grid->itemAtPosition(i + 1, 1)->widget();
        QString s = line->text();
        p[i] = s.toFloat();
    }

    //set r and V
    r = new int[type];
    Vk = new int[type];
    for (int i = 0; i < type; i++){
        QLineEdit *perOne = (QLineEdit*)ui->defence_grid->itemAtPosition(i + 1, 1)->widget();
        r[i] = perOne->text().toInt();

        QLineEdit *amount = (QLineEdit*)ui->defence_grid->itemAtPosition(i +1, 2)->widget();
        Vk[i] = amount->text().toInt();
    }

    int V = 0;
    int length = ui->meanCount->text().toInt();
    for (int i = 0; i < length; i++){
        V += r[i] * Vk[i];
    }

    double sumPos = 0;
    for (int i = 0; i < direction; i++){
        sumPos += 1 / p[i];
    }

    float lambda = V / sumPos;

    float vMax = ui->attack->text().toInt() - lambda;

    // a new window with a grid of answears
    QWidget *answear = new QWidget;
    QGridLayout *table = new QGridLayout;
    // set heads of columns and rows
    table->addWidget(new QLabel("k/i"), 0, 0);
    for (int k = 1; k <= type; k++){
        table->addWidget(new QLabel(QString::number(k)), k, 0);
    }
    for (int i = 1; i <= direction; i++){
        table->addWidget(new QLabel(QString::number(i)), 0, i);
    }

    // set answear
    for (int k = 0; k < type; k++){
        for (int i = 0; i < direction; i++){
            table->addWidget(new QLabel(QString::number((Vk[k] / p[i]) / sumPos)), k + 1, i + 1);
        }
    }

    // set Lambda
    table->addWidget(new QLabel("Lambda"), type + 2, 0);
    table->addWidget(new QLabel(QString::number(floor(lambda))), type + 2, 1);

    // Vmax
    table->addWidget(new QLabel("Vmax"), type + 3, 0);
    table->addWidget(new QLabel(QString::number(floor(vMax))), type + 3, 1);

    answear->setLayout(table);
    answear->setGeometry(0, 0, 500, 300);
    answear->show();
}
