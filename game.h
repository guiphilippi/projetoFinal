#ifndef GAME_H
#define GAME_H

#include <QtWidgets>

enum tipo {livre,obstaculo,final,jogador,monstro,movel,empurravel,bonus,amigo,inativo};

class bloco;
//class entidade;
class game;

class bloco : public QTableWidgetItem {
public:
    bloco();
    bloco(int i, int j, game *jogo);
    //bloco(int i, int j, tipo tp, game *jogo);
    bloco(tipo tp);
    void Tipo(tipo tp);
    tipo Tipo();
    QPoint posicao();
    int pontuacao();
    void pontuacao(int valor);
    void soma(int valor);
//    entidade *entidade_;
private:
    tipo tipo_;
    int pontuacao_;
};
/*
class entidade : public bloco {
public:
    entidade(tipo tp);
    entidade(int x, int y, tipo tp, game *jogo);
    virtual void acao() {};
    QPoint posicao();
    int row();
    int column();
    bloco *bloco_;
};
*/
class jogador_ : public bloco {
public:
    jogador_();
    QPoint posicao();
    int row();
    int column();
    bloco *bloco_;
//    jogador_(bloco *bloco_, game *jogo);
//    void acao() {};
};
/*
class inimigo_ : public entidade {
public:
    inimigo_();
    void acao() {};
};
*/
class game : public QTableWidget
{
public:
    game(int rows, int columns, QWidget *parent, QLabel *tela_[2]);
    bool movimento(int x, int y, bloco *inicio);
    void setbloco(int x, int y, tipo tp);
    bool mudanca(int cont);
    bloco *Bloco(int x, int y);
    bloco *Bloco(QPoint pt);
//private:
    jogador_ *jogador1;
    QLabel   *tela[2];
    bloco   **blocos;
    bool      ativo;
};

#endif // GAME_H
