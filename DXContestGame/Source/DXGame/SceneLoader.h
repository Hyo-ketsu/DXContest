#ifndef ____SCENELOADER_H____
#define ____SCENELOADER_H____

#include <DXGame/Singleton.h>
#include <DXGame/ClassName.h>
#include <DXGame/GameObjectUpdater.h>
#include <DXGame/Scene.h>


// �V�[�����Ǘ�����N���X
class SceneLoader : public Singleton<SceneLoader> {
public:
    // �f�X�g���N�^
    ~SceneLoader(void);


    // �V�[�����ړ�����
    // @ Temp : �ړ��������V�[��
    template <typename MoveScene>
    void MoveScene(void);


    // ���݃V�[�����擾����
    SceneBase* GetScene(void);


    // �Q�[���A�b�v�f�[�^�[������
    void InitGameUpdater(void);
    // �Q�[���A�b�v�f�[�^�[�I��
    void UninitGameUpdater(void);


    // �Q�[���A�b�v�f�[�^�[���擾����
    // @ Memo : �����������A��O�𓊂��܂�
    // @ Ret  : �Q�[���A�b�v�f�[�^�[�ւ̎Q��
    GameUpdater& GetGameUpdaterRef(void);

private:
    // �R���X�g���N�^
    SceneLoader(void);


    // �t�����h�錾
    friend class Singleton<SceneLoader>;


    std::unique_ptr<GameUpdater> m_gameUpdater;     // �Q�[���A�b�v�f�[�^�[
    std::unique_ptr<SceneBase>   m_currentScene;    // ���݂̃V�[��
};


// �V�[�����ړ�����
// @ Temp : �ړ��������V�[��
template <typename MoveScene>
void SceneLoader::MoveScene(void) {
    //----- �A�\�[�g
    static_assert(std::is_same_v<SceneBase, T>, "Template error! Not a class that inherits SceneBase!");    // �V�[������p������Ă��邩�̃A�\�[�g

    //----- �ړ�
    m_currentScene = std::make_unique<MoveScene>();
}


#endif // !____SCENELOADER_H____
