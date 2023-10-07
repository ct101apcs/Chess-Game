#include "../../../ChessBoard/ChessBoard.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    ChessBoard chessApp;
    chessApp.show();
    return app.exec();
}
