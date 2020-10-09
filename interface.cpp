#include <QtWidgets>

#include "interface.h"
#include "game.h"

Interface::Interface()
{
    //createMenu();
    createMensagens();
    createTabela();
    createComandos();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    //mainLayout->setMenuBar(menuBar);

    mainLayout->addWidget(mensagem);
    mainLayout->addWidget(tabela);
    mainLayout->addWidget(comandos);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Jogo"));
}
/*
void Interface::createMenu()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, &QAction::triggered, this, &QDialog::accept);
}
*/
void Interface::createMensagens()
{
    mensagem = new QGroupBox(tr("Mensagens"));

    QFormLayout *layout = new QFormLayout;

        tela[0] = new QLabel;
        tela[1] = new QLabel;
        layout->addWidget(tela[0]);
        layout->addWidget(tela[1]);

    tela[0]->setText(QString("Blocos: azul = jogador / preto = obstaculo / cinza = obstaculo movel / amarelo = obstaculo empurravel "
                             "\n"
                             "             ciano = pontuacao / roxo(escuro) = amigo(inativo) / vermelho = morte / verde = fim do jogo."));

    tela[1]->setText(QString("Pontuacao: 0"));

    mensagem->setLayout(layout);
}

void Interface::createTabela()
{
    tabela = new QGroupBox(tr("Tabela"));

    QBoxLayout *layout = new QHBoxLayout;

        jogo = new game(15,15,this,tela);
        layout->addWidget(jogo);

    tabela->setFixedSize(400,400);

    tabela->setLayout(layout);
}

void Interface::createComandos()
{
    comandos = new QGroupBox(tr("Comandos"));

    QGridLayout *layout = new QGridLayout;

    for (int i = 0; i < 3; ++i) {

        for (int j = 0; j < 3; ++j) {

            buttons[i][j] = new QPushButton;

            layout->addWidget(buttons[i][j], i + 1, j + 1);

            //connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec00(new QPoint(i,j))));

            if (i==0 && j==0) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec_1_1()));}
            if (i==0 && j==1) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec0_1()));}
            if (i==0 && j==2) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec1_1()));}
            if (i==1 && j==0) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec_10()));}
            if (i==1 && j==2) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec10()));}
            if (i==2 && j==0) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec_11()));}
            if (i==2 && j==1) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec01()));}
            if (i==2 && j==2) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(vec11()));}

            //if (i==1 && j==1) {connect(buttons[i][j],SIGNAL(clicked()),this,SLOT(reiniciar()));}

        }
    }

    comandos->setLayout(layout);
}

//void Interface::vec00(QPoint *pt) {jogo->movimento(pt->x(),pt->y(),jogo->jogador1);}

void Interface::vec01() {jogo->movimento(1,0,jogo->jogador1->bloco_);}
void Interface::vec0_1() {jogo->movimento(-1,0,jogo->jogador1->bloco_);}
void Interface::vec10() {jogo->movimento(0,1,jogo->jogador1->bloco_);}
void Interface::vec_10() {jogo->movimento(0,-1,jogo->jogador1->bloco_);}
void Interface::vec_11() {jogo->movimento(1,-1,jogo->jogador1->bloco_);}
void Interface::vec1_1() {jogo->movimento(-1,1,jogo->jogador1->bloco_);}
void Interface::vec11() {jogo->movimento(1,1,jogo->jogador1->bloco_);}
void Interface::vec_1_1() {jogo->movimento(-1,-1,jogo->jogador1->bloco_);}

