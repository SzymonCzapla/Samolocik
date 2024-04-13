#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QKeyEvent>
#include <QTime>
#include <QMessageBox>

int actualrow , actualcolumn, random, punkty = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int rows = 10, columns = 10;
    ui->tableWidget->setColumnCount(columns);
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setAlternatingRowColors(true);
    QString styleSheet = "\
        QTableWidget {\
            background-color: #f5f5f5; /* Ustaw kolor tła */ \
    } \
        QTableWidget::item {\
                padding: 10px; /* Ustaw wewnętrzny odstęp */ \
        border-bottom: 1px solid #cccccc; /* Dodaj dolną krawędź */ \
        color: #333333; /* Ustaw kolor tekstu */ \
        } \
            QTableWidget::item:selected {\
                background-color: #a6c5ff; /* Ustaw kolor tła dla zaznaczonych elementów */ \
    }";

            // Ustawiamy arkusz stylów dla QTableWidget
            ui->tableWidget->setStyleSheet(styleSheet);

            // Ustawiamy czcionkę dla całej tabeli
            ui->tableWidget->setFont(QFont("Arial", 12));

            // Ustawiamy kolor tła dla wierszy nieparzystych
            ui->tableWidget->setAlternatingRowColors(true);
            for(int i = 0; i< rows; i++){
                ui->tableWidget->setRowHeight(i, 40);
            }
            for(int i = 0; i< columns; i++){
                ui->tableWidget->setColumnWidth(i, 40);
            }
            for(int i = 0; i < columns; i++){
                for(int j = 0; j < rows; j++){
                    ui->tableWidget->setItem(j,i, new QTableWidgetItem(" "));
                }
            }
            actualrow = 5, actualcolumn = ui->tableWidget->columnCount()-1;
            srand(QTime::currentTime().msec());
            random = rand() % 10;
            ui->tableWidget->setItem(actualrow,2, new QTableWidgetItem(">"));
        }

        MainWindow::~MainWindow()
        {
            delete ui;
        }
        void MainWindow::keyPressEvent(QKeyEvent *event) {
            if(actualcolumn < 0){
                actualcolumn = ui->tableWidget->columnCount()-1;
                srand(QTime::currentTime().msec());
                random = rand() % 10;
            }
            if(event->key() == Qt::Key_W || event->key() == Qt::Key_S){
                punkty++;
                ui->punkty_label->setText("Punkty: " + QString::number(punkty));
                int columns = ui->tableWidget->columnCount();
                int rows = ui->tableWidget->rowCount();
                for(int i = 0; i < columns; i++){
                    for(int j = 0; j < rows; j++){
                        if(i == actualcolumn && j != random && j != random-1 && j != random+1){
                            ui->tableWidget->setItem(j,i, new QTableWidgetItem("[]"));
                        }
                        else{
                            ui->tableWidget->setItem(j,i, new QTableWidgetItem(" "));
                        }
                    }
                }
                if(event->key() == Qt::Key_W){
                    if(actualrow != 0){
                        if(ui->tableWidget->item(actualrow - 1, 3)->text() == "[]" || ui->tableWidget->item(actualrow - 1, 2)->text() == "[]") {
                            QMessageBox::warning(this, "Błąd", "Nie można przejść przez przeszkodę!");
                            actualcolumn = ui->tableWidget->columnCount();
                            actualrow = 5;
                            punkty = 0;
                            ui->punkty_label->setText("Punkty: " + QString::number(punkty));
                            for(int i = 0; i < columns; i++){
                                for(int j = 0; j < rows; j++){
                                        ui->tableWidget->setItem(j,i, new QTableWidgetItem(" "));
                                }
                            }
                        }
                        ui->tableWidget->setItem(actualrow, 2, new QTableWidgetItem(" "));
                        ui->tableWidget->setItem(actualrow - 1, 2, new QTableWidgetItem(">"));
                        actualrow--;
                    }
                    else{
                        ui->tableWidget->setItem(actualrow, 2, new QTableWidgetItem(">"));
                    }
                }
                else if (event->key() == Qt::Key_S) {
                    if (actualrow != ui->tableWidget->rowCount()-1) {
                        if(ui->tableWidget->item(actualrow + 1, 3)->text() == "[]" || ui->tableWidget->item(actualrow + 1, 2)->text() == "[]") {
                            QMessageBox::warning(this, "Błąd", "Nie można przejść przez przeszkodę!");
                            actualcolumn = ui->tableWidget->columnCount();
                            actualrow = 5;
                            punkty = 0;
                            ui->punkty_label->setText("Punkty: " + QString::number(punkty));
                            for(int i = 0; i < columns; i++){
                                for(int j = 0; j < rows; j++){
                                        ui->tableWidget->setItem(j,i, new QTableWidgetItem(" "));
                                }
                            }
                        }
                        ui->tableWidget->setItem(actualrow, 2, new QTableWidgetItem(" "));
                        ui->tableWidget->setItem(actualrow + 1, 2, new QTableWidgetItem(">"));
                        actualrow++;
                    }
                    else{
                        ui->tableWidget->setItem(actualrow, 2, new QTableWidgetItem(">"));
                    }
                }
                actualcolumn--;
                ui->tableWidget->setCurrentCell(5, 2);
                ui->tableWidget->setCurrentCell(actualrow, 2);
            }
        }
