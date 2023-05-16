#pragma once
#include "Board.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "TryMove.hpp"



gameLogic::Board::Board(std::string fen) {
	int pos = 0;
	size_t end = fen.find(' ');
	std::string boardDescription = fen.substr(0, end);
	for (char character : boardDescription)
		if (isdigit(character))
			pos += character - 48;
		else if (character == '/')
			continue;
		else {
			setup(character, pos);
			pos++;
		}
	whiteTurn_ = (fen[end + 1] == 'w');
}

void gameLogic::Board::placePiece(std::unique_ptr<Piece> pieceP, const int positionOut) {
	if (pieceP->isKing()) 
		kingPositions_[pieceP->isWhite()] = positionOut;
	pieces_[positionOut] = move(pieceP);
}

std::unique_ptr<Piece> gameLogic::Board::movePiece(const int positionIn, const int positionOut) {
	std::unique_ptr<Piece> replaced = move(pieces_[positionOut]);
	if (pieces_[positionIn]->isKing())
		kingPositions_[whiteTurn_] = positionOut;
	pieces_[positionOut] = move(pieces_[positionIn]);
	return replaced;
}

void gameLogic::Board::confirmedMove(const int positionIn, const int positionOut) {

	if (pieces_[positionIn]->isKing())
		kingPositions_[whiteTurn_] = positionOut;

	pieces_[positionOut] = move(pieces_[positionIn]);

	//si la piece est un pion et quil est rendu a lextremite du board, elle est remplace par une reine
	if (dynamic_cast<Pawn*>(pieces_[positionOut].get()) && (positionOut < 8 || positionOut > 55))
		placePiece(make_unique<Queen>(pieces_[positionOut]->getColor()), positionOut);

	pieces_[positionOut]->hasMoved();

	//si le joueur a finis son tour, son roi est forcement pas en echec
	dynamic_cast<King*>((pieces_)[kingPositions_[whiteTurn_]].get())->inCheck = false;
	
	whiteTurn_ = !whiteTurn_;
	checkEndGameConditions();
}

bool gameLogic::Board::moveIsLegal(const int columnIn,const int rowIn,const int columnOut,const int rowOut,const bool real) {
	using namespace gameLogic;
	int positionIn = columnIn + rowIn * 8;
	int positionOut = columnOut + rowOut * 8;
	if (positionIn == positionOut)
		return false;

	bool capture = false;

	if (pieces_[positionOut] != nullptr) {
		if (pieces_[positionOut]->isWhite() == pieces_[positionIn]->isWhite())
			return false;
		//definis si le mouvement est une capture
		capture = pieces_[positionIn]->isWhite() != pieces_[positionOut]->isWhite();
	}
	int step = pieces_[positionIn]->canMove(columnOut - columnIn, rowOut - rowIn, capture);
	if (step == 0)
		return false;

	//if (step == 50)


	//verifie que le chemin est libre, si step == 100 le mouvement est directement valide (king ou knight)
	if (step != 100)
		for (int i = positionIn + step; i != positionOut; i += step)
			if (pieces_[i] != nullptr)
				return false;
	//n essais pas le move si la fonction est appele pour verifier un echec
	if (!real)
		return true;

	TryMove triedMove(positionIn, positionOut, this);

	if (isCheck(kingPositions_[whiteTurn_]))
		return false;
	return true;
}



bool gameLogic::Board::pieceSelectable(const int column,const int row) const {
	if (pieces_[column + row * 8] == nullptr)
		return false;
	return pieces_[column + row * 8]->isWhite() == whiteTurn_;
}

std::string gameLogic::Board::getPieceInfo(const int column,const int row) const {
	int pos = column + row*8;
	if (pieces_[pos] == nullptr)
		return "";
	return pieces_[pos]->showPiece();
}

bool gameLogic::Board::isCheck(const int kingPosition){
	int positionIn =0;
	for (const auto& piece : pieces_) {
		if (piece != nullptr)
			if (piece->isWhite()!=(pieces_)[kingPosition]->isWhite())
				if (moveIsLegal(positionIn % 8, positionIn / 8, kingPosition % 8, kingPosition / 8, false))
					return true;
		positionIn++;
	}
	return false;
}


bool gameLogic::Board::isMate() {
	int kingPos = kingPositions_[whiteTurn_];
	for (int pos = 0; pos < 64; pos++) {
		if (kingPos == pos)
			continue;
		if (moveIsLegal(kingPos % 8, kingPos / 8, pos % 8, pos / 8))
			return false;
	}
	int positionIn = 0;
	for (auto& pieceP : pieces_) {
		if (pieceP != nullptr)
			if (pieceP->isWhite() == whiteTurn_)
				for (int positionOut = 0; positionOut < 64; positionOut++)
					if (moveIsLegal(positionIn % 8, positionIn / 8, positionOut % 8, positionOut / 8))
						return false;
		positionIn++;
	}
	return true;

}

bool gameLogic::Board::isStalemate() {
	int kingPos = kingPositions_[whiteTurn_];
	int min = kingPos > 9 ? kingPos - 9 : 0;
	int max = kingPos < 54 ? kingPos + 9 : 63;
	for (int pos = min; pos < max; pos++) {
		if (kingPos == pos)
			continue;
		if (moveIsLegal(kingPos % 8, kingPos / 8, pos % 8, pos / 8))
			return false;
	}
	int positionIn = 0;
	for (auto& pieceP : pieces_) {
		if (pieceP != nullptr && positionIn != kingPos)
			if (pieceP->isWhite() == whiteTurn_)
				for (int positionOut = 0; positionOut < 64; positionOut++)
					if (moveIsLegal(positionIn % 8, positionIn / 8, positionOut % 8, positionOut / 8))
						return false;
		positionIn++;
	}
	return true;
}

void gameLogic::Board::checkEndGameConditions() {
	if (isCheck(kingPositions_[whiteTurn_])) {
		dynamic_cast<King*>((pieces_)[kingPositions_[whiteTurn_]].get())->inCheck = true;
		if (isMate()) {
			if (whiteTurn_)
				emit endOfGame("black wins by checkmate");
			else
				emit endOfGame("white wins by checkmate");
		}
	}
	else if (isStalemate())
		if (whiteTurn_)
			emit endOfGame("stalemate white cannot move");
		else
			emit endOfGame("stalement black cannot move");
}

void gameLogic::Board::setup(const char id, const int pos) {
	std::string color;
	if (id < 97)
		color = "white";
	else
		color = "black";
	switch (tolower(id)) {
	case 'p':
		placePiece(std::move(std::make_unique<Pawn>(Pawn(color))),pos);
		break;
	case 'b':
		placePiece(std::move(std::make_unique<Bishop>(Bishop(color))),pos);
		break;
	case 'k':
		placePiece(std::move(std::make_unique<King>(King(color))), pos);
		kingPositions_[color == "white"] = pos;
		break;
	case 'q':
		placePiece(std::move(std::make_unique<Queen>(Queen(color))), pos);
		break;
	case 'n':
		placePiece(std::move(std::make_unique<Knight>(Knight(color))), pos);
		break;
	case 'r':
		placePiece(std::move(std::make_unique<Rook>(Rook(color))), pos);
		break;
	}
	int position = 0;
	for (auto& pieceP : pieces_) {
		if (dynamic_cast<Pawn*>(pieceP.get()) && !(position / 8 == 1 || position / 8 == 6))
			pieceP->hasMoved();
		position++;
	}	
}