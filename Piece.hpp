#pragma once
#include "Board.hpp"


	class Piece {
	public:
		Piece(std::string color) : color_(color) {}
		virtual std::string showPiece() const = 0;

		//regarde si la piece peut se deplacer de cette facon, si oui, elle renvois son deplacement par case pour verifier qu elle n est pas bloquee. 
		// 0 signifie impossible, 100 signifie que la piece passe sans verification, autrement elle retourne le nombre de place dans l array que la piece traverse pas case
		virtual int canMove(const int deplacementX, const int deplacementY, const bool capture = false) const = 0;
		virtual bool isKing() const = 0;
		//getter de color_
		std::string getColor();
		//un setter pour lattribut moved
		void hasMoved();
		//retourne color_ == "white"
		bool isWhite();
	protected:
		std::string color_;
		//si la piece a bougee depuis le debut de la partie, pour le mouvement de 2 cases des pions et castle pour le roi et les tours
		bool moved_ = false;
	};
