// 
#include "ChessWindow.hpp"
#include "MenuWindow.hpp"
#pragma warning(push, 0)
#include "Board.hpp"
#pragma pop()
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QScreen>


viewInterface::MenuWindow::MenuWindow(QWidget* parent) :
    QMainWindow(parent), chessWindow(std::make_unique<ChessWindow>(new gameLogic::Board("")))
{
    auto widgetPrincipal = new QWidget(this);

    setCentralWidget(widgetPrincipal);
    setWindowTitle("Ch*ss.com");
    setupUi(this);
}

viewInterface::MenuWindow::~MenuWindow() {

}

QPushButton* viewInterface::MenuWindow::newButton(const char* identifier, QString gameId) {
    QPushButton* button = new QPushButton(gridLayoutWidget);
    button->setText(QCoreApplication::translate("MainWindow", identifier, nullptr));
    button->setProperty("gameId", gameId);
    QObject::connect(button, &QPushButton::clicked, this, [=]() {startGame(button->property("gameId").toString()); });
    return button;
}
void viewInterface::MenuWindow::setupUi(QMainWindow* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(800, 600);
    centralwidget = new QWidget(MainWindow);
    gridLayoutWidget = new QWidget(centralwidget);
    gridLayoutWidget->setGeometry(QRect(10, 10, 340, 540));
    QGridLayout* gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    gridLayout->addWidget(newButton("queen checkmate", "8/8/8/4k3/8/8/8/3QK3 w KQkq - 0 1"), 0, 0, 1, 1);
    gridLayout->addWidget(newButton("rook checkmate", "8/8/8/4k3/8/8/8/3RK3 w KQkq - 0 1"), 1, 0, 1, 1);
    gridLayout->addWidget(newButton("two bishop checkmate", "8/8/8/4k3/8/8/8/2B1KB2 w KQkq - 0 1"), 2, 0, 1, 1);
    gridLayout->addWidget(newButton("bishop and knight checkmate", "8/8/8/4k3/8/8/8/4KBN1 w KQkq - 0 1"), 3, 0, 1, 1);
    gridLayout->addWidget(newButton("classic board", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"), 0, 1, 1, 1);
    gridLayout->addWidget(newButton("pawn endgame", "8/1p5p/4k2P/p3p1P1/P3K3/8/8/8 b - - 0 48"), 1, 1, 1, 1);
    gridLayout->addWidget(newButton("pawn and rook endgame", "8/8/8/2k5/8/4K3/3R1P1r/8 w KQkq - 0 1"), 2, 1, 1, 1);
    gridLayout->addWidget(newButton("bishop vs rook endgame", "R7/5pkp/4b1p1/3p4/8/5P2/5KPP/8 b - - 0 43"), 3, 1, 1, 1);

    QTextEdit* textEdit = new QTextEdit(centralwidget);
    textEdit->setGeometry(QRect(450, 400, 300, 30));
    textEdit->setPlainText("enter game code (Fen notation)");;

    QPushButton* customGame = new QPushButton(centralwidget);
    customGame->setText(QCoreApplication::translate("MainWindow", "start custom game", nullptr));
    QObject::connect(customGame, &QPushButton::clicked, this, [=]() {startGame(textEdit->toPlainText()); });
    customGame->setGeometry(QRect(500, 470, 200, 40));

    MainWindow->setCentralWidget(centralwidget);
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ch*ss.com", nullptr));
}


void viewInterface::MenuWindow::startGame(QString gameId) {
    gameLogic::Board* boardP = new gameLogic::Board(gameId.toStdString());
    chessWindow = std::make_unique<ChessWindow>(boardP);
    chessWindow->show();
    chessWindow->setGeometry(screen()->geometry().center().x()-400, screen()->geometry().center().y()-400, 800, 800);
    hide();
};

