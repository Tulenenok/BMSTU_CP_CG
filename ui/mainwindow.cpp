//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <iostream>
#include "mainwindow.h"
#include "ui_MainWindow.h"

#include "../tests/all_tests.h"
#include "../server/triangle_vector.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
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

    change_factor = allocate_change_factor_t();

    color_t color = {255, 255, 255};
    set_default_color(screen_matrix, &color);
    reset_screen(screen_matrix);

    fillScene();
}

MainWindow::~MainWindow() {
    free_screen_t(screen_matrix);
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    reset_screen(screen_matrix);

    handler.load_figure(screen_matrix);
    complex_change();
    handler.render(screen_matrix);

    fillScene();

//    Fractal fr = test_fractal_show();
//    for(auto l: fr.links)
//        drawLine(l.from, l.to);

    std::cout << "Load success\n";
}

void MainWindow::on_cleanButton_clicked()
{
    reset_screen(screen_matrix);
    handler.polygons.clear();
    handler.light_sources.clear();
    reset_change_factor_t(change_factor);
    fillScene();
}

void MainWindow::on_pushButton_clicked()
{
    reset_screen(screen_matrix);
    increment_push_factor(change_factor,
                          ui->DxField->value(),
                          ui->DyField->value(),
                          ui->DzField->value());

    complex_change();
    handler.render(screen_matrix);
    fillScene();

    std::cout << "Push success\n";
}

void MainWindow::on_scaleButton_clicked()
{
    reset_screen(screen_matrix);
    increment_scale_factor(change_factor,
                          ui->KxField->value(),
                          ui->KyField->value(),
                          ui->KzField->value());

    complex_change();
    handler.render(screen_matrix);
    fillScene();

    std::cout << "Scale success\n";
}

void MainWindow::on_rotateButton_clicked()
{
    reset_screen(screen_matrix);
    increment_rotate_factor(change_factor,
                           ui->AxField->value(),
                           ui->AyField->value(),
                           ui->AzField->value());

    complex_change();
    handler.render(screen_matrix);
    fillScene();

    std::cout << "Rotate success\n";
}

void MainWindow::on_addLightButton_clicked()
{
    double lx = ui->LxField->value();
    double ly = ui->LyField->value();
    double lz = ui->LzField->value();

    handler.add_light_source(screen_matrix, lx, ly, lz);
    fillScene();

    std::cout << "Add light success\n";
}

void MainWindow::fillScene()
{
//    ui->graphicsView->scene()->clear();

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

void MainWindow::drawLine(vertex_t p1, vertex_t p2)
{
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

   scene->addLine(p1[0] + w / 2, -p1[1] + h / 5 * 4, p2[0] + w / 2, -p2[1] + h / 5 * 4);
}

void MainWindow::complex_change()
{
    group_reset_processed_vertexes(handler.polygons);

    handler.push(screen_matrix,
                 change_factor->push_factor[0],
                 change_factor->push_factor[1],
                 change_factor->push_factor[2]);

    handler.scale(screen_matrix,
                  change_factor->scale_factor[0],
                  change_factor->scale_factor[1],
                  change_factor->scale_factor[2]);

    handler.rotate(screen_matrix,
                   change_factor->rotate_factor[0],
                   change_factor->rotate_factor[1],
                   change_factor->rotate_factor[2]);
}
