#ifndef ____COLLSION_H____
#define ____COLLSION_H____

#include <DXGame/ClassName.h>
#include <DXGame/SystemDefines.h>
#include <DXGame/Geometory.h>

    
// �����蔻�肪�Փ˂����ۂ̏����i�[����
struct CollsionHitData {
    Collsion* hitCollsion;  // �ՓˑΏۂ̓����蔻��
};


// CollsionHitData�̓��I�z��p
struct CollsionHitDataVector {
    //// �����擾����
    //// @ Arg1 : �S�t���[���ɏՓ˂������
    //std::vector<CollsionHitData> GetDate(const bool isProvFrameHit);


    std::vector<CollsionHitData> list;  // �Փˏ��
};


// �����蔻����s���N���X
// @ Memo : �l�p�`�̓����蔻����s���܂�
// @ Memo : ��]�͍l�����܂���
class Collsion {
public:
    // �R���X�g���N�^
    // @ Arg1 : �����Q�[���I�u�W�F�N�g
    // @ Arg2 : �����߂����s����
    // @ Arg3 : �g�k�i�f�t�H���g�F�S��1�j
    // @ Arg4 : ���΍��W�i�f�t�H���g�F�S��0�j
    Collsion(GameObject* gameObject, const bool isHitMove, const DirectX::XMFLOAT3& size = DirectX::XMFLOAT3(1, 1, 1), const DirectX::XMFLOAT3& pos = DirectX::XMFLOAT3(0, 0, 0));
    // �f�X�g���N�^
    ~Collsion(void);


    // �^�O�Q�b�^�[
    const Tag GetTag(void) const { return m_tag; }
    // �^�O�Z�b�^�[
    void SetTag(const Tag in) { m_tag = in; }


    // �A�N�e�B�u�Q�b�^�[
    const bool GetActive(void) const { return m_isActive; }
    // �A�N�e�B�u�Q�b�^�[
    void SetActive(const bool in) { m_isActive = in; }


    // ���΍��W�Q�b�^�[
    const DirectX::XMFLOAT3 GetPos(void) const { return m_pos; }
    // ���΍��W�Z�b�^�[
    void SetPos(const DirectX::XMFLOAT3& in) { m_size = in; }


    // �g�k�Q�b�^�[
    const DirectX::XMFLOAT3 GetSize(void) const { return m_size; }
    // �g�k�Z�b�^�[
    void SetSize(const DirectX::XMFLOAT3& in) { m_size = in; }


    // �����Q�[���I�u�W�F�N�g�Q�b�^�[
    GameObject* const GetGameObject(void) const { return m_gameObject; }


    // �^����ꂽ�����蔻��ƏՓ˔�����s��
    // @ Memo : �Փˏ��Ȃǂ́i�Փ˂��Ă���΁j�֐����Œ��ڒǉ����܂�
    // @ Ret  : ����ȏ�̔��肪�K�v��
    // @ Memo : �������蔻�������󋵂ł͂Ȃ��iacitve �� false ���j�A�������͂����Փ˂���ꂽ�ꍇ�� true �ł�
    // @ Arg1 : ���g�̍��W
    // @ Arg2 : �Ώۂ̓����蔻��
    const bool CollsionHitCheck(const DirectX::XMFLOAT3 thisTransform, Collsion* const collsion);


private:
    Tag         m_tag;          // ���g�ɐݒ肳�ꂽ�^�O
    bool        m_isActive;     // �L����
    bool        m_isHitMove;    // �����߂��͍s����
    GameObject* m_gameObject;   // �����Q�[���I�u�W�F�N�g
    DirectX::XMFLOAT3 m_pos;    // ���ΓI���W
    DirectX::XMFLOAT3 m_size;   // �g�k
};

#endif // !____COLLSION_H____
