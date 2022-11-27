//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_MAINWINDOW_H
#define C_VERSION_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "../connect/handle_buttons.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_loadButton_clicked();
    void on_cleanButton_clicked();
    void on_pushButton_clicked();
    void on_scaleButton_clicked();
    void on_rotateButton_clicked();
    void on_addLightButton_clicked();

private:
    void fillScene();

    Ui::MainWindow *ui;
    Handler handler;
    screen_t *screen_matrix;
};


#endif //C_VERSION_MAINWINDOW_H
