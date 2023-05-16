#pragma once
#include "Board.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements a /W4.
#include <QMainWindow>
#pragma pop()


namespace viewInterface {
	class ChessWindow : public QMainWindow {
		Q_OBJECT

	public:
		ChessWindow(gameLogic::Board* boardP, QWidget* parent = nullptr);
		~ChessWindow();
		//colorie les cases de lechiquier
		virtual void paintEvent(QPaintEvent* event);
		//appelle squareClicked si les coordonnee du click sont bonnes
		void mousePressEvent(QMouseEvent* event);
		//permet resize chessWindow mais de garder lechiquier proportionne
		int getSquareSize() const;
		//valide un click sur une case
		void SquareClicked(const int column,const int row);
	public slots:
		//affiche le resultat dune partie
		void showResult(std::string result);

	private:
		gameLogic::Board* boardP;
		//coordonnee de la case presentement selectionnee
		std::pair<int, int> coordinatesIn = { -1,-1 };
	};
}