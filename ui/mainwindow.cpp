//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <iostream>
#include "mainwindow.h"
#include "ui_MainWindow.h"

#include "../tests/server_test.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, 1, 1);

    connect(ui->LoadFigureButton, SIGNAL (clicked()),this, SLOT(on_LoadButton_clicked()));
    connect(ui->DrawButton, SIGNAL (clicked()),this, SLOT(on_DrawButton_clicked()));
    connect(ui->AddLightButton, SIGNAL (clicked()),this, SLOT(on_AddLightButton_clicked()));

    screen_properties_t screenProperties {ui->graphicsView->width(), ui->graphicsView->height()};
    screen_matrix = allocate_screen_t(&screenProperties);

//    ui->graphicsView->setStyleSheet("background-color: black");
}

MainWindow::~MainWindow() {
    free_screen_t(screen_matrix);
    delete ui;
}

void MainWindow::on_LoadButton_clicked() {
    server_test_set_default_color(screen_matrix);
    fillScreen();

    handleButton(LOAD);
}

void MainWindow::on_DrawButton_clicked() {
    server_test_draw_triangle(screen_matrix);
    fillScreen();

    handleButton(DRAW);
}

void MainWindow::on_AddLightButton_clicked() {
    handleButton(ADD_LIGHT);
}

void MainWindow::fillScreen()
{
    int w = screen_matrix->width;
    int h = screen_matrix->height;

    QImage image(w, h, QImage::Format_ARGB32 );
    for(int y = 0; y < h; ++y)
        for(int x = 0; x < w; ++x)
            if (screen_matrix->change[x][y])
            {
                color_t color_pix = screen_matrix->color[x][y];
                QRgb argb = qRgb(color_pix.r,color_pix.g,color_pix.b);
                image.setPixel(QPoint(x, y), argb);
            }

    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));
}