//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <iostream>
#include "mainwindow.h"
#include "ui_MainWindow.h"

#include "../tests/all_tests.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, 1, 1);

    connect(ui->LoadB, SIGNAL (clicked()),this, SLOT(on_loadButton_clicked()));
    connect(ui->CleanB, SIGNAL (clicked()),this, SLOT(on_cleanButton_clicked()));
    connect(ui->RotateB, SIGNAL (clicked()),this, SLOT(on_rotateButton_clicked()));
    connect(ui->PushB, SIGNAL (clicked()),this, SLOT(on_pushButton_clicked()));
    connect(ui->ScaleB, SIGNAL (clicked()),this, SLOT(on_scaleButton_clicked()));
    connect(ui->AddLightB, SIGNAL (clicked()),this, SLOT(on_addLightButton_clicked()));

    screen_properties_t screenProperties {ui->graphicsView->width(), ui->graphicsView->height()};
    screen_matrix = allocate_screen_t(&screenProperties);
}

MainWindow::~MainWindow() {
    free_screen_t(screen_matrix);
    delete ui;
}

void MainWindow::on_loadButton_clicked() {
    handler.load_figure(screen_matrix);
    fillScreen();

    std::cout << "Load success\n";
}

void MainWindow::on_cleanButton_clicked(){
    ui->graphicsView->scene()->clear();

    free_screen_t(screen_matrix);
    screen_properties_t screenProperties {ui->graphicsView->width(), ui->graphicsView->height()};
    screen_matrix = allocate_screen_t(&screenProperties);
}

void MainWindow::on_pushButton_clicked()
{
    double dx = ui->DxField->value();
    double dy = ui->DyField->value();
    double dz = ui->DzField->value();

    handler.push(screen_matrix, dx, dy, dz);
    fillScreen();

    std::cout << "Push success\n";
}

void MainWindow::on_scaleButton_clicked()
{
    double kx = ui->KxField->value();
    double ky = ui->KyField->value();
    double kz = ui->KzField->value();

    handler.scale(screen_matrix, kx, ky, kz);
    fillScreen();

    std::cout << "Scale success\n";
}

void MainWindow::on_rotateButton_clicked()
{
    double ax = ui->AxField->value();
    double ay = ui->AyField->value();
    double az = ui->AzField->value();

    handler.rotate(screen_matrix, ax, ay, az);
    fillScreen();

    std::cout << "Rotate success\n";
}

void MainWindow::on_addLightButton_clicked()
{
    double lx = ui->LxField->value();
    double ly = ui->LyField->value();
    double lz = ui->LzField->value();

    handler.add_light_source(screen_matrix, lx, ly, lz);
    fillScreen();

    std::cout << "Add light success\n";
}

void MainWindow::fillScreen()
{
    ui->graphicsView->scene()->clear();

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
                screen_matrix->change[x][y] = false;
            }

    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));
}