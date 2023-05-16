

#include "ChessWindow.hpp"
#pragma warning(push, 0)
#include <QString>
#include "Board.hpp"
#pragma pop()
#include <QPaintEvent>
#include "qpainter.h"
#include <qmessagebox.h>
viewInterface::ChessWindow::~ChessWindow() {
	delete boardP;
}

viewInterface::ChessWindow::ChessWindow(gameLogic::Board* boardP, QWidget* parent) :
	QMainWindow(parent), boardP(boardP)
{
	// Si on objet n a pas encore de parent on lui met "this" comme parent en attendant, si possible, pour s assurer que tous les pointeurs sont geres par un delete automatique en tout temps sans utiliser de unique_ptr.
	auto widgetPrincipal = new QWidget(this);

	setCentralWidget(widgetPrincipal);
	setWindowTitle("Ch*ss.com");
	connect(boardP, &gameLogic::Board::endOfGame, this, &ChessWindow::showResult);
}


int viewInterface::ChessWindow::getSquareSize() const{
	QSize screen = size();
	int SquareSize;
	if (screen.height() > screen.width())
		SquareSize = screen.width() / 8;
	else
		SquareSize = screen.height() / 8;
	return SquareSize;
}

void viewInterface::ChessWindow::paintEvent(QPaintEvent *event) {
	
	int SquareSize = getSquareSize();
	QPainter boardPainter(this);
	int x = 0, y = 0;
	bool isWhite = true;
	QColor white(240, 217, 181);
	QColor black(181, 136, 99);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			QRect r(x, y, SquareSize, SquareSize);
			if (j == coordinatesIn.first && i == coordinatesIn.second)
				boardPainter.fillRect(r, QColor(40, 160, 40));
			else if (isWhite)
				boardPainter.fillRect(r,white);
			else
				boardPainter.fillRect(r,black);
			std::string pieceInfo = boardP->getPieceInfo(j, i);
			if (!pieceInfo.empty()) {
				QString path = QString::fromStdString("images/Chess_" + pieceInfo + ".png");
				QPixmap pixmapWPawn(path);
				boardPainter.drawPixmap(r, pixmapWPawn);
			}
			
			isWhite = !isWhite;
			x += SquareSize;
		}
		y += SquareSize;
		x = 0;
		isWhite = !isWhite;
	}
}

void viewInterface::ChessWindow::mousePressEvent(QMouseEvent* event) {
	int squareSize = getSquareSize();
	QPoint pos = event->pos();
	
	if (pos.x() >= 0 && pos.x()/squareSize <= 7 && pos.y() >= 0 && pos.y()/squareSize <= 7)
		SquareClicked(pos.x()/squareSize, pos.y()/squareSize);
	update();
};

//determine si la piece peux etre selectionne, si oui elle deviens la piece selectionne. Autrement si elle ne peux pas etre selectionne et une piece est selectionne, essais de bouger la piece et affiche le board si possible
void viewInterface::ChessWindow::SquareClicked(const int column,const int row) {
	if (boardP->pieceSelectable(column, row))
		coordinatesIn = { column,row };
	else if (coordinatesIn.first != -1) {
		if (boardP->moveIsLegal(coordinatesIn.first, coordinatesIn.second, column, row)) {
			boardP->confirmedMove(coordinatesIn.first + coordinatesIn.second * 8, column + row * 8);
			update();
		}
		coordinatesIn = std::pair<int, int>(-1, -1);
	}
}

void viewInterface::ChessWindow::showResult(std::string result) {
	QMessageBox results;
	results.setText(QString::fromStdString(result));
	results.resize(200, 200);
	results.exec();
}
