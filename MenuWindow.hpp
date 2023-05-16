#pragma once
#pragma warning(push, 0)
#include <QMainWindow>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include "Board.hpp"
#pragma pop()

class ChessWindow;

namespace viewInterface {

	class MenuWindow : public QMainWindow {
		Q_OBJECT

	public:
        std::unique_ptr<ChessWindow> chessWindow;
		MenuWindow(QWidget* parent = nullptr);
        void startGame(QString gameId);
        QPushButton* newButton(const char* identifier, QString gameId);
        ~MenuWindow();
	private:
		QWidget* centralwidget;
		QWidget* gridLayoutWidget;
        void setupUi(QMainWindow* MainWindow);
	};
}
