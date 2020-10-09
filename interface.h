#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDialog>
#include "game.h"

class Interface : public QDialog
{
    Q_OBJECT

public:
    Interface();

public slots:

    //void vec00(QPoint *pt);

    void vec01();
    void vec0_1();
    void vec10();
    void vec_10();
    void vec_11();
    void vec1_1();
    void vec11();
    void vec_1_1();

private:
    //void createMenu();
    void createMensagens();
    void createTabela();
    void createComandos();

    //QMenuBar *menuBar;
    QGroupBox *mensagem;
    QGroupBox *tabela;
    QGroupBox *comandos;
    QPushButton *buttons[3][3];
    QDialogButtonBox *buttonBox;

    //QMenu *fileMenu;
    //QAction *exitAction;

    game *jogo;

    QLabel *tela[2];

};

#endif // INTERFACE_H
