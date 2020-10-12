#ifndef GAME_H
#define GAME_H

#include <QtWidgets>

//enum tipo {jogador,livre,obstaculo,final,monstro,movel,empurravel,bonus,amigo,inativo};

class bloco;
class entidade;
class pontuavel;
class game;
class lista;

class bloco : public QTableWidgetItem {
public:
    QPoint posicao();
    game *jogo();
    void deslocamento(bloco *bloco_);
    bool deslocamento(int x, int y);
    bool finaliza(QString texto);
    bloco *deslocado(int x, int y);
    bool tenta_mover(int x, int y);
    entidade *entidade_;
};

class entidade {
public:
    virtual QColor cor() = 0;
    virtual void acao();
    virtual bool reacao(int x, int y, bloco *inicio);
    virtual void setbloco(bloco *bloco_);
    virtual int pontuacao();
    virtual bool soma(bloco *b);
//    virtual bloco *Bloco();
};

class pontuavel : public entidade {
public:
    pontuavel();
    pontuavel(int x, int y);
    virtual bool reacao(int x, int y, bloco *inicio);
    virtual void setbloco(bloco *bloco_);
    int pontuacao();
    void pontuacao(int valor);
    bool soma(bloco *b);
private:
    int pontuacao_;
};

class autonomo {
public:
//    autonomo_(lista *lista_);
    void acao();
//    void setbloco(bloco *b);
    bloco *Bloco();
    bloco *bloco_;
};

class livre_ : public entidade {
public:
    QColor cor();
    bool reacao(int x, int y, bloco *inicio);
};

class obstaculo_ : public entidade {
public:
    QColor cor();
};

class final_ : public entidade {
    QColor cor();
    bool reacao(int x, int y, bloco *inicio);
};

class movel_ : public entidade, public autonomo {
public:
    movel_(lista *lista_);
    QColor cor();
    void acao();
    void setbloco(bloco *b);
};

class empurravel_ : public entidade {
    QColor cor();
    bool reacao(int x, int y, bloco *inicio);
};

class monstro_ : public pontuavel, public autonomo {
public:
    monstro_(lista *lista_);
    QColor cor();
    void acao();
    void setbloco(bloco *b);
    bool reacao(int x, int y, bloco *inicio);
};

class bonus_ : public pontuavel {
public:
    bonus_(int x, int y);
    QColor cor();
    bool reacao(int x, int y, bloco *inicio);
};

class amigo_ : public pontuavel {
public:
    amigo_(bloco *bloco_);
    QColor cor();
    bool reacao(int x, int y, bloco *inicio);
};

class inativo_ : public pontuavel {
public:
    inativo_(int x, int y);
    QColor cor();
    bool reacao(int x, int y, bloco *inicio);
    //~inativo_();
};

class jogador_ : public pontuavel {
public:
    QColor cor();
    bool reacao(int x, int y, bloco *inicio);
    void setbloco(bloco *b);
    bool soma(bloco *b);
    QPoint posicao();
    bloco *bloco_;
};

class lista {
public:
    lista();
    entidade **entidades;
    int quantidade;
    void adiciona(entidade *ent);
};

class game : public QTableWidget
{
public:
    game(int rows, int columns, QWidget *parent, QLabel *tela_[2]);
    void criaBloco(int x, int y, entidade *ent);
    bool movimento(int x, int y, bloco *inicio);
    void mudanca();
    bloco *Bloco(int x, int y);
    bloco *Bloco(QPoint ponto);
    lista *lista_;
//private:
    jogador_ *jogador1;
    livre_   *livre1;
    obstaculo_ *obstaculo1;
    final_ *final1;
    //movel_ *movel1;
    empurravel_ *empurravel1;
    QLabel   *tela[2];
    bool      ativo;
};

#endif // GAME_H
