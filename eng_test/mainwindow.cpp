#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Я просто тут оголосив, щоб контур квадратів був трохи ширший
    // PS: Це значення не має ефекту на картинки, лише намальовані фігури
    pen.setWidth(5);
}


// Функція виводить на екран усі графічні елементи
// PS: клас QRect використано усюди задля більш простого контролю за положенням елементів
// Можна вважати об'єкти QRect "каркасом" елементу, або ж hitbox'ом, якщо ви знайомі з ігровою термінологією
void MainWindow::paintEvent(QPaintEvent *event) {
    painter.begin(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRoundedRect(rects[0], 20, 20, Qt::RelativeSize);
    painter.drawRoundedRect(rects[1], 20, 20, Qt::RelativeSize);
    painter.drawRoundedRect(rects[2], 20, 20, Qt::RelativeSize);
    painter.drawPixmap(img_pos[0], images[0]);
    painter.drawPixmap(img_pos[1], images[1]);
    painter.drawPixmap(img_pos[2], images[2]);
    painter.end();
}


// Ця функція вмикається, коли тільки натиснуто клавішу миші (будь яку) та перевіряє, чи це натискання було на якусь із картинок
// Якщо натискання сталося поза межами будь-якої з картинок, то активним значенням стає nullptr
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (img_pos[0].contains(event->pos())) {
        active_img=img_pos;
        location_buffer=active_img->center()-event->pos();
    } else if (img_pos[1].contains(event->pos())) {
        active_img=img_pos+1;
        location_buffer=active_img->center()-event->pos();
    } else if (img_pos[2].contains(event->pos())) {
        active_img=img_pos+2;
        location_buffer=active_img->center()-event->pos();
    } else {
        active_img=nullptr;
    }
}


// Ця функція перетягує за курсором картинку, поки мишу натиснуто
// PS: Якщо активним значенням є nullptr, то функція перериває себе на початку та нічого не переміщає
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (active_img==nullptr) return;

    active_img->moveCenter(event->pos()+location_buffer);
    update();
}


// Коли відпускається клавіша миші, активується ця функція
// Вона "притягує" картинку до центру квадрату, якщо курсор на момент спрацьовування функції знаходиться всередині квадрата
// PS: Тут знову є перевірка на nullptr задля того, щоб не переміщувати неіснуючу картинку
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (active_img==nullptr) return;

    if (rects[0].contains(event->pos())) {
        active_img->moveCenter(rects[0].center());
    } else if (rects[1].contains(event->pos())) {
        active_img->moveCenter(rects[1].center());
    } else if (rects[2].contains(event->pos())) {
        active_img->moveCenter(rects[2].center());
    }
    update();
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Перевіряє правильність виконання завдання після натискання кнопки
// Виводить "Correct!" при правильному виконанні та "Wrong :(" при неправильному
void MainWindow::on_pushButton_clicked()
{
    if (rects[0].center()==img_pos[1].center() && rects[1].center()==img_pos[0].center() && rects[2].center()==img_pos[2].center()) {
        this->ui->label_4->setText("Correct!");
    } else {
        this->ui->label_4->setText("Wrong :(");
    }
}



// Кнопка для виходу з програми
void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}

