#ifndef ____GAMEOBJECT_H____
#define ____GAMEOBJECT_H____

#include <DXGame/ClassName.h>
#include <DXGame/Transform.h>
#include <DXGame/Component.h>
#include <DXGame/Collsion.h>


// �Q�[���I�u�W�F�N�g
class GameObject {
public:
    // �R���X�g���N�^
    // @ Arg1 : �����V�[��
    // @ Arg2 : ���W�i�f�t�H���g�F���W��]�� 0,�g�k�� 1�j
    GameObject(SceneBase* scene, const Transform& transform = Transform());
    // �f�X�g���N�^
    virtual ~GameObject(void);


    // �A�N�e�B�u�Q�b�^�[
    const bool GetActive(void) const { return m_isActive; }
    // �A�N�e�B�u�Z�b�^�[
    void SetActive(const bool in) { m_isActive = in; }


    // ���O�Q�b�^�[
    const std::string& GetName(void) const { return m_name; }
    // ���O�Z�b�^�[
    void SetName(const std::string& in) { m_name = in; }


    // ���W�Q�b�^�[
    const Transform& GetTransform(void) const { return m_transform; }
    // ���W�Z�b�^�[
    void SetTransform(const Transform in) { m_transform = in; }


    // �����W�Q�b�^�[
    const Transform& GetOldTransform(void) const { return m_oldTransform; }


    // �����蔻�胊�X�g�Q�b�^�[
    const CollsionHitDataVector& GetCollsionData(void) const { return m_collsionData; }
    // �����蔻�胊�X�g�Q�b�^�[
    CollsionHitDataVector* const GetCollsionDataPointer(void) { return &m_collsionData; }
    // �����蔻�胊�X�g�Z�b�^�[
    void SetCollsionData(const CollsionHitDataVector& in) { m_collsionData = in; }


    // �v���n�u�����ۃQ�b�^�[
    const bool GetCreatePrefab(void) const { return m_isCreatePrefab; }


    // �V�[���Q�b�^�[
    SceneBase* const GetScene(void) const { return m_scene; }


    // �R���|�[�l���g�̏������������s��
    // @ Memo : ���Q�[������(Update��)�ƈႢ�A�N�e�B�u�@���ɂ�炸�������������s���܂�
    void Start(void);
    // �R���|�[�l���g�̍X�V�������s��
    // @ Memo : �A�N�e�B�u�X�e�[�^�X�ɂ���ăQ�[���I�u�W�F�N�g�P�ʁE�R���|�[�l���g�P�ʂōs�������肳��܂�
    void Update(void);
    // �R���|�[�l���g�̌�X�V�������s��
    // @ Memo : �A�N�e�B�u�X�e�[�^�X�ɂ���ăQ�[���I�u�W�F�N�g�P�ʁE�R���|�[�l���g�P�ʂōs�������肳��܂�
    void LateUpdate(void);
    // �R���|�[�l���g�̕`�揈�����s��
    // @ Memo : �A�N�e�B�u�X�e�[�^�X�ɂ���ăQ�[���I�u�W�F�N�g�P�ʁE�R���|�[�l���g�P�ʂōs�������肳��܂�
    void Draw(void);
    // �R���|�[�l���g�̓����蔻�菈�����s��
    // @ Memo : �A�N�e�B�u�X�e�[�^�X�ɂ���ăQ�[���I�u�W�F�N�g�P�ʁE�R���|�[�l���g�P�ʂōs�������肳��܂�
    void CollsionUpdate(void);


    // �v���n�u�𐶐�����
    // @ Ret  : �����������i�������ł���� true,�����ς݂ł���� false�j
    const bool CreatePrefab(void);


    // �Q�[���I�u�W�F�N�g����
    void DeleteGameObject(void);


    // �R���|�[�l���g��ǉ�����
    // @ Ret  : �ǉ������R���|�[�l���g
    // @ Arg1 : �ǉ�����R���|�[�l���g
    Component* AddComponent(Component* component);
    // �R���|�[�l���g��ǉ�����
    // @ Ret  : �ǉ������R���|�[�l���g
    // @ Temp : �ǉ�����R���|�[�l���g�̌^
    template <typename TComponent>
    TComponent* AddComponent(void);
    // �����蔻���ǉ�����
    // @ Ret  : �ǉ����������蔻��
    // @ Arg1 : �����߂����s����
    // @ Arg2 : �g�k�i�f�t�H���g�F�S��1�j
    // @ Arg3 : ���΍��W�i�f�t�H���g�F�S��0�j
    Collsion* AddCollsion(const bool isHitMove, const DirectX::XMFLOAT3& size = DirectX::XMFLOAT3(1, 1, 1), const DirectX::XMFLOAT3& pos = DirectX::XMFLOAT3(0, 0, 0));


    // �R���|�[�l���g���擾����
    // @ Temp : �擾����R���|�[�l���g�̌^
    template <typename TComponent>
    TComponent* GetComponent(void);


    // �����蔻������
    // @ Arg1 : �����蔻������Ώۂ̃Q�[���I�u�W�F�N�g
    void UpdateCollsion(GameObject* const gameObject);
    // �����蔻�肪���݂��邩
    // @ Ret  : ���݂��邩
    const bool GetCollsionEnable(void) const;
    // �����蔻�胊�X�g�̏���
    void ResetCollsionData(void);

protected:
    // �v���n�u�𐶐�����
    virtual void Prefab(void) {}

private:
    bool m_isActive;            // ���ݗL���ɂȂ��Ă��邩
    bool m_isCreatePrefab;      // �v���n�u���������ꂽ��
    std::string m_name;         // ���O
    Transform   m_transform;    // ���W
    Transform   m_oldTransform; // �O�t���[�����W
    SceneBase*  m_scene;        // �����V�[��
    std::vector<std::unique_ptr<Component>> m_component;    // �ێ��R���|�[�l���g
    std::vector<std::unique_ptr<Collsion>>  m_collsion;     // �ێ������蔻��
    CollsionHitDataVector                   m_collsionData; // �����蔻����̕ێ�
};


// �R���|�[�l���g��ǉ�����
// @ Temp : �ǉ�����R���|�[�l���g�̌^
template <typename TComponent>
TComponent* GameObject::AddComponent(void) {
    //----- Template���R���|�[�l���g���p�����Ă��Ȃ�������A�\�[�g
    static_assert(std::is_base_of_v<Component, TComponent>, "Template error! Not a class that inherits Component!");

    //----- �ǉ�
    m_component.push_back(std::unique_ptr<TComponent>(new TComponent(this)));

    //----- �ԋp
    return dynamic_cast<TComponent*>(m_component.back().get());
}


// �R���|�[�l���g���擾����
// @ Temp : �擾����R���|�[�l���g�̌^
template <typename TComponent>
TComponent* GameObject::GetComponent(void) {
    //----- Template���R���|�[�l���g���p�����Ă��Ȃ�������A�\�[�g
    static_assert(std::is_base_of_v<Component, TComponent>, "Template error! Not a class that inherits Component!");

    //----- �擾
    for (auto& it : m_component) {
        //----- �_�E���L���X�g�ł��邩
        if (dynamic_cast<TComponent*>(it.get()) != nullptr) {
            //----- �\�B�w�肳�ꂽ�^�Ƃ��ĕԋp����
            return dynamic_cast<TComponent*>(it.get());
        }
    }

    //----- ���݂��Ȃ��Bnullptr��Ԃ�
    return nullptr;
}

#endif // !____GAMEOBJECT_H____
