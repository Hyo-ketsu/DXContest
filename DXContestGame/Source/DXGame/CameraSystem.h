#ifndef ____CAMERASYSTEM_H____
#define ____CAMERASYSTEM_H____

#include <DXGame/Singleton.h>
#include <DXGame/CameraBase.h>


// �J������ێ������s���N���X
class CameraSystem : public Singleton<CameraSystem> {
public:
    // �f�X�g���N�^
    ~CameraSystem(void) override {}


    // �J������o�^����
    // @ Arg1 : �ǉ�����J�����R���|�[�l���g
    void AddCamera(CameraBase* camera);
    // �J�����̓o�^���폜����
    // @ Arg1 : �폜����J�����R���|�[�l���g
    void DeleteCamera(CameraBase* camera);


    // �J�������擾����
    // @ Memo : ���C���J�����A���C�����ݒ肳��Ă��Ȃ���Γo�^���ꂽ�̂������J������ԋp����
    // @ Memo : �J������������݂��Ȃ���Η�O�𓊂��܂�
    // @ Ret  : ���݂̃J����
    CameraBase const* GetCamera(void) const;

private:
    // �R���X�g���N�^
    CameraSystem(void) {}

    // �t�����h�錾
    friend class Singleton<CameraSystem>;

    std::vector<CameraBase*> m_camera;  // �J��������ێ�����
};


#endif // !____CAMERASYSTEM_H____
