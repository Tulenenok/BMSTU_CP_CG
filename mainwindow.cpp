//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <iostream>
#include "mainwindow.h"
#include "ui_MainWindow.h"

#include "server/screen_t.h"
#include "server/screen_properties_t.h"
#include "server/triangle_t.h"
#include "server/z_buffer.h"

int my_random(int a,int b)
{
    if (a > 0) return a + rand() % (b - a);
    else return a + rand() % (abs(a) + b);
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scene->setSceneRect(0, 0, 1, 1);

    connect(ui->LoadFigureButton, SIGNAL (clicked()),this, SLOT(on_LoadButton_clicked()));
    connect(ui->DrawButton, SIGNAL (clicked()),this, SLOT(on_DrawButton_clicked()));
    connect(ui->AddLightButton, SIGNAL (clicked()),this, SLOT(on_AddLightButton_clicked()));

//    ui->graphicsView->setStyleSheet("background-color: black");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_LoadButton_clicked() {
    fillScreen(NULL);

    handleButton(LOAD);
}

void MainWindow::on_DrawButton_clicked() {
    handleButton(DRAW);
}

void MainWindow::on_AddLightButton_clicked() {
    handleButton(ADD_LIGHT);
}

//void MainWindow::fillScreen(color_t **matrix_color)
//{
//    int w = ui->graphicsView->width();
//    int h = ui->graphicsView->height();
//
//    QImage image(w, h, QImage::Format_ARGB32 );
//    for(int y = 0; y < h; ++y)
//        for(int x = 0; x < w ;x++)
//        {
//            color_t color_pix = matrix_color[x][y];
//            QRgb argb = qRgb(color_pix.r,color_pix.g,color_pix.b);
//            image.setPixel(QPoint(x, y), argb);
//        }
//    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));
//}

//// TEST 1
//void MainWindow::fillScreen(int **matrix_color)
//{
//    int w = ui->graphicsView->width();
//    int h = ui->graphicsView->height();
//
//    screen_properties_t screenProperties {w, h};
//
//    screen_t *screen = allocate_screen_t(&screenProperties);
//    color_t color = {150, 128, 90};
//    set_default_color(screen, &color);
//
//    color_t **mat = screen->color;
//
//    QImage image(w, h, QImage::Format_ARGB32 );
//    for(int y = 0; y < h; ++y)
//        for(int x = 0; x < w ;x++)
//        {
//            color_t color_pix = mat[x][y];
//            QRgb argb = qRgb(color_pix.r,color_pix.g,color_pix.b);
//            image.setPixel(QPoint(x, y), argb);
//        }
//    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));
//
//    free_screen_t(screen);
//}

// TEST 2
void MainWindow::fillScreen(int **matrix_color)
{
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    std::cout << w << " " << h;

    screen_properties_t screenProperties {w, h};
    screen_t *screen = allocate_screen_t(&screenProperties);

    std::vector<triangle_t*> triangles;
    triangle_t *tr1 = allocate_triangle_t();

    set_vertex_by_index(tr1, 0, 0, 0, 0);
    set_vertex_by_index(tr1, 1, 0, 520, 0);
    set_vertex_by_index(tr1, 2, 200, 100, 0);


    color_t color = {243, 50, 18};
    set_color(tr1, &color);
    triangles.push_back(tr1);

    z_buffer_render(screen, triangles);

    color_t **mat = screen->color;

    QImage image(w, h, QImage::Format_ARGB32 );
    for(int y = 0; y < h; ++y)
        for(int x = 0; x < w ;x++)
        {
            color_t color_pix = mat[x][y];
            QRgb argb = qRgb(color_pix.r,color_pix.g,color_pix.b);
            image.setPixel(QPoint(x, y), argb);
        }
    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(image));

    free_screen_t(screen);
}