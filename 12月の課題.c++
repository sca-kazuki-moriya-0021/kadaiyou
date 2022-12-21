#include <iostream>
#include <string>
using namespace std;

class Player {
public:
  //コンストラクタの定義
  Player(const string &name = " ");
  //ゲッター
  string GetName() const;
  //次にいるプレイヤーのポインタをえる
  Player *GetNext() const;
  //次にいるプレイヤーを設定するセッター
  void SetNext(Player *next);

private:
  //名前
  string m_Name;
  // 次のプレイヤー
  Player *m_pNext;
};

//コンストラクタ
Player::Player(const string &name)
    : m_Name(name),
      //ヌルポインタ
      //とりあえず返しておく
      m_pNext(0) {}

//ゲッター定義
string Player::GetName() const { return m_Name; }

//ゲッター定義
//次のプレイヤーの値を返す
Player *Player::GetNext() const { return m_pNext; }

//次のプレイヤーの値をセットする
void Player::SetNext(Player *next) { m_pNext = next; }

//プレイヤーを格納
//先頭プレイヤーだけ格納。次に入ってきたプレイヤーはプレイヤークラスに持たせる
class Lobby {
  //通常の関数からもアクセスできるようにする
  friend ostream &operator<<(ostream &os, const Lobby &aLobby);

public:
  //コンストラクタ・デストラクタ
  Lobby();
  ~Lobby();
  void AddPlayer();
  void RemovePlayer();
  void Clear();

private:
  //一番最初に入ってきたプレイヤーのアドレス
  Player *m_pHead;
};

//コンストラクタ

Lobby::Lobby()
    : //ヌルポインタ
      m_pHead(0) {}

//デストラクタ
Lobby::~Lobby() { Clear(); }

void Lobby::AddPlayer() {
  //新しいプレイヤノードを作成
  cout << "Please enter a name of the new player: ";
  string name;
  cin >> name;
  //プレイヤーのアドレスを確保している
  //プレイヤーのコンストラクタを呼ぶ。
  Player *pNewPlayer = new Player(name);

  //リストは空っぽの状態だと、新しいプレイヤがリストの最初の項目となる
  // if list is empty, make head of list this new player
  if (m_pHead == 0) {
    m_pHead = pNewPlayer;
  }
  //　ではなければリストの最終項目に追加する
  // otherwise find the end of the list and add the player there
  else {
    // m_pHeadのアドレスをいれる
    Player *pIter = m_pHead;
    //アドレスが入っており、ヌルポインタではないときに
    while (pIter->GetNext() != 0) {
      //参照したアドレスにアクセスする
      pIter = pIter->GetNext();
    }
    //次のプレイヤーを設定している
    pIter->SetNext(pNewPlayer);
  }
}

void Lobby::RemovePlayer() {
  if (m_pHead == 0) {
    //ゲームロビーには誰もいません。削除することができません。
    cout << "The game lobby is empty.	No one to remove!\n";
  } else {
    //先頭のプレイヤーのアドレスを入れて
    Player *pTemp = m_pHead;
    //先頭のプレイヤーと次のプレイヤーを入れ替える
    m_pHead = m_pHead->GetNext();
    //先頭のプレイヤーだったものを削除する
    delete pTemp;
  }
}

void Lobby::Clear() {
  while (m_pHead != 0) {
    RemovePlayer();
  }
}

ostream &operator<<(ostream &os, const Lobby &aLobby) {
  //ロビーにいる先頭のプレイヤーのアドレスをセット
  Player *pIter = aLobby.m_pHead;
  //現在のゲームロビーにいるプレイヤリスト：
  os << "\nHere's who's in the game lobby:\n";
  if (pIter == 0) {
    //ゲームロビーには誰もいません。
    os << "The lobby is empty.\n";
  } else {
    //アドレスが入っていた時
    while (pIter != 0) {
      //アクセスして出力
      os << pIter->GetName() << endl;
      //アクセスしアドレスをセット
      pIter = pIter->GetNext();
    }
  }

  //出力した文字列をかえす
  return os;
}

int main() {
  Lobby myLobby;
  int choice;

  do {
    cout << myLobby;
    //ゲームロビー
    cout << "\nGAME LOBBY\n";
    //プログラムを終了
    cout << "0 - Exit the program\n";
    //ゲームロビーにプレイヤを追加
    cout << "1 - Add a player to the lobby\n";
    //ゲームロビーからプレイヤを削除
    cout << "2 - Remove a player from the lobby\n";
    //ゲームロビーをクリアする
    cout << "3 - Clear the lobby\n";
    //選択を入力
    cout << endl << "Enter a choice: ";
    cin >> choice;

    switch (choice) {
    //さようなら
    case 0:
      cout << "Good-bye\n";
      break;
    case 1:
      myLobby.AddPlayer();
      break;
    case 2:
      myLobby.RemovePlayer();
      break;
    case 3:
      myLobby.Clear();
      break;
      //不正入力をしました
    default:
      cout << "That was not a valid choice\n";
    }
  } while (choice != 0);

  return 0;
}