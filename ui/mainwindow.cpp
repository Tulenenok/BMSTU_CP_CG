//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <iostream>
#include "mainwindow.h"
#include "ui_MainWindow.h"
#include <string>
#include <vector>

#include "../tests/all_tests.h"


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

    connect(ui->Preset, SIGNAL(activated(int)), this, SLOT(on_preset_clicked(int)));

    screen_properties_t screenProperties {ui->graphicsView->width(), ui->graphicsView->height()};
    screen_matrix = allocate_screen_t(&screenProperties);

    setFractalForm(get_spiral());
}

MainWindow::~MainWindow() {
    free_screen_t(screen_matrix);
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    reset_screen(screen_matrix);
    handler.clean_handler();

    preset_setting_t preset = getFractalForm();

    handler.load_figure(screen_matrix, preset);
    fillScene();

//    for(auto l: fr.links)
//        drawLine(l.from, l.to);

    std::cout << "Load success\n";
}

void MainWindow::on_cleanButton_clicked()
{
    reset_screen(screen_matrix);
    handler.clean_handler();
    fillScene();
}

void MainWindow::on_pushButton_clicked()
{
    double dx = ui->DxField->value();
    double dy = ui->DyField->value();
    double dz = ui->DzField->value();

    handler.push(screen_matrix, dx, dy, dz);
    fillScene();

    std::cout << "Push success\n";
}

void MainWindow::on_scaleButton_clicked()
{
    double kx = ui->KxField->value();
    double ky = ui->KyField->value();
    double kz = ui->KzField->value();

    handler.scale(screen_matrix, kx, ky, kz);
    fillScene();

    std::cout << "Scale success\n";
}

void MainWindow::on_rotateButton_clicked()
{
    double ax = ui->AxField->value();
    double ay = ui->AyField->value();
    double az = ui->AzField->value();

    handler.rotate(screen_matrix, ax, ay, az);
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

    scene->addLine(p1[0], p1[1], p2[0], p2[1]);

//   scene->addLine(p1[0] + w / 2, -p1[1] + h / 5 * 4, p2[0] + w / 2, -p2[1] + h / 5 * 4);
}

void MainWindow::setFractalForm(preset_setting_t preset)
{
    ui->axiom->setText((" " + preset.params.axiom).c_str());
    ui->consts->setText((" " + std::to_string(preset.params.n)).c_str());
    ui->angle->setText((" " + std::to_string(preset.params.delta)).c_str());

    std::vector<QLineEdit *> rules = {ui->rule1, ui->rule2, ui->rule3, ui->rule4, ui->rule5};

    auto it = preset.params.rules.data.begin();
    int i = 0;
    for (; it != preset.params.rules.data.end(); it++, i++) {
        rules[i]->setText((" " + std::string(1, it->first) + ": " + it->second).c_str());
        rules[i]->setCursorPosition(0);
    }

    for (; i < rules.size(); i++)
        rules[i]->setText("");
}

void MainWindow::on_preset_clicked(int index)
{
    if (index == 0)
        setFractalForm(get_spiral());
    else if (index == 1)
        setFractalForm(get_fern());
    else if (index == 2)
        setFractalForm(get_ivy());
    else if (index == 3)
        setFractalForm(get_verbena());
}

preset_setting_t MainWindow::getFractalForm()
{
    preset_setting_t preset;

    preset.params.axiom = ui->axiom->text().toStdString();
    preset.params.n = ui->consts->text().toInt();
    preset.params.delta = ui->angle->text().toFloat();

    std::vector<QLineEdit *> rules = {ui->rule1, ui->rule2, ui->rule3, ui->rule4, ui->rule5};
    std::vector<char> from;
    std::vector<std::string> to;

    for (auto & i : rules)
    {
        std::string rule = i->text().toStdString();
        if (!rule.empty())
        {
            from.push_back(rule[1]);
            to.push_back(rule.substr(4, rule.size() - 2));
        }
    }
    Rules r{from, to};
    preset.params.rules = r;

    int ind = ui->Preset->currentIndex();

    int x_list[4] = {SPIRAL_X, FERN_X, IVY_X, VERBENA_X};
    int y_list[4] = {SPIRAL_Y, FERN_Y, IVY_Y, VERBENA_Y};
    int z_list[4] = {SPIRAL_Z, FERN_Z, IVY_Z, VERBENA_Z};
    float a_list[4] = {SPIRAL_ALPHA, FERN_ALPHA, IVY_ALPHA, VERBENA_ALPHA};
    float s_list[4] = {SPIRAL_STEP, FERN_STEP, IVY_STEP, VERBENA_STEP};

    preset.params.p[0] = x_list[ind];
    preset.params.p[1] = y_list[ind];
    preset.params.p[2] = z_list[ind];
    preset.params.alpha = a_list[ind];
    preset.params.step = s_list[ind];

    int c = ui->comboBox->currentIndex();
    if (c == 0)
        preset.color = {200, 255, 0};       // зеленый
    else if (c == 1)
        preset.color = {255,151,187};       // розовый
    else if (c == 2)
        preset.color = {53,102,204};        // фиолетовый
    else if (c == 3)
        preset.color = {255, 255, 102};     // желтый
    else if (c == 4)
        preset.color = {51, 51, 255};       // синий
    else if (c == 5)
        preset.color = {255, 51, 51};       // красный
    else if (c == 6)
        preset.color = {150, 75, 0};        // коричневый

    return preset;
}
