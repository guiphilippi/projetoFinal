#ifndef GAME_H
#define GAME_H

#include <QtWidgets>

#define param interacao I

//enum tipo {jogador,livre,obstaculo,final,monstro,movel,empurravel,bonus,amigo,inativo};

class bloco;
class entidade;
class pontuavel;
class movel_;
class game;
class lista;

class bloco : public QTableWidgetItem {
public:
    bloco(int x, int y, entidade *ent, game *jogo);
    QPoint posicao();
    game *jogo();
    bloco *deslocado(QPoint Vetor);
    void atualiza();
    void deslocamento(QPoint Vetor);
    bool tenta_mover(QPoint Vetor);
    entidade *Entidade();
    void Entidade(entidade *ent);
    ~bloco();
//private:
    entidade *entidade_;
};

class interacao {
public:
    interacao(bloco *ativo_, QPoint vetor_);
    bloco *ativo();
    bloco *reativo();
    QPoint vetor();
    game *jogo();
    bool _true();
    bool _return();
    void _return(bool b);
//private:
    bloco *ativo_;
    QPoint vetor_;
    bool return_;
};

class entidade {
public:
    virtual QColor cor() = 0;
    virtual void setbloco(bloco *bloco_);
    virtual bool acao(param);
    virtual bool reacao(param);
    virtual ~entidade();
};

class pontuavel : public entidade {
public:
    virtual void setbloco(bloco *bloco_);
    virtual bool acao(param);
    virtual bool reacao(param);
    pontuavel();
    pontuavel(int x, int y);
    virtual void soma(pontuavel *ent);
    int pontuacao();
    void pontuacao(int valor);
    virtual ~pontuavel();
private:
    int pontuacao_;
};

class obstaculo_ : public entidade {
public:
    QColor cor();
};

class ocupavel_ : public entidade {
public:
    virtual QColor cor();
    virtual bool acao(param);
};

class empurravel_ : public ocupavel_ {
public:
    virtual QColor cor();
    virtual bool acao(param);
};

class bonus_ : public pontuavel, public ocupavel_ {
public:
    QColor cor();
    bool acao(param);
    bonus_(int x, int y);
};

class inativo_ : public pontuavel {
public:
    QColor cor();
    bool acao(param);
    inativo_(int x, int y);
};

class final_ : public entidade {
public:
    virtual QColor cor();
    virtual bool acao(param);
    virtual QString mensagem();
};

class movel_ : public entidade {
public:
    virtual QColor cor();
    virtual void setbloco(bloco *b);
    movel_();
    movel_(lista *lista_);
    virtual QPoint posicao();
    virtual void Bloco(bloco *b);
    virtual bloco *Bloco();
    //virtual ~movel_();
//private:
    bloco *bloco_;
};
/*
class criatura : public pontuavel, public movel_ {
public:
    QColor cor();
    //virtual bool acao(param);
    //virtual bool reacao(param);
    //void setbloco(bloco *b);
    //void ativa(bloco *bloco_, lista *lista_);
    criatura();
    //criatura(lista *lista_);
    //criatura(bloco *bloco_, lista *lista_);
};
*/
class amigo_ : public pontuavel, public movel_, public empurravel_ {
public:
    virtual QColor cor();
    bool acao(param);
    //virtual bool reacao(param);
    virtual void setbloco(bloco *b);
    amigo_(bloco *bloco_, lista *lista_);
};

class monstro_ : public pontuavel, public movel_, public final_ {
public:
    QColor cor();
    bool acao(param);
    //bool reacao(param);
    void ativa(bloco *bloco_, lista *lista_);
    void setbloco(bloco *b);
    QString mensagem();
    monstro_(lista *lista_);
    //monstro_(bloco *bloco_, lista *lista_);
};

class jogador_ : public pontuavel, public movel_ {
public:
    QColor cor();
    bool acao(param);
    //bool reacao(param);
    void setbloco(bloco *b);
    void soma(pontuavel *ent);
};

class lista {
public:
    lista();
    movel_ **entidades;
    int quantidade;
    void adiciona(movel_ *ent);
    ~lista();
};

class game : public QTableWidget
{
public:
    game(int rows, int columns, QWidget *parent, QLabel *tela_[2]);
    void criaBloco(int x, int y, entidade *ent);
    void movimento(int x, int y, bloco *inicio);
    void mudanca();
    bloco *Bloco(int x, int y);
    bloco *Bloco(QPoint ponto);
    lista *lista_;
//private:
    jogador_ *jogador;
    ocupavel_   *ocupavel;
    obstaculo_ *obstaculo1;
    final_ *final1;
    //movel_ *movel1;
    empurravel_ *empurravel1;
    bool      ativo;
    QLabel   *tela[2];
};

#endif // GAME_H
