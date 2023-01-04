#ifndef ____TRANSFORM_H____
#define ____TRANSFORM_H____


struct Transform {
    // コンストラクタ
    // @ Arg1 : 座標（デフォルト：全て 0 ）
    // @ Arg2 : 拡縮（デフォルト：全て 1 ）
    // @ Arg3 : 回転（デフォルト：全て 0 ）
    Transform(const DirectX::XMFLOAT3& pos = { 0.0f,0.0f,0.0f }, const DirectX::XMFLOAT3& size = { 1.0f,1.0f,1.0f }, const DirectX::XMFLOAT3& angle = { 0.0f,0.0f,0.0f });


    DirectX::XMFLOAT3 pos;      // 座標
    DirectX::XMFLOAT3 size;     // 拡縮
    DirectX::XMFLOAT3 angle;    // 回転


    const Transform& operator=(const Transform& r);
};


#endif // !____TRANSFORM_H____
