#include <QtWidgets>

#include "game.h"

//--- interacao - "get/set" - bloco - cores - construtores - setbloco - soma - mensagens - acao/reacao - movimento - mudanca - lista - game()

//*** interacao

interacao::interacao(bloco *ativo1, QPoint vetor1) {ativo_ = ativo1; vetor_ = vetor1; return_ = false;}

bloco *interacao::ativo() {return ativo_;}
bloco *interacao::reativo() {return ativo()->deslocado(vetor());}
QPoint interacao::vetor() {return vetor_;}
game *interacao::jogo() {return ativo()->jogo();}
bool interacao::_true() {return_ = true; return return_;}
bool interacao::_return() {return return_;}
void interacao::_return(bool b) {return_ = b;}

//*** "get/set"

game *bloco::jogo() {return (game*) tableWidget();}
QPoint bloco::posicao() {return QPoint(row(),column());}
entidade *bloco::Entidade() {return entidade_;}
void bloco::Entidade(entidade *ent) {entidade_ = ent;}

QPoint movel_::posicao() {return Bloco()->posicao();}
bloco *movel_::Bloco() {return bloco_;}
void movel_::Bloco(bloco *b) {bloco_ = b;}

int pontuavel::pontuacao() {return pontuacao_;}
void pontuavel::pontuacao(int valor) {pontuacao_ = valor;}

bloco *game::Bloco(int x, int y) {return (bloco*) item(x,y);}
bloco *game::Bloco(QPoint ponto) {return Bloco(ponto.x(),ponto.y());}

// *** bloco

bloco *bloco::deslocado(QPoint vetor) {return jogo()->Bloco(this->posicao() + vetor);}

void bloco::atualiza() {Entidade()->setbloco(this);}

void bloco::deslocamento(QPoint vetor) {Entidade()->setbloco(deslocado(vetor)); jogo()->ocupavel->setbloco(this);}

bool bloco::tenta_mover(QPoint vetor) {return deslocado(vetor)->Entidade()->acao(interacao(this, vetor));}

//*** entidades

      //*** cores

      QColor ocupavel_::cor() {return Qt::white;}
      QColor obstaculo_::cor() {return Qt::black;}
      QColor movel_::cor() {return Qt::gray;}
      QColor empurravel_::cor() {return Qt::yellow;}
      QColor final_::cor() {return Qt::green;}
      QColor amigo_::cor() {return Qt::magenta;}
      QColor monstro_::cor() {return Qt::red;}
      QColor bonus_::cor() {return Qt::cyan;}
      QColor inativo_::cor() {return Qt::darkMagenta;}
      QColor jogador_::cor() {return Qt::blue;}

      //QColor criatura::cor() {return Qt::darkYellow;}

      //*** construtores & destrutores

      bloco::bloco(int x, int y, entidade *ent, game *jogo) {jogo->setItem(x,y,this); ent->setbloco(this);}
      void game::criaBloco(int x, int y, entidade *ent) {new bloco(x,y,ent,this);}
      bloco::~bloco() {if(Entidade()) delete Entidade();}

      entidade::~entidade() {}
      pontuavel::~pontuavel() {}
      //movel_::~movel_() {}

      pontuavel::pontuavel() {pontuacao(0);}
      pontuavel::pontuavel(int x, int y) {pontuacao(QRandomGenerator::global()->bounded(x,y));}

      movel_::movel_() {}
      movel_::movel_(lista *lista_) {lista_->adiciona(this);}

      bonus_::bonus_(int x, int y) : pontuavel(x, y) {}
      inativo_::inativo_(int x, int y) : pontuavel(x, y) {}
      monstro_::monstro_(lista *lista_) : pontuavel() , movel_(lista_) {}
      amigo_::amigo_(bloco *bloco_, lista *lista_) : pontuavel() , movel_(lista_) {setbloco(bloco_);}

      //criatura::criatura() : pontuavel() {}
      //criatura::criatura(lista *lista_) : pontuavel() , movel_(lista_) {}
      //criatura::criatura(bloco *bloco_, lista *lista_) : pontuavel() , movel_(lista_) {setbloco(bloco_);}
      /*
      monstro_::monstro_(lista *lista_) : criatura(lista_) {}
      monstro_::monstro_(bloco *bloco_, lista *lista_) : criatura(bloco_, lista_) {}
      amigo_::amigo_(bloco *bloco_, lista *lista_) : criatura(bloco_, lista_) {}
      */

      //void criatura::ativa(bloco *bloco_, lista *lista_) {new amigo_(bloco_, lista_);}
      //void monstro_::ativa(bloco *bloco_, lista *lista_) {new monstro_(bloco_, lista_);}

      //*** setbloco

      void entidade::setbloco(bloco *bloco_) {bloco_->setBackground(cor()); bloco_->setText(QString("")); bloco_->Entidade(this);}
      void pontuavel::setbloco(bloco *bloco_) {entidade::setbloco(bloco_); bloco_->setText(QString("%1").arg(this->pontuacao()));}

      void movel_::setbloco(bloco *b) {entidade::setbloco(b); Bloco(b);}
      //void criatura::setbloco(bloco *b) {pontuavel::setbloco(b); Bloco(b);}
      void amigo_::setbloco(bloco *b) {pontuavel::setbloco(b); Bloco(b);}
      void monstro_::setbloco(bloco *b) {pontuavel::setbloco(b); Bloco(b);}
      void jogador_::setbloco(bloco *b) {pontuavel::setbloco(b); Bloco(b);}

      //***soma

      void pontuavel::soma(pontuavel *ent) {pontuacao(pontuacao() + ent->pontuacao()); delete ent;}
      void jogador_::soma(pontuavel *ent) {pontuavel::soma(ent); bloco_->jogo()->tela[1]->setText(QString("Pontuacao: %1").arg(this->pontuacao()));}

      //*** mensagens

      QString final_::mensagem() {return QString("Voce venceu!");}
      QString monstro_::mensagem() {return QString("Voce perdeu!");}

      //*** reacoes

      bool entidade::acao(param) {return false;}
      bool entidade::reacao(param) {return false;}

      bool pontuavel::acao(param) {return I.ativo()->Entidade()->reacao(I);}
      bool pontuavel::reacao(param) {soma((pontuavel*) I.reativo()->Entidade()); return true;}
      // se ativo tambem for pontuavel vai somar

      bool ocupavel_::acao(param) {I.ativo()->deslocamento(I.vetor()); return I._true();}

      bool empurravel_::acao(param) {if(I.reativo()->tenta_mover(I.vetor())) I._return(ocupavel_::acao(I)); return I._return();}

      bool final_::acao(param) {if(I.ativo()->Entidade()==(pontuavel*)I.jogo()->jogador)

          {I.jogo()->tela[0]->setText(QString(mensagem())); I.jogo()->ativo = false;} return false;}

      bool monstro_::acao(param) {return final_::acao(I);}
      //bool monstro_::reacao(param) {new monstro_(I.reativo(), I.jogo()->lista_);}

      bool bonus_::acao(param) {if(pontuavel::acao(I)) I._return(ocupavel_::acao(I)); return I._return();}

      bool inativo_::acao(param) {if(pontuavel::acao(I)) {I.ativo()->atualiza(); new amigo_(I.reativo(),I.jogo()->lista_);} return false;}

          //criatura *atv = (criatura*) (pontuavel*) I.ativo()->Entidade(); atv->ativa(I.reativo(),I.jogo()->lista_);}

      bool amigo_::acao(param) {return empurravel_::acao(I);}
      //bool amigo_::reacao(param) {}

      bool jogador_::acao(param) {return false;}
      //bool jogador_::reacao(param) {}

      //bool criatura::acao(param) {return false;}

//*** lista

lista::lista() {entidades = new movel_*[45]; quantidade = 0;}

void lista::adiciona(movel_ *ent) {if(quantidade < 50) {entidades[quantidade] = ent; quantidade++;}}

lista::~lista() {delete entidades;}

// *** game

void game::movimento(int x, int y, bloco *inicio) {if (ativo) inicio->tenta_mover(QPoint(x,y)); mudanca();}

void game::mudanca() {

    int ctrl = 0;
    int qt, item;
    while (ctrl<3) {

        ctrl++;
        qt = lista_->quantidade;
        item = QRandomGenerator::global()->bounded(0,qt);
        int x = QRandomGenerator::global()->bounded(-1,2);
        int y = QRandomGenerator::global()->bounded(-1,2);

        if(x!=0 || y!=0) lista_->entidades[item]->Bloco()->tenta_mover(QPoint(x,y));
    }
}

game::game(int rows, int columns, QWidget *parent, QLabel *tela_[2]) : QTableWidget(rows, columns, parent)
{

obstaculo1 = new obstaculo_();
empurravel1 = new empurravel_();
final1 = new final_();
//movel1 = new movel_();

lista_ = new lista();
jogador = new jogador_();
ocupavel = new ocupavel_();

for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {

        int rand = QRandomGenerator::global()->bounded(0,30);

        if (i==0 || j==0 || i==rows-1 || j==columns-1) criaBloco(i,j, obstaculo1);

        else if (i==1 && j==1) criaBloco(i,j, (pontuavel*) jogador);

        else if (i<3 && j<3) criaBloco(i,j, ocupavel);

        else if (i==rows-2 && j==columns-2) criaBloco(i,j, final1);

        else if (i>rows-4 && j>columns-4) criaBloco(i,j, ocupavel);

        else if ((rand % 21) == 0) criaBloco(i,j, (pontuavel*) new bonus_(1,4));

        else if ((rand % 19) == 0) criaBloco(i,j, (pontuavel*) new monstro_(lista_));

        else if ((rand % 17) == 0) criaBloco(i,j, new inativo_(1,4));

        else if ((rand % 6) == 0) criaBloco(i,j, new movel_(lista_));

        else if ((rand % 5) == 0) criaBloco(i,j, obstaculo1);

        else if ((rand % 4) == 0) criaBloco(i,j, empurravel1);

        else criaBloco(i,j, ocupavel);
    }
}

ativo = true;

tela[0] = tela_[0];
tela[1] = tela_[1];

resizeRowsToContents();
resizeColumnsToContents();
this->setDisabled(1);
}

