#ifndef ____SCENE_H____
#define ____SCENE_H____

#include <DXGame/ClassName.h>
#include <DXGame/GameObject.h>
#include <DXGame/Transform.h>
#include <DXGame/GameObjectUpdater.h>


// �V�[�������ۂ̒��ۃN���X
class SceneBase {
public:
    // �R���X�g���N�^
    SceneBase(void);
    // �f�X�g���N�^
    ~SceneBase(void);


    // �Q�[���A�b�v�f�[�^�[�Q�b�^�[
    GameUpdater *const GetUpdater(void) const { return m_updater.get(); }


    // �V�[���𐶐�����
    virtual void InitScene(void) = 0;


    // �v���n�u�𐶐�����
    // @ Temp : ��������Q�[���I�u�W�F�N�g�̌^
    // @ Arg1 : ���W���
    template <typename TGameObject>
    TGameObject* CreatePrefab(const Transform& transform = Transform());

private:
    std::unique_ptr<GameUpdater> m_updater; // �Q�[���A�b�v�f�[�^�[
};


// �v���n�u�𐶐�����
// @ Temp : ��������Q�[���I�u�W�F�N�g�̌^
// @ Arg1 : ���W���
template <typename TGameObject>
TGameObject* SceneBase::CreatePrefab(const Transform& transform) {
    //----- �A�\�[�g
    // Memo : �Q�[���I�u�W�F�N�g���p�����Ă��Ȃ��i = �v���n�u�łȂ��j���A�Q�[���I�u�W�F�N�g�łȂ���΃A�\�[�g���܂�
    static_assert(std::disjunction_v<std::is_base_of<GameObject, TGameObject>, std::is_same<GameObject, TGameObject>>,
        "Template Error! Not a prefab or GameObject");

    //----- ����
    TGameObject* gameObject = new TGameObject(this, transform);

    //----- �o�^
    this->GetUpdater()->AddGameObject(gameObject);

    //----- �ԋp
    return gameObject;
}


#endif // !____SCENE_H____
