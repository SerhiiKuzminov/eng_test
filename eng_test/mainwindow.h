#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Функція paintEvent виводить на екран картинки ті прямокутники, у які їх треба перенести
    void paintEvent(QPaintEvent *event);

    // Наступні три функції фіксують, коли користувач натискає на картинку та дозволяють її перетягувати
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слоти кнопок на вихід з програми та перевірки на правильність розташування картинок
    // PS: можна ще дописати, щоб картинки після невдачної спроби поверталися у початкове положення
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    // Ці дві змінні зберігають у собі інформацію про картинку, на яку натиснув користувач
    // PS: змінна location_buffer створена просто для того, щоб під час перетягування картинка не зміщувалася відносно курсору миші
    QPoint location_buffer;
    QRect *active_img;

    // Інструменти для виведення зображення за допомогою класу QPainter
    QPainter painter;
    QPen pen=QPen(10);
    QBrush brush=QBrush(Qt::lightGray);

    // Цей масив зберігає положення та розмір квадратиків, у які треба вкладати картинки
    QRect rects[3] = {QRect(25, 60, 150, 150), QRect(225, 60, 150, 150), QRect(425, 60, 150, 150)};

    // Два наступні масиви зберігають інформацію про положення й розмір картинок та їх вміст відповідно
    QRect img_pos[3] = {QRect(25, 400, 125, 125), QRect(225, 400, 125, 125), QRect(425, 400, 125, 125)};
    QPixmap images[3] = {QPixmap(":/images/cat.jpg"), QPixmap(":/images/dawg.jpg"), QPixmap(":/images/DA_RAT.jpg")};


    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
