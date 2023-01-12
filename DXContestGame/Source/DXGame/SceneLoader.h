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
    ~SceneLoader(void) override;


    // ���݃V�[�����擾����
    SceneBase* const GetScene(void) const;


    // �V�[�����ړ�����
    // @ Temp : �ړ��������V�[��
    template <typename MoveScene>
    void MoveScene(void);
    // �V�[�����폜����
    // @ Memo : �S�ẴV�[�����폜���܂�
    void DeleteScene(void);


    // �X�V�������s��
    void Update(void);
    // �`�揈�����s��
    void Draw(void);

private:
    // �R���X�g���N�^
    SceneLoader(void);


    // �t�����h�錾
    friend class Singleton<SceneLoader>;

    std::unique_ptr<SceneBase> m_scene;     // ���݂̃V�[��
    std::unique_ptr<SceneBase> m_newScene;  // �V�����V�[��
};


// �V�[�����ړ�����
// @ Temp : �ړ��������V�[��
template <typename MoveScene>
void SceneLoader::MoveScene(void) {
    //----- �A�\�[�g
    static_assert(std::is_base_of_v<SceneBase, MoveScene>, "Template error! Not a class that inherits SceneBase!");    // �V�[������p������Ă��邩�̃A�\�[�g

    //----- �ړ�
    m_newScene = std::make_unique<MoveScene>();
    m_newScene->InitScene();
}


#endif // !____SCENELOADER_H____
