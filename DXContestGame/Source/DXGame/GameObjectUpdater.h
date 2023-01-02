#ifndef ____GAMEOBJECTUPDATER_H____
#define ____GAMEOBJECTUPDATER_H____

#include <DXGame/ClassName.h>
#include <DXGame/GameObject.h>


class GameUpdater {
public:
    // �R���X�g���N�^
    GameUpdater(void);
    // �f�X�g���N�^
    ~GameUpdater(void);


    // �X�V�������s��
    void Update(void);
    // �`�揈�����s��
    void Draw(void);


    // �Q�[���I�u�W�F�N�g��ǉ�����
    // @ Arg1 : �ǉ�����Q�[���I�u�W�F�N�g�̃|�C���^
    void AddGameObject(GameObject* gameObject);
    // �Q�[���I�u�W�F�N�g���폜����
    // @ Ret  : �폜�ɐ���������
    // @ Arg1 : �폜����Q�[���I�u�W�F�N�g�̃|�C���^
    const bool DeleteGameObject(GameObject* gameObject);


    // �Q�[���I�u�W�F�N�g�𖼑O��������
    // @ Memo : �P�̂Ō������܂��B���������̃I�u�W�F�N�g�����݂���ꍇ�͂ǂ��Ԃ����͕ۏ؂��܂���
    // @ Ret  : �������ʁi�Ȃ���� nullptr�j
    // @ Arg1 : ������
    GameObject* FindGameObject(const std::string& name) const;


private:
    std::vector<std::unique_ptr<GameObject>> m_gameObject;  // �ێ����Ă���Q�[���I�u�W�F�N�g
};


#endif // !____GAMEOBJECTUPDATER_H____
