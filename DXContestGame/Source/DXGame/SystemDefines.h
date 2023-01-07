#ifndef ____SYSTEMDEFINES_H____
#define ____SYSTEMDEFINES_H____


const std::string DEFAULT_NAME_GAMEOBJECT = "GameObject";   // ゲームオブジェクトのdefault名
const unsigned int SCREEN_X = 1280; // ウィンドウサイズ横
const unsigned int SCREEN_Y = 720;  // ウィンドウサイズ縦


// タグ
enum class Tag {
    Player = 0,
    PlayerAttack,
    Enemy,
    EnemyAttack,
    Ground,
    Non,
};


#endif // !____SYSTEMDEFINES_H____
