#ifndef ____SCORE_H____
#define ____SCORE_H____

#include <DXGame/GameObject.h>
#include <DXGame/Component.h>
#include <DXGame/Number.h>


class ScoreControl : public Component {
public:
    using Component::Component;

    void Start(void) override;
    void Update(void) override;

private:
    DirectX::XMFLOAT3 m_firstPos;   // �v���C���[�̏����ʒu
    NumberShow* m_number;           // �ԍ��\���R���|�[�l���g�ێ�
};


class Score : public GameObject {
public:
    using GameObject::GameObject;

private:
    void Prefab(void) override;
};


#endif // !____SCORE_H____
