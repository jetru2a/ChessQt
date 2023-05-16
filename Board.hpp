#pragma once
#pragma warning(push, 0)
#include <QObject>
#pragma pop()
#include <fstream>
#include <string>

class Piece;

namespace gameLogic {

	class Board : public QObject{
		Q_OBJECT
	public:
		//utilise la notation FEN pour construire un board
		Board(std::string fen);
		//place un pointeur unique d une piece sur un case
		void placePiece(std::unique_ptr<Piece> pieceP, const int positionOut);

		// bouge une piece et retourne ce qui etait sur la piece maintenant occupe
		//bouge une piece et retourne la piece remplace
		std::unique_ptr<Piece> movePiece(const int positionIn, const int positionOut);

		//determine si un mouvement est legal (direction correct de la piece, aucune piece dans le chemin, et pas en echec apres le mouvement)
		bool moveIsLegal(const int columnIn, const int rowIn, const int columnOut, const int rowOut, const bool real = true);

		// retourne un string contenant la couleur et le nom de la piece. avec un C si il sagit dun roi en echec
		std::string getPieceInfo(const int column,const int row) const;

		//determine si la case possede une piece et si elle peut etre jouee durant ce tour
		bool pieceSelectable(const int column,const int row) const;

		//determine si une piece de couleur oppose au roi possede un mouvement legal sur lui
		bool isCheck(const int kingPosition);

		//determine si le roi peux echapper a son attaqueur ou si une autre piece de la meme couleur peux larreter
		bool isMate();

		//determine si le joueur na aucun move possible
		bool isStalemate();

		//effectue le mouvement, change les position des roi dans largument de Board et determine si ladversaire est maintenant en echec
		void confirmedMove(const int positionIn, const int positionOut);

		//determine si la game est termine
		void checkEndGameConditions();

		//creer et place la piece
		void setup(const char id, const int pos);

	signals:
		//envois un singal au window chessWindow pour afficher le resultat
		void endOfGame(std::string result);

	protected:
		std::unique_ptr<Piece> pieces_[64];

		// les positions des deux roi sur le board : roi noir, roi blanc
		int kingPositions_[2] = { 4,60 };
		bool whiteTurn_ = true;
	};
}