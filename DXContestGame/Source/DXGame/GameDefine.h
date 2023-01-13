#ifndef ____GAMEDEFINE_H____
#define ____GAMEDEFINE_H____


const std::string NAME_PLAYER = "Player";   //プレイヤーのオブジェクトの名称
const std::string NAME_SCORE  = "Score";    //点数表示オブジェクトの名称


const std::string LOAD_OBSTACLES_FILENAME = "Obstacles.obj";
const float       LOAD_OBSTACLES_SCALE    = 0.2f;
const std::string LOAD_BLOCK_FILENAME     = "Block.obj";
const float       LOAD_BLOCK_SCALE        = 0.2f;
const std::string LOAD_PLAYER_FILENAME    = "Player.obj";
const float       LOAD_PLAYER_SCALE       = 0.3f;


const std::string LOAD_GAME_BUTTON_FILENAME   = "GamePlay.png";
const std::string LOAD_RESULT_BUTTON_FILENAME = "Result.png";
const std::string LOAD_TITLE_BUTTON_FILENAME  = "ReturnTitle.png";


const DirectX::XMFLOAT3 SIZE_BUTTON = DirectX::XMFLOAT3(0.5f, 0.25f, 1.0f);
const int KEY_BUTTON = VK_RETURN;  // ボタンキー


#endif // !____GAMEDEFINE_H____
