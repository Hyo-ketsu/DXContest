#ifndef ____SCENE_H____
#define ____SCENE_H____

#include <DXGame/ClassName.h>


// �V�[�������ۂ̒��ۃN���X
class SceneBase {
public:
    // �R���X�g���N�^
    SceneBase(void);
    // �f�X�g���N�^
    ~SceneBase(void);


    // �V�[���𐶐�����
    virtual void InitScene(void) = 0;


    // �Q�[���A�b�v�f�[�^�[�Q�b�^�[
    GameUpdater *const GetUpdater(void) const { return m_updater.get(); }

private:
    std::unique_ptr<GameUpdater> m_updater; // �Q�[���A�b�v�f�[�^�[
};


#endif // !____SCENE_H____
