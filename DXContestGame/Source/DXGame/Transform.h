#ifndef ____TRANSFORM_H____
#define ____TRANSFORM_H____


struct Transform {
    // �R���X�g���N�^
    // @ Arg1 : ���W�i�f�t�H���g�F�S�� 0 �j
    // @ Arg2 : �g�k�i�f�t�H���g�F�S�� 1 �j
    // @ Arg3 : ��]�i�f�t�H���g�F�S�� 0 �j
    Transform(const DirectX::XMFLOAT3& pos = { 0.0f,0.0f,0.0f }, const DirectX::XMFLOAT3& size = { 1.0f,1.0f,1.0f }, const DirectX::XMFLOAT3& angle = { 0.0f,0.0f,0.0f });


    DirectX::XMFLOAT3 pos;      // ���W
    DirectX::XMFLOAT3 size;     // �g�k
    DirectX::XMFLOAT3 angle;    // ��]


    const Transform& operator=(const Transform& r);
};


#endif // !____TRANSFORM_H____
